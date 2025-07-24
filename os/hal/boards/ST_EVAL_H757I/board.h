/*
    ChibiOS - Copyright (C) 2006..2023 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for STMicroelectronics STM32H757I-EVAL board.
 */

/*
 * Board identifier.
 */
#define BOARD_ST_EVAL_H757I
#define BOARD_NAME                  "STMicroelectronics STM32H757I-EVAL"

/*
 * Ethernet PHY type.
 */
#define BOARD_PHY_ID                MII_LAN8742A_ID
#define BOARD_PHY_RMII

/*
 * The board has an ULPI USB PHY.
 */
#define BOARD_OTG2_USES_ULPI

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                25000000U
#endif

/*
 * MCU type as defined in the ST header.
 */
#define STM32H757xx

/*
 * IO pins assignments.
 */
#define GPIOA_WAKEUP                0U
#define GPIOA_RMII_REF_CLK          1U
#define GPIOA_RMII_MDIO             2U
#define GPIOA_ULPI_D0               3U
#define GPIOA_EXT_RESET             4U
#define GPIOA_ULPI_CK               5U
#define GPIOA_LCD_BL_CTRL           6U
#define GPIOA_RMII_CRS_DV           7U
#define GPIOA_MCO1                  8U
#define GPIOA_VBUS_FS2              9U
#define GPIOA_USB_FS2_ID            10U
#define GPIOA_USB_FS2_DM            11U
#define GPIOA_USB_FS2_DP            12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_JTDI                  15U

#define GPIOB_ULPI_D1               0U
#define GPIOB_ULPI_D2               1U
#define GPIOB_QSPI_CLK              2U
#define GPIOB_JTDO_TRACESWO         3U
#define GPIOB_NJTRST                4U
#define GPIOB_ULPI_D7               5U
#define GPIOB_I2C1_SCL              6U
#define GPIOB_I2C1_SDA              7U
#define GPIOB_SDIO1_CKIN            8U
#define GPIOB_SDIO1_CDIR            9U
#define GPIOB_ULPI_D3               10U
#define GPIOB_ULPI_D4               11U
#define GPIOB_ULPI_D5               12U
#define GPIOB_ULPI_D6               13U
#define GPIOB_USART1_TX             14U
#define GPIOB_USART1_RX             15U

#define GPIOC_ULPI_STP              0U
#define GPIOC_RMII_MDC              1U
#define GPIOC_DFSDM_CLKOUT          2U
#define GPIOC_DFSDM_DATA1           3U
#define GPIOC_RMII_RXD0             4U
#define GPIOC_RMII_RXD1             5U
#define GPIOC_SDIO1_D0DIR           6U
#define GPIOC_SDIO1_D123DIR         7U
#define GPIOC_SDIO1_D0              8U
#define GPIOC_SDIO1_D1              9U
#define GPIOC_SDIO1_D2              10U
#define GPIOC_SDIO1_D3              11U
#define GPIOC_SDIO1_CLK             12U
#define GPIOC_TAMPER_KEY            13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_FMC_D2                0U
#define GPIOD_FMC_D3                1U
#define GPIOD_SDIO1_CMD             2U
#define GPIOD_FDCAN1_STBY           3U
#define GPIOD_FMC_NOE               4U
#define GPIOD_FMC_NWE               5U
#define GPIOD_FMC_NWAIT             6U
#define GPIOD_FMC_NE1               7U
#define GPIOD_FMC_D13               8U
#define GPIOD_FMC_D14               9U
#define GPIOD_FMC_D15               10U
#define GPIOD_FMC_A16               11U
#define GPIOD_FMC_A17               12U
#define GPIOD_FMC_A18               13U
#define GPIOD_FMC_D0                14U
#define GPIOD_FMC_D1                15U

#define GPIOE_FMC_NBL0              0U
#define GPIOE_FMC_NBL1              1U
#define GPIOE_PDM1_CLK1             2U
#define GPIOE_SAI1_SDB              3U
#define GPIOE_SAI1_FSA              4U
#define GPIOE_SAI1_SCKA             5U
#define GPIOE_SAI1_SDA              6U
#define GPIOE_FMC_D4                7U
#define GPIOE_FMC_D5                8U
#define GPIOE_FMC_D6                9U
#define GPIOE_FMC_D7                10U
#define GPIOE_FMC_D8                11U
#define GPIOE_FMC_D9                12U
#define GPIOE_FMC_D10               13U
#define GPIOE_FMC_D11               14U
#define GPIOE_FMC_D12               15U

#define GPIOF_FMC_A0                0U
#define GPIOF_FMC_A1                1U
#define GPIOF_FMC_A2                2U
#define GPIOF_FMC_A3                3U
#define GPIOF_FMC_A4                4U
#define GPIOF_FMC_A5                5U
#define GPIOF_QSPI_BK1_IO3          6U
#define GPIOF_QSPI_BK1_IO2          7U
#define GPIOF_QSPI_BK1_IO0          8U
#define GPIOF_QSPI_BK1_IO1          9U
#define GPIOF_DSI_RESET             10U
#define GPIOF_SDNRAS                11U
#define GPIOF_FMC_A6                12U
#define GPIOF_FMC_A7                13U
#define GPIOF_FMC_A8                14U
#define GPIOF_FMC_A9                15U

#define GPIOG_FMC_A10               0U
#define GPIOG_FMC_A11               1U
#define GPIOG_FMC_A12               2U
#define GPIOG_FMC_A13               3U
#define GPIOG_FMC_A14               4U
#define GPIOG_FMC_A15               5U
#define GPIOG_QSPI_BK1_NCS          6U
#define GPIOG_SAI1_MCLKA            7U
#define GPIOG_SDCLK                 8U
#define GPIOG_QSPI_BK2_IO2          9U
#define GPIOG_FMC_NE3               10U
#define GPIOG_RMII_TX_EN            11U
#define GPIOG_RMII_TXD1             12U
#define GPIOG_RMII_TXD0             13U
#define GPIOG_QSPI_BK2_IO3          14U
#define GPIOG_SDNCAS                15U

#define GPIOH_OSCIN                 0U
#define GPIOH_OSCOUT                1U
#define GPIOH_QSPI_BK2_IO0          2U
#define GPIOH_QSPI_BK2_IO1          3U
#define GPIOH_ULPI_NXT              4U
#define GPIOH_SDNWE                 5U
#define GPIOH_SDNE1                 6U
#define GPIOH_SDCKE1                7U
#define GPIOH_FMC_D16               8U
#define GPIOH_FMC_D17               9U
#define GPIOH_FMC_D18               10U
#define GPIOH_FMC_D19               11U
#define GPIOH_FMC_D20               12U
#define GPIOH_FMC_D21               13U
#define GPIOH_FMC_D22               14U
#define GPIOH_FMC_D23               15U

#define GPIOI_FMC_D24               0U
#define GPIOI_FMC_D25               1U
#define GPIOI_FMC_D26               2U
#define GPIOI_FMC_D27               3U
#define GPIOI_FMC_NBL2              4U
#define GPIOI_FMC_NBL3              5U
#define GPIOI_FMC_D28               6U
#define GPIOI_FMC_D29               7U
#define GPIOI_EXPANDER_INT          8U
#define GPIOI_FMC_D30               9U
#define GPIOI_FMC_D31               10U
#define GPIOI_ULPI_DIR              11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

#define GPIOJ_PIN0                  0U
#define GPIOJ_PIN1                  1U
#define GPIOJ_DSI_TE                2U
#define GPIOJ_PIN3                  3U
#define GPIOJ_PIN4                  4U
#define GPIOJ_PIN5                  5U
#define GPIOJ_PIN6                  6U
#define GPIOJ_TRGIN                 7U
#define GPIOJ_PIN8                  8U
#define GPIOJ_PIN9                  9U
#define GPIOJ_PIN10                 10U
#define GPIOJ_PIN11                 11U
#define GPIOJ_TRGOUT                12U
#define GPIOJ_PIN13                 13U
#define GPIOJ_PIN14                 14U
#define GPIOJ_PIN15                 15U

#define GPIOK_PIN0                  0U
#define GPIOK_PIN1                  1U
#define GPIOK_PIN2                  2U
#define GPIOK_LED1                  3U
#define GPIOK_LED2                  4U
#define GPIOK_LED3                  5U
#define GPIOK_LED4                  6U
#define GPIOK_PIN7                  7U
#define GPIOK_PIN8                  8U
#define GPIOK_PIN9                  9U
#define GPIOK_PIN10                 10U
#define GPIOK_PIN11                 11U
#define GPIOK_PIN12                 12U
#define GPIOK_PIN13                 13U
#define GPIOK_PIN14                 14U
#define GPIOK_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_WAKEUP                 PAL_LINE(GPIOA, 0U)
#define LINE_RMII_REF_CLK           PAL_LINE(GPIOA, 1U)
#define LINE_RMII_MDIO              PAL_LINE(GPIOA, 2U)
#define LINE_ULPI_D0                PAL_LINE(GPIOA, 3U)
#define LINE_EXT_RESET              PAL_LINE(GPIOA, 4U)
#define LINE_ULPI_CK                PAL_LINE(GPIOA, 5U)
#define LINE_LCD_BL_CTRL            PAL_LINE(GPIOA, 6U)
#define LINE_RMII_CRS_DV            PAL_LINE(GPIOA, 7U)
#define LINE_MCO1                   PAL_LINE(GPIOA, 8U)
#define LINE_VBUS_FS2               PAL_LINE(GPIOA, 9U)
#define LINE_USB_FS2_ID             PAL_LINE(GPIOA, 10U)
#define LINE_USB_FS2_DM             PAL_LINE(GPIOA, 11U)
#define LINE_USB_FS2_DP             PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_JTDI                   PAL_LINE(GPIOA, 15U)
#define LINE_ULPI_D1                PAL_LINE(GPIOB, 0U)
#define LINE_ULPI_D2                PAL_LINE(GPIOB, 1U)
#define LINE_QSPI_CLK               PAL_LINE(GPIOB, 2U)
#define LINE_JTDO_TRACESWO          PAL_LINE(GPIOB, 3U)
#define LINE_NJTRST                 PAL_LINE(GPIOB, 4U)
#define LINE_ULPI_D7                PAL_LINE(GPIOB, 5U)
#define LINE_I2C1_SCL               PAL_LINE(GPIOB, 6U)
#define LINE_I2C1_SDA               PAL_LINE(GPIOB, 7U)
#define LINE_SDIO1_CKIN             PAL_LINE(GPIOB, 8U)
#define LINE_SDIO1_CDIR             PAL_LINE(GPIOB, 9U)
#define LINE_ULPI_D3                PAL_LINE(GPIOB, 10U)
#define LINE_ULPI_D4                PAL_LINE(GPIOB, 11U)
#define LINE_ULPI_D5                PAL_LINE(GPIOB, 12U)
#define LINE_ULPI_D6                PAL_LINE(GPIOB, 13U)
#define LINE_USART1_TX              PAL_LINE(GPIOB, 14U)
#define LINE_USART1_RX              PAL_LINE(GPIOB, 15U)
#define LINE_ULPI_STP               PAL_LINE(GPIOC, 0U)
#define LINE_RMII_MDC               PAL_LINE(GPIOC, 1U)
#define LINE_DFSDM_CLKOUT           PAL_LINE(GPIOC, 2U)
#define LINE_DFSDM_DATA1            PAL_LINE(GPIOC, 3U)
#define LINE_RMII_RXD0              PAL_LINE(GPIOC, 4U)
#define LINE_RMII_RXD1              PAL_LINE(GPIOC, 5U)
#define LINE_SDIO1_D0DIR            PAL_LINE(GPIOC, 6U)
#define LINE_SDIO1_D123DIR          PAL_LINE(GPIOC, 7U)
#define LINE_SDIO1_D0               PAL_LINE(GPIOC, 8U)
#define LINE_SDIO1_D1               PAL_LINE(GPIOC, 9U)
#define LINE_SDIO1_D2               PAL_LINE(GPIOC, 10U)
#define LINE_SDIO1_D3               PAL_LINE(GPIOC, 11U)
#define LINE_SDIO1_CLK              PAL_LINE(GPIOC, 12U)
#define LINE_TAMPER_KEY             PAL_LINE(GPIOC, 13U)
#define LINE_OSC32_IN               PAL_LINE(GPIOC, 14U)
#define LINE_OSC32_OUT              PAL_LINE(GPIOC, 15U)
#define LINE_FMC_D2                 PAL_LINE(GPIOD, 0U)
#define LINE_FMC_D3                 PAL_LINE(GPIOD, 1U)
#define LINE_SDIO1_CMD              PAL_LINE(GPIOD, 2U)
#define LINE_FDCAN1_STBY            PAL_LINE(GPIOD, 3U)
#define LINE_FMC_NOE                PAL_LINE(GPIOD, 4U)
#define LINE_FMC_NWE                PAL_LINE(GPIOD, 5U)
#define LINE_FMC_NWAIT              PAL_LINE(GPIOD, 6U)
#define LINE_FMC_NE1                PAL_LINE(GPIOD, 7U)
#define LINE_FMC_D13                PAL_LINE(GPIOD, 8U)
#define LINE_FMC_D14                PAL_LINE(GPIOD, 9U)
#define LINE_FMC_D15                PAL_LINE(GPIOD, 10U)
#define LINE_FMC_A16                PAL_LINE(GPIOD, 11U)
#define LINE_FMC_A17                PAL_LINE(GPIOD, 12U)
#define LINE_FMC_A18                PAL_LINE(GPIOD, 13U)
#define LINE_FMC_D0                 PAL_LINE(GPIOD, 14U)
#define LINE_FMC_D1                 PAL_LINE(GPIOD, 15U)
#define LINE_FMC_NBL0               PAL_LINE(GPIOE, 0U)
#define LINE_FMC_NBL1               PAL_LINE(GPIOE, 1U)
#define LINE_PDM1_CLK1              PAL_LINE(GPIOE, 2U)
#define LINE_SAI1_SDB               PAL_LINE(GPIOE, 3U)
#define LINE_SAI1_FSA               PAL_LINE(GPIOE, 4U)
#define LINE_SAI1_SCKA              PAL_LINE(GPIOE, 5U)
#define LINE_SAI1_SDA               PAL_LINE(GPIOE, 6U)
#define LINE_FMC_D4                 PAL_LINE(GPIOE, 7U)
#define LINE_FMC_D5                 PAL_LINE(GPIOE, 8U)
#define LINE_FMC_D6                 PAL_LINE(GPIOE, 9U)
#define LINE_FMC_D7                 PAL_LINE(GPIOE, 10U)
#define LINE_FMC_D8                 PAL_LINE(GPIOE, 11U)
#define LINE_FMC_D9                 PAL_LINE(GPIOE, 12U)
#define LINE_FMC_D10                PAL_LINE(GPIOE, 13U)
#define LINE_FMC_D11                PAL_LINE(GPIOE, 14U)
#define LINE_FMC_D12                PAL_LINE(GPIOE, 15U)
#define LINE_FMC_A0                 PAL_LINE(GPIOF, 0U)
#define LINE_FMC_A1                 PAL_LINE(GPIOF, 1U)
#define LINE_FMC_A2                 PAL_LINE(GPIOF, 2U)
#define LINE_FMC_A3                 PAL_LINE(GPIOF, 3U)
#define LINE_FMC_A4                 PAL_LINE(GPIOF, 4U)
#define LINE_FMC_A5                 PAL_LINE(GPIOF, 5U)
#define LINE_QSPI_BK1_IO3           PAL_LINE(GPIOF, 6U)
#define LINE_QSPI_BK1_IO2           PAL_LINE(GPIOF, 7U)
#define LINE_QSPI_BK1_IO0           PAL_LINE(GPIOF, 8U)
#define LINE_QSPI_BK1_IO1           PAL_LINE(GPIOF, 9U)
#define LINE_DSI_RESET              PAL_LINE(GPIOF, 10U)
#define LINE_SDNRAS                 PAL_LINE(GPIOF, 11U)
#define LINE_FMC_A6                 PAL_LINE(GPIOF, 12U)
#define LINE_FMC_A7                 PAL_LINE(GPIOF, 13U)
#define LINE_FMC_A8                 PAL_LINE(GPIOF, 14U)
#define LINE_FMC_A9                 PAL_LINE(GPIOF, 15U)
#define LINE_FMC_A10                PAL_LINE(GPIOG, 0U)
#define LINE_FMC_A11                PAL_LINE(GPIOG, 1U)
#define LINE_FMC_A12                PAL_LINE(GPIOG, 2U)
#define LINE_FMC_A13                PAL_LINE(GPIOG, 3U)
#define LINE_FMC_A14                PAL_LINE(GPIOG, 4U)
#define LINE_FMC_A15                PAL_LINE(GPIOG, 5U)
#define LINE_QSPI_BK1_NCS           PAL_LINE(GPIOG, 6U)
#define LINE_SAI1_MCLKA             PAL_LINE(GPIOG, 7U)
#define LINE_SDCLK                  PAL_LINE(GPIOG, 8U)
#define LINE_QSPI_BK2_IO2           PAL_LINE(GPIOG, 9U)
#define LINE_FMC_NE3                PAL_LINE(GPIOG, 10U)
#define LINE_RMII_TX_EN             PAL_LINE(GPIOG, 11U)
#define LINE_RMII_TXD1              PAL_LINE(GPIOG, 12U)
#define LINE_RMII_TXD0              PAL_LINE(GPIOG, 13U)
#define LINE_QSPI_BK2_IO3           PAL_LINE(GPIOG, 14U)
#define LINE_SDNCAS                 PAL_LINE(GPIOG, 15U)
#define LINE_OSCIN                  PAL_LINE(GPIOH, 0U)
#define LINE_OSCOUT                 PAL_LINE(GPIOH, 1U)
#define LINE_QSPI_BK2_IO0           PAL_LINE(GPIOH, 2U)
#define LINE_QSPI_BK2_IO1           PAL_LINE(GPIOH, 3U)
#define LINE_ULPI_NXT               PAL_LINE(GPIOH, 4U)
#define LINE_SDNWE                  PAL_LINE(GPIOH, 5U)
#define LINE_SDNE1                  PAL_LINE(GPIOH, 6U)
#define LINE_SDCKE1                 PAL_LINE(GPIOH, 7U)
#define LINE_FMC_D16                PAL_LINE(GPIOH, 8U)
#define LINE_FMC_D17                PAL_LINE(GPIOH, 9U)
#define LINE_FMC_D18                PAL_LINE(GPIOH, 10U)
#define LINE_FMC_D19                PAL_LINE(GPIOH, 11U)
#define LINE_FMC_D20                PAL_LINE(GPIOH, 12U)
#define LINE_FMC_D21                PAL_LINE(GPIOH, 13U)
#define LINE_FMC_D22                PAL_LINE(GPIOH, 14U)
#define LINE_FMC_D23                PAL_LINE(GPIOH, 15U)
#define LINE_FMC_D24                PAL_LINE(GPIOI, 0U)
#define LINE_FMC_D25                PAL_LINE(GPIOI, 1U)
#define LINE_FMC_D26                PAL_LINE(GPIOI, 2U)
#define LINE_FMC_D27                PAL_LINE(GPIOI, 3U)
#define LINE_FMC_NBL2               PAL_LINE(GPIOI, 4U)
#define LINE_FMC_NBL3               PAL_LINE(GPIOI, 5U)
#define LINE_FMC_D28                PAL_LINE(GPIOI, 6U)
#define LINE_FMC_D29                PAL_LINE(GPIOI, 7U)
#define LINE_EXPANDER_INT           PAL_LINE(GPIOI, 8U)
#define LINE_FMC_D30                PAL_LINE(GPIOI, 9U)
#define LINE_FMC_D31                PAL_LINE(GPIOI, 10U)
#define LINE_ULPI_DIR               PAL_LINE(GPIOI, 11U)
#define LINE_DSI_TE                 PAL_LINE(GPIOJ, 2U)
#define LINE_TRGIN                  PAL_LINE(GPIOJ, 7U)
#define LINE_TRGOUT                 PAL_LINE(GPIOJ, 12U)
#define LINE_LED1                   PAL_LINE(GPIOK, 3U)
#define LINE_LED2                   PAL_LINE(GPIOK, 4U)
#define LINE_LED3                   PAL_LINE(GPIOK, 5U)
#define LINE_LED4                   PAL_LINE(GPIOK, 6U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - WAKEUP                    (input floating).
 * PA1  - RMII_REF_CLK              (alternate 11).
 * PA2  - RMII_MDIO                 (alternate 11).
 * PA3  - ULPI_D0                   (alternate 10).
 * PA4  - EXT_RESET                 (output pushpull maximum).
 * PA5  - ULPI_CK                   (alternate 10).
 * PA6  - LCD_BL_CTRL               (output pushpull minimum).
 * PA7  - RMII_CRS_DV               (alternate 11).
 * PA8  - MCO1                      (alternate 0).
 * PA9  - VBUS_FS2                  (analog).
 * PA10 - USB_FS2_ID                (alternate 10).
 * PA11 - USB_FS2_DM                (alternate 10).
 * PA12 - USB_FS2_DP                (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - JTDI                      (alternate 0).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_INPUT(GPIOA_WAKEUP) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_RMII_REF_CLK) |\
                                     PIN_MODE_ALTERNATE(GPIOA_RMII_MDIO) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_ULPI_D0) |    \
                                     PIN_MODE_OUTPUT(GPIOA_EXT_RESET) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_ULPI_CK) |    \
                                     PIN_MODE_OUTPUT(GPIOA_LCD_BL_CTRL) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_RMII_CRS_DV) |\
                                     PIN_MODE_ALTERNATE(GPIOA_MCO1) |       \
                                     PIN_MODE_ANALOG(GPIOA_VBUS_FS2) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_FS2_ID) | \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_FS2_DM) | \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_FS2_DP) | \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_JTDI))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_WAKEUP) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RMII_REF_CLK) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RMII_MDIO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ULPI_D0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_EXT_RESET) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_ULPI_CK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LCD_BL_CTRL) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_RMII_CRS_DV) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_MCO1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_VBUS_FS2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_FS2_ID) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_FS2_DM) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_FS2_DP) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_JTDI))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_WAKEUP) |        \
                                     PIN_OSPEED_HIGH(GPIOA_RMII_REF_CLK) |  \
                                     PIN_OSPEED_HIGH(GPIOA_RMII_MDIO) |     \
                                     PIN_OSPEED_HIGH(GPIOA_ULPI_D0) |       \
                                     PIN_OSPEED_HIGH(GPIOA_EXT_RESET) |     \
                                     PIN_OSPEED_HIGH(GPIOA_ULPI_CK) |       \
                                     PIN_OSPEED_VERYLOW(GPIOA_LCD_BL_CTRL) |\
                                     PIN_OSPEED_VERYLOW(GPIOA_RMII_CRS_DV) |\
                                     PIN_OSPEED_HIGH(GPIOA_MCO1) |          \
                                     PIN_OSPEED_HIGH(GPIOA_VBUS_FS2) |      \
                                     PIN_OSPEED_HIGH(GPIOA_USB_FS2_ID) |    \
                                     PIN_OSPEED_HIGH(GPIOA_USB_FS2_DM) |    \
                                     PIN_OSPEED_HIGH(GPIOA_USB_FS2_DP) |    \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_JTDI))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_WAKEUP) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_RMII_REF_CLK) |\
                                     PIN_PUPDR_PULLUP(GPIOA_RMII_MDIO) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_ULPI_D0) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_EXT_RESET) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_ULPI_CK) |    \
                                     PIN_PUPDR_PULLDOWN(GPIOA_LCD_BL_CTRL) |\
                                     PIN_PUPDR_FLOATING(GPIOA_RMII_CRS_DV) |\
                                     PIN_PUPDR_FLOATING(GPIOA_MCO1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_VBUS_FS2) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_FS2_ID) | \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_FS2_DM) | \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_FS2_DP) | \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_PULLUP(GPIOA_JTDI))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_WAKEUP) |           \
                                     PIN_ODR_HIGH(GPIOA_RMII_REF_CLK) |     \
                                     PIN_ODR_HIGH(GPIOA_RMII_MDIO) |        \
                                     PIN_ODR_HIGH(GPIOA_ULPI_D0) |          \
                                     PIN_ODR_HIGH(GPIOA_EXT_RESET) |        \
                                     PIN_ODR_HIGH(GPIOA_ULPI_CK) |          \
                                     PIN_ODR_LOW(GPIOA_LCD_BL_CTRL) |       \
                                     PIN_ODR_HIGH(GPIOA_RMII_CRS_DV) |      \
                                     PIN_ODR_HIGH(GPIOA_MCO1) |             \
                                     PIN_ODR_HIGH(GPIOA_VBUS_FS2) |         \
                                     PIN_ODR_HIGH(GPIOA_USB_FS2_ID) |       \
                                     PIN_ODR_HIGH(GPIOA_USB_FS2_DM) |       \
                                     PIN_ODR_HIGH(GPIOA_USB_FS2_DP) |       \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_JTDI))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_WAKEUP, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_RMII_REF_CLK, 11U) | \
                                     PIN_AFIO_AF(GPIOA_RMII_MDIO, 11U) |    \
                                     PIN_AFIO_AF(GPIOA_ULPI_D0, 10U) |      \
                                     PIN_AFIO_AF(GPIOA_EXT_RESET, 0U) |     \
                                     PIN_AFIO_AF(GPIOA_ULPI_CK, 10U) |      \
                                     PIN_AFIO_AF(GPIOA_LCD_BL_CTRL, 0U) |   \
                                     PIN_AFIO_AF(GPIOA_RMII_CRS_DV, 11U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_MCO1, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_VBUS_FS2, 0U) |      \
                                     PIN_AFIO_AF(GPIOA_USB_FS2_ID, 10U) |   \
                                     PIN_AFIO_AF(GPIOA_USB_FS2_DM, 10U) |   \
                                     PIN_AFIO_AF(GPIOA_USB_FS2_DP, 10U) |   \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_JTDI, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - ULPI_D1                   (alternate 10).
 * PB1  - ULPI_D2                   (alternate 10).
 * PB2  - QSPI_CLK                  (alternate 9).
 * PB3  - JTDO_TRACESWO             (alternate 0).
 * PB4  - NJTRST                    (alternate 0).
 * PB5  - ULPI_D7                   (alternate 10).
 * PB6  - I2C1_SCL                  (alternate 4).
 * PB7  - I2C1_SDA                  (alternate 4).
 * PB8  - SDIO1_CKIN                (alternate 7).
 * PB9  - SDIO1_CDIR                (alternate 7).
 * PB10 - ULPI_D3                   (alternate 10).
 * PB11 - ULPI_D4                   (alternate 10).
 * PB12 - ULPI_D5                   (alternate 10).
 * PB13 - ULPI_D6                   (alternate 10).
 * PB14 - USART1_TX                 (alternate 4).
 * PB15 - USART1_RX                 (alternate 4).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_ULPI_D1) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_ULPI_D2) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_QSPI_CLK) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_JTDO_TRACESWO) |\
                                     PIN_MODE_ALTERNATE(GPIOB_NJTRST) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_ULPI_D7) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SDA) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_SDIO1_CKIN) | \
                                     PIN_MODE_ALTERNATE(GPIOB_SDIO1_CDIR) | \
                                     PIN_MODE_ALTERNATE(GPIOB_ULPI_D3) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_ULPI_D4) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_ULPI_D5) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_ULPI_D6) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_USART1_TX) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_USART1_RX))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_QSPI_CLK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_JTDO_TRACESWO) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_NJTRST) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D7) |    \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SDA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SDIO1_CKIN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SDIO1_CDIR) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D4) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D5) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ULPI_D6) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART1_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_USART1_RX))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_ULPI_D1) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ULPI_D2) |       \
                                     PIN_OSPEED_HIGH(GPIOB_QSPI_CLK) |      \
                                     PIN_OSPEED_HIGH(GPIOB_JTDO_TRACESWO) | \
                                     PIN_OSPEED_HIGH(GPIOB_NJTRST) |        \
                                     PIN_OSPEED_HIGH(GPIOB_ULPI_D7) |       \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SCL) |      \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SDA) |      \
                                     PIN_OSPEED_VERYLOW(GPIOB_SDIO1_CKIN) | \
                                     PIN_OSPEED_VERYLOW(GPIOB_SDIO1_CDIR) | \
                                     PIN_OSPEED_HIGH(GPIOB_ULPI_D3) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ULPI_D4) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ULPI_D5) |       \
                                     PIN_OSPEED_HIGH(GPIOB_ULPI_D6) |       \
                                     PIN_OSPEED_HIGH(GPIOB_USART1_TX) |     \
                                     PIN_OSPEED_HIGH(GPIOB_USART1_RX))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLUP(GPIOB_ULPI_D1) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_ULPI_D2) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_QSPI_CLK) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_JTDO_TRACESWO) |\
                                     PIN_PUPDR_PULLUP(GPIOB_NJTRST) |       \
                                     PIN_PUPDR_PULLUP(GPIOB_ULPI_D7) |      \
                                     PIN_PUPDR_PULLUP(GPIOB_I2C1_SCL) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_I2C1_SDA) |     \
                                     PIN_PUPDR_FLOATING(GPIOB_SDIO1_CKIN) | \
                                     PIN_PUPDR_FLOATING(GPIOB_SDIO1_CDIR) | \
                                     PIN_PUPDR_FLOATING(GPIOB_ULPI_D3) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_ULPI_D4) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_ULPI_D5) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_ULPI_D6) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_USART1_TX) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_USART1_RX))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_ULPI_D1) |          \
                                     PIN_ODR_HIGH(GPIOB_ULPI_D2) |          \
                                     PIN_ODR_HIGH(GPIOB_QSPI_CLK) |         \
                                     PIN_ODR_HIGH(GPIOB_JTDO_TRACESWO) |    \
                                     PIN_ODR_LOW(GPIOB_NJTRST) |            \
                                     PIN_ODR_HIGH(GPIOB_ULPI_D7) |          \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SCL) |         \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SDA) |         \
                                     PIN_ODR_HIGH(GPIOB_SDIO1_CKIN) |       \
                                     PIN_ODR_HIGH(GPIOB_SDIO1_CDIR) |       \
                                     PIN_ODR_HIGH(GPIOB_ULPI_D3) |          \
                                     PIN_ODR_HIGH(GPIOB_ULPI_D4) |          \
                                     PIN_ODR_HIGH(GPIOB_ULPI_D5) |          \
                                     PIN_ODR_HIGH(GPIOB_ULPI_D6) |          \
                                     PIN_ODR_HIGH(GPIOB_USART1_TX) |        \
                                     PIN_ODR_HIGH(GPIOB_USART1_RX))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_ULPI_D1, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_ULPI_D2, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_QSPI_CLK, 9U) |      \
                                     PIN_AFIO_AF(GPIOB_JTDO_TRACESWO, 0U) | \
                                     PIN_AFIO_AF(GPIOB_NJTRST, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_ULPI_D7, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_I2C1_SCL, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_I2C1_SDA, 4U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_SDIO1_CKIN, 7U) |    \
                                     PIN_AFIO_AF(GPIOB_SDIO1_CDIR, 7U) |    \
                                     PIN_AFIO_AF(GPIOB_ULPI_D3, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_ULPI_D4, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_ULPI_D5, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_ULPI_D6, 10U) |      \
                                     PIN_AFIO_AF(GPIOB_USART1_TX, 4U) |     \
                                     PIN_AFIO_AF(GPIOB_USART1_RX, 4U))

/*
 * GPIOC setup:
 *
 * PC0  - ULPI_STP                  (alternate 10).
 * PC1  - RMII_MDC                  (alternate 11).
 * PC2  - DFSDM_CLKOUT              (alternate 6).
 * PC3  - DFSDM_DATA1               (alternate 3).
 * PC4  - RMII_RXD0                 (alternate 11).
 * PC5  - RMII_RXD1                 (alternate 11).
 * PC6  - SDIO1_D0DIR               (alternate 8).
 * PC7  - SDIO1_D123DIR             (alternate 8).
 * PC8  - SDIO1_D0                  (alternate 12).
 * PC9  - SDIO1_D1                  (alternate 12).
 * PC10 - SDIO1_D2                  (alternate 12).
 * PC11 - SDIO1_D3                  (alternate 12).
 * PC12 - SDIO1_CLK                 (alternate 12).
 * PC13 - TAMPER_KEY                (input floating).
 * PC14 - OSC32_IN                  (input floating).
 * PC15 - OSC32_OUT                 (output pushpull minimum).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ALTERNATE(GPIOC_ULPI_STP) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_RMII_MDC) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_DFSDM_CLKOUT) |\
                                     PIN_MODE_ALTERNATE(GPIOC_DFSDM_DATA1) |\
                                     PIN_MODE_ALTERNATE(GPIOC_RMII_RXD0) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_RMII_RXD1) |  \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_D0DIR) |\
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_D123DIR) |\
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_D0) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_D1) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_D2) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_D3) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO1_CLK) |  \
                                     PIN_MODE_INPUT(GPIOC_TAMPER_KEY) |     \
                                     PIN_MODE_INPUT(GPIOC_OSC32_IN) |       \
                                     PIN_MODE_OUTPUT(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_ULPI_STP) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_RMII_MDC) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_DFSDM_CLKOUT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_DFSDM_DATA1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_RMII_RXD0) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_RMII_RXD1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_D0DIR) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_D123DIR) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_D0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_D1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_D2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_D3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO1_CLK) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_TAMPER_KEY) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_ULPI_STP) |      \
                                     PIN_OSPEED_HIGH(GPIOC_RMII_MDC) |      \
                                     PIN_OSPEED_HIGH(GPIOC_DFSDM_CLKOUT) |  \
                                     PIN_OSPEED_HIGH(GPIOC_DFSDM_DATA1) |   \
                                     PIN_OSPEED_HIGH(GPIOC_RMII_RXD0) |     \
                                     PIN_OSPEED_HIGH(GPIOC_RMII_RXD1) |     \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_D0DIR) |   \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_D123DIR) | \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_D0) |      \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_D1) |      \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_D2) |      \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_D3) |      \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO1_CLK) |     \
                                     PIN_OSPEED_HIGH(GPIOC_TAMPER_KEY) |    \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_IN) |   \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_ULPI_STP) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_RMII_MDC) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_DFSDM_CLKOUT) |\
                                     PIN_PUPDR_FLOATING(GPIOC_DFSDM_DATA1) |\
                                     PIN_PUPDR_FLOATING(GPIOC_RMII_RXD0) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_RMII_RXD1) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_D0DIR) |\
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_D123DIR) |\
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_D0) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_D1) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_D2) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_D3) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO1_CLK) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_TAMPER_KEY) | \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_ULPI_STP) |         \
                                     PIN_ODR_HIGH(GPIOC_RMII_MDC) |         \
                                     PIN_ODR_HIGH(GPIOC_DFSDM_CLKOUT) |     \
                                     PIN_ODR_HIGH(GPIOC_DFSDM_DATA1) |      \
                                     PIN_ODR_HIGH(GPIOC_RMII_RXD0) |        \
                                     PIN_ODR_HIGH(GPIOC_RMII_RXD1) |        \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_D0DIR) |      \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_D123DIR) |    \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_D0) |         \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_D1) |         \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_D2) |         \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_D3) |         \
                                     PIN_ODR_HIGH(GPIOC_SDIO1_CLK) |        \
                                     PIN_ODR_HIGH(GPIOC_TAMPER_KEY) |       \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_ULPI_STP, 10U) |     \
                                     PIN_AFIO_AF(GPIOC_RMII_MDC, 11U) |     \
                                     PIN_AFIO_AF(GPIOC_DFSDM_CLKOUT, 6U) |  \
                                     PIN_AFIO_AF(GPIOC_DFSDM_DATA1, 3U) |   \
                                     PIN_AFIO_AF(GPIOC_RMII_RXD0, 11U) |    \
                                     PIN_AFIO_AF(GPIOC_RMII_RXD1, 11U) |    \
                                     PIN_AFIO_AF(GPIOC_SDIO1_D0DIR, 8U) |   \
                                     PIN_AFIO_AF(GPIOC_SDIO1_D123DIR, 8U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SDIO1_D0, 12U) |     \
                                     PIN_AFIO_AF(GPIOC_SDIO1_D1, 12U) |     \
                                     PIN_AFIO_AF(GPIOC_SDIO1_D2, 12U) |     \
                                     PIN_AFIO_AF(GPIOC_SDIO1_D3, 12U) |     \
                                     PIN_AFIO_AF(GPIOC_SDIO1_CLK, 12U) |    \
                                     PIN_AFIO_AF(GPIOC_TAMPER_KEY, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - FMC_D2                    (alternate 12).
 * PD1  - FMC_D3                    (alternate 12).
 * PD2  - SDIO1_CMD                 (alternate 12).
 * PD3  - FDCAN1_STBY               (output pushpull maximum).
 * PD4  - FMC_NOE                   (alternate 12).
 * PD5  - FMC_NWE                   (alternate 12).
 * PD6  - FMC_NWAIT                 (alternate 12).
 * PD7  - FMC_NE1                   (alternate 12).
 * PD8  - FMC_D13                   (alternate 12).
 * PD9  - FMC_D14                   (alternate 12).
 * PD10 - FMC_D15                   (alternate 12).
 * PD11 - FMC_A16                   (alternate 12).
 * PD12 - FMC_A17                   (alternate 12).
 * PD13 - FMC_A18                   (alternate 12).
 * PD14 - FMC_D0                    (alternate 12).
 * PD15 - FMC_D1                    (alternate 12).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ALTERNATE(GPIOD_FMC_D2) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D3) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_SDIO1_CMD) |  \
                                     PIN_MODE_OUTPUT(GPIOD_FDCAN1_STBY) |   \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NOE) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NWE) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NWAIT) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_NE1) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D13) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D14) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D15) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A16) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A17) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_A18) |    \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D0) |     \
                                     PIN_MODE_ALTERNATE(GPIOD_FMC_D1))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FMC_D2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_SDIO1_CMD) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FDCAN1_STBY) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NOE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NWE) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NWAIT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_NE1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D14) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D15) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A16) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A17) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_A18) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_FMC_D1))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FMC_D2) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D3) |        \
                                     PIN_OSPEED_HIGH(GPIOD_SDIO1_CMD) |     \
                                     PIN_OSPEED_HIGH(GPIOD_FDCAN1_STBY) |   \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NOE) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NWE) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NWAIT) |     \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_NE1) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D13) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D14) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D15) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A16) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A17) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_A18) |       \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D0) |        \
                                     PIN_OSPEED_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FMC_D2) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D3) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_SDIO1_CMD) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_FDCAN1_STBY) |\
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NOE) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NWE) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NWAIT) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_NE1) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D13) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D14) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D15) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A16) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A17) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_A18) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D0) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_FMC_D1))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_FMC_D2) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D3) |           \
                                     PIN_ODR_HIGH(GPIOD_SDIO1_CMD) |        \
                                     PIN_ODR_HIGH(GPIOD_FDCAN1_STBY) |      \
                                     PIN_ODR_HIGH(GPIOD_FMC_NOE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_NWE) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_NWAIT) |        \
                                     PIN_ODR_HIGH(GPIOD_FMC_NE1) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D13) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D14) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D15) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_A16) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_A17) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_A18) |          \
                                     PIN_ODR_HIGH(GPIOD_FMC_D0) |           \
                                     PIN_ODR_HIGH(GPIOD_FMC_D1))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FMC_D2, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D3, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_SDIO1_CMD, 12U) |    \
                                     PIN_AFIO_AF(GPIOD_FDCAN1_STBY, 0U) |   \
                                     PIN_AFIO_AF(GPIOD_FMC_NOE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_NWE, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_NWAIT, 12U) |    \
                                     PIN_AFIO_AF(GPIOD_FMC_NE1, 12U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_FMC_D13, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D14, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D15, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_A16, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_A17, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_A18, 12U) |      \
                                     PIN_AFIO_AF(GPIOD_FMC_D0, 12U) |       \
                                     PIN_AFIO_AF(GPIOD_FMC_D1, 12U))

/*
 * GPIOE setup:
 *
 * PE0  - FMC_NBL0                  (alternate 12).
 * PE1  - FMC_NBL1                  (alternate 12).
 * PE2  - PDM1_CLK1                 (alternate 2).
 * PE3  - SAI1_SDB                  (alternate 6).
 * PE4  - SAI1_FSA                  (alternate 6).
 * PE5  - SAI1_SCKA                 (alternate 6).
 * PE6  - SAI1_SDA                  (alternate 6).
 * PE7  - FMC_D4                    (alternate 6).
 * PE8  - FMC_D5                    (alternate 12).
 * PE9  - FMC_D6                    (alternate 12).
 * PE10 - FMC_D7                    (alternate 12).
 * PE11 - FMC_D8                    (alternate 12).
 * PE12 - FMC_D9                    (alternate 12).
 * PE13 - FMC_D10                   (alternate 12).
 * PE14 - FMC_D11                   (alternate 12).
 * PE15 - FMC_D12                   (alternate 12).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ALTERNATE(GPIOE_FMC_NBL0) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_NBL1) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_PDM1_CLK1) |  \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_SDB) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_FSA) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_SCKA) |  \
                                     PIN_MODE_ALTERNATE(GPIOE_SAI1_SDA) |   \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D4) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D5) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D6) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D7) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D8) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D9) |     \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D10) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D11) |    \
                                     PIN_MODE_ALTERNATE(GPIOE_FMC_D12))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL0) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_NBL1) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PDM1_CLK1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_SDB) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_FSA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_SCKA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_SAI1_SDA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D9) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FMC_D12))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_FMC_NBL0) |      \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_NBL1) |      \
                                     PIN_OSPEED_HIGH(GPIOE_PDM1_CLK1) |     \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_SDB) |      \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_FSA) |      \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_SCKA) |     \
                                     PIN_OSPEED_HIGH(GPIOE_SAI1_SDA) |      \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D4) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D5) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D6) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D7) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D8) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D9) |        \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D10) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D11) |       \
                                     PIN_OSPEED_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_FMC_NBL0) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_NBL1) |   \
                                     PIN_PUPDR_PULLUP(GPIOE_PDM1_CLK1) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_SDB) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_FSA) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_SCKA) |  \
                                     PIN_PUPDR_FLOATING(GPIOE_SAI1_SDA) |   \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D4) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D5) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D6) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D7) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D8) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D9) |     \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D10) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D11) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_FMC_D12))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_FMC_NBL0) |         \
                                     PIN_ODR_HIGH(GPIOE_FMC_NBL1) |         \
                                     PIN_ODR_HIGH(GPIOE_PDM1_CLK1) |        \
                                     PIN_ODR_HIGH(GPIOE_SAI1_SDB) |         \
                                     PIN_ODR_HIGH(GPIOE_SAI1_FSA) |         \
                                     PIN_ODR_HIGH(GPIOE_SAI1_SCKA) |        \
                                     PIN_ODR_HIGH(GPIOE_SAI1_SDA) |         \
                                     PIN_ODR_HIGH(GPIOE_FMC_D4) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D5) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D6) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D7) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D8) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D9) |           \
                                     PIN_ODR_HIGH(GPIOE_FMC_D10) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D11) |          \
                                     PIN_ODR_HIGH(GPIOE_FMC_D12))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_FMC_NBL0, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_FMC_NBL1, 12U) |     \
                                     PIN_AFIO_AF(GPIOE_PDM1_CLK1, 2U) |     \
                                     PIN_AFIO_AF(GPIOE_SAI1_SDB, 6U) |      \
                                     PIN_AFIO_AF(GPIOE_SAI1_FSA, 6U) |      \
                                     PIN_AFIO_AF(GPIOE_SAI1_SCKA, 6U) |     \
                                     PIN_AFIO_AF(GPIOE_SAI1_SDA, 6U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D4, 6U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_FMC_D5, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D6, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D7, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D8, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D9, 12U) |       \
                                     PIN_AFIO_AF(GPIOE_FMC_D10, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D11, 12U) |      \
                                     PIN_AFIO_AF(GPIOE_FMC_D12, 12U))

/*
 * GPIOF setup:
 *
 * PF0  - FMC_A0                    (alternate 12).
 * PF1  - FMC_A1                    (alternate 12).
 * PF2  - FMC_A2                    (alternate 12).
 * PF3  - FMC_A3                    (alternate 12).
 * PF4  - FMC_A4                    (alternate 12).
 * PF5  - FMC_A5                    (alternate 12).
 * PF6  - QSPI_BK1_IO3              (alternate 9).
 * PF7  - QSPI_BK1_IO2              (alternate 9).
 * PF8  - QSPI_BK1_IO0              (alternate 10).
 * PF9  - QSPI_BK1_IO1              (alternate 10).
 * PF10 - DSI_RESET                 (output pushpull maximum).
 * PF11 - SDNRAS                    (alternate 12).
 * PF12 - FMC_A6                    (alternate 12).
 * PF13 - FMC_A7                    (alternate 12).
 * PF14 - FMC_A8                    (alternate 12).
 * PF15 - FMC_A9                    (alternate 12).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ALTERNATE(GPIOF_FMC_A0) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A1) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A2) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A3) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A4) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A5) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_QSPI_BK1_IO3) |\
                                     PIN_MODE_ALTERNATE(GPIOF_QSPI_BK1_IO2) |\
                                     PIN_MODE_ALTERNATE(GPIOF_QSPI_BK1_IO0) |\
                                     PIN_MODE_ALTERNATE(GPIOF_QSPI_BK1_IO1) |\
                                     PIN_MODE_OUTPUT(GPIOF_DSI_RESET) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_SDNRAS) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A6) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A7) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A8) |     \
                                     PIN_MODE_ALTERNATE(GPIOF_FMC_A9))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_FMC_A0) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A2) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A3) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A4) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A5) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_QSPI_BK1_IO3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_QSPI_BK1_IO2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_QSPI_BK1_IO0) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_QSPI_BK1_IO1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOF_DSI_RESET) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOF_SDNRAS) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A6) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A7) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A8) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOF_FMC_A9))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_FMC_A0) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A1) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A2) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A3) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A4) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A5) |        \
                                     PIN_OSPEED_HIGH(GPIOF_QSPI_BK1_IO3) |  \
                                     PIN_OSPEED_HIGH(GPIOF_QSPI_BK1_IO2) |  \
                                     PIN_OSPEED_HIGH(GPIOF_QSPI_BK1_IO0) |  \
                                     PIN_OSPEED_HIGH(GPIOF_QSPI_BK1_IO1) |  \
                                     PIN_OSPEED_HIGH(GPIOF_DSI_RESET) |     \
                                     PIN_OSPEED_HIGH(GPIOF_SDNRAS) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A6) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A7) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A8) |        \
                                     PIN_OSPEED_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_FMC_A0) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A1) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A2) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A3) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A4) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A5) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_QSPI_BK1_IO3) |\
                                     PIN_PUPDR_FLOATING(GPIOF_QSPI_BK1_IO2) |\
                                     PIN_PUPDR_FLOATING(GPIOF_QSPI_BK1_IO0) |\
                                     PIN_PUPDR_FLOATING(GPIOF_QSPI_BK1_IO1) |\
                                     PIN_PUPDR_FLOATING(GPIOF_DSI_RESET) |  \
                                     PIN_PUPDR_FLOATING(GPIOF_SDNRAS) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A6) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A7) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A8) |     \
                                     PIN_PUPDR_FLOATING(GPIOF_FMC_A9))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_FMC_A0) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A1) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A2) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A3) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A4) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A5) |           \
                                     PIN_ODR_HIGH(GPIOF_QSPI_BK1_IO3) |     \
                                     PIN_ODR_HIGH(GPIOF_QSPI_BK1_IO2) |     \
                                     PIN_ODR_HIGH(GPIOF_QSPI_BK1_IO0) |     \
                                     PIN_ODR_HIGH(GPIOF_QSPI_BK1_IO1) |     \
                                     PIN_ODR_HIGH(GPIOF_DSI_RESET) |        \
                                     PIN_ODR_HIGH(GPIOF_SDNRAS) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A6) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A7) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A8) |           \
                                     PIN_ODR_HIGH(GPIOF_FMC_A9))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_FMC_A0, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A1, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A2, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A3, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A4, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A5, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_QSPI_BK1_IO3, 9U) |  \
                                     PIN_AFIO_AF(GPIOF_QSPI_BK1_IO2, 9U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_QSPI_BK1_IO0, 10U) | \
                                     PIN_AFIO_AF(GPIOF_QSPI_BK1_IO1, 10U) | \
                                     PIN_AFIO_AF(GPIOF_DSI_RESET, 0U) |     \
                                     PIN_AFIO_AF(GPIOF_SDNRAS, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A6, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A7, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A8, 12U) |       \
                                     PIN_AFIO_AF(GPIOF_FMC_A9, 12U))

/*
 * GPIOG setup:
 *
 * PG0  - FMC_A10                   (alternate 12).
 * PG1  - FMC_A11                   (alternate 12).
 * PG2  - FMC_A12                   (alternate 12).
 * PG3  - FMC_A13                   (alternate 12).
 * PG4  - FMC_A14                   (alternate 12).
 * PG5  - FMC_A15                   (alternate 12).
 * PG6  - QSPI_BK1_NCS              (alternate 10).
 * PG7  - SAI1_MCLKA                (alternate 6).
 * PG8  - SDCLK                     (alternate 12).
 * PG9  - QSPI_BK2_IO2              (alternate 9).
 * PG10 - FMC_NE3                   (alternate 12).
 * PG11 - RMII_TX_EN                (alternate 11).
 * PG12 - RMII_TXD1                 (alternate 11).
 * PG13 - RMII_TXD0                 (alternate 11).
 * PG14 - QSPI_BK2_IO3              (alternate 9).
 * PG15 - SDNCAS                    (alternate 12).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ALTERNATE(GPIOG_FMC_A10) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A11) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A12) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A13) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A14) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_A15) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_QSPI_BK1_NCS) |\
                                     PIN_MODE_ALTERNATE(GPIOG_SAI1_MCLKA) | \
                                     PIN_MODE_ALTERNATE(GPIOG_SDCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOG_QSPI_BK2_IO2) |\
                                     PIN_MODE_ALTERNATE(GPIOG_FMC_NE3) |    \
                                     PIN_MODE_ALTERNATE(GPIOG_RMII_TX_EN) | \
                                     PIN_MODE_ALTERNATE(GPIOG_RMII_TXD1) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_RMII_TXD0) |  \
                                     PIN_MODE_ALTERNATE(GPIOG_QSPI_BK2_IO3) |\
                                     PIN_MODE_ALTERNATE(GPIOG_SDNCAS))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_FMC_A10) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A11) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A12) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A13) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A14) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_A15) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_QSPI_BK1_NCS) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_SAI1_MCLKA) | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_SDCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_QSPI_BK2_IO2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_FMC_NE3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOG_RMII_TX_EN) | \
                                     PIN_OTYPE_PUSHPULL(GPIOG_RMII_TXD1) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_RMII_TXD0) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOG_QSPI_BK2_IO3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOG_SDNCAS))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_FMC_A10) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A11) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A12) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A13) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A14) |       \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_A15) |       \
                                     PIN_OSPEED_HIGH(GPIOG_QSPI_BK1_NCS) |  \
                                     PIN_OSPEED_HIGH(GPIOG_SAI1_MCLKA) |    \
                                     PIN_OSPEED_HIGH(GPIOG_SDCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOG_QSPI_BK2_IO2) |  \
                                     PIN_OSPEED_HIGH(GPIOG_FMC_NE3) |       \
                                     PIN_OSPEED_HIGH(GPIOG_RMII_TX_EN) |    \
                                     PIN_OSPEED_HIGH(GPIOG_RMII_TXD1) |     \
                                     PIN_OSPEED_HIGH(GPIOG_RMII_TXD0) |     \
                                     PIN_OSPEED_HIGH(GPIOG_QSPI_BK2_IO3) |  \
                                     PIN_OSPEED_HIGH(GPIOG_SDNCAS))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_FMC_A10) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A11) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A12) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A13) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A14) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_A15) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_QSPI_BK1_NCS) |\
                                     PIN_PUPDR_PULLUP(GPIOG_SAI1_MCLKA) |   \
                                     PIN_PUPDR_FLOATING(GPIOG_SDCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_QSPI_BK2_IO2) |\
                                     PIN_PUPDR_FLOATING(GPIOG_FMC_NE3) |    \
                                     PIN_PUPDR_FLOATING(GPIOG_RMII_TX_EN) | \
                                     PIN_PUPDR_FLOATING(GPIOG_RMII_TXD1) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_RMII_TXD0) |  \
                                     PIN_PUPDR_FLOATING(GPIOG_QSPI_BK2_IO3) |\
                                     PIN_PUPDR_FLOATING(GPIOG_SDNCAS))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_FMC_A10) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A11) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A12) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A13) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A14) |          \
                                     PIN_ODR_HIGH(GPIOG_FMC_A15) |          \
                                     PIN_ODR_HIGH(GPIOG_QSPI_BK1_NCS) |     \
                                     PIN_ODR_HIGH(GPIOG_SAI1_MCLKA) |       \
                                     PIN_ODR_HIGH(GPIOG_SDCLK) |            \
                                     PIN_ODR_HIGH(GPIOG_QSPI_BK2_IO2) |     \
                                     PIN_ODR_HIGH(GPIOG_FMC_NE3) |          \
                                     PIN_ODR_HIGH(GPIOG_RMII_TX_EN) |       \
                                     PIN_ODR_HIGH(GPIOG_RMII_TXD1) |        \
                                     PIN_ODR_HIGH(GPIOG_RMII_TXD0) |        \
                                     PIN_ODR_HIGH(GPIOG_QSPI_BK2_IO3) |     \
                                     PIN_ODR_HIGH(GPIOG_SDNCAS))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_FMC_A10, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A11, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A12, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A13, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A14, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_FMC_A15, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_QSPI_BK1_NCS, 10U) | \
                                     PIN_AFIO_AF(GPIOG_SAI1_MCLKA, 6U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_SDCLK, 12U) |        \
                                     PIN_AFIO_AF(GPIOG_QSPI_BK2_IO2, 9U) |  \
                                     PIN_AFIO_AF(GPIOG_FMC_NE3, 12U) |      \
                                     PIN_AFIO_AF(GPIOG_RMII_TX_EN, 11U) |   \
                                     PIN_AFIO_AF(GPIOG_RMII_TXD1, 11U) |    \
                                     PIN_AFIO_AF(GPIOG_RMII_TXD0, 11U) |    \
                                     PIN_AFIO_AF(GPIOG_QSPI_BK2_IO3, 9U) |  \
                                     PIN_AFIO_AF(GPIOG_SDNCAS, 12U))

/*
 * GPIOH setup:
 *
 * PH0  - OSCIN                     (analog).
 * PH1  - OSCOUT                    (analog).
 * PH2  - QSPI_BK2_IO0              (alternate 9).
 * PH3  - QSPI_BK2_IO1              (alternate 9).
 * PH4  - ULPI_NXT                  (alternate 10).
 * PH5  - SDNWE                     (alternate 12).
 * PH6  - SDNE1                     (alternate 12).
 * PH7  - SDCKE1                    (alternate 12).
 * PH8  - FMC_D16                   (alternate 12).
 * PH9  - FMC_D17                   (alternate 12).
 * PH10 - FMC_D18                   (alternate 12).
 * PH11 - FMC_D19                   (alternate 12).
 * PH12 - FMC_D20                   (alternate 12).
 * PH13 - FMC_D21                   (alternate 12).
 * PH14 - FMC_D22                   (alternate 12).
 * PH15 - FMC_D23                   (alternate 12).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_ANALOG(GPIOH_OSCIN) |         \
                                     PIN_MODE_ANALOG(GPIOH_OSCOUT) |        \
                                     PIN_MODE_ALTERNATE(GPIOH_QSPI_BK2_IO0) |\
                                     PIN_MODE_ALTERNATE(GPIOH_QSPI_BK2_IO1) |\
                                     PIN_MODE_ALTERNATE(GPIOH_ULPI_NXT) |   \
                                     PIN_MODE_ALTERNATE(GPIOH_SDNWE) |      \
                                     PIN_MODE_ALTERNATE(GPIOH_SDNE1) |      \
                                     PIN_MODE_ALTERNATE(GPIOH_SDCKE1) |     \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D16) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D17) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D18) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D19) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D20) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D21) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D22) |    \
                                     PIN_MODE_ALTERNATE(GPIOH_FMC_D23))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSCIN) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSCOUT) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_QSPI_BK2_IO0) |\
                                     PIN_OTYPE_PUSHPULL(GPIOH_QSPI_BK2_IO1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOH_ULPI_NXT) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOH_SDNWE) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_SDNE1) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_SDCKE1) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D16) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D17) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D18) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D19) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D20) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D21) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D22) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_FMC_D23))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOH_OSCIN) |      \
                                     PIN_OSPEED_VERYLOW(GPIOH_OSCOUT) |     \
                                     PIN_OSPEED_HIGH(GPIOH_QSPI_BK2_IO0) |  \
                                     PIN_OSPEED_HIGH(GPIOH_QSPI_BK2_IO1) |  \
                                     PIN_OSPEED_HIGH(GPIOH_ULPI_NXT) |      \
                                     PIN_OSPEED_HIGH(GPIOH_SDNWE) |         \
                                     PIN_OSPEED_HIGH(GPIOH_SDNE1) |         \
                                     PIN_OSPEED_HIGH(GPIOH_SDCKE1) |        \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D16) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D17) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D18) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D19) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D20) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D21) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D22) |       \
                                     PIN_OSPEED_HIGH(GPIOH_FMC_D23))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSCIN) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_OSCOUT) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_QSPI_BK2_IO0) |\
                                     PIN_PUPDR_FLOATING(GPIOH_QSPI_BK2_IO1) |\
                                     PIN_PUPDR_FLOATING(GPIOH_ULPI_NXT) |   \
                                     PIN_PUPDR_FLOATING(GPIOH_SDNWE) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_SDNE1) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_SDCKE1) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D16) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D17) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D18) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D19) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D20) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D21) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D22) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_FMC_D23))
#define VAL_GPIOH_ODR               (PIN_ODR_LOW(GPIOH_OSCIN) |             \
                                     PIN_ODR_LOW(GPIOH_OSCOUT) |            \
                                     PIN_ODR_HIGH(GPIOH_QSPI_BK2_IO0) |     \
                                     PIN_ODR_HIGH(GPIOH_QSPI_BK2_IO1) |     \
                                     PIN_ODR_HIGH(GPIOH_ULPI_NXT) |         \
                                     PIN_ODR_HIGH(GPIOH_SDNWE) |            \
                                     PIN_ODR_HIGH(GPIOH_SDNE1) |            \
                                     PIN_ODR_HIGH(GPIOH_SDCKE1) |           \
                                     PIN_ODR_HIGH(GPIOH_FMC_D16) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D17) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D18) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D19) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D20) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D21) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D22) |          \
                                     PIN_ODR_HIGH(GPIOH_FMC_D23))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSCIN, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_OSCOUT, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_QSPI_BK2_IO0, 9U) |  \
                                     PIN_AFIO_AF(GPIOH_QSPI_BK2_IO1, 9U) |  \
                                     PIN_AFIO_AF(GPIOH_ULPI_NXT, 10U) |     \
                                     PIN_AFIO_AF(GPIOH_SDNWE, 12U) |        \
                                     PIN_AFIO_AF(GPIOH_SDNE1, 12U) |        \
                                     PIN_AFIO_AF(GPIOH_SDCKE1, 12U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_FMC_D16, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D17, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D18, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D19, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D20, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D21, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D22, 12U) |      \
                                     PIN_AFIO_AF(GPIOH_FMC_D23, 12U))

/*
 * GPIOI setup:
 *
 * PI0  - FMC_D24                   (alternate 12).
 * PI1  - FMC_D25                   (alternate 12).
 * PI2  - FMC_D26                   (alternate 12).
 * PI3  - FMC_D27                   (alternate 12).
 * PI4  - FMC_NBL2                  (alternate 12).
 * PI5  - FMC_NBL3                  (alternate 12).
 * PI6  - FMC_D28                   (alternate 12).
 * PI7  - FMC_D29                   (alternate 12).
 * PI8  - EXPANDER_INT              (input pullup).
 * PI9  - FMC_D30                   (alternate 12).
 * PI10 - FMC_D31                   (alternate 12).
 * PI11 - ULPI_DIR                  (alternate 10).
 * PI12 - PIN12                     (input floating).
 * PI13 - PIN13                     (input floating).
 * PI14 - PIN14                     (input floating).
 * PI15 - PIN15                     (input floating).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_ALTERNATE(GPIOI_FMC_D24) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D25) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D26) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D27) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_NBL2) |   \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_NBL3) |   \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D28) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D29) |    \
                                     PIN_MODE_INPUT(GPIOI_EXPANDER_INT) |   \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D30) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_FMC_D31) |    \
                                     PIN_MODE_ALTERNATE(GPIOI_ULPI_DIR) |   \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_FMC_D24) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D25) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D26) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D27) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_NBL2) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_NBL3) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D28) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D29) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_EXPANDER_INT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D30) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_FMC_D31) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOI_ULPI_DIR) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_FMC_D24) |       \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D25) |       \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D26) |       \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D27) |       \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_NBL2) |      \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_NBL3) |      \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D28) |       \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D29) |       \
                                     PIN_OSPEED_VERYLOW(GPIOI_EXPANDER_INT) |\
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D30) |       \
                                     PIN_OSPEED_HIGH(GPIOI_FMC_D31) |       \
                                     PIN_OSPEED_HIGH(GPIOI_ULPI_DIR) |      \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_FMC_D24) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D25) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D26) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D27) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_NBL2) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_NBL3) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D28) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D29) |    \
                                     PIN_PUPDR_PULLUP(GPIOI_EXPANDER_INT) | \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D30) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_FMC_D31) |    \
                                     PIN_PUPDR_FLOATING(GPIOI_ULPI_DIR) |   \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_FMC_D24) |          \
                                     PIN_ODR_HIGH(GPIOI_FMC_D25) |          \
                                     PIN_ODR_HIGH(GPIOI_FMC_D26) |          \
                                     PIN_ODR_HIGH(GPIOI_FMC_D27) |          \
                                     PIN_ODR_HIGH(GPIOI_FMC_NBL2) |         \
                                     PIN_ODR_HIGH(GPIOI_FMC_NBL3) |         \
                                     PIN_ODR_HIGH(GPIOI_FMC_D28) |          \
                                     PIN_ODR_HIGH(GPIOI_FMC_D29) |          \
                                     PIN_ODR_HIGH(GPIOI_EXPANDER_INT) |     \
                                     PIN_ODR_HIGH(GPIOI_FMC_D30) |          \
                                     PIN_ODR_HIGH(GPIOI_FMC_D31) |          \
                                     PIN_ODR_HIGH(GPIOI_ULPI_DIR) |         \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_FMC_D24, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_FMC_D25, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_FMC_D26, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_FMC_D27, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_FMC_NBL2, 12U) |     \
                                     PIN_AFIO_AF(GPIOI_FMC_NBL3, 12U) |     \
                                     PIN_AFIO_AF(GPIOI_FMC_D28, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_FMC_D29, 12U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_EXPANDER_INT, 0U) |  \
                                     PIN_AFIO_AF(GPIOI_FMC_D30, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_FMC_D31, 12U) |      \
                                     PIN_AFIO_AF(GPIOI_ULPI_DIR, 10U) |     \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*
 * GPIOJ setup:
 *
 * PJ0  - PIN0                      (input floating).
 * PJ1  - PIN1                      (input floating).
 * PJ2  - DSI_TE                    (alternate 13).
 * PJ3  - PIN3                      (input floating).
 * PJ4  - PIN4                      (input floating).
 * PJ5  - PIN5                      (input floating).
 * PJ6  - PIN6                      (input floating).
 * PJ7  - TRGIN                     (alternate 0).
 * PJ8  - PIN8                      (input floating).
 * PJ9  - PIN9                      (input floating).
 * PJ10 - PIN10                     (input floating).
 * PJ11 - PIN11                     (input floating).
 * PJ12 - TRGOUT                    (alternate 0).
 * PJ13 - PIN13                     (input floating).
 * PJ14 - PIN14                     (input floating).
 * PJ15 - PIN15                     (input floating).
 */
#define VAL_GPIOJ_MODER             (PIN_MODE_INPUT(GPIOJ_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN1) |           \
                                     PIN_MODE_ALTERNATE(GPIOJ_DSI_TE) |     \
                                     PIN_MODE_INPUT(GPIOJ_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN6) |           \
                                     PIN_MODE_ALTERNATE(GPIOJ_TRGIN) |      \
                                     PIN_MODE_INPUT(GPIOJ_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOJ_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN11) |          \
                                     PIN_MODE_ALTERNATE(GPIOJ_TRGOUT) |     \
                                     PIN_MODE_INPUT(GPIOJ_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOJ_PIN15))
#define VAL_GPIOJ_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOJ_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_DSI_TE) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_TRGIN) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_TRGOUT) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOJ_PIN15))
#define VAL_GPIOJ_OSPEEDR           (PIN_OSPEED_HIGH(GPIOJ_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_DSI_TE) |        \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_TRGIN) |         \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOJ_TRGOUT) |        \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOJ_PIN15))
#define VAL_GPIOJ_PUPDR             (PIN_PUPDR_FLOATING(GPIOJ_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_DSI_TE) |     \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_TRGIN) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_TRGOUT) |     \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOJ_PIN15))
#define VAL_GPIOJ_ODR               (PIN_ODR_HIGH(GPIOJ_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOJ_DSI_TE) |           \
                                     PIN_ODR_HIGH(GPIOJ_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOJ_TRGIN) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOJ_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOJ_TRGOUT) |           \
                                     PIN_ODR_HIGH(GPIOJ_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOJ_PIN15))
#define VAL_GPIOJ_AFRL              (PIN_AFIO_AF(GPIOJ_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_DSI_TE, 13U) |       \
                                     PIN_AFIO_AF(GPIOJ_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_TRGIN, 0U))
#define VAL_GPIOJ_AFRH              (PIN_AFIO_AF(GPIOJ_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOJ_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_TRGOUT, 0U) |        \
                                     PIN_AFIO_AF(GPIOJ_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOJ_PIN15, 0U))

/*
 * GPIOK setup:
 *
 * PK0  - PIN0                      (input floating).
 * PK1  - PIN1                      (input floating).
 * PK2  - PIN2                      (input floating).
 * PK3  - LED1                      (output pushpull maximum).
 * PK4  - LED2                      (output pushpull maximum).
 * PK5  - LED3                      (output pushpull maximum).
 * PK6  - LED4                      (output pushpull maximum).
 * PK7  - PIN7                      (input floating).
 * PK8  - PIN8                      (input pullup).
 * PK9  - PIN9                      (input pullup).
 * PK10 - PIN10                     (input pullup).
 * PK11 - PIN11                     (input pullup).
 * PK12 - PIN12                     (input pullup).
 * PK13 - PIN13                     (input pullup).
 * PK14 - PIN14                     (input pullup).
 * PK15 - PIN15                     (input pullup).
 */
#define VAL_GPIOK_MODER             (PIN_MODE_INPUT(GPIOK_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN2) |           \
                                     PIN_MODE_OUTPUT(GPIOK_LED1) |          \
                                     PIN_MODE_OUTPUT(GPIOK_LED2) |          \
                                     PIN_MODE_OUTPUT(GPIOK_LED3) |          \
                                     PIN_MODE_OUTPUT(GPIOK_LED4) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOK_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOK_PIN15))
#define VAL_GPIOK_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOK_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_LED1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_LED2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_LED3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_LED4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOK_PIN15))
#define VAL_GPIOK_OSPEEDR           (PIN_OSPEED_HIGH(GPIOK_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOK_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOK_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOK_LED1) |          \
                                     PIN_OSPEED_HIGH(GPIOK_LED2) |          \
                                     PIN_OSPEED_HIGH(GPIOK_LED3) |          \
                                     PIN_OSPEED_HIGH(GPIOK_LED4) |          \
                                     PIN_OSPEED_HIGH(GPIOK_PIN7) |          \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN14) |      \
                                     PIN_OSPEED_VERYLOW(GPIOK_PIN15))
#define VAL_GPIOK_PUPDR             (PIN_PUPDR_FLOATING(GPIOK_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN2) |       \
                                     PIN_PUPDR_PULLUP(GPIOK_LED1) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_LED2) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_LED3) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_LED4) |         \
                                     PIN_PUPDR_FLOATING(GPIOK_PIN7) |       \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOK_PIN15))
#define VAL_GPIOK_ODR               (PIN_ODR_HIGH(GPIOK_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOK_LED1) |             \
                                     PIN_ODR_HIGH(GPIOK_LED2) |             \
                                     PIN_ODR_HIGH(GPIOK_LED3) |             \
                                     PIN_ODR_HIGH(GPIOK_LED4) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOK_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOK_PIN15))
#define VAL_GPIOK_AFRL              (PIN_AFIO_AF(GPIOK_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_LED1, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_LED2, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_LED3, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_LED4, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN7, 0U))
#define VAL_GPIOK_AFRH              (PIN_AFIO_AF(GPIOK_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOK_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOK_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
