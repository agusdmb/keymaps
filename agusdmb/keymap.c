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
  // L_NUMPAD,
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
    RGB_TOG,        RGB_MOD,      RGB_HUI,       RGB_SAI,       RGB_VAI,        KC_NO,                KC_NO,        KC_KB_POWER,  KC_SLEP,      KC_NO,        KC_NO,        KC_NO,
    // KC_NO,          RGB_RMOD,     RGB_HUD,       RGB_SAD,       RGB_VAD,        KC_NO,                TG(L_NUMPAD), KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
    KC_NO,          RGB_RMOD,     RGB_HUD,       RGB_SAD,       RGB_VAD,        KC_NO,                KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,
    KC_NO,          KC_NO,        KC_TRNS,       KC_TRNS,       KC_NO,          KC_NO
  ),
	// [L_NUMPAD] = LAYOUT_split_3x6_3(
 //    KC_NO,          KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_PSLS,      KC_P7,        KC_P8,        KC_P9,        KC_PMNS,      KC_BSPC,
 //    TG(L_NUMPAD),   KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_PAST,      KC_P4,        KC_P5,        KC_P6,        KC_PPLS,      KC_NO,
 //    KC_NO,          KC_NO,        KC_NO,         KC_NO,         KC_NO,          KC_NO,                KC_P0,        KC_P1,        KC_P2,        KC_P3,        KC_PDOT,      KC_NO,
 //    KC_NO,          KC_NO,        KC_NO,         KC_PEQL,       KC_NO,          KC_0
 //  ),
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
        // case L_NUMPAD:
        //     oled_write_ln_P(PSTR("Num Pad"), false);
        //     break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
}


void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
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
