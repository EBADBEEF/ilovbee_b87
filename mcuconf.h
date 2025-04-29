// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// See ./lib/chibios-contrib/os/hal/ports/WB32/LLD/ for defaults

// SPI (priority of the WS2812 must be higher than other SPI devices)
#undef WB32_SPI_USE_SPIM2
#define WB32_SPI_USE_SPIM2 TRUE

#undef WB32_SPI_SPIM2_IRQ_PRIORITY
#define WB32_SPI_SPIM2_IRQ_PRIORITY 9

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

#undef WB32_SPI_QSPI_IRQ_PRIORITY
#define WB32_SPI_QSPI_IRQ_PRIORITY 10

// Clocks (system 96MHz)
#undef WB32_PLLDIV_VALUE
#define WB32_PLLDIV_VALUE 2

#undef WB32_PLLMUL_VALUE
#define WB32_PLLMUL_VALUE 16

#undef WB32_USBPRE
#define WB32_USBPRE WB32_USBPRE_DIV2
