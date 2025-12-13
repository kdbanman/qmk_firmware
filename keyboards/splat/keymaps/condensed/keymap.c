// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define BASL 0
#define SYML 1
#define NAVL 2
#define NUML 3

#define TD_8_ASTR 0
#define TD_3_COMM 1
#define TD_ENT 2


// Left hand
#define HM_EXLM LSFT_T(KC_EXLM)

#define HM_O LCTL_T(KC_O)
#define HM_AT RCTL_T(KC_AT)

#define HM_E LALT_T(KC_E)
#define HM_LPRN RALT_T(KC_LPRN)

#define HM_U LGUI_T(KC_U)
#define HM_RPRN RGUI_T(KC_RPRN)

#define HM_P LCAG_T(KC_P)
#define HM_DOT HYPR_T(KC_DOT)

#define HM_BSPC LT(NUML, KC_BSPC)


// Right hand
#define HM_H LGUI_T(KC_H)
#define HM_LBRC RGUI_T(KC_LBRC)

#define HM_T LALT_T(KC_T)
#define HM_RBRC RALT_T(KC_RBRC)

#define HM_N RCTL_T(KC_N)
#define HM_LCBR RCTL_T(KC_LCBR)

#define HM_G LCAG_T(KC_G)
#define HM_C HYPR_T(KC_C)

#define HM_SPC LT(NAVL, KC_SPC)

// Hyper keys
#define KC_HYP LCTL(LALT(KC_RGUI))
#define KC_SHYP LSFT(LCTL(LALT(KC_RGUI)))



tap_dance_action_t tap_dance_actions[] = {
    [TD_8_ASTR] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_ASTR),
    [TD_3_COMM]  = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_COMM),
    [TD_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_NO, KC_ENT),

};

// Handedness map for Chordal Hold.
// Use your keyboard's LAYOUT(...) and mark each key: 'L' (left), 'R' (right), '*' (exempt).
const char PROGMEM chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] =
    LAYOUT(
            'L','L','L','L','L',   'R','R','R','R','R',
        'L','L','L','L','L','L',   'R','R','R','R','R','R',
            'L','L','L','L','L',   'R','R','R','R','R',
                        '*','*',   '*','*',
                    '*','*','*',   '*','*','*'
    );



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASL] = LAYOUT(
                KC_QUOT , KC_COMM , HM_DOT  , HM_P    , KC_Y    ,         KC_F    , HM_G    , HM_C    , KC_R    , KC_L    , \
      KC_ESC  , KC_A    , HM_O    , HM_E    , HM_U    , KC_I    ,         KC_D    , HM_H    , HM_T    , HM_N    , KC_S    , KC_MINS , \
                KC_SCLN , KC_Q    , KC_J    , KC_K    , KC_X    ,         KC_B    , KC_M    , KC_W    , KC_V    , KC_Z    , \
                                              KC_LSFT , XXXXXXX ,         XXXXXXX , MO(SYML), \
                                    HM_BSPC , XXXXXXX , XXXXXXX ,         XXXXXXX , XXXXXXX , HM_SPC \
    ),

    //
    //   ? ^ [ ] &
    // | ! @ ( ) ~     CMD OPT CTRL SHIFT
    //   \ # { } `
    //
    [SYML] = LAYOUT(
                KC_DQUO , KC_LABK , KC_RABK , KC_DLR  , KC_PERC ,         KC_CIRC , KC_AMPR , KC_ASTR , KC_PIPE , KC_QUES , \
      _______ , KC_EXLM , HM_AT   , HM_LPRN , HM_RPRN , KC_PLUS ,         KC_EQL  , HM_LBRC , HM_RBRC , HM_LCBR , KC_RCBR , KC_UNDS , \
                KC_COLN , XXXXXXX , KC_HASH , KC_SLSH , KC_GRV  ,         KC_TILD , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX  , \
                                              _______ , _______ ,         _______ , _______ , \
                                    KC_TAB  , _______ , _______ ,         _______ , _______ , _______ \
    ),

    // HOLD BACKSPACE
    // - have shift on left pinky
    // - need backspace, but holding, so move to right thumb
    // - most common num symbols on left hand

    //       TODO: actually make this map, with HRM on left hand and right hand
    //       - HM_DOT is correct?
    //       - HM_MINS, HM_PLUS
    //       - HM_4, HM_5, HM_6, HM_0

    //
    // T for TRANS
    //   for NONE
    //
    //     $ : =            7 8 9
    //     . - +            4 5 6 0
    //     % / *            1 2 3
    [NUML] = LAYOUT(
                XXXXXXX , KC_DLR  , KC_COLN , KC_EQL  , XXXXXXX ,         XXXXXXX , KC_7    , KC_8    , KC_9    , XXXXXXX , \
      _______ , KC_LSFT , HM_DOT  , HM_MINS , HM_PLUS , XXXXXXX ,         XXXXXXX , HM_4    , HM_5    , HM_6    , HM_0    , XXXXXXX , \
                XXXXXXX , KC_PERC , KC_HASH , KC_SLSH , XXXXXXX ,         XXXXXXX , KC_1    , KC_2    , KC_3    , KC_DOT  , \
                                              _______ , _______ ,         _______ , KC_BSPC , \
                                    _______ , _______ , _______ ,         _______ , _______ , KC_ENT \
    ),

    // HOLD SPACE
    // - have shift on right pinky
    // - backspace becomes tab
    // - no need for backspace on nav layer
    // - alternative space could be useful, so replace shift
    [NAVL] = LAYOUT(
                XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX ,         XXXXXXX , KC_HYP  , KC_SHYP , XXXXXXX , XXXXXXX , \
      XXXXXXX , XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX ,         XXXXXXX , KC_RGUI , KC_RALT , KC_RCTL , KC_RSFT , XXXXXXX , \
                XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , \
                                              KC_SPC  , _______ ,         _______ , _______ , \
                                    KC_TAB  , _______ , QK_BOOT ,         _______ , _______ , _______ \
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Custom homerow mod keys that need to send shifted keycodes when tapped.
  // (Standard mod-tap functionality doesn't support the shifted keycodes - the
  // HM_* cases work around that limitation.)
  switch (keycode) {
    // Right Alt when held, '@' when tapped
    case HM_AT:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_AT);
        return false;
      }
      break;

    // Right Ctrl when held, '(' when tapped
    case HM_LPRN:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_LPRN);
        return false;
      }
      break;

    // Right GUI when held, ')' when tapped
    case HM_RPRN:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_RPRN);
        return false;
      }
      break;

    // Right Alt when held, '{' when tapped
    case HM_LCBR:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_LCBR);
        return false;
      }
      break;
  }
  return true;
}
