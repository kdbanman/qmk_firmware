// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stddef.h>
#include <stdint.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_G, KC_R, KC_A, KC_Y
    )
};

#define SECRET_HOLD_MS 1500

// NAME, STR, keys...
#define SECRET_LIST(X) \
  X(G,    "goose ",    KC_G) \
  X(R,    "hamster ",    KC_R) \
  X(A,    "chicken ",    KC_A) \
  X(Y,    "pencil ",    KC_Y) \
  X(GR,   "flops ",   KC_G, KC_R) \
  X(GA,   "jumps ",   KC_G, KC_A) \
  X(GY,   "toots ",   KC_G, KC_Y) \
  X(RA,   "explodes ",   KC_R, KC_A) \
  X(RY,   "grows ",   KC_R, KC_Y) \
  X(AY,   "hammers ",   KC_A, KC_Y) \
  X(GRA,  "its wings ",  KC_G, KC_R, KC_A) \
  X(GRY,  "into a cloud ",  KC_G, KC_R, KC_Y) \
  X(GAY,  "on a bus ",  KC_G, KC_A, KC_Y) \
  X(RAY,  "through a window ",  KC_R, KC_A, KC_Y) \
  X(GRAY, "a toilet ", KC_G, KC_R, KC_A, KC_Y)

enum combo_events {
#   define X(NAME, STR, ...) CMB_##NAME,
    SECRET_LIST(X)
#   undef X
    COMBO_LEN
};

#   define X(NAME, STR, ...) const uint16_t PROGMEM cmb_##NAME[] = { __VA_ARGS__, COMBO_END };
    SECRET_LIST(X)
#   undef X

combo_t key_combos[COMBO_LEN] = {
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

static deferred_token secret_tokens[COMBO_LEN];

static uint32_t secret_cb(uint32_t trigger_time, void *cb_arg) {
    uint16_t idx = (uint16_t)(uintptr_t)cb_arg;
    const char *p = (const char *)pgm_read_ptr(&secrets[idx]);
    send_string_with_delay_P(p, 20);
    secret_tokens[idx] = INVALID_DEFERRED_TOKEN;
    return 0;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (combo_index >= COMBO_LEN) return;

    if (pressed) {
        secret_tokens[combo_index] =
            defer_exec(SECRET_HOLD_MS, secret_cb, (void*)(uintptr_t)combo_index);
    } else {
        cancel_deferred_exec(secret_tokens[combo_index]);
        secret_tokens[combo_index] = INVALID_DEFERRED_TOKEN;
    }
}
