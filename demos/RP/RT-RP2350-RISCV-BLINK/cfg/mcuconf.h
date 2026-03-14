/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio

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

#ifndef MCUCONF_H
#define MCUCONF_H

/*
 * RP2350 RISC-V (Hazard3) drivers configuration.
 *
 * This is a minimal configuration for the LED blink demo.
 */

#define RP2350_MCUCONF

/*
 * HAL driver system settings.
 */
#define RP_NO_INIT                          FALSE
#define RP_CORE1_START                      TRUE

/*
 * SIO driver system settings.
 */
#define RP_SIO_USE_UART0                    TRUE
#define RP_SIO_USE_UART1                    FALSE

/*
 * SPI driver system settings.
 */
#define RP_SPI_USE_SPI0                     FALSE
#define RP_SPI_USE_SPI1                     FALSE

/*
 * IRQ priorities (required even if drivers are disabled).
 * Hazard3 uses 4 priority levels (0-3, lower = lower priority).
 */
#define RP_IRQ_UART0_PRIORITY               2
#define RP_IRQ_UART1_PRIORITY               2
#define RP_IRQ_SPI0_PRIORITY                2
#define RP_IRQ_SPI1_PRIORITY                2
#define RP_IRQ_I2C0_PRIORITY                2
#define RP_IRQ_I2C1_PRIORITY                2
#define RP_IRQ_DMA_PRIORITY                 2
#define RP_IRQ_USB_PRIORITY                 2
#define RP_IRQ_TIMER0_PRIORITY              3
#define RP_IRQ_TIMER1_PRIORITY              3

#endif /* MCUCONF_H */
