#pragma once
#include QMK_KEYBOARD_H
#include "naginata.h" // NG_SAFE_RANGE やカーソル関数を使用するため[cite: 5]

// カスタムキーコードの定義
// 薙刀式内部のキーコードと重複しないよう、NG_SAFE_RANGE を基準にします
enum custom_keycodes {
  EISU = NG_SAFE_RANGE, // 既存の薙刀式設定（もしあれば）[cite: 1]
  KANA2,                // 既存の薙刀式設定（もしあれば）[cite: 1]
  OFF_UP,
  OFF_DOWN,
  OFF_LEFT,
  OFF_RIGHT
};

// 処理を切り分ける関数の宣言
bool process_ime_off(uint16_t keycode, keyrecord_t *record);