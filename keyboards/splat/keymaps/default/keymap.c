// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * F G C R L 
     * D H T N S -
     * B M W V Z
     * + /
     * ENTER SHIFT SPACE
     */
    [0] = LAYOUT(
        KC_F,   KC_G,   KC_C,   KC_R,   KC_L,
        KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,
        KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,
        KC_PLUS,KC_SLSH,
        KC_ENT, KC_LSFT, KC_SPC
    )
};