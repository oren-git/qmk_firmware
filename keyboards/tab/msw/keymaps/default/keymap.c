/* Copyright 2020 Tab.co
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "process_rgb.h"
#include "rgb.h"
extern rgblight_config_t rgblight_config;
extern rgb_config_t rgb_matrix_config;
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MAT_MOD = SAFE_RANGE,
    MAT_VAD,
    MAT_VAI,
    MAT_TOG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //*
    [_BASE] = KEYMAP(
        //1      2        3        4       5        6        7        8        9        10       11       12       13       14       15
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN),
        KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT
    ),
    [_FN] = KEYMAP(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   KC_INS,  KC_DEL,
        KC_CAPS, RGB_MOD, RGB_VAI, RGB_VAD, MAT_MOD, MAT_VAI, MAT_VAD, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,  KC_TRNS,  KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, KC_TRNS,KC_TRNS,
        RGB_TOG, MAT_TOG, KC_TRNS, KC_TRNS, KC_TRNS, EEP_RST
    )
    /*/
    [_BASE] = KEYMAP(
        //1      2        3        4       5        6        7        8        9        10       11       12       13       14       15
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  EEP_RST, RESET,   MO(_FN),
        KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT
    ),
    [_FN] = KEYMAP(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   KC_INS,  KC_DEL,
        KC_CAPS, RGB_MOD, RGB_VAI, RGB_VAD, MAT_MOD, MAT_VAI, MAT_VAD, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP,  KC_TRNS,  KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,KC_PENT,
        RGB_MOD, RGB_VAI, RGB_VAD, MAT_MOD, MAT_VAI, MAT_VAD, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T,KC_TRNS,
        RGB_TOG, MAT_TOG, RGB_M_P, RGB_M_B, RGB_M_R, EEP_RST
    )
    //*/
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed)
    {
        switch (keycode) {
            case MAT_TOG:
                rgb_matrix_toggle();
                return false;
            case MAT_MOD:
                rgb_matrix_step();
                return false;
            case MAT_VAI:
                if (rgb_matrix_config.enable)
                {
                    rgb_matrix_increase_val();
                } else {
                    rgb_matrix_enable();
                }
                return false;
            case MAT_VAD:
                if (rgb_matrix_config.enable)
                {
                    rgb_matrix_decrease_val();
                    if (rgb_matrix_get_val() == 0)
                    {
                        rgb_matrix_disable();
                    }
                }
                return false;
            case RGB_VAI:
                if (rgblight_config.enable)
                {
                    rgblight_increase_val();
                } else {
                    rgblight_enable();
                }
                return false;
            case RGB_VAD:
                if (rgblight_config.enable)
                {
                    rgblight_decrease_val();
                    if (rgblight_get_val() == 0)
                    {
                        rgblight_disable();
                    }
                }
                return false;
        }
    }
    return true;
}
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  #ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
  #endif
  #ifdef RGBLIGHT_ENABLE
  rgblight_set_effect_range(61, 13);
  #endif
  //debug_keyboard=true;
  //debug_mouse=true;
//   rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
}

// void rgb_matrix_indicators_kb(void) {
//     rgb_matrix_set_color(3, 0, 0, 255);
// }
bool led_update_user(led_t led_state) {
    // rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set();
    return true;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set();
    return state;
}
#ifdef RGBLIGHT_CUSTOM_DRIVER
void rgblight_set(void) {
    LED_TYPE *start_led;
    if (!rgblight_config.enable) {
        for (uint8_t i = rgblight_ranges.effect_start_pos; i < rgblight_ranges.effect_end_pos; i++) {
            led[i].r = 0;
            led[i].g = 0;
            led[i].b = 0;
        }
    } else if (rgblight_config.mode == RGBLIGHT_MODE_STATIC_LIGHT) {
        for (uint8_t i = rgblight_ranges.effect_start_pos; i < rgblight_ranges.effect_end_pos; i++) {
            sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[i]);
        }
    }

    uint8_t ind_led = host_keyboard_leds();
    if (IS_LED_ON(ind_led, USB_LED_CAPS_LOCK)) {
        sethsv(85, 255, rgblight_config.val, (LED_TYPE *)&led[71]);
        // setrgb(RGB_GREEN, (LED_TYPE *)&led[71]);
    }
    if (IS_LED_ON(ind_led, USB_LED_SCROLL_LOCK)) {
        sethsv(43, 255, rgblight_config.val, (LED_TYPE *)&led[72]);
        // setrgb(RGB_YELLOW, (LED_TYPE *)&led[72]);
    }
    if (IS_LED_ON(ind_led, USB_LED_NUM_LOCK)) {
        sethsv(170, 255, rgblight_config.val, (LED_TYPE *)&led[73]);
        // setrgb(RGB_BLUE, (LED_TYPE *)&led[73]);
    }
    if (layer_state)
    {
        sethsv(191, 255, rgblight_config.val, (LED_TYPE *)&led[64]);
    }

    // for (int32_t i = 0; i < 4; i++) {
    //     if(layer_state_is(i+1)) {
    //         sethsv(HSV_PURPLE, (LED_TYPE *)&led[61 + i]);
    //     }
    // }
    start_led = led + rgblight_ranges.clipping_start_pos;
    ws2812_setleds(start_led, rgblight_ranges.clipping_num_leds);
}
#endif
