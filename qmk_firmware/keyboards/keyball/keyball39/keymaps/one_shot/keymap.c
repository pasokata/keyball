#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"
#include "quantum.h"
#include "lib/keyball/keyball.h"
#include "macro_str.h"

#define FWD KC_BTN5
#define BACK KC_BTN4
#define SPACE_L A(G(KC_LEFT))
#define SPACE_R A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define KC_VOLU KC_KB_VOLUME_UP
#define KC_VOLD KC_KB_VOLUME_DOWN
#define KC_MUTE KC_KB_MUTE
#define TERM A(C(KC_T))

enum layers
{
  DEF,
  MOU,
  SYM,
  NAV,
  NUM,
};

enum custom_keycodes
{
  // Custom oneshot mod implementation with no timers.
  OS_SHFT = KEYBALL_SAFE_RANGE,
  OS_CTRL,
  OS_ALT,
  OS_CMD,

  SW_WIN,   // Switch to next window         (cmd-tab)
  SW_LANG,  // Switch to next input language (ctl-spc)
  SW_TAB_L, // Switch to prev tab            (ctl-tab)
  SW_TAB_R, // Switch to next tab            (ctl-tab)

  MACRO1,
  H_SCRL,
};

// TODO: mod keys for mouse layer

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [DEF] = LAYOUT_universal(
    KC_Q        , KC_W     , KC_F     , KC_P         , KC_G         ,                                 KC_J     , KC_L     , KC_U     , KC_Y     , KC_SCLN,
    KC_A        , KC_R     , KC_S     , KC_T         , KC_D         ,                                 KC_H     , KC_N     , KC_E     , KC_I     , KC_O   ,
    KC_Z        , KC_X     , KC_C     , KC_V         , KC_B         ,                                 KC_K     , KC_M     , KC_COMM  , KC_DOT   , KC_QUOT,
    G(KC_L)     , _______  , _______  , KC_LSFT      , LA_NAV      , KC_TAB,               KC_SPC,   LA_SYM    , XXXXXXX  , XXXXXXX  , XXXXXXX  , SCRL_TO
  ),
  [MOU] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            KC_BTN5  , SCRL_MO  , H_SCRL   , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , MO(MOU)    ,
    _______  , _______  , _______  , _______  , _______   , _______  ,      _______,  _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______ 
  ),
  [SYM] = LAYOUT_universal(
    KC_TAB      , KC_LBRC  , KC_LCBR  , KC_LPRN      , KC_TILD      ,                                KC_CIRC   , KC_RPRN  , KC_RCBR  , KC_RBRC  , KC_GRV ,
    KC_MINS     , KC_ASTR  , KC_EQL   , KC_UNDS      , KC_DLR       ,                                KC_HASH   , OS_CTRL  , OS_SHFT  , OS_ALT   , OS_CMD ,
    KC_PLUS     , KC_PIPE  , KC_AT    , KC_SLSH      , KC_PERC      ,                                XXXXXXX   , KC_BSLS  , KC_AMPR  , KC_EXLM  , KC_QUES,
    _______     , MACRO1   , _______  , _______      , _______      , _______   ,         _______ ,  _______   , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______
  ),
  [NAV] = LAYOUT_universal(
    KC_ESC      , SW_WIN   , SW_TAB_L , SW_TAB_R     , KC_VOLU      ,                                KC_CAPS   , KC_HOME  , KC_UP    , KC_END   , KC_DEL,
    OS_CMD      , OS_ALT   , OS_SHFT  , OS_CTRL      , KC_VOLD      ,                                XXXXXXX   , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_BSPC,
    SPACE_L     , SPACE_R  , BACK     , FWD          , KC_MUTE      ,                                TERM      , KC_PGDN  , KC_PGUP  , SW_LANG  , KC_ENT,
    _______     , _______  , _______  , _______      , _______      ,  _______ ,           _______  ,   _______ , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______
  ),
  [NUM] = LAYOUT_universal(
    KC_1        , KC_2     , KC_3     , KC_4         , KC_5         ,                                 KC_6     , KC_7     , KC_8     , KC_9     , KC_0,
    OS_CMD      , OS_ALT   , OS_SHFT  , OS_CTRL      , KC_F11       ,                                 KC_F12   , OS_CTRL  , OS_SHFT  , OS_ALT   , OS_CMD, 
    KC_F1       , KC_F2    , KC_F3    , KC_F4        , KC_F5        ,                                 KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10,
    _______     , _______  , _______  , _______      , _______      , _______  ,          _______ ,  _______   , _______  , _______  , _______  , _______ 
  )
};
// clang-format on
layer_state_t layer_state_set_user(layer_state_t state)
{
  state = update_tri_layer_state(state, SYM, NAV, NUM);
  switch (get_highest_layer(state))
  {
  case DEF:
    rgblight_sethsv(HSV_OFF);
    keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
    break;
  case SYM:
    rgblight_sethsv(HSV_PINK);
    break;
  case NAV:
    rgblight_sethsv(HSV_MAGENTA);
    break;
  case NUM:
    rgblight_sethsv(HSV_PURPLE);
    break;
  case MOU:
    rgblight_sethsv(HSV_RED);
    break;
  }
  return state;
}

bool is_oneshot_cancel_key(uint16_t keycode)
{
  switch (keycode)
  {
  case LA_SYM:
  case LA_NAV:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode)
{
  switch (keycode)
  {
  case LA_SYM:
  case LA_NAV:
  case KC_LSFT:
  case OS_SHFT:
  case OS_CTRL:
  case OS_ALT:
  case OS_CMD:
    return true;
  default:
    return false;
  }
}

bool sw_win_active = false;
bool sw_lang_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (keycode == H_SCRL){
    keyball_set_scrollsnap_mode( record->event.pressed ? KEYBALL_SCROLLSNAP_MODE_HORIZONTAL : KEYBALL_SCROLLSNAP_MODE_VERTICAL);
    return false;
  }
  if (keycode == MACRO1 && record->event.pressed)
  {
    SEND_STRING(MACRO1_STR);
    return false;
  }

  update_swapper(
      &sw_win_active, KC_LALT, KC_TAB, SW_WIN,
      keycode, record);
  update_swapper(
      &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
      keycode, record);
  update_swapper2(
      &sw_tab_active, KC_LCTL, S(KC_TAB), KC_TAB, SW_TAB_L, SW_TAB_R,
      keycode, record);

  update_oneshot(
      &os_shft_state, KC_LSFT, OS_SHFT,
      keycode, record);
  update_oneshot(
      &os_ctrl_state, KC_LCTL, OS_CTRL,
      keycode, record);
  update_oneshot(
      &os_alt_state, KC_LALT, OS_ALT,
      keycode, record);
  update_oneshot(
      &os_cmd_state, KC_LCMD, OS_CMD,
      keycode, record);

  return true;
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