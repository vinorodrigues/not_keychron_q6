# `not_keychron_q6`

> This is ***not*** the code to the Keychron Q6 *(but it is the one I use)*.

> :warning: : THIS CODE IS INTENDED FOR EDUCATIONAL PURPOSES ONLY AND DOES NOT REPRESENT KEYCHRON IN ANY WAY.

<p align="center"><img src="docs/image-00.png" width="50%"></p>

* Keyboard Maintainer: [Vino Rodrigues](https://github.com/vinorodrigues)
* Hardware Supported: **Keychron Q6**
* Hardware Availability: [Keychron Q6](https://www.keychron.com/products/keychron-q6-qmk-custom-mechanical-keyboard)

Make example for this keyboard (after setting up your build environment):

    make notkeychron/q6:default

Flashing example for this keyboard:

    make notkeychron/q6:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button underneath the Space Bar
* **Keycode in layout**: Press the key mapped to `QK_BOOT` *(or `RESET`)* if it is available


***

## Why?

Basically, I wanted to compile from `qmk/qmk_firmware:master` but that code caused me strife.  So I wrote my own, different in the following ways:

* Initially I ported the code to make use of the I²C EEPROM slot on the Q1 PCB. *(This code is still there, but now requires the `EEPROM=1` make command argument added.)*
* The code consolidates all the different variants in `keychron/qmk_firmware:playground` into one common source code base. *(I'm a huge proponent of refactoring.)*
* With a recent PR into `qmk/qmk_firmware:develop` QMK admins added a EFL/EL driver that now allows the STM32 flash to run as an emulated EEPROM.  This code is now incorporated and is the default compile.

Use this code to learn from - but it's not endorsed by either Keychron or QMK.

## How To

Please read the [HOW2COMPILE.md](HOW2COMPILE.md) file for instructions on how to use this code.

-- Made with :heart: &nbsp; by Vino Rodrigues
