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

// #ifdef PAL_USE_CALLBACKS

// void encoder0_pad_cb(void *param) {
//     (void)param;
//     encoder_insert_state(0);
// }

// void keyboard_post_init_kb(void) {
//     pin_t encoders_pad_a[] = ENCODERS_PAD_A;
//     pin_t encoders_pad_b[] = ENCODERS_PAD_B;
//     palEnableLineEvent(encoders_pad_a[0], PAL_EVENT_MODE_BOTH_EDGES);
//     palEnableLineEvent(encoders_pad_b[0], PAL_EVENT_MODE_BOTH_EDGES);
//     palSetLineCallback(encoders_pad_a[0], encoder0_pad_cb, NULL);
//     palSetLineCallback(encoders_pad_b[0], encoder0_pad_cb, NULL);
// }

// #endif  // PAL_USE_CALLBACKS
#endif  // ENCODER_ENABLE
