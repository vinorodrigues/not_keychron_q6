// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "keymaps.h"

#define Q6_M_FN MO(MAC_FN)
#define Q6_M_NL TG(MAC_NUML)
#define Q6_W_FN MO(WIN_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_all(
                                                                                                                        KC_VOLD, KC_VOLU,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, Q6_SHOT, Q6_SIRI, RGB_TOG, KC_F13,  KC_F14,  KC_F15,  KC_F16,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, Q6_M_NL, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_HOME, KC_UP,   KC_PGUP, KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_LEFT, XXXXXXX, KC_RGHT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_END,  KC_DOWN, KC_PGDN, KC_ENT,
        KC_LCTL, Q6_LOPT, Q6_LCMD,                            KC_SPC,                             Q6_RCMD, Q6_ROPT, Q6_M_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,           KC_DEL           ),

    [MAC_NUML] = LAYOUT_ansi_all(
                                                                                                                        _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            KC_P4,   KC_P5,   KC_P6,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,          KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, KC_P0,            KC_PDOT          ),

    [MAC_FN] = LAYOUT_ansi_all(
                                                                                                                        RGB_VAD, RGB_VAI,
        _______, KC_BRID, KC_BRIU, Q6_MCON, Q6_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG, _______, _______, RGB_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,          QK_BOOT, _______, _______, Q6_VRSN, _______, NK_TOGG, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______,          _______          ),

    [WIN_BASE] = LAYOUT_ansi_all(
                                                                                                                        KC_VOLD, KC_VOLU,
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_PSCR, Q6_CRTN, RGB_TOG, _______, _______, _______, _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LWIN, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RWIN, Q6_W_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,            KC_PDOT          ),

    [WIN_FN] = LAYOUT_ansi_all(
                                                                                                                        RGB_VAD, RGB_VAI,
        _______, KC_BRID, KC_BRIU, Q6_TASK, Q6_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, RGB_TOG, _______, _______, RGB_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_RMD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,          QK_BOOT, _______, _______, Q6_VRSN, _______, NK_TOGG, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______,           _______         )
};


/* ----------
 * DIP SWITCH
 * ---------- */

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? WIN_BASE : MAC_BASE));
    }
    return true;
}

#endif  // DIP_SWITCH_ENABLE


/* --------------
 * ROTARY ENCODER
 * -------------- */

#ifdef ENCODER_ENABLE

static uint8_t  encoder_state = 0;
static keypos_t encoder_cw    = {8, 5};
static keypos_t encoder_ccw   = {7, 5};

void encoder_action_unregister(void) {
    if (encoder_state) {
        keyevent_t encoder_event = (keyevent_t){
            .key = encoder_state >> 1 ? encoder_cw : encoder_ccw,
            .pressed = false,
            .time = (timer_read() | 1)
        };
        encoder_state = 0;
        action_exec(encoder_event);
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    if (index != 0) return;

    keyevent_t encoder_event = (keyevent_t){
        .key = clockwise ? encoder_cw : encoder_ccw,
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return false;
};

#endif  // ENCODER_ENABLE


/* ------------
 * Key specific
 * ------------ */

void matrix_scan_user(void) {
    #ifdef ENCODER_ENABLE
    encoder_action_unregister();
    #endif  // ENCODER_ENABLE
}


/* --------------
 * LED Indicators
 * -------------- */

void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, RGB_WHITE);
    }

    uint8_t layer = get_highest_layer(layer_state);
    if (host_keyboard_led_state().num_lock || (MAC_NUML == layer)) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, RGB_WHITE);
    }
}
