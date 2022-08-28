// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

enum custom_keycodes {
    #if VIA_ENABLE
    KC_MISSION_CONTROL = USER00,
    #else
    KC_MISSION_CONTROL = SAFE_RANGE,
    #endif
    KC_LAUNCHPAD,
    KC_LEFT_OPTION,
    KC_RIGHT_OPTION,
    KC_LEFT_COMMAND,
    KC_RIGHT_COMMAND,
    KC_SIRI,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA,
    KC_CLEAR_EEPROM,
    KC_VERSION
};

enum macos_consumer_usages {
    _AC_SHOW_ALL_WINDOWS = 0x29F,  // mapped to Q1_MCON
    _AC_SHOW_ALL_APPS    = 0x2A0   // mapped to Q1_LPAD
};

#define Q6_MCON KC_MISSION_CONTROL
#define Q6_LPAD KC_LAUNCHPAD
#define Q6_LOPT KC_LEFT_OPTION
#define Q6_ROPT KC_RIGHT_OPTION
#define Q6_LCMD KC_LEFT_COMMAND
#define Q6_RCMD KC_RIGHT_COMMAND
#define Q6_SIRI KC_SIRI
#define Q6_TASK KC_TASK_VIEW
#define Q6_FLXP KC_FILE_EXPLORER
#define Q6_SHOT KC_SCREEN_SHOT
#define Q6_CRTN KC_CORTANA
#define Q6_EECL KC_CLEAR_EEPROM
#define Q6_VRSN KC_VERSION
#define RGB_RMD RGB_RMOD
