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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
                                          KC_W     , KC_E     , KC_R          ,                                                        KC_U           , KC_I        , KC_O       ,                                
    KC_LALT          , KC_Q             , KC_W     , KC_E     , KC_R          , KC_T       , _______       , _______ ,   KC_Y        , KC_U           , KC_I        , KC_O       , KC_P            , KC_RALT    ,
    KC_LSFT          , KC_A             , KC_S     , KC_D     , KC_F          , KC_G       , _______       , _______ ,   KC_H        , KC_J           , KC_K        , LT(2,KC_L) , KC_SCLN         , KC_RSFT    ,
    KC_LCTL          , KC_Z             , KC_X     , KC_C     , KC_V          , KC_B       ,                             KC_N        , KC_M           , KC_COMM     , KC_DOT     , KC_SLSH         , KC_RCTL    ,
                       KC_LGUI          , _______  , _______  , LT(1,KC_LBRC) , KC_SPC     , LCTL_T(KC_DEL),  KC_ENT , LT(2,KC_RBRC) , _______        , _______     , _______    , KC_RGUI
  ),

  [1] = LAYOUT_universal(
                                          KC_W     , KC_E     , KC_R          ,                                                        KC_U           , KC_I        , KC_O       ,                                
    KC_LALT          , KC_ESC           , KC_EXLM  , KC_AT    , KC_HASH       , KC_DLR     , _______       , _______ ,   KC_CIRC     , KC_AMPR        , KC_ASTR     , KC_GRV   , KC_BSLS          , KC_RALT    ,
    KC_LSFT          , KC_1             , KC_2     , KC_3     , KC_4          , KC_5       , _______       , _______ ,   KC_LEFT     , KC_DOWN        , KC_UP       , KC_RIGHT , KC_QUOT          , KC_RSFT    ,
    KC_LCTL          , KC_6             , KC_7     , KC_8     , KC_9          , KC_0       ,                             KC_MINS     , KC_EQL         , S(KC_9)     , S(KC_0)  , KC_PERC          , KC_RCTL    ,
                       KC_LGUI          , _______  , _______  , _______       , _______    , _______       , _______ , LT(3,KC_RBRC) , _______        , _______     , _______  , KC_RGUI
  ),

  [2] = LAYOUT_universal(
                                          KC_W     , KC_E     , KC_R          ,                                                        KC_U           , KC_I        , KC_O       ,                                
    KC_LALT          , KC_ESC           , KC_F11   , KC_F12   , _______       , _______     , _______       , _______ ,   KC_DEL      , KC_INS         , KC_PAST     , KC_BSPC  , A(KC_GRV)        , KC_RALT    ,
    KC_LSFT          , KC_F1            , KC_F2    , KC_F3    , KC_F4         , KC_F5       , _______       , _______ ,   KC_BTN2     , KC_BTN1        , KC_BTN3     , _______  , SCRL_MO          , KC_RSFT    ,
    KC_LCTL          , KC_F6            , KC_F7    , KC_F8    , KC_F9         , KC_F10      ,                             KC_PMNS     , KC_PPLS        , _______     , KC_PDOT  , KC_PSLS          , KC_RCTL    ,
                       KC_LGUI          , _______  , _______  , LT(3,KC_LBRC) , KC_TAB      , _______       , _______ ,   _______     , _______        , _______     , _______  , KC_RGUI
  ),

  [3] = LAYOUT_universal(
                                          KC_W     , KC_E     , KC_R          ,                                                        KC_U           , KC_I        , KC_O       ,                                
    KC_LALT          , KC_ESC           , KC_F11   , KC_F12   , _______       , _______     , _______       , _______ ,   _______     , _______        , _______     , _______  , _______          , KC_RALT    ,
    KC_LSFT          , KC_P1            , KC_P2    , KC_P3    , KC_P4         , KC_P5       , _______       , _______ ,   _______     , _______        , _______     , _______  , _______          , KC_RSFT    ,
    KC_LCTL          , KC_P6            , KC_P7    , KC_P8    , KC_P9         , KC_P0       ,                             _______     , _______        , _______     , _______  , _______          , KC_RCTL    ,
                       KC_LGUI          , _______  , _______  , _______       , _______     , _______       , _______ ,   _______     , _______        , _______     , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif
