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
#ifdef RGB_MATRIX_ENABLE
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware
    return process_record_user(keycode, record);
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
#endif
