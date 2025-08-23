// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_G,   KC_R,   KC_A,   KC_Y
    )
};

enum combo_events { CMB_GR_HOLDSEQ, COMBO_LEN };
const uint16_t PROGMEM gr_combo[] = { KC_G, KC_R, COMBO_END };
combo_t key_combos[COMBO_LEN] = {
  [CMB_GR_HOLDSEQ] = COMBO_ACTION(gr_combo),
};

static deferred_token gr_token = INVALID_DEFERRED_TOKEN;

static uint32_t gr_fire_cb(uint32_t trigger_time, void *cb_arg) {
  SEND_STRING("h" SS_DELAY(50) "e" SS_DELAY(50) "l" SS_DELAY(50) "l" SS_DELAY(50) "o");
  return 0;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
    case CMB_GR_HOLDSEQ:
      if (pressed) {
        // schedule for 2000 ms from now
        gr_token = defer_exec(2000, gr_fire_cb, NULL);
      } else {
        // released early? cancel so nothing fires
        cancel_deferred_exec(gr_token);
        gr_token = INVALID_DEFERRED_TOKEN;
      }
      break;
  }
}