// IME_OFF時薙刀式の実装(操作面、編集面、拡張面)
#include "imeoff_custom_h.h"

// 実際のカーソル操作の処理
bool process_ime_off(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case OFF_UP:
        ng_prev_row(); // 前の行へ移動[cite: 5]
        return false;
      case OFF_DOWN:
        ng_next_row(); // 次の行へ移動[cite: 5]
        return false;
      case OFF_LEFT:
        ng_prev_char(); // 前の文字へ移動[cite: 5]
        return false;
      case OFF_RIGHT:
        ng_next_char(); // 次の文字へ移動[cite: 5]
        return false;
    }
  }
  // 該当しないキーコードだった場合は true を返し、QMKの通常の処理に渡す
  return true;
}