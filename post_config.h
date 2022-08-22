// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

/* --------------
 * Compiler flags
 * -------------- */

#ifdef IS_ANSI_KNOB
    #define IS_ANSI
#endif
#ifdef IS_ISO_KNOB
    #define IS_ISO
#endif

#if !defined(IS_ANSI) && defined(IS_ISO)
    #error "Unknown keyboard variant"
#endif
