// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define KEYBOARD_keychron_q6_ansi_stm32l432_ec11  // legacy
// #define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x04  // override of the layout options default value.

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

// #ifdef ENCODER_RESOLUTION
//     #undef ENCODER_RESOLUTION
// #endif
// #define ENCODER_RESOLUTION 4

#undef FORCE_NKRO  // NKRO stops macOS Fn key functionality

/* ----
 * VIAL
 * ---- */

#define VIAL_KEYBOARD_UID {0x18, 0xE6, 0x23, 0x34, 0x08, 0xC4, 0xF4, 0x5D}
// Unlock with Esc + Enter
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }
