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
 * @brief   RISC-V Hazard3 vectored trap handlers for ChibiOS.
 * @details Vectored mtvec (mode=1) with preemptive nesting for external IRQs
 *          via Xh3irq. ISR nesting counter controls mscratch swap (first
 *          entry/last exit only).
 *
 * @addtogroup RISCV_HAZARD3_GCC_VECTORS
 * @{
 */

#define _FROM_ASM_
#include "rvparams.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/* Stack frame: 16 caller-saved regs + mepc + (reserved) + mstatus + pad = 20 words.
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
#define TRAP_FRAME_MEICONTEXT       68
#define TRAP_FRAME_MSTATUS          72

/*===========================================================================*/
/* Vector table (vectored mode).                                             */
/*===========================================================================*/

#if !defined(__DOXYGEN__)

                .section .vectors, "ax", @progbits
                .balign 64
                .globl  _vectors
                .type   _vectors, @function

/*
 * Vectored mtvec table: exceptions → BASE+0, interrupts → BASE + 4*cause.
 * Each entry is a single 4-byte J instruction (norvc forces no compression).
 *
 * IMPORTANT: Hazard3 computes the vector address as mtvec | (cause << 2),
 * using OR instead of ADD. The base must be aligned to 64 bytes so that
 * bits [5:2] are zero, preventing OR/ADD divergence for causes 0-11.
 */
                .option push
                .option norvc

_vectors:
                j       _exception_entry        /* +0:  Exceptions (cause 0)  */
                j       _unhandled_interrupt     /* +4:  (cause 1, reserved)  */
                j       _unhandled_interrupt     /* +8:  (cause 2, reserved)  */
                j       _software_irq_entry      /* +12: M software IRQ (3)  */
                j       _unhandled_interrupt     /* +16: (cause 4, reserved)  */
                j       _unhandled_interrupt     /* +20: (cause 5, reserved)  */
                j       _unhandled_interrupt     /* +24: (cause 6, reserved)  */
                j       _timer_irq_entry         /* +28: M timer IRQ (7)     */
                j       _unhandled_interrupt     /* +32: (cause 8, reserved)  */
                j       _unhandled_interrupt     /* +36: (cause 9, reserved)  */
                j       _unhandled_interrupt     /* +40: (cause 10, reserved) */
                j       _ext_irq_entry           /* +44: M external IRQ (11) */

                .option pop

                .size   _vectors, . - _vectors

/*===========================================================================*/
/* Register save/restore macros.                                             */
/*===========================================================================*/

/*
 * Save all caller-saved registers + mepc + mstatus to the trap frame.
 * Assumes sp already points to the allocated frame.
 */
.macro SAVE_CONTEXT
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
                csrr    t0, mepc
                csrr    t1, mstatus
                sw      t0, TRAP_FRAME_MEPC(sp)
                sw      t1, TRAP_FRAME_MSTATUS(sp)
.endm

/*
 * Restore all caller-saved registers + mepc + mstatus, deallocate frame, mret.
 */
.macro RESTORE_CONTEXT_AND_MRET
                lw      t0, TRAP_FRAME_MSTATUS(sp)
                csrw    mstatus, t0
                lw      t0, TRAP_FRAME_MEPC(sp)
                csrw    mepc, t0
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
                addi    sp, sp, TRAP_FRAME_SIZE
                mret
.endm

/*
 * ISR nesting entry: increment counter, conditional mscratch swap.
 * Uses a0-a4 as scratch (already saved to frame).
 */
.macro NESTING_ENTRY
                lui     a0, 0xD0000
                lw      a0, 0(a0)               /* SIO->CPUID */
                la      a1, port_isr_nesting
                add     a2, a0, a1              /* &nesting[cpuid] */
                lbu     a3, 0(a2)               /* old_nesting */
                addi    a4, a3, 1
                sb      a4, 0(a2)               /* nesting++ */
                bnez    a3, 1f                  /* if old > 0: already on ISR stack */
                csrrw   sp, mscratch, sp        /* first entry: swap to ISR stack */
1:
.endm

/*
 * ISR nesting exit: ensure MIE=0, decrement counter, conditional mscratch swap.
 * Uses a0-a3 as scratch. After macro: a3=new nesting value.
 */
.macro NESTING_EXIT
                csrci   mstatus, 0x8            /* Ensure MIE=0 */
                lui     a0, 0xD0000
                lw      a0, 0(a0)               /* SIO->CPUID */
                la      a1, port_isr_nesting
                add     a2, a0, a1              /* &nesting[cpuid] */
                lbu     a3, 0(a2)
                addi    a3, a3, -1
                sb      a3, 0(a2)               /* nesting-- */
                bnez    a3, 1f                  /* if still > 0: stay on ISR stack */
                csrrw   sp, mscratch, sp        /* outermost: swap back to thread stack */
1:
.endm

/*
 * Outermost ISR exit: preemption check + context restore + mret.
 * For nested returns: just restore + mret.
 * Expects a3 = nesting value after decrement (from NESTING_EXIT).
 */
.macro ISR_EXIT_WITH_PREEMPTION
                bnez    a3, .Lnested_\@

                /* Outermost exit — now on thread stack. Check preemption. */
                lui     a0, 0xD0000
                lw      a0, 0(a0)               /* SIO->CPUID */
                la      a1, port_preemption_pending
                add     a0, a0, a1
                lbu     a0, 0(a0)
                beqz    a0, .Lnested_\@

                call    __port_switch_from_isr

.Lnested_\@:
                RESTORE_CONTEXT_AND_MRET
.endm

/*===========================================================================*/
/* Exception entry (vector offset +0).                                       */
/*===========================================================================*/

                .section .text, "ax", @progbits
                .balign 4
                .type   _exception_entry, @function
_exception_entry:
                addi    sp, sp, -TRAP_FRAME_SIZE
                SAVE_CONTEXT

                /* Stay on thread stack, no nesting change. */
                csrr    a0, mcause
                csrr    a1, mtval
                mv      a2, sp                  /* trap frame pointer */
                call    _exception_handler

                RESTORE_CONTEXT_AND_MRET

                .size   _exception_entry, . - _exception_entry

/*===========================================================================*/
/* Timer IRQ entry (vector offset +28, cause 7).                             */
/* Non-preemptive: MIE stays clear during handler.                           */
/*===========================================================================*/

                .balign 4
                .type   _timer_irq_entry, @function
_timer_irq_entry:
                addi    sp, sp, -TRAP_FRAME_SIZE
                SAVE_CONTEXT
                NESTING_ENTRY

                call    _timer_interrupt_handler

                NESTING_EXIT
                ISR_EXIT_WITH_PREEMPTION

                .size   _timer_irq_entry, . - _timer_irq_entry

/*===========================================================================*/
/* Software IRQ entry (vector offset +12, cause 3).                          */
/* Non-preemptive: MIE stays clear during handler.                           */
/*===========================================================================*/

                .balign 4
                .type   _software_irq_entry, @function
_software_irq_entry:
                addi    sp, sp, -TRAP_FRAME_SIZE
                SAVE_CONTEXT
                NESTING_ENTRY

                call    _software_interrupt_handler

                NESTING_EXIT
                ISR_EXIT_WITH_PREEMPTION

                .size   _software_irq_entry, . - _software_irq_entry

/*===========================================================================*/
/* External IRQ entry (vector offset +44, cause 11).                         */
/* Preemptive nesting via Xh3irq — MEICONTEXT saved to trap frame so the     */
/* hardware mret pop handles priority stack restoration.                      */
/*===========================================================================*/

                .balign 4
                .type   _ext_irq_entry, @function
_ext_irq_entry:
                addi    sp, sp, -TRAP_FRAME_SIZE
                SAVE_CONTEXT

                /* Save MEICONTEXT to trap frame. Plain read (no clearts) —
                   timer/software IRQs don't affect the Xh3irq priority stack.
                   Snapshot includes mreteirq=1 from hardware push on entry. */
                csrr    t0, 0xBE5
                sw      t0, TRAP_FRAME_MEICONTEXT(sp)

                NESTING_ENTRY

                call    _ext_irq_dispatch

                NESTING_EXIT

                /* ISR exit with MEICONTEXT restore for hardware mret pop. */
                bnez    a3, .Lnested_ext

                /* Outermost exit — now on thread stack. Check preemption. */
                lui     a0, 0xD0000
                lw      a0, 0(a0)               /* SIO->CPUID */
                la      a1, port_preemption_pending
                add     a0, a0, a1
                lbu     a0, 0(a0)
                beqz    a0, .Lnested_ext

                call    __port_switch_from_isr

.Lnested_ext:
                /* Restore MEICONTEXT (mreteirq=1) so hardware pops the
                   priority stack on mret. MIE=0 prevents intervening traps. */
                lw      t0, TRAP_FRAME_MEICONTEXT(sp)
                csrw    0xBE5, t0
                RESTORE_CONTEXT_AND_MRET

                .size   _ext_irq_entry, . - _ext_irq_entry

/*===========================================================================*/
/* Default weak handlers.                                                    */
/*===========================================================================*/

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

                /* Default external interrupt dispatch (overridden by vectors_riscv.c) */
                .globl  _ext_irq_dispatch
                .weak   _ext_irq_dispatch
                .type   _ext_irq_dispatch, @function
_ext_irq_dispatch:
                ret
                .size   _ext_irq_dispatch, . - _ext_irq_dispatch

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
