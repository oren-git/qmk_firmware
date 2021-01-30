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

#include "hacking_msw.h"
#include "timer.h"
#include "rgblight.h"

extern rgblight_config_t rgblight_config;
extern rgb_config_t rgb_matrix_config;

uint8_t mode;
bool matrix_is_enabled;
uint16_t timer_buffer;

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
    led_set_user(usb_led);
}

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {     0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12 },
  {    28,     27,     26,     25,     24,     23,     22,     21,     20,     19,     18,     17,     16 },
  {    29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     41 },
  {    54,     53,     52,     51,     50,     49,     48,     47,     46,     45,     44,     43,     42 },
  {    55,     56,     57,     58,     NO_LED, NO_LED, NO_LED, NO_LED, 59,     60,     15,     13,     14 }
}, {
  // LED Index to Physical Position
  {  0,   0}, { 16,   0}, { 32,   0}, { 48,   0}, { 64,   0}, { 80,   0}, { 96,   0}, {112,   0}, {128,   0}, {144,   0}, {160,   0}, {176,   0}, {192,   0}, {208,   0}, {224,   0},
  {  0,  16}, { 17,  16}, { 34,  16}, { 52,  16}, { 69,  16}, { 86,  16}, {103,  16}, {121,  16}, {138,  16}, {155,  16}, {172,  16}, {190,  16}, {207,  16}, {224,  16},
  {  0,  32}, { 19,  32}, { 37,  32}, { 56,  32}, { 75,  32}, { 93,  32}, {112,  32}, {131,  32}, {149,  32}, {168,  32}, {187,  32}, {205,  32}, {224,  32},
  {  0,  48}, { 19,  48}, { 37,  48}, { 56,  48}, { 75,  48}, { 93,  48}, {112,  48}, {131,  48}, {149,  48}, {168,  48}, {187,  48}, {205,  48}, {224,  48},
  {  0,  64}, { 45,  64}, { 90,  64}, {134,  64}, {179,  64}, {224,  64}
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4
} };


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed)
    {
        switch (keycode) {
            case KC_LALT:
                if (layer_state_is(1))
                {
                    rgb_matrix_toggle();
                    return false;
                }
            case KC_R:
                if (layer_state_is(1))
                {
                    rgb_matrix_step();
                    return false;
                }
            case KC_T:
                if (layer_state_is(1))
                {
                    if (rgb_matrix_config.enable)
                    {
                        rgb_matrix_increase_val();
                    } else {
                        rgb_matrix_enable();
                    }
                    return false;
                }

            case KC_Y:
                if (layer_state_is(1)) {
                    if (rgb_matrix_config.enable)
                    {
                        rgb_matrix_decrease_val();
                        if (rgb_matrix_get_val() == 0)
                        {
                            rgb_matrix_disable();
                        }
                    }
                    return false;
                }
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
void keyboard_post_init_kb(void) {
  // Customise these values to desired behaviour
  #ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
  #endif
  #ifdef RGBLIGHT_ENABLE
  rgblight_set_effect_range(DRIVER_LED_TOTAL, RGBLED_NUM - DRIVER_LED_TOTAL);
  #endif
  //debug_keyboard=true;
  //debug_mouse=true;
//   rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
  matrix_is_enabled = rgb_matrix_is_enabled();
  mode = rgb_matrix_get_mode();
  timer_buffer = timer_read();
  if (!matrix_is_enabled)
  {
      rgb_matrix_enable_noeeprom();
  }
  rgb_matrix_mode_noeeprom(16);
}

void matrix_scan_kb()
{
    if (timer_buffer > 0 && timer_elapsed(timer_buffer) > 3000)
    {
        timer_buffer = 0;
        if (!matrix_is_enabled)
        {
            rgb_matrix_disable_noeeprom();
        }
        rgb_matrix_mode_noeeprom(mode);
    }
}

// void rgb_matrix_indicators_kb(void) {
//     rgb_matrix_set_color(3, 0, 0, 255);
// }
bool led_update_kb(led_t led_state) {
    // rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set();
    return true;
}
layer_state_t layer_state_set_kb(layer_state_t state) {
    rgblight_set();
    return state;
}

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
    // bool layer_flag = 0;
    // for (size_t i = 1; i < 7; i++) {
    //     if (layer_state_is(i)) {
    //         flag = 1;
    //     }
    // }
    // if (layer_flag) {
    //     sethsv(191, 255, rgblight_config.val, (LED_TYPE *)&led[64]);
    // }
    if (layer_state) {
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
