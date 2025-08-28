// keymap.c — Option 2
// Tap G/R/A/Y -> sends the letter
// Hold (>= SECRET_HOLD_MS) -> sends the secret string
// 2+ key combos still work on hold using the combo engine

#include QMK_KEYBOARD_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// ===================== Timing =====================
#define SECRET_HOLD_MS 1500

// ===================== Custom single keys =====================
enum custom_keycodes {
    S_I = SAFE_RANGE, S_S, S_L, S_A
};

// Base layer uses custom keys
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( S_I, S_S, S_L, S_A )
};

// ===================== Single-key hold strings =====================
static const char singlestr_I[] PROGMEM = "duck ";
static const char singlestr_S[] PROGMEM = "mouse ";
static const char singlestr_L[] PROGMEM = "sandwich ";
static const char singlestr_A[] PROGMEM = "pony ";

static const char * const single_secrets[] PROGMEM = {
    singlestr_I, singlestr_S, singlestr_L, singlestr_A
};

#define SINGLE_COUNT 4
static deferred_token single_tokens[SINGLE_COUNT];
static bool           single_fired[SINGLE_COUNT]; // set true once hold fires

static uint32_t single_cb(uint32_t t, void *arg) {
    uint8_t idx = (uint8_t)(uintptr_t)arg;
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

// Tap = base letter; Hold >= SECRET_HOLD_MS = secret string
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t  idx;
    uint16_t tapkc;

    switch (keycode) {
        case S_I: idx = 0; tapkc = KC_I; break;
        case S_S: idx = 1; tapkc = KC_S; break;
        case S_L: idx = 2; tapkc = KC_L; break;
        case S_A: idx = 3; tapkc = KC_A; break;
        default: return true; // not our key
    }

    if (record->event.pressed) {
        single_fired[idx]  = false;
        single_tokens[idx] = defer_exec(SECRET_HOLD_MS, single_cb, (void*)(uintptr_t)idx);
    } else {
        if (single_tokens[idx] != INVALID_DEFERRED_TOKEN) {
            // Released before hold threshold → cancel secret and send tap
            cancel_deferred_exec(single_tokens[idx]);
            single_tokens[idx] = INVALID_DEFERRED_TOKEN;
            tap_code16(tapkc);
        } else {
            // Held long enough → secret already sent; swallow base key
        }
    }
    return false; // we've handled the event
}

// ===================== Multi-key combos (2+ keys only) =====================
// NAME, STR, keys...   (no single-key combos here)
#define SECRET_LIST(X) \
  X(GR,   "leaps ",             S_I, S_S) \
  X(GA,   "flies ",             S_I, S_L) \
  X(GY,   "chomps ",             S_I, S_A) \
  X(RA,   "farts ",          S_S, S_L) \
  X(RY,   "bonks ",             S_S, S_A) \
  X(AY,   "falls ",           S_L, S_A) \
  X(GRA,  "its nose ",         S_I, S_S, S_L) \
  X(GRY,  "into a black hole  ",      S_I, S_S, S_A) \
  X(GAY,  "on a horse ",          S_I, S_L, S_A) \
  X(RAY,  "in a millisecond ",  S_S, S_L, S_A) \
  X(GRAY, "through a toilet ",       S_I, S_S, S_L, S_A)

enum combo_events {
#   define X(NAME, STR, ...) CMB_##NAME,
    SECRET_LIST(X)
#   undef X
    COMBO_SEN
};

#   define X(NAME, STR, ...) const uint16_t PROGMEM cmb_##NAME[] = { __VA_ARGS__, COMBO_END };
    SECRET_LIST(X)
#   undef X

combo_t key_combos[COMBO_SEN] = {
#   define X(NAME, STR, ...) [CMB_##NAME] = COMBO_ACTION(cmb_##NAME),
    SECRET_LIST(X)
#   undef X
};

#   define X(NAME, STR, ...) static const char str_##NAME[] PROGMEM = STR;
    SECRET_LIST(X)
#   undef X

static const char * const secrets[] PROGMEM = {
#   define X(NAME, STR, ...) str_##NAME,
    SECRET_LIST(X)
#   undef X
};

static deferred_token secret_tokens[COMBO_SEN];

static uint32_t secret_cb(uint32_t trigger_time, void *cb_arg) {
    uint16_t idx = (uint16_t)(uintptr_t)cb_arg;
    const char *p = (const char *)pgm_read_ptr(&secrets[idx]);
    send_string_with_delay_P(p, 20);
    secret_tokens[idx] = INVALID_DEFERRED_TOKEN;
    return 0;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (combo_index >= COMBO_SEN) return;

    if (pressed) {
        // A combo was recognized — prevent any pending single-key holds from firing.
        cancel_all_single_tokens();

        secret_tokens[combo_index] =
            defer_exec(SECRET_HOLD_MS, secret_cb, (void*)(uintptr_t)combo_index);
    } else {
        if (secret_tokens[combo_index] != INVALID_DEFERRED_TOKEN) {
            cancel_deferred_exec(secret_tokens[combo_index]);
            secret_tokens[combo_index] = INVALID_DEFERRED_TOKEN;
        }
    }
}
