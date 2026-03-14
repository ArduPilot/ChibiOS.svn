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

/**
 * @file    vectors_hazard3.S
 * @brief   RISC-V Hazard3 trap vector and handler for ChibiOS.
 *
 * @addtogroup RISCV_HAZARD3_GCC_VECTORS
 * @{
 */

#define _FROM_ASM_
#include "rvparams.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/* Stack frame: 16 caller-saved regs + mepc + mcause + mstatus + pad = 20 words.
   20 * 4 = 80 bytes (16-byte aligned). */
#define TRAP_FRAME_SIZE             (20 * 4)

/* Offsets within trap frame */
#define TRAP_FRAME_RA               0
#define TRAP_FRAME_T0               4
#define TRAP_FRAME_T1               8
#define TRAP_FRAME_T2               12
#define TRAP_FRAME_A0               16
#define TRAP_FRAME_A1               20
#define TRAP_FRAME_A2               24
#define TRAP_FRAME_A3               28
#define TRAP_FRAME_A4               32
#define TRAP_FRAME_A5               36
#define TRAP_FRAME_A6               40
#define TRAP_FRAME_A7               44
#define TRAP_FRAME_T3               48
#define TRAP_FRAME_T4               52
#define TRAP_FRAME_T5               56
#define TRAP_FRAME_T6               60
#define TRAP_FRAME_MEPC             64
#define TRAP_FRAME_MCAUSE           68
#define TRAP_FRAME_MSTATUS          72

/*===========================================================================*/
/* Code section.                                                             */
/*===========================================================================*/

#if !defined(__DOXYGEN__)

                .section .vectors, "ax", @progbits
                .balign 4
                .globl  _vectors
                .type   _vectors, @function

/*
 * RISC-V trap vector entry point.
 * This is the single entry point for all traps (exceptions and interrupts).
 * The mtvec CSR points here with mode = Direct (0).
 *
 * ISR stack switching: mscratch holds the ISR stack top (set by CRT0 and
 * port_init). For interrupts, after saving the trap frame on the thread
 * stack, sp is swapped with mscratch to run handlers on the ISR stack.
 */
_vectors:
                addi    sp, sp, -TRAP_FRAME_SIZE

                /* Save registers */
                sw      ra, TRAP_FRAME_RA(sp)
                sw      t0, TRAP_FRAME_T0(sp)
                sw      t1, TRAP_FRAME_T1(sp)
                sw      t2, TRAP_FRAME_T2(sp)
                sw      a0, TRAP_FRAME_A0(sp)
                sw      a1, TRAP_FRAME_A1(sp)
                sw      a2, TRAP_FRAME_A2(sp)
                sw      a3, TRAP_FRAME_A3(sp)
                sw      a4, TRAP_FRAME_A4(sp)
                sw      a5, TRAP_FRAME_A5(sp)
                sw      a6, TRAP_FRAME_A6(sp)
                sw      a7, TRAP_FRAME_A7(sp)
                sw      t3, TRAP_FRAME_T3(sp)
                sw      t4, TRAP_FRAME_T4(sp)
                sw      t5, TRAP_FRAME_T5(sp)
                sw      t6, TRAP_FRAME_T6(sp)

                /* Save mepc, mcause and mstatus */
                csrr    t0, mepc
                csrr    t1, mcause
                csrr    t2, mstatus
                sw      t0, TRAP_FRAME_MEPC(sp)
                sw      t1, TRAP_FRAME_MCAUSE(sp)
                sw      t2, TRAP_FRAME_MSTATUS(sp)

                /* Check if this is an interrupt */
                bltz    t1, .Lis_interrupt

                /* It's an exception - stay on thread stack, call handler */
                mv      a0, t1                  /* mcause as first argument */
                csrr    a1, mtval               /* mtval as second argument */
                mv      a2, sp                  /* trap frame pointer */
                call    _exception_handler
                j       .Ltrap_restore

.Lis_interrupt:
                csrrw   sp, mscratch, sp

                /* Dispatch by interrupt type t1 still contains mcause */
                andi    a0, t1, 0x7FF           /* Mask off interrupt */

                li      t2, 7
                beq     a0, t2, .Ltimer_interrupt

                li      t2, 11
                beq     a0, t2, .Lexternal_interrupt

                li      t2, 3
                beq     a0, t2, .Lsoftware_interrupt

                /* Unknown interrupt so call unhandled handler */
                call    _unhandled_interrupt
                j       .Lisr_done

.Ltimer_interrupt:
                call    _timer_interrupt_handler
                j       .Lisr_done

.Lexternal_interrupt:
                /* Clear mreteirq so mret doesn't pop Xh3irq priority stack. */
                csrw    0xBE5, zero

                /* If the next pending IRQ is the SIO FIFO (IRQ 25), handle it
                   via a direct call to VectorA4, bypassing the general dispatch
                   table lookup else fall through to the general handler. */
                csrr    a0, 0xBE4               /* Read MEINEXT (no update) */
                bltz    a0, .Lisr_done          /* NOIRQ (bit 31) → done */

                srli    a1, a0, 2               /* Extract IRQ number [10:2] */
                andi    a1, a1, 0x1FF
                li      a2, 25                  /* SIO FIFO IRQ */
                bne     a1, a2, .Lext_general

                /* Direct call to FIFO handler as a performance optimisation.
                   VectorA4 drains the FIFO, clearing the IRQ 25 source. */
                call    VectorA4

                /* Check for more pending external IRQs after FIFO handling. */
                csrr    a0, 0xBE4               /* Read MEINEXT */
                bltz    a0, .Lisr_done

                /* More IRQs pending — general handler processes remaining. */
.Lext_general:
                call    _external_interrupt_handler
                j       .Lisr_done

.Lsoftware_interrupt:
                call    _software_interrupt_handler

.Lisr_done:
                /* Switch back to thread stack for preemption check and
                   trap frame restore. */
                csrrw   sp, mscratch, sp

.Ltrap_restore:
                /* Inline preemption pending check. This avoids function call
                   overhead on every interrupt return. */
                lui     a0, 0xD0000
                lw      a0, 0(a0)             /* SIO->CPUID (0 or 1) */
                la      a1, port_preemption_pending
                add     a0, a0, a1
                lbu     a0, 0(a0)
                beqz    a0, .Lno_preemption

                /* Preemption is needed - call the switch function. */
                call    __port_switch_from_isr

.Lno_preemption:
                /* Restore mstatus */
                lw      t0, TRAP_FRAME_MSTATUS(sp)
                csrw    mstatus, t0

                /* Restore mepc */
                lw      t0, TRAP_FRAME_MEPC(sp)
                csrw    mepc, t0

                /* Restore saved registers */
                lw      ra, TRAP_FRAME_RA(sp)
                lw      t0, TRAP_FRAME_T0(sp)
                lw      t1, TRAP_FRAME_T1(sp)
                lw      t2, TRAP_FRAME_T2(sp)
                lw      a0, TRAP_FRAME_A0(sp)
                lw      a1, TRAP_FRAME_A1(sp)
                lw      a2, TRAP_FRAME_A2(sp)
                lw      a3, TRAP_FRAME_A3(sp)
                lw      a4, TRAP_FRAME_A4(sp)
                lw      a5, TRAP_FRAME_A5(sp)
                lw      a6, TRAP_FRAME_A6(sp)
                lw      a7, TRAP_FRAME_A7(sp)
                lw      t3, TRAP_FRAME_T3(sp)
                lw      t4, TRAP_FRAME_T4(sp)
                lw      t5, TRAP_FRAME_T5(sp)
                lw      t6, TRAP_FRAME_T6(sp)

                /* Restore stack pointer */
                addi    sp, sp, TRAP_FRAME_SIZE

                /* Return from trap */
                mret

                .size   _vectors, . - _vectors

/*===========================================================================*/
/* Default weak handlers.                                                    */
/*===========================================================================*/

                .section .text, "ax", @progbits

                /* Reset handler, jumps to C runtime entry */
                .globl  Reset_Handler
                .weak   Reset_Handler
                .type   Reset_Handler, @function
Reset_Handler:
                j       _crt0_entry
                .size   Reset_Handler, . - Reset_Handler

                /* Default exception handler */
                .globl  _exception_handler
                .weak   _exception_handler
                .type   _exception_handler, @function
_exception_handler:
                /* Arguments: a0 = mcause, a1 = mtval, a2 = trap_frame */
                j       _unhandled_exception
                .size   _exception_handler, . - _exception_handler

                /* Default timer interrupt handler */
                .globl  _timer_interrupt_handler
                .weak   _timer_interrupt_handler
                .type   _timer_interrupt_handler, @function
_timer_interrupt_handler:
                ret
                .size   _timer_interrupt_handler, . - _timer_interrupt_handler

                /* Default external interrupt handler */
                .globl  _external_interrupt_handler
                .weak   _external_interrupt_handler
                .type   _external_interrupt_handler, @function
_external_interrupt_handler:
                ret
                .size   _external_interrupt_handler, . - _external_interrupt_handler

                /* Default software interrupt handler */
                .globl  _software_interrupt_handler
                .weak   _software_interrupt_handler
                .type   _software_interrupt_handler, @function
_software_interrupt_handler:
                ret
                .size   _software_interrupt_handler, . - _software_interrupt_handler

                /* Default unhandled interrupt handler */
                .globl  _unhandled_interrupt
                .weak   _unhandled_interrupt
                .type   _unhandled_interrupt, @function
_unhandled_interrupt:
                j       _unhandled_interrupt
                .size   _unhandled_interrupt, . - _unhandled_interrupt

                /* Default unhandled exception handler */
                .globl  _unhandled_exception
                .weak   _unhandled_exception
                .type   _unhandled_exception, @function
_unhandled_exception:
                j       _unhandled_exception
                .size   _unhandled_exception, . - _unhandled_exception

#endif /* !defined(__DOXYGEN__) */

/** @} */
