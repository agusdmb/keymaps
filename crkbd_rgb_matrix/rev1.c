/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 25 24 19 18 11 10   0
  //    03    02    01
  // 26 23 20 17 12 09   1
  //    04    05    06
  // 27 22 21 16 13 08   2
  //
  //          15 14 07   3
  //
  // Right
  // 0  1  2  3  4  5
  //                    ROWS
  // 25 24 19 18 11 10   4
  //    03    02    01
  // 26 23 20 17 12 09   5
  //    04    05    06
  // 27 22 21 16 13 08   6
  //
  //          15 14 07   7
  //
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 25 24 19 18 11 10       10 11 18 19 24 25  0
  //    03    02    01       01    02    03
  // 26 23 20 17 12 09       09 12 17 20 23 26  1
  //    04                               04
  // 27 22 21 16 13 08       08 13 16 21 22 27  2
  //          05    06       06    05
  //           15 14 07     07 14 15              3

led_config_t g_led_config = { {
    {  18,  17,  12,  11,  4,   3 },
    {  19,  16,  13,  10,  5,   2 },
    {  20,  15,  14,  9,  6,   1 },
    { NO_LED, NO_LED, NO_LED,  8,  7,   0 },
    {  39,  38,  33,  32,  25,  24 },
    {  40,  37,  34,  31,  26,  23 },
    {  41,  36,  35,  30,  27,  22 },
    { NO_LED, NO_LED, NO_LED,  29,  28,  21 }
}, {
    {  95,  63 }, {  85,  39 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  68,  37 }, {  80,  58 },
    {  60,  55 }, {  50,  35 }, {  50,  18 }, {  50,   0 }, {  33,   3 }, {  33,  20 }, {  33,  37 },
    {  16,  42 }, {  16,  24 }, {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 },
    { 129,  63 }, { 139,  39 }, { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 }, { 156,  37 }, { 144,  58 }, { 164,  55 },
    { 174,  35 }, { 174,  18 }, { 174,   0 }, { 191,   3 }, { 191,  20 }, { 191,  37 }, { 208,  42 },
    { 208,  24 }, { 208,   7 }, { 224,   7 }, { 224,  24 }, { 224,  41 }
}, {
    1, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
