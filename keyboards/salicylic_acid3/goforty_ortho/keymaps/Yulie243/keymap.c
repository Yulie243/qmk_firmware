/*
Copyright 2025 Salicylic_Acid

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

#include "naginata.h"
NGKEYS naginata_keys;
#include "custom_cursor_h.h"
#include QMK_KEYBOARD_H

// Alt_Tabキー用
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.


enum keymap_layers {
  _QWERTY,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _2,
  _3,
  _4,
  _5,
  _6,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, QK_GESC,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, LM(_2, MOD_LCTL | MOD_LALT),    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_NUHS,    KC_N,    KC_M, KC_COMM,  KC_DOT,   KC_SLSH, LT(_4, KC_LBRC),
        LGUI(LSFT(KC_H)), KC_LGUI, KC_LALT,  MO(_3),LSFT_T(KC_SPC),LT(_2, KC_ENT),LT(_6, KC_BSPC),LSFT_T(KC_SPC), KC_LEFT, KC_DOWN,KC_UP, KC_RGHT
    ),
    [_NAGINATA] = LAYOUT(
        _______, NG_Q,   NG_W,     NG_E,    NG_R,    NG_T, _______,     NG_Y,   NG_U,    NG_I,    NG_O,    NG_P, _______, 
        _______, NG_A,   NG_S,     NG_D,    NG_F,    NG_G, KC_QUOT,     NG_H,   NG_J,    NG_K,    NG_L, NG_SCLN, _______,
        _______, NG_Z,   NG_X,     NG_C,    NG_V,    NG_B, _______,     NG_N,   NG_M,  NG_COMM,  NG_DOT,NG_SLSH, LT(_4, KC_LBRC),
        _______, _______, _______, _______, NG_SHFT,   _______,      KC_INT4, NG_SHFT, _______, _______, _______, _______
    ),
    [_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,     KC_P9, KC_PSLS, UC(0x00F7), 
        _______, _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,     KC_P6, KC_PAST, UC(0x00D7),
        _______, _______, _______, _______, _______, _______, _______,   KC_P0, KC_P1,   KC_P2,     KC_P3, KC_PMNS, _______,
        _______, _______, _______, _______,   _______,   KC_TRNS, _______,   _______,  KC_PDOT,   KC_PEQL, KC_PPLS, _______
    ),
    [_3] = LAYOUT(
        _______, _______, _______, _______, _______, KC_LEFT, _______, KC_RGHT, _______,   KC_UP, _______, KC_PSCR, KC_DEL, 
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, ALT_TAB, MS_BTN1,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,  KC_END,   MS_UP, MS_BTN2,
        _______, _______, _______, KC_TRNS,   _______,   _______, _______,   KC_MENU,    KC_PGDN, MS_LEFT, MS_DOWN, MS_RGHT
    ),
    [_4] = LAYOUT(
        _______, _______, KC_F7,   KC_F8,   KC_F9,  KC_F12, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, KC_F4,   KC_F5,   KC_F6,  KC_F11, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, KC_F1,   KC_F2,   KC_F3,  KC_F10, _______, _______, _______, _______, _______, _______, KC_TRNS,
        _______, _______, _______, _______,   _______,   _______, _______,   _______,    _______, _______, _______, _______
    ),
    [_5] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TRNS, _______, _______, _______,   _______,   _______, _______,   _______,    _______, _______, _______, _______
    ),
    [_6] = LAYOUT(
        _______, S(KC_1), KC_SCLN, S(KC_INT3), KC_MINS, UC(0x00B7), QK_GESC, S(KC_SLSH), S(KC_5), S(KC_4), KC_INT3, S(KC_EQL), _______,
        _______, KC_SLSH, KC_QUOT,    S(KC_6), KC_LBRC,    S(KC_3), S(KC_2), S(KC_RBRC), S(KC_8), KC_RBRC, S(KC_COMM), S(KC_LBRC), _______,
        _______, S(KC_QUOT), S(KC_SCLN), KC_EQL, S(KC_INT1), S(KC_MINS), S(KC_7), S(KC_NUHS), S(KC_9), KC_NUHS,  S(KC_DOT), KC_COMM, KC_DOT,
        _______, _______, _______, _______,  _______,   _______, KC_TRNS, _______,    _______, _______, _______, _______
    )
};
/* v1,01
    [_6] = LAYOUT(
        KC_EQL, KC_SCLN, S(KC_7), S(KC_8), S(KC_9), 	KC_INT3, QK_GESC, _______, _______, _______, _______, _______, _______, 
        KC_COMM, KC_QUOT, S(KC_4), S(KC_5), S(KC_6), 	KC_RBRC, KC_MINS, _______, _______, _______, _______, _______, _______,
        KC_DOT, KC_SLSH, S(KC_1), S(KC_2), S(KC_3),  KC_NUHS, KC_INT1, KC_LCTL, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,  KC_LBRC,   _______, KC_TRNS, KC_LSFT,    _______, _______, _______, _______
    )
};
*/

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
}

// ★追加・修正：ここから下の処理を process_record_user の中に包み込みます★
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  // IME_OFF時薙刀式の処理(操作面、編集面、拡張面)
 if (!process_custom_cursor(keycode, record)) {
    return false;
  }
  // 薙刀式のキー処理（他のキーより先に判定させるために最初に書きます）
  if (!process_naginata(keycode, record)) {
    return false;
  }

  // カスタムキーコードの処理
  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
      }
      return false;
      break;

    case KANA2:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
      }
      return false;
      break;
  }
// ALT_TAB
switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case KC_RIGHT: case KC_LEFT: case KC_DOWN: case KC_UP: case KC_TAB:
      if (is_alt_tab_active) {
        alt_tab_timer = timer_read();
      }
      break;
    default:
      if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
      }
      break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // 現在一番上にあるアクティブなレイヤーを判定
  switch (get_highest_layer(state)) {
    
    case _2:
      // PC側のNumLockが「オフ」なら、NumLockキーを1回押して「オン」にする
      if (!host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM);
      }
      break;

    default:
      // 指定したレイヤー以外に戻った時、NumLockが「オン」なら「オフ」にする
      if (host_keyboard_led_state().num_lock) {
        tap_code(KC_NUM);
      }
      break;
  }
  return state;
}


// ALT_TAB キーのキーマップへの割り当てコードは省略

void matrix_scan_user(void) {
  if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 1000) {
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
  }
}
