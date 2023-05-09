# Copyright 2022 Keychron (https://www.keychron.com)
# SPDX-License-Identifier: GPL-2.0-or-later

# *** most settings now in `info.json` ***

# Build Options
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# custom matrix setup
CUSTOM_MATRIX = lite

VPATH += keyboards/keychron/common
SRC += matrix.c
