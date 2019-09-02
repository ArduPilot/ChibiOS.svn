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
                tst.w       lr, #8
                beq.n       .normal_hf
                mrs         r3, CONTROL
                tst.w       r3, #1
                bne.w       .exit_thd
.normal_hf:     ldr         r3, =HardFault_Handler_SB
                bx          r3

                .align      2
                .thumb_func
                .global     MemManage_Handler
MemManage_Handler:
                tst.w       lr, #8
                beq.n       .normal_mm
                mrs         r3, CONTROL
                tst.w       r3, #1
                bne.w       .exit_thd
.normal_mm:     ldr         r3, =MemManage_Handler_SB
                bx          r3

                .align      2
                .thumb_func
                .global     BusFault_Handler
BusFault_Handler:
                tst.w       lr, #8
                beq.n       .normal_bf
                mrs         r3, CONTROL
                tst.w       r3, #1
                bne.w       .exit_thd
.normal_bf:     ldr         r3, =BusFault_Handler_SB
                bx          r3

                .align      2
                .thumb_func
                .global     UsageFault_Handler
UsageFault_Handler:
                tst.w       lr, #8
                beq.n       .normal_uf
                mrs         r3, CONTROL
                tst.w       r3, #1
                bne.w       .exit_thd
.normal_uf:     ldr         r3, =UsageFault_Handler_SB
                bx          r3

/*
 * Common thread-exit handler on exception.
 * Makes the current exception return on chThdExit() with the PSR
 * value as exit message.
 */
.exit_thd:
                /* Back to privileged mode.*/
                mrs         r3, CONTROL
                bic.w       r3, #1
                msr         CONTROL, r3
                mrs         r3, PSP
                /* PSR value is the exit message.*/
                mrs         r2, PSR
                str         r2, [r3, #0]
                /* Forcing return on exit syscall code.*/
                ldr         r2, =.do_exit
                str         r2, [r3, #24]
                bx          lr
.do_exit:
                /* TODO: Restore S_PSP stack.*/
                bl          chThdExit
.here:          b           .here

                .align      2
                .thumb_func
                .weak       HardFault_Handler_SB
                .weak       MemManage_Handler_SB
                .weak       BusFault_Handler_SB
                .weak       UsageFault_Handler_SB
HardFault_Handler_SB:
MemManage_Handler_SB:
BusFault_Handler_SB:
UsageFault_Handler_SB:
                ldr         r3, =_unhandled_exception
                bx          r3

#endif /* !defined(__DOXYGEN__) */

/** @} */
