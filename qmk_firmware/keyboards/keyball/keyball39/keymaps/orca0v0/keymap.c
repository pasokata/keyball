#include QMK_KEYBOARD_H
#include "quantum.h"
#include "lib/keyball/keyball.h"
#include "secret.h"

enum custom_keycodes
{
  MACRO1 = KEYBALL_SAFE_RANGE,
  H_SCRL,
  MY_HOME,
  MY_END,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  os_variant_t os = detected_host_os();
  switch (keycode)
  {
  case MACRO1:
    if(record->event.pressed)SEND_STRING(MACRO1_STR);
    return false;
    break;
  case H_SCRL:
    if(record->event.pressed)keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL);
    else keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
    return false;
    break;
  case MY_HOME:
    if (record->event.pressed)
    {
      if (os == OS_MACOS)
      {
        register_code(KC_LALT); // GUI and ALT are swapped in macOS
        register_code(KC_LEFT);
      }
      else {
        register_code(KC_HOME);
      }
    }
    else {
      if (os == OS_MACOS)
      {
        unregister_code(KC_LEFT);
        unregister_code(KC_LALT);
      }
      else {
        unregister_code(KC_HOME);
      }
    }
    return false;
    break;
  case MY_END:
    if (record->event.pressed)
    {
      if (os == OS_MACOS)
      {
        register_code(KC_LALT);
        register_code(KC_RIGHT);
      }
      else {
        register_code(KC_END);
      }
    }
    else {
      if (os == OS_MACOS)
      {
        unregister_code(KC_RIGHT);
        unregister_code(KC_LALT);
      }
      else {
        unregister_code(KC_END);
      }
    }
    return false;
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
    _______     , KC_LGUI  , KC_LCTL  , LSFT_T(KC_TAB) , LT(2,KC_SPC) , LT(3,KC_ESC),     KC_RALT, MO(1)  , XXXXXXX  , XXXXXXX  , XXXXXXX  , SCRL_TO
  ),

  [1] = LAYOUT_universal(
    S(KC_5)  , S(KC_6)  , S(KC_7)  , S(KC_4)  , KC_SLSH  ,                                      KC_BSLS    , S(KC_LBRC) , S(KC_RBRC) , S(KC_COMM) , S(KC_DOT)   ,
    S(KC_2)  , S(KC_3)  , S(KC_8)  , S(KC_EQL), KC_EQL  ,                                       S(KC_MINS) , S(KC_9)    , S(KC_0)    , KC_SCLN    , S(KC_SCLN)  ,
    KC_GRV   ,S(KC_GRV) , KC_MINUS , S(KC_1)  , S(KC_SLSH) ,                                    S(KC_BSLS) , KC_LBRC    , KC_RBRC    , KC_QUOT    , S(KC_QUOT)  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                  _______ , _______   , XXXXXXX    , XXXXXXX    , XXXXXXX    , _______
  ),

  [2] = LAYOUT_universal(
    XXXXXXX  , KC_7     , KC_8     , KC_9     , XXXXXXX  ,                                        XXXXXXX , MY_HOME     , XXXXXXX     , MY_END  , XXXXXXX,
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
    _______  , _______  , _______  , _______  , _______  ,                            KC_BTN5  , SCRL_MO  , H_SCRL   , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , OSL(4)    ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______,   _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______ 
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
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
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
    rgblight_sethsv(HSV_RED);
    break;
  }
  
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

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void keyboard_post_init_user(void)
{
  set_auto_mouse_enable(true);
}
#endif