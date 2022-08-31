# Define your variant from the `make` command line `EEPROM=1`
# or by adding `EEPROM yes` to the keymap rules.mk file.

EEPROM ?= yes
ifneq ($(strip $(EEPROM)), yes)
	OPT_DEFS += -DEEPROM_ENABLE
else
	OPT_DEFS += -DEFL_WL_ENABLE
endif

FACTORY_RESET ?= yes
ifeq ($(strip $(FACTORY_RESET)), yes)
	OPT_DEFS += -DFACTORY_RESET_ENABLE
endif
