#include "hacking_sc.h"
#include "timer.h"

#include "rgblight.h"
extern rgblight_config_t rgblight_config;

void keyboard_pre_init_kb(void)
{
    rgblight_config.val = 125;
}

uint8_t mode;
bool rgblight_enabled;
uint16_t timer_buffer;

void keyboard_post_init_kb(void) {
  rgblight_enabled = rgblight_is_enabled();
  mode = rgblight_get_mode();
  timer_buffer = timer_read();
  if (!rgblight_enabled)
  {
      rgblight_enable_noeeprom();
  }
  rgblight_mode_noeeprom(21);
}

void matrix_scan_kb()
{
    if (timer_buffer > 0 && timer_elapsed(timer_buffer) > 3000)
    {
        timer_buffer = 0;
        if (!rgblight_enabled)
        {
            rgblight_disable_noeeprom();
        }
        rgblight_mode_noeeprom(mode);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed)
    {
        switch (keycode) {
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
        sethsv(85, 255, rgblight_config.val, (LED_TYPE *)&led[10]);
    }
    if (IS_LED_ON(ind_led, USB_LED_SCROLL_LOCK)) {
        sethsv(43, 255, rgblight_config.val, (LED_TYPE *)&led[11]);
    }
    if (IS_LED_ON(ind_led, USB_LED_NUM_LOCK)) {
        sethsv(170, 255, rgblight_config.val, (LED_TYPE *)&led[12]);
    }

    if (layer_state) {
        sethsv(191, 255, rgblight_config.val, (LED_TYPE *)&led[3]);
    }

    start_led = led + rgblight_ranges.clipping_start_pos;
    ws2812_setleds(start_led, rgblight_ranges.clipping_num_leds);
}
