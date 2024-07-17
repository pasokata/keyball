/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"
#include "lib/keyball/keyball.h"

// Tap Dance Declarations
enum
{
  TD_ESC_CAPS = 0,
  TD_GA,
  TD_EC,
  TD_QC,
  TD_ZS,
};

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Esc, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    // Other declarations would go here, separated by commas, if you have them
    [TD_GA] = ACTION_TAP_DANCE_DOUBLE(KC_RGUI, KC_RALT),
    [TD_QC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_LCTL),
    [TD_ZS] = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_LSFT),
};

#include "secret.h"
enum custom_keycodes
{
  MACRO1 = KEYBALL_SAFE_RANGE,
  H_SCRL
};
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case MACRO1:
    if(record->event.pressed)SEND_STRING(MACRO1_STR);
    break;
  case H_SCRL:
    if(record->event.pressed)keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL);
    else keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
    break;
  }
  return true;
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q        , KC_W     , KC_E     , KC_R         , KC_T         ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A        , KC_S     , KC_D     , KC_F         , KC_G         ,                            KC_H     , KC_J     , KC_K     , KC_L     , RCTL_T(KC_ENT),
    KC_Z        , KC_X     , KC_C     , KC_V         , KC_B         ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , RSFT_T(KC_BSPC),
    _______     , KC_LGUI  , KC_LCTL  , LSFT_T(KC_TAB) , LT(2,KC_SPC) , LT(3,KC_ESC),     KC_RALT, MO(1)  , XXXXXXX  , XXXXXXX  , XXXXXXX  , TG(4)
  ),

  [1] = LAYOUT_universal(
    S(KC_5)  , S(KC_6)  , S(KC_7)  , S(KC_4)  , KC_SLSH  ,                                      KC_BSLS    , S(KC_LBRC) , S(KC_RBRC) , S(KC_COMM) , S(KC_DOT)   ,
    S(KC_2)  , S(KC_3)  , S(KC_8)  , S(KC_EQL), KC_EQL  ,                                       S(KC_MINS) , S(KC_9)    , S(KC_0)    , KC_SCLN    , S(KC_SCLN)  ,
    KC_GRV   ,S(KC_GRV) , KC_MINUS , S(KC_1)  , S(KC_SLSH) ,                                    S(KC_BSLS) , KC_LBRC    , KC_RBRC    , KC_QUOT    , S(KC_QUOT)  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                  _______ , _______   , XXXXXXX    , XXXXXXX    , XXXXXXX    , _______
  ),

  [2] = LAYOUT_universal(
    XXXXXXX  , KC_7     , KC_8     , KC_9     , XXXXXXX  ,                                        XXXXXXX , KC_HOME     , XXXXXXX     , KC_END  , XXXXXXX,
    KC_0     , KC_4     , KC_5     , KC_6     , XXXXXXX  ,                                        KC_LEFT , KC_DOWN     , KC_UP       , KC_RGHT , KC_RCTL,
    XXXXXXX  , KC_1     , KC_2     , KC_3     , XXXXXXX  ,                                        XXXXXXX , RSA(KC_RBRC), RSA(KC_LBRC), XXXXXXX , RSFT_T(KC_BSPC),
    _______  , _______  , _______  , _______  , _______  , _______ ,                   _______ ,  _______ , XXXXXXX     , XXXXXXX     , XXXXXXX , _______
  ),

  [3] = LAYOUT_universal(
    _______  , KC_F7    , KC_F8    , KC_F9    , KC_F10    ,                             XXXXXXX          , XXXXXXX          , XXXXXXX        , XXXXXXX       , XXXXXXX ,
    MACRO1   , KC_F4    , KC_F5    , KC_F6    , KC_F11    ,                             RCTL(KC_LEFT)    , RCTL(KC_DOWN)    , RCTL(KC_UP)    , RCTL(KC_RGHT) , RCTL(KC_ENT),
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F12    ,                             KC_KB_MUTE       , KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, XXXXXXX       , XXXXXXX ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      LCA(KC_T) ,  RCTL(KC_GRV)     , _______          , _______        , _______       , _______ 
  ),
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , SCRL_TO  , H_SCRL   , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , TT(4)    ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      KC_BTN4,   KC_BTN5  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______ 
  ),
};
// clang-format on

layer_state_t
layer_state_set_user(layer_state_t state)
{
  switch (get_highest_layer(state))
  {
  case 0:
    rgblight_sethsv(HSV_OFF);
    break;
  case 1:
    rgblight_sethsv(HSV_PINK);
    break;
  case 2:
    rgblight_sethsv(HSV_MAGENTA);
    break;
  case 3:
    rgblight_sethsv(HSV_PURPLE);
    break;
  case 4:
    if (keyball_get_scroll_mode())
    {
      rgblight_sethsv(HSV_BLUE);
    }
    else{
        rgblight_sethsv(HSV_RED);
    }
    break;
  }
  // LOWER + RAISE = ADJUST のようなTri Layersを使う場合
  // これを先に書いておかないと3の色がおかしくなる
  // state = update_tri_layer_state(state, 1, 2, 3);

  set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
  keyball_oled_render_layerinfo();
}
#endif

void pointing_device_init_user(void)
{
  set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}