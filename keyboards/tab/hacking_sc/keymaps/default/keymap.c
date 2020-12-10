/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H

#define BASE 0
#define HHKB 1

#include "rgblight.h"
extern rgblight_config_t rgblight_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE Level: Default Layer
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Esc   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -     | =   | \     | ` |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Tab   | Q | W | E | R | T | Y | U | I | O | P | [     | ]   | Backs |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Cont  | A | S | D | F | G | H | J | K | L | ; | '     | Ent |       |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|
     | Shift | Z | X | C | V | B | N | M | , | . | / | Shift | Fn0 |       |   |
     |-------+---+---+---+---+---+---+---+---+---+---+-------+-----+-------+---|

            |------+------+-----------------------+------+------|
            | LAlt | LGUI | ******* Space ******* | RGUI | RAlt |
            |------+------+-----------------------+------+------|
    */

    [BASE] = LAYOUT( //  default layer
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(HHKB),
        KC_LALT, KC_LGUI, /*        */ KC_SPC, KC_RGUI, KC_RALT),

    /* Layer HHKB: HHKB mode (HHKB Fn)
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Pwr  | F1  | F2  | F3  | F4 | F5 | F6 | F7 | F8  | F9  | F10 | F11 | F12   | Ins   | Del |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      | Caps |     |     |     |    |    |    |    | Psc | Slk | Pus | Up  |       | Backs |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      | VoD | VoU | Mut |    |    | *  | /  | Hom | PgU | Lef | Rig | Enter |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|
      |      |     |     |     |    |    | +  | -  | End | PgD | Dow |     |       |       |     |
      |------+-----+-----+-----+----+----+----+----+-----+-----+-----+-----+-------+-------+-----|

                 |------+------+----------------------+------+------+
                 | **** | **** | ******************** | **** | **** |
                 |------+------+----------------------+------+------+

     */

    [HHKB] = LAYOUT(
        KC_PWR, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_CAPS, RGB_MOD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_UP, KC_TRNS, KC_BSPC,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_PENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PPLS, KC_PMNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};

void keyboard_pre_init_user(void)
{
    rgblight_config.val = 125;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
#endif
