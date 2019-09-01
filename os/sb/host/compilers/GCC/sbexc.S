/*
    ChibiOS - Copyright (C) 2006..2019 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    sb/sbexc.S
 * @brief   Exception handlers for sandbox.
 *
 * @defgroup ARMV7M_SANDBOX_EXCEPTIONS SandBox Exception Vectors
 * @{
 */

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Code section.                                                             */
/*===========================================================================*/

#if !defined(__DOXYGEN__)

                .syntax unified
                .cpu    cortex-m3
                .thumb

                .text

                .align      2
                .thumb_func
                .global     HardFault_Handler
HardFault_Handler:
                mrs         r0, CONTROL
                ands.w      r0, r0, #1
                bne         .exit_thd
                bl          HardFault_Handler_SB

                .align      2
                .thumb_func
                .global     MemManage_Handler
MemManage_Handler:
                mrs         r0, CONTROL
                ands.w      r0, r0, #1
                bne         .exit_thd
                bl          MemManage_Handler_SB

                .align      2
                .thumb_func
                .global     BusFault_Handler
BusFault_Handler:
                mrs         r0, CONTROL
                ands.w      r0, r0, #1
                bne         .exit_thd
                bl          BusFault_Handler_SB

                .align      2
                .thumb_func
                .global     UsageFault_Handler
UsageFault_Handler:
                mrs         r0, CONTROL
                ands.w      r0, r0, #1
                bne         .exit_thd
                bl          UsageFault_Handler_SB

.exit_thd:
                bl          _unhandled_exception

                .align      2
                .thumb_func
                .weak       HardFault_Handler_SB
HardFault_Handler_SB:
                bl          _unhandled_exception

                .align      2
                .thumb_func
                .weak       MemManage_Handler_SB
MemManage_Handler_SB:
                bl          _unhandled_exception

                .align      2
                .thumb_func
                .weak       BusFault_Handler_SB
BusFault_Handler_SB:
                bl          _unhandled_exception

                .align      2
                .thumb_func
                .weak       UsageFault_Handler_SB
UsageFault_Handler_SB:
                bl          _unhandled_exception

#endif /* !defined(__DOXYGEN__) */

/** @} */
