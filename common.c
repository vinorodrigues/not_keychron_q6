// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "common.h"
#include "version.h"


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

void matrix_scan_user(void) {
    encoder_action_unregister();
}

#endif  // ENCODER_ENABLE


/* ---------------
 * Custom keycodes
 * --------------- */

#ifdef FACTORY_RESET_ENABLE

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

#endif  // FACTORY_RESET_ENABLE


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

#ifdef FACTORY_RESET_ENABLE

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

#endif  // FACTORY_RESET_ENABLE


/* ----------------------
 * RGB and Indicator LEDs
 * ---------------------- */

#if defined(RGB_MATRIX_ENABLE) \
    && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX))

    #ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
        #define LED_BRIGHTNESS_HI RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #else
        #define LED_BRIGHTNESS_HI 0xFF
    #endif

    #ifdef RGB_MATRIX_VAL_STEP
        #define LED_VAL_STEP RGB_MATRIX_VAL_STEP
    #else
        #define LED_VAL_STEP 8
    #endif

    #define LED_BRIGHTNESS_LO LED_VAL_STEP

typedef union {
    uint32_t raw;
    struct {
        bool rgb_disable_led:1;
    };
} kb_config_t;

kb_config_t kb_config;

bool is_q6_rgb_disabled(void) {
    return kb_config.rgb_disable_led;
}

typedef union {
    uint16_t raw;
    struct {
        bool caps_led:1;
        bool num_led:1;
        bool scrl_led:1;
    };
} led_sngltn_kb_t;

led_sngltn_kb_t led_sngltn_kb;

void update_q6_rgb_mode(void) {
    if (kb_config.rgb_disable_led) {
        rgb_matrix_set_flags(1 << 7);  // set high bit, don't use 0, disables LED to off condition
        rgb_matrix_set_color_all(HSV_OFF);
    } else {
        rgb_matrix_set_flags(LED_FLAG_ALL);
        rgb_matrix_enable_noeeprom();
    }
}

void get_q6_rgb_mode(void) {
    kb_config.raw = eeconfig_read_kb();  // read config from EEPROM
    update_q6_rgb_mode();
}

void set_q6_rgb_mode(void) {
    eeconfig_update_kb(kb_config.raw);  // write back to EEPROM
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
    led_sngltn_kb.raw = 0;
    get_q6_rgb_mode();
}

void eeconfig_init_kb(void) {
    // EEPROM is getting reset!
    eeconfig_init_user();
    kb_config.raw = 0;
    set_q6_rgb_mode();
}

uint8_t get_q6_brightness(void) {
    uint8_t value = rgb_matrix_get_val();
    if (value < LED_BRIGHTNESS_LO) {
        value = LED_BRIGHTNESS_LO;
    } else if (value < (LED_BRIGHTNESS_HI - LED_VAL_STEP)) {
        if (!is_q6_rgb_disabled())
            value += LED_VAL_STEP; // one step more than current brightness
    } else {
        value = LED_BRIGHTNESS_LO;
    }
    return value;
}

extern void rgb_matrix_update_pwm_buffers(void);

void rgb_matrix_indicators_kb(void) {
    rgb_matrix_indicators_user();

    uint8_t v = get_q6_brightness();
    led_t led_state = host_keyboard_led_state();

    #if defined(CAPS_LOCK_LED_INDEX)
    if (led_state.caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, v, v, v);
        if (!led_sngltn_kb.caps_led && !is_q6_rgb_disabled())
            led_sngltn_kb.caps_led = true;
    } else if (led_sngltn_kb.caps_led) {
        rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        led_sngltn_kb.caps_led = false;
    }
    #endif

    #if defined(NUM_LOCK_LED_INDEX)
    if (led_state.num_lock) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v);
        if (!led_sngltn_kb.num_led && !is_q6_rgb_disabled())
            led_sngltn_kb.num_led = true;
    } else if (led_sngltn_kb.num_led) {
        rgb_matrix_set_color(NUM_LOCK_LED_INDEX, 0, 0, 0);
        led_sngltn_kb.num_led = false;
    }
    #endif

    #if defined(SCROLL_LOCK_LED_INDEX)
    if (led_state.scroll_lock) {
        rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, v, v, v);
        if (!led_sngltn_kb.scrl_led && !is_q6_rgb_disabled())
            led_sngltn_kb.scrl_led = true;
    } else if (led_sngltn_kb.scrl_led) {
        rgb_matrix_set_color(SCROLL_LOCK_LED_INDEX, 0, 0, 0);
        led_sngltn_kb.scrl_led = false;
    }
    #endif
}

// does this do anything?
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        rgb_matrix_update_pwm_buffers();
    }
    return res;
}

#endif // CAPS_LOCK_LED_INDEX or NUM_LOCK_LED_INDEX or SCROLL_LOCK_LED_INDEX


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
        case KC_SIRI: return __code_2(record, KC_LOPT, KC_SPACE);
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
                    #ifdef EEPROM_ENABLE
                    SEND_STRING("EPROM");
                    #elif EFL_WL_ENABLE
                    SEND_STRING("FL/WL");
                    #else
                    SEND_STRING("rr");  // should never run
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
        #ifdef FACTORY_RESET_ENABLE

        case MO(WIN_FN_LAYER):
        case MO(MAC_FN_LAYER): return __factory_rt(record, KEY_PRESS_FN);
        case KC_J: return __factory_rt(record, KEY_PRESS_J);
        case KC_Z: return __factory_rt(record, KEY_PRESS_Z);

        #endif  // FACTORY_RESET_ENABLE

        case RGB_TOG:
            /* |    Level    | LED |
             * |-------------|-----|
             * | 0 (default) | on  |
             * |     1       | OFF |
             */
            if (record->event.pressed) {
                kb_config.rgb_disable_led = kb_config.rgb_disable_led ? 0 : 1;
                set_q6_rgb_mode();  // save
                update_q6_rgb_mode();  // set kb states
            }
            return false;  // block default RGB_TOG

        case QK_BOOT:
            if (record->event.pressed) {
                rgblight_enable_noeeprom();
                rgblight_mode_noeeprom(1);
                rgb_matrix_set_color_all(LED_BRIGHTNESS_HI, 0, 0);  // All red
                rgb_matrix_update_pwm_buffers();
                wait_ms(10);  // give it time to change LED's
            }
            return true;


        // Default
        default:
            return true;   // Process all other keycodes normally
    }
}
