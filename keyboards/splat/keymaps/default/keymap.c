// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define BASL 0
#define SYML 1
#define NAVL 2
#define NUML 3

// Tap dance
// Use this in a layout as TD(TD_EXAMPLE)
# define TD_EXAMPLE 0
tap_dance_action_t tap_dance_actions[] = {
    [TD_EXAMPLE] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_ASTR),
};


// Hyper and Shift Hyper keys
#define KC_HYP LCTL(LALT(KC_RGUI))
#define KC_SHYP LSFT(LCTL(LALT(KC_RGUI)))


// Left hand, base layer
#define HM_O LCTL_T(KC_O)           // O -> Ctrl
#define HM_E LALT_T(KC_E)           // E -> Alt
#define HM_U LGUI_T(KC_U)           // U -> Gui
#define HM_P LCAG_T(KC_P)           // P -> Hyper
#define HM_DOT HYPR_T(KC_DOT)       // . -> Shift Hyper

// Left hand, symbol layer
#define HM_EXLM LSFT_T(KC_EXLM)     // ! -> Shift
#define HM_AT LCTL_T(KC_AT)         // @ -> Ctrl
#define HM_LPRN LALT_T(KC_LPRN)     // ( -> Alt
#define HM_RPRN LGUI_T(KC_RPRN)     // ) -> Gui

// Left hand, num layer
#define HM_MINS LCTL_T(KC_MINS)     // - -> Ctrl
#define HM_PLUS LALT_T(KC_PLUS)     // + -> Alt
#define HM_CDOT LGUI_T(KC_DOT)      // . -> Gui

// Left thumb, backspace, hold for num layer
#define HM_BSPC LT(NUML, KC_BSPC)


// Right hand, base layer
#define HM_H RGUI_T(KC_H)           // H -> Gui
#define HM_T RALT_T(KC_T)           // T -> Alt
#define HM_N RCTL_T(KC_N)           // N -> Ctrl
#define HM_G RCAG_T(KC_G)           // G -> Hyper
#define HM_C HYPR_T(KC_C)           // C -> Shift Hyper

// Right hand, symbol layer
#define HM_LBRC RGUI_T(KC_LBRC)     // [ -> Gui
#define HM_RBRC RALT_T(KC_RBRC)     // ] -> Alt
#define HM_LCBR RCTL_T(KC_LCBR)     // { -> Ctrl
#define HM_RCBR RSFT_T(KC_RCBR)     // } -> Shift

// Right hand, num layer
#define HM_4 RGUI_T(KC_4)           // 4 -> Gui
#define HM_5 RALT_T(KC_5)           // 5 -> Alt
#define HM_6 RCTL_T(KC_6)           // 6 -> Ctrl
#define HM_0 RSFT_T(KC_0)           // 0 -> Shift

// Right thumb, space, hold for nav layer
#define HM_SPC LT(NAVL, KC_SPC)


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
    // B for backslash
    //
    //   " < > $ %          ^ & * | ?
    //   ! @ ( ) +          = [ ] { }
    //   :   # / `          ~ B
    //
    [SYML] = LAYOUT(
                KC_DQUO , KC_LABK , KC_RABK , KC_DLR  , KC_PERC ,         KC_CIRC , KC_AMPR , KC_ASTR , KC_PIPE , KC_QUES , \
      KC_BSPC , KC_EXLM , HM_AT   , HM_LPRN , HM_RPRN , KC_PLUS ,         KC_EQL  , HM_LBRC , HM_RBRC , HM_LCBR , HM_RCBR , KC_SPC  , \
                KC_COLN , XXXXXXX , KC_HASH , KC_SLSH , KC_GRV  ,         KC_TILD , KC_BSLS , XXXXXXX , XXXXXXX , XXXXXXX  , \
                                              _______ , _______ ,         _______ , _______ , \
                                    _______  , _______ , _______ ,         _______ , _______ , _______ \
    ),

    // HOLD BACKSPACE
    // - have shift on left pinky
    // - need backspace, but holding, so move to right thumb
    // - most common num symbols on left hand
    // - HRM on left hand and right hand
    //
    //     : = $            7 8 9
    //     - + .            4 5 6 0
    //     / * %            1 2 3
    //
    [NUML] = LAYOUT(
                XXXXXXX , KC_COLN , KC_EQL  , KC_DLR  , XXXXXXX ,         XXXXXXX , KC_7    , KC_8    , KC_9    , XXXXXXX , \
      KC_BSPC , KC_LSFT , HM_MINS , HM_PLUS , HM_CDOT , XXXXXXX ,         XXXXXXX , HM_4    , HM_5    , HM_6    , HM_0    , KC_SPC  , \
                XXXXXXX , KC_SLSH , KC_ASTR , KC_PERC , XXXXXXX ,         XXXXXXX , KC_1    , KC_2    , KC_3    , KC_DOT  , \
                                              _______ , _______ ,         _______ , _______ , \
                                    _______ , _______ , _______ ,         _______ , _______ , KC_ENT \
    ),

    // HOLD SPACE
    // - have shift on right pinky
    // - backspace becomes tab
    // - no need for backspace on nav layer
    // - alternative space could be useful, so replace shift
    [NAVL] = LAYOUT(
                XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX ,         XXXXXXX , KC_HYP  , KC_SHYP , XXXXXXX , XXXXXXX , \
      KC_BSPC , XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX ,         XXXXXXX , KC_RGUI , KC_RALT , KC_RCTL , KC_RSFT , KC_SPC  , \
                XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , \
                                              _______ , _______ ,         _______ , _______ , \
                                    KC_TAB  , _______ , QK_BOOT ,         _______ , _______ , _______ \
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Custom homerow mod keys that need to send shifted keycodes when tapped.
  // (Standard mod-tap functionality doesn't support the shifted keycodes - the
  // HM_* cases work around that limitation.)

  // Without this, the following keys would send unshifted keycodes when tapped.
  // e.g. '9' instead of '('

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

    // Right Shift when held, '}' when tapped
    case HM_RCBR:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_RCBR);
        return false;
      }
      break;

    // Right GUI when held, '+' when tapped
    case HM_PLUS:
      if (record->tap.count && record->event.pressed) {
        tap_code16(KC_PLUS);
        return false;
      }
      break;
  }
  return true;
}
