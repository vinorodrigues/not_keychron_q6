// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "common.h"

#ifdef VIA_PROTOCOL_VERSION
    // make sure this runs with VIA >= 1.3.1
    #undef VIA_PROTOCOL_VERSION
    #define VIA_PROTOCOL_VERSION 0x0009
#endif

enum my_layers {
    MY_MAC_BASE,
    MY_MAC_NUML,
    MY_MAC_FN,
    MY_WIN_BASE,
    MY_WIN_FN
};

#undef MAC_FN_LAYER
#define MAC_FN_LAYER MY_MAC_FN

#define Q6_M_FN MO(MY_MAC_FN)
#define Q6_M_NL TG(MY_MAC_NUML)
#define Q6_W_FN MO(MY_WIN_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MY_MAC_BASE] = LAYOUT_ansi_all(
                                                                                                                        KC_VOLD, KC_VOLU,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, Q6_SHOT, Q6_SIRI, RGB_TOG, KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, Q6_M_NL, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_HOME, KC_UP,   KC_PGUP, KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_LEFT, XXXXXXX, KC_RGHT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_END,  KC_DOWN, KC_PGDN, KC_ENT,
        KC_LCTL, Q6_LOPT, Q6_LCMD,                            KC_SPC,                             Q6_RCMD, Q6_ROPT, Q6_M_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,           KC_DEL           ),

    [MY_MAC_NUML] = LAYOUT_ansi_all(
                                                                                                                        _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            KC_P4,   KC_P5,   KC_P6,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,          KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, KC_P0,            KC_PDOT          ),

    [MY_MAC_FN] = LAYOUT_ansi_all(
                                                                                                                        RGB_VAD, RGB_VAI,
        _______, KC_BRID, KC_BRIU, Q6_MCON, Q6_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG, _______, _______, RGB_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,          QK_BOOT, _______, _______, Q6_VRSN, _______, NK_TOGG, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______,          _______          ),

    [MY_WIN_BASE] = LAYOUT_ansi_all(
                                                                                                                        KC_VOLD, KC_VOLU,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_PSCR, Q6_CRTN, RGB_TOG, _______, _______, _______, _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LWIN, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RWIN, Q6_W_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,            KC_PDOT          ),

    [MY_WIN_FN] = LAYOUT_ansi_all(
                                                                                                                        RGB_VAD, RGB_VAI,
        _______, KC_BRID, KC_BRIU, Q6_TASK, Q6_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG, _______, _______, RGB_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,          QK_BOOT, _______, _______, Q6_VRSN, _______, NK_TOGG, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______,           _______         )
};


/* ------------
 * LED OVERRIDE
 * ------------ */

#ifdef RGB_MATRIX_ENABLE

#define LED_FLAG_ALPHA_KEY 0x10  // Alpha keys (for Caps Lock)
#define LED_FLAG_LAYER_IND 0x20  // Layer indicator

const uint8_t g_led_config_new_flags[DRIVER_LED_TOTAL] = {
    // Extended LED Index to Flag
    0x01, 0x01, 0x01, 0x01, 0x01, 0x21, 0x21, 0x21, 0x21, 0x01, 0x01, 0x01, 0x01,       0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x01, 0x01, 0x01, 0x09, 0x04, 0x04, 0x04,
    0x01, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04, 0x01, 0x01, 0x01, 0x04, 0x04, 0x04,
    0x09, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04,       0x01,                   0x04, 0x04, 0x04, 0x04,
    0x01,       0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x04, 0x04, 0x04,       0x01,       0x01,       0x04, 0x04, 0x04,
    0x01, 0x01, 0x01,                   0x04,                   0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x04,       0x04, 0x01,
};

void keyboard_pre_init_user(void) {
    // override config.flags with new values
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) g_led_config.flags[i] = g_led_config_new_flags[i];
}

#endif  // RGB_MATRIX_ENABLE


/* ----------
 * DIP SWITCH
 * ---------- */

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        layer_state_set(1UL << (active ? MY_WIN_BASE : MY_MAC_BASE));
        default_layer_set(1UL << (active ? MY_WIN_BASE : MY_MAC_BASE));
        return false;
    }
    return true;
}

#endif  // DIP_SWITCH_ENABLE


/* --------------
 * LED Indicators
 * -------------- */

#ifdef RGB_MATRIX_ENABLE

typedef union {
    uint16_t raw;
    struct {
        bool caps_led:1;
        bool num_led:1;
        bool lyr_led:1;
    };
} led_sngltn_user_t;

led_sngltn_user_t led_sngltn_user;

void keyboard_post_init_user(void) {
    led_sngltn_user.raw = 0;
}

void __rgb_matrix_set_all_color_by_flag(uint8_t flag, uint8_t R, uint8_t G, uint8_t B) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (0 != (g_led_config.flags[i] & flag)) {
            rgb_matrix_set_color(i, R, G, B);
        }
    }
}

void rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    bool mac_nl = (layer == MY_MAC_NUML);

    uint8_t v = get_q6_brightness();
    led_t led_state = host_keyboard_led_state();

    // caps-lock indicators - not the caps-lock key, but all the alphas
    if (led_state.caps_lock) {
        if (!is_q6_rgb_disabled()) {
            __rgb_matrix_set_all_color_by_flag(LED_FLAG_ALPHA_KEY, v, 0, 0);  // red
            if (!led_sngltn_user.caps_led)
                led_sngltn_user.caps_led = true;
        }
    } else if (led_sngltn_user.caps_led) {
        __rgb_matrix_set_all_color_by_flag(LED_FLAG_ALPHA_KEY, 0, 0, 0);
        led_sngltn_user.caps_led = false;
    }

    // num-lock indicators - only the mac-mode layer hack
    if (mac_nl) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v);  // white
        if (!led_sngltn_user.num_led && !is_q6_rgb_disabled())
            led_sngltn_user.num_led = true;
    } else if (led_sngltn_user.num_led) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, HSV_OFF);  // off, if it was on before
        led_sngltn_user.num_led = false;
    }

    // layer indicators
    switch (layer) {
        case MY_MAC_FN:
            __rgb_matrix_set_all_color_by_flag(LED_FLAG_LAYER_IND, 0, 0, v);  // blue
            if (!led_sngltn_user.lyr_led)
                led_sngltn_user.lyr_led = true;
            break;

        case MY_WIN_FN:
            __rgb_matrix_set_all_color_by_flag(LED_FLAG_LAYER_IND, 0, v, 0);  // green
            if (!led_sngltn_user.lyr_led && is_q6_rgb_disabled())
                led_sngltn_user.lyr_led = true;
            break;

        // case MY_MAC_BASE:
        // case MY_MAC_NUML:
        // case MY_WIN_BASE:
        default:
            if (led_sngltn_user.lyr_led && is_q6_rgb_disabled()) {
                __rgb_matrix_set_all_color_by_flag(LED_FLAG_LAYER_IND, 0, 0, 0);  // off
                led_sngltn_user.lyr_led = false;
            }
            break;  // do nothing
    }
}

#endif  // RGB_MATRIX_ENABLE
