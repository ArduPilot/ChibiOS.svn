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
 * @file    crt0_c1_hazard3.S
 * @brief   RISC-V Hazard3 core 1 startup file for ChibiOS SMP.
 * @details Core 1 entry point. Core 0 has already initialized .data, .bss,
 *          and global constructors. Core 1 only needs to set up its own
 *          stack, global pointer, trap vector, and call c1_main().
 *
 * @addtogroup RISCV_HAZARD3_GCC_STARTUP
 * @{
 */

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

#if !defined(FALSE) || defined(__DOXYGEN__)
#define FALSE                               0
#endif

#if !defined(TRUE) || defined(__DOXYGEN__)
#define TRUE                                1
#endif

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   Stack initialization switch.
 */
#if !defined(CRT0_INIT_STACKS) || defined(__DOXYGEN__)
#define CRT0_INIT_STACKS                    TRUE
#endif

/**
 * @brief   Stack fill pattern.
 */
#if !defined(CRT0_STACKS_FILL_PATTERN) || defined(__DOXYGEN__)
#define CRT0_STACKS_FILL_PATTERN            0x55555555
#endif

/*===========================================================================*/
/* Code section.                                                             */
/*===========================================================================*/

#if !defined(__DOXYGEN__)

                .section .text, "ax", @progbits
                .balign 4
                .globl  _crt0_c1_entry
                .type   _crt0_c1_entry, @function
_crt0_c1_entry:
                /* Disable interrupts globally */
                csrci   mstatus, 0x8            /* Clear MIE bit */

                /* Clear all interrupt enable bits */
                csrw    mie, zero

                /* Set up the global pointer gp for linker relaxation. */
                .option push
                .option norelax
                la      gp, __global_pointer$
                .option pop

                /* Set up the stack pointer sp in SCRATCH_Y. */
                la      sp, __c1_process_stack_end__

                /* Set up the trap vector which is shared with core 0. */
                la      t0, _vectors
                csrw    mtvec, t0

                /* Initialize mscratch with core 1's ISR stack top. */
                la      t0, __c1_main_stack_end__
                csrw    mscratch, t0

#if CRT0_INIT_STACKS == TRUE
                /* Main Stack initialization for core 1 */
                li      t0, CRT0_STACKS_FILL_PATTERN
                la      t1, __c1_main_stack_base__
                la      t2, __c1_main_stack_end__
.Lc1msloop:
                bge     t1, t2, .Lc1msloop_done
                sw      t0, 0(t1)
                addi    t1, t1, 4
                j       .Lc1msloop
.Lc1msloop_done:

                /* Process Stack initialization for core 1 */
                la      t1, __c1_process_stack_base__
                la      t2, __c1_process_stack_end__
.Lc1psloop:
                bge     t1, t2, .Lc1psloop_done
                sw      t0, 0(t1)
                addi    t1, t1, 4
                j       .Lc1psloop
.Lc1psloop_done:
#endif /* CRT0_INIT_STACKS == TRUE */

                /* Call core 1 main */
                call    c1_main

                /* Fall through to exit */
                j       __c1_default_exit

                .size   _crt0_c1_entry, . - _crt0_c1_entry

/*===========================================================================*/
/* Default weak handlers for core 1.                                         */
/*===========================================================================*/

                /* Default exit handler for core 1 infinite WFI loop. */
                .weak   __c1_default_exit
                .type   __c1_default_exit, @function
__c1_default_exit:
                wfi
                j       __c1_default_exit
                .size   __c1_default_exit, . - __c1_default_exit

#endif /* !defined(__DOXYGEN__) */

/** @} */
