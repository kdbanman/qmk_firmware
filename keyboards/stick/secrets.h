// secrets.h — shared module (header-only)
// Each keymap defines:
//   - SECRET_LAYOUT             -> LAYOUT(...) with S_* keys
//   - SINGLE_LIST(X)            -> X(NAME, "string ", KC_<tap>)
//   - (optional) COMBO_LIST(X)  -> X(NAME, "string ", S_<...>, S_<...>[, ...])
//
// Requires: COMBO_ENABLE, DEFERRED_EXEC_ENABLE, SEND_STRING_ENABLE

#pragma once
#include QMK_KEYBOARD_H
#include <stdbool.h>

#ifndef SECRET_HOLD_MS
#    define SECRET_HOLD_MS 1500
#endif
#ifndef SINGLE_LIST
#    error "Define SINGLE_LIST(X) before including secrets.h"
#endif
#ifndef SECRET_LAYOUT
#    error "Define SECRET_LAYOUT before including secrets.h"
#endif
#ifndef COMBO_LIST
#    define COMBO_LIST(X)
#endif

// ---------- Single-key indices & custom keycodes ----------
enum single_index {
#    define X(NAME, STR, TAPKC) IDX_##NAME,
    SINGLE_LIST(X)
#    undef X
    SINGLE_COUNT
};

enum custom_keycodes {
    S_BASE = SAFE_RANGE,
#    define X(NAME, STR, TAPKC) S_##NAME,
    SINGLE_LIST(X)
#    undef X
};

// PROGMEM strings and tap keycodes for singles
#    define X(NAME, STR, TAPKC) static const char singlestr_##NAME[] PROGMEM = STR;
SINGLE_LIST(X)
#    undef X

static const char * const single_secrets[] PROGMEM = {
#    define X(NAME, STR, TAPKC) singlestr_##NAME,
    SINGLE_LIST(X)
#    undef X
};

static const uint16_t single_tapkcs[] PROGMEM = {
#    define X(NAME, STR, TAPKC) TAPKC,
    SINGLE_LIST(X)
#    undef X
};

static deferred_token single_tokens[SINGLE_COUNT];
static bool           single_fired[SINGLE_COUNT];

// Track how many S_* keys are currently held
static uint8_t s_down_count = 0;

static uint32_t single_cb(uint32_t t, void *arg) {
    uint8_t idx = (uint8_t)(uintptr_t)arg;

    // If 2+ S_* keys are held, this is part of a chord — suppress single output.
    if (s_down_count >= 2) {
        single_tokens[idx] = INVALID_DEFERRED_TOKEN;
        single_fired[idx]  = false;
        return 0;
    }

    const char *p = (const char *)pgm_read_ptr(&single_secrets[idx]);
    send_string_with_delay_P(p, 20);
    single_tokens[idx] = INVALID_DEFERRED_TOKEN;
    single_fired[idx]  = true;
    return 0;
}

static inline void cancel_all_single_tokens(void) {
    for (uint8_t i = 0; i < SINGLE_COUNT; i++) {
        if (single_tokens[i] != INVALID_DEFERRED_TOKEN) {
            cancel_deferred_exec(single_tokens[i]);
            single_tokens[i] = INVALID_DEFERRED_TOKEN;
        }
    }
}

// ---------- Keymap (layer 0) ----------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = SECRET_LAYOUT
};

// ---------- process_record_user (tap = letter, hold = secret) ----------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    int8_t  idx   = -1;

    switch (keycode) {
#    define X(NAME, STR, TAPKC) case S_##NAME: idx = IDX_##NAME; break;
        SINGLE_LIST(X)
#    undef X
        default: return true; // not our key
    }

    if (record->event.pressed) {
        // count how many S_* keys are down; cancel singles once a chord starts
        s_down_count++;
        if (s_down_count >= 2) {
            cancel_all_single_tokens();
        }

        single_fired[idx]  = false;
        single_tokens[idx] = defer_exec(SECRET_HOLD_MS, single_cb, (void*)(uintptr_t)idx);
    } else {
        if (s_down_count) s_down_count--;

        if (single_tokens[idx] != INVALID_DEFERRED_TOKEN) {
            // Released before hold threshold → treat as tap
            cancel_deferred_exec(single_tokens[idx]);
            single_tokens[idx] = INVALID_DEFERRED_TOKEN;
            tap_code16((uint16_t)pgm_read_word(&single_tapkcs[idx]));
        } else {
            // Held long enough (or suppressed by chord) → no base tap
        }
    }
    return true;  // let QMK features (combos) keep processing this event
}

// ---------- Combos (2+ keys) ----------
enum combo_events {
#    define X(NAME, STR, ...) CMB_##NAME,
    COMBO_LIST(X)
#    undef X
    COMBO_LEN
};

#if COMBO_LEN > 0
#    define X(NAME, STR, ...) const uint16_t PROGMEM cmb_##NAME[] = { __VA_ARGS__, COMBO_END };
COMBO_LIST(X)
#    undef X

combo_t key_combos[COMBO_LEN] = {
#    define X(NAME, STR, ...) [CMB_##NAME] = COMBO_ACTION(cmb_##NAME),
    COMBO_LIST(X)
#    undef X
};

#    define X(NAME, STR, ...) static const char combostr_##NAME[] PROGMEM = STR;
COMBO_LIST(X)
#    undef X

static const char * const combo_secrets[] PROGMEM = {
#    define X(NAME, STR, ...) combostr_##NAME,
    COMBO_LIST(X)
#    undef X
};

static deferred_token combo_tokens[COMBO_LEN];

static uint32_t combo_cb(uint32_t t, void *arg) {
    uint16_t idx = (uint16_t)(uintptr_t)arg;
    const char *p = (const char *)pgm_read_ptr(&combo_secrets[idx]);
    send_string_with_delay_P(p, 20);
    combo_tokens[idx] = INVALID_DEFERRED_TOKEN;
    return 0;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (combo_index >= COMBO_LEN) return;
    if (pressed) {
        // a combo was recognized; ensure no single timers are pending
        cancel_all_single_tokens();
        combo_tokens[combo_index] =
            defer_exec(SECRET_HOLD_MS, combo_cb, (void*)(uintptr_t)combo_index);
    } else {
        if (combo_tokens[combo_index] != INVALID_DEFERRED_TOKEN) {
            cancel_deferred_exec(combo_tokens[combo_index]);
            combo_tokens[combo_index] = INVALID_DEFERRED_TOKEN;
        }
    }
}
#else
// No combos in this keymap: placeholder so keymap_introspection links.
combo_t key_combos[1];
__attribute__((weak)) void process_combo_event(uint16_t combo_index, bool pressed) {
    (void)combo_index; (void)pressed;
}
#endif // COMBO_LEN > 0
