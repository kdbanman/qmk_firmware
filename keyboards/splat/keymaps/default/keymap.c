// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define BASL 0
#define SYML 1
#define NAVL 2
#define NUML 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *     ' , . P Y               F G C R L 
     * ESC A O E U I               D H T N S -
     *     ; Q J K X               B M W V Z
     *           NUM_LAYER none    none NAV_LAYER
     *         BKSPC LSHIFT none   ENTER SHIFT SPACE
     */
    [BASL] = LAYOUT(
                   KC_QUOT, KC_COMM, KC_DOT, KC_P,   KC_Y,        KC_F,   KC_G,   KC_C,   KC_R,   KC_L,
          KC_ESC,  KC_A,    KC_O,    KC_E,   KC_U,   KC_I,        KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,
                   KC_SCLN, KC_Q,    KC_J,   KC_K,   KC_X,         KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,
                                             KC_TRNS,  KC_NO,    KC_NO,  KC_TRNS,
                                KC_BSPC, KC_LSFT, KC_NO,          KC_ENT, KC_LSFT, KC_SPC
    )

    // /*
    //  *     1 2 3 4 5               6 7 8 9 0
    //  * TAB ! @ # $ %               ^ & * ( ) +
    //  *     ~ ` { } |               \ < > ? _
    //  *           BAS_LAYER none    none SYM_LAYER
    //  *         BKSPC LSHIFT none   ENTER SHIFT SPACE
    //  */
    // [SYML] = LAYOUT(
    //                KC_1,    KC_2,    KC_3,    KC_4,   KC_5,        KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    //       KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC,     KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_PLUS,
    //                                                               KC_TILD,KC_GRV, KC_LCBR,KC_RCBR,KC_PIPE,
    //                                          KC_TRNS,  KC_NO,    KC_NO,  KC_TRNS,
    //                             KC_BSPC, KC_LSFT, KC_NO,          KC_ENT, KC_LSFT, KC_SPC
    // ),

    // /*
    //  *    7 8 9 - =               0 ) ( _ +
    //     * TAB 4 5 6 / *               % $ # @ !
    //     *    1 2 3 . ,               < > ? ~ `
    //     *         TRANS none    none TRANS
    //     *       BKSPC LSHIFT none   ENTER SHIFT SPACE
    //     * 
    // */
    // [NUML] = LAYOUT(
    //                KC_7,    KC_8,    KC_9,    KC_MINS,KC_EQL,      KC_0,   KC_RPRN,KC_LPRN,KC_UNDS,KC_PLUS,
    //       KC_TAB,  KC_4,    KC_5,    KC_6,   KC_SLSH,KC_ASTR,     KC_PERC,KC_DLR, KC_HASH,KC_AT,  KC_EXLM,
    //                                                               KC_1,   KC_2,   KC_3,   KC_DOT, KC_COMM,
    //                                          KC_TRNS,  KC_NO,    KC_NO,  KC_TRNS,
    //                             KC_BSPC, KC_LSFT, KC_NO,          KC_ENT, KC_LSFT, KC_SPC
    // ),

    // /*
    //  *     UP                    PGUP
    //  * LEFT DOWN RIGHT         HOME END
    //  *     ESC                  PGDN
    //  *
    //  *        BAS_LAYER none    none SYM_LAYER
    //  *      BKSPC LSHIFT none   ENTER SHIFT SPACE
    //     */
    // [NAVL] = LAYOUT(
    //                KC_UP,   KC_NO,   KC_NO,   KC_NO,   KC_PGUP,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //       KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,       KC_HOME, KC_END,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //                                                               KC_ESC,  KC_NO,   KC_NO,   KC_PGDN, KC_NO,
    //                                          MO(BASL),  KC_NO,    KC_NO,  MO(SYML),
    //                             KC_BSPC, KC_LSFT, KC_NO,          KC_ENT,  KC_LSFT, KC_SPC
    // )
     
};