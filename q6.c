// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "q6.h"

/* ----- NOTE: -----
 * LED Matrix resides in the `v2_{layout_name}.c` files.
 * ----------------- */

#ifdef USE_EEPROM
    #pragma message "NOTE: ** Using EEPROM driver **"
#endif


/* ----------
 * DIP Switch
 * ---------- */

const matrix_row_t matrix_mask[] = {
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111101111,
};

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif  // DIP_SWITCH_ENABLE


/* ----- Rotary Encoder ------ */

#ifdef ENCODER_ENABLE

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, TAP_CODE_DELAY);
        } else {
            tap_code_delay(KC_VOLD, TAP_CODE_DELAY);
        }
    }
    return true;
}

#endif  // ENCODER_ENABLE
