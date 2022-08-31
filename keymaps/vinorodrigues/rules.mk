# Copyright 2022 Vino Rodrigues (@vinorodrigues)
# SPDX-License-Identifier: GPL-3.0-or-later

OPT_DEFS += -DIS_ANSI_KNOB
SRC += q6_ansi_knob.c

# MOUSEKEY_ENABLE = no
# DIP_SWITCH_ENABLE = no

LTO_ENABLE = yes
VIA_ENABLE = yes

# --- Vial Specific ---
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes
QMK_SETTINGS = no        # save eeprom
TAP_DANCE_ENABLE = no    # save eeprom
COMBO_ENABLE = no        # save eeprom
KEY_OVERRIDE_ENABLE = no # save eeprom

# --- force EEPROM ---
EEPROM_DRIVER = i2c
OPT_DEFS += -DEEPROM_ENABLE

OPT_DEFS += -DFACTORY_RESET_ENABLE
