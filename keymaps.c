// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "keymaps.h"
#include "version.h"


/* ---------------
 * Custom keycodes
 * --------------- */

#ifdef USE_FACTORY_RESET

// rember to overide these in your keymap
#define MAC_FN_LAYER 1
#define WIN_FN_LAYER 3

static void timer_3s_task(void);
static void timer_300ms_task(void);

#define KEY_PRESS_FN (0x1<<0)
#define KEY_PRESS_J  (0x1<<1)
#define KEY_PRESS_Z  (0x1<<2)
#define KEY_PRESS_FACTORY_RESET (KEY_PRESS_FN | KEY_PRESS_J | KEY_PRESS_Z)

uint16_t key_press_status = 0;
uint32_t timer_3s_buffer = 0;
uint32_t timer_300ms_buffer = 0;
uint8_t factory_reset_count = 0;

void matrix_scan_kb(void) {
    if (timer_3s_buffer) { timer_3s_task(); }
    if (timer_300ms_buffer) { timer_300ms_task(); }
    matrix_scan_user();
}

static void timer_3s_task(void) {
    if (sync_timer_elapsed32(timer_3s_buffer) > 3000) {
        timer_3s_buffer = 0;
        if (key_press_status == KEY_PRESS_FACTORY_RESET) {
            timer_300ms_buffer = sync_timer_read32();
            factory_reset_count++;
            layer_state_t default_layer_tmp = default_layer_state;
            eeconfig_init();
            default_layer_set(default_layer_tmp);
        }
        key_press_status = 0;
    }
}

static void timer_300ms_task(void) {
    if (timer_300ms_buffer && sync_timer_elapsed32(timer_300ms_buffer) > 300) {
        if (factory_reset_count++ > 6) {
            timer_300ms_buffer = 0;
            factory_reset_count = 0;
        } else {
            timer_300ms_buffer = sync_timer_read32();
        }
    }
}

#endif  // USE_FACTORY_RESET


/* -----------------
 * Internal commands
 * ----------------- */

bool __consumer_send(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        host_consumer_send(data);
    } else {
        host_consumer_send(0);
    }
    return false;  // Skip all further processing of this key
}

bool __code_1(keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        register_code(data);
    } else {
        unregister_code(data);
    }
    return false;  // Skip all further processing of this key
}

bool __code_2(keyrecord_t *record, uint16_t data1, uint16_t data2) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
    } else {
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

bool __code_3(keyrecord_t *record, uint16_t data1, uint16_t data2, uint16_t data3) {
    if (record->event.pressed) {
        register_code(data1);
        register_code(data2);
        register_code(data3);
    } else {
        unregister_code(data3);
        unregister_code(data2);
        unregister_code(data1);
    }
    return false;  // Skip all further processing of this key
}

#ifdef USE_FACTORY_RESET

bool __factory_rt(keyrecord_t *record, uint8_t data) {
    if (record->event.pressed) {
        key_press_status |= data;
        if ((key_press_status == KEY_PRESS_FACTORY_RESET) && (KEY_PRESS_FN != data)) {
            timer_3s_buffer = sync_timer_read32() | 1;
        }
    } else {
        key_press_status &= ~data;
        timer_3s_buffer = 0;
    }
    return true;
}

#endif  // USE_FACTORY_RESET


/* -------------------
 * Keypress processing
 * ------------------- */

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) return false;

    switch (keycode) {
        // macOS keys
        case KC_MISSION_CONTROL: return __consumer_send(record, _AC_SHOW_ALL_WINDOWS);
        case KC_LAUNCHPAD: return __consumer_send(record, _AC_SHOW_ALL_APPS);
        case KC_LEFT_OPTION: return __code_1(record, KC_LOPT);
        case KC_RIGHT_OPTION: return __code_1(record, KC_ROPT);
        case KC_LEFT_COMMAND: return __code_1(record, KC_LCMD);
        case KC_RIGHT_COMMAND: return __code_1(record, KC_RCMD);
        case KC_SIRI: return __code_2(record, KC_LCMD, KC_SPACE);
        case KC_SCREEN_SHOT: return __code_3(record, KC_LSFT, KC_LCMD, KC_4);

        // Windows keys
        case KC_TASK_VIEW: return __code_2(record, KC_LWIN, KC_TAB);
        case KC_FILE_EXPLORER: return __code_2(record, KC_LWIN, KC_E);
        case KC_CORTANA: return __code_2(record, KC_LWIN, KC_C);

        // clear EEPROM
        case KC_CLEAR_EEPROM:
            eeconfig_init_quantum();
            soft_reset_keyboard();
            return false;

        // print firmware version
        case KC_VERSION:
            if (!get_mods()) {
                if (!record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " (v" QMK_VERSION ")");

                    SEND_STRING(" [E");
                    #ifdef USE_EEPROM
                    SEND_STRING("EPROM");
                    #elif USE_EFL_WL
                    SEND_STRING("FL/WL");
                    #endif
                    SEND_STRING("]");

                    // #ifdef VIA_ENABLE
                    // /* show the Layout Options stored in VIA */
                    // char str[9];
                    // itoa(via_get_layout_options(), str, 16);
                    // SEND_STRING(" [0x");
                    // send_string_with_delay(str, 0);
                    // SEND_STRING("]");
                    // #endif
                }
            }
            return false;

        // Factory reset
        #ifdef USE_FACTORY_RESET

        case MO(WIN_FN_LAYER):
        case MO(MAC_FN_LAYER): return __factory_rt(record, KEY_PRESS_FN);
        case KC_J: return __factory_rt(record, KEY_PRESS_J);
        case KC_Z: return __factory_rt(record, KEY_PRESS_Z);

        #endif  // USE_FACTORY_RESET

        // Default
        default:
            return true;   // Process all other keycodes normally
    }
}
