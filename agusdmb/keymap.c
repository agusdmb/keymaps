/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include <stdio.h>

enum layers {
  L_QWERTY,
  L_SYMBOLS,
  L_NUMBERS,
  L_OTHER,
  L_NUMPAD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   // ---------------, ------------, ------------,  ------------,  --------------, --------------------, ------------, ------------, ------------, ------------, ------------, ------------,
	[L_QWERTY] = LAYOUT_split_3x6_3(
    LALT_T(KC_TAB), KC_Q,         KC_W,          KC_E,          KC_R,           KC_T,                 KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,         KC_BSPC,
    LCTL_T(KC_ESC), KC_A,         KC_S,          KC_D,          KC_F,           KC_G,                 KC_H,         KC_J,         KC_K,         KC_L,         KC_SCLN,      KC_QUOT,
    KC_LSFT,        KC_Z,         KC_X,          KC_C,          KC_V,           KC_B,                 KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,      KC_RSFT,
    KC_LGUI,        KC_SPC,       MO(L_SYMBOLS), MO(L_NUMBERS), LCTL_T(KC_ENT), KC_RALT
  ),
	[L_NUMBERS] = LAYOUT_split_3x6_3(
    KC_TRNS,        KC_1,         KC_2,          KC_3,          KC_4,           KC_5,                 KC_6,         KC_7,         KC_8,         KC_9,         KC_0,         KC_BSPC,
    KC_TRNS,        KC_NO,        KC_MPRV,       KC_MPLY,       KC_MNXT,        KC_NO,                KC_LEFT,      KC_DOWN,      KC_UP,        KC_RGHT,      KC_NO,        KC_RALT,
    KC_LSFT,        KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_HOME,      KC_PGDN,      KC_PGUP,      KC_END,       KC_NO,        KC_LALT,
    KC_TRNS,        KC_TRNS,      MO(L_OTHER),   KC_TRNS,       KC_NO,          KC_NO
  ),
	[L_SYMBOLS] = LAYOUT_split_3x6_3(
    KC_TRNS,        KC_EXLM,      KC_AT,         KC_HASH,       KC_DLR,         KC_PERC,              KC_CIRC,      KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      KC_DEL,
    KC_TRNS,        KC_NO,        KC_MUTE,       KC_VOLD,       KC_VOLU,        KC_PSCR,              KC_MINS,      KC_EQL,       KC_LBRC,      KC_RBRC,      KC_BSLS,      KC_GRV,
    KC_LSFT,        KC_NO,        KC_NO,         KC_BRID,       KC_BRIU,        KC_NO,                KC_UNDS,      KC_PLUS,      KC_LCBR,      KC_RCBR,      KC_PIPE,      KC_TILD,
    KC_NO,          KC_NO,        KC_TRNS,       MO(L_OTHER),   KC_TRNS,        KC_TRNS
  ),
	[L_OTHER] = LAYOUT_split_3x6_3(
    KC_F1,          KC_F2,        KC_F3,         KC_F4,         KC_F5,          KC_F6,                KC_F7,        KC_F8,        KC_F9,        KC_F10,       KC_F11,       KC_F12,
    RGB_TOG,        RGB_MOD,      RGB_HUI,       RGB_SAI,       RGB_VAI,        RGB_SPI,              KC_NO,        KC_KB_POWER,  KC_SLEP,      KC_NO,        KC_NO,        KC_NO,
    KC_NO,          RGB_RMOD,     RGB_HUD,       RGB_SAD,       RGB_VAD,        RGB_SPD,              TG(L_NUMPAD), KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
    KC_NO,          KC_NO,        KC_TRNS,       KC_TRNS,       KC_NO,          KC_NO
  ),
	[L_NUMPAD] = LAYOUT_split_3x6_3(
    KC_NO,          KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_PSLS,      KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_BSPC,
    TG(L_NUMPAD),   KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_PAST,      KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NUM,
    KC_NO,          KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_P0,        KC_P1,        KC_P2,        KC_P3,        KC_PDOT,      KC_NO,
    KC_NO,          KC_NO,        KC_NO,         KC_PEQL,       KC_NO,          KC_0
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case L_QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case L_SYMBOLS:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case L_NUMBERS:
            oled_write_ln_P(PSTR("Nums & Arrows"), false);
            break;
        case L_OTHER:
            oled_write_ln_P(PSTR("F keys"), false);
            break;
        case L_NUMPAD:
            oled_write_ln_P(PSTR("Num Pad"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
}


void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        // oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
