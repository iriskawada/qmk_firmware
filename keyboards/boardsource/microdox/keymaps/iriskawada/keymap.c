/*
Copyright 2022 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
};

enum custom_keycodes {
    TMUX_RESTORE = SAFE_RANGE,
    CTRL_B,
    CTRL_C,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TMUX_RESTORE:
            if (record->event.pressed) {
                // Send Ctrl+B then Ctrl+R
                SEND_STRING(SS_LCTRL("b") SS_LCTRL("r"));
            }
            return false;
        case CTRL_B:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("b"));
            }
            return false;
        case CTRL_C:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("c"));
            }
            return false;
    }
    return true;
}

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_LSFT,
                      KC_LCMD, KC_BKSP, LOWER,        RAISE,   KC_SPC,  KC_SLSH
  ),

  [_LOWER] = LAYOUT_split_3x5_3(
    KC_ESC,  KC_1,   KC_2,    KC_3,   KC_5,         KC_6,    KC_7,    KC_8,    KC_F12,    KC_0,
    KC_TAB,  KC_4,   KC_5,    KC_6,   KC_RGHT,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_LCTL, KC_7,   KC_8,    KC_9,   XXXXXXX,      XXXXXXX, KC_GRV,  KC_PIPE, KC_BSLS, KC_TILD,
                     KC_0,    KC_DOT, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_RAISE] = LAYOUT_split_3x5_3(
    KC_EXLM,      KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_ASTR,
    KC_ESC,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
    TMUX_RESTORE, KC_TILD, CTRL_C,  XXXXXXX, CTRL_B,       KC_UND,  KC_PPLS, KC_LCBR, KC_RCBR,  KC_DQT,
                      XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX, KC_DEL
  )
};
