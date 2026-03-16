/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3 of the License.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    RISCV-HAZARD3/chcore.c
 * @brief   RISC-V Hazard3 port code.
 *
 * @addtogroup RISCV_HAZARD3_CORE
 * @{
 */

#include <string.h>

#include "ch.h"
#include "osal.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/**
 * @brief   Flags indicating a pending context switch.
 * @note    In SMP mode each core has its own preemption flag indexed
 *          by SIO->CPUID.
 * @note    Non-static: accessed directly from assembly in vectors_hazard3.S
 *          and chcoreasm.S for inline preemption check/clear.
 */
#if CH_CFG_SMP_MODE == TRUE
volatile bool port_preemption_pending[PORT_CORES_NUMBER];
#define PREEMPT_PENDING port_preemption_pending[SIO->CPUID]
#else
volatile bool port_preemption_pending;
#define PREEMPT_PENDING port_preemption_pending
#endif

/**
 * @brief   ISR nesting counter.
 * @details Set to non-zero on ISR entry, cleared on ISR exit. Used by
 *          port_is_isr_context() for reliable ISR detection. A simple
 *          flag (0/1) suffices since Hazard3 uses non-preemptive dispatch
 *          (MIE stays clear during handlers, no nesting).
 * @note    Non-static: accessed directly from assembly in vectors_hazard3.S.
 */
#if CH_CFG_SMP_MODE == TRUE
volatile uint8_t port_isr_nesting[PORT_CORES_NUMBER];
#define ISR_NESTING port_isr_nesting[SIO->CPUID]
#else
volatile uint8_t port_isr_nesting;
#define ISR_NESTING port_isr_nesting
#endif

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local macros for timer access.                                     */
/*===========================================================================*/

/**
 * @brief   Pointer to MTIME register (low 32 bits).
 */
#define MTIME       (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIME_OFFSET))

/**
 * @brief   Pointer to MTIMEH register (high 32 bits).
 */
#define MTIMEH      (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIMEH_OFFSET))

/**
 * @brief   Pointer to MTIMECMP register (low 32 bits).
 */
#define MTIMECMP    (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIMECMP_OFFSET))

/**
 * @brief   Pointer to MTIMECMPH register (high 32 bits).
 */
#define MTIMECMPH   (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIMECMPH_OFFSET))

/**
 * @brief   Pointer to MTIME_CTRL register.
 */
#define MTIME_CTRL  (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIME_CTRL_OFFSET))

/**
 * @brief   Tick interval in timer counts.
 * @note    MTIME runs at 1 MHz, OSAL_ST_FREQUENCY is typically 1000 (1kHz).
 *          So interval = 1000000 / 1000 = 1000 counts per tick.
 */
#define TICK_INTERVAL   (RISCV_MTIME_FREQUENCY / OSAL_ST_FREQUENCY)

/**
 * @brief   RISC-V machine timer interrupt handler.
 * @details This handler is called from the trap vector when mcause indicates
 *          a machine timer interrupt (0x80000007). It clears the interrupt
 *          by updating MTIMECMP and calls the OSAL timer handler.
 *
 * @note    Per RP2350 datasheet 3.1.8 and RISC-V ISA manual, the safe write
 *          sequence for MTIMECMP to avoid spurious interrupts is:
 *          1. Write -1 (0xFFFFFFFF) to MTIMECMP (low) - makes comparison always false
 *          2. Write new high word to MTIMECMPH
 *          3. Write new low word to MTIMECMP
 */
void _timer_interrupt_handler(void) {
  uint32_t current_lo;
  uint32_t current_hi;
  uint32_t next_lo;
  uint32_t next_hi;

  /* Read current MTIME value (full 64 bits, atomic). */
  do {
    current_hi = MTIMEH;
    current_lo = MTIME;
  } while (current_hi != MTIMEH);

  /* Calculate next tick time (64-bit add). */
  next_lo = current_lo + TICK_INTERVAL;
  next_hi = current_hi + (next_lo < current_lo ? 1U : 0U);

  /* Update MTIMECMP using safe write sequence per RISC-V ISA manual:
     1. Write -1 to low word (makes MTIME < MTIMECMP always true temporarily)
     2. Write new high word to MTIMECMPH
     3. Write new low word to MTIMECMP */
  MTIMECMP = 0xFFFFFFFFU;
  MTIMECMPH = next_hi;
  MTIMECMP = next_lo;

  /* Call the OSAL system timer handler. */
  osalSysLockFromISR();
  osalOsTimerHandlerI();
  osalSysUnlockFromISR();

  /* Check for preemption. */
  __port_irq_epilogue();
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Port-related initialization code.
 *
 * @param[in, out] oip  pointer to the @p os_instance_t structure
 *
 * @notapi
 */
void port_init(os_instance_t *oip) {

  (void)oip;

  /* Starting in a known IRQ configuration.*/
  port_suspend();

  /* Initialize pending preemption flag and ISR nesting counter.*/
  PREEMPT_PENDING = false;
  ISR_NESTING = 0U;

  /* In SMP mode port_init() is called per-core, so we reinitialize
     to ensure each core has the correct ISR stack pointer.*/
  {
#if CH_CFG_SMP_MODE == TRUE
    extern uint32_t __main_stack_end__;
    extern uint32_t __c1_main_stack_end__;
    uint32_t isr_sp = (SIO->CPUID == 0U)
                    ? (uint32_t)&__main_stack_end__
                    : (uint32_t)&__c1_main_stack_end__;
    __asm__ volatile ("csrw mscratch, %0" : : "r"(isr_sp));
#else
    extern uint32_t __main_stack_end__;
    __asm__ volatile ("csrw mscratch, %0" : : "r"((uint32_t)&__main_stack_end__));
#endif
  }

  MTIME_CTRL = MTIME_CTRL_EN;

  {
    uint32_t hi, lo;
    do {
      hi = MTIMEH;
      lo = MTIME;
    } while (hi != MTIMEH);
    uint32_t next_lo = lo + TICK_INTERVAL;
    uint32_t next_hi = hi + (next_lo < lo ? 1U : 0U);
    MTIMECMP = 0xFFFFFFFFU;
    MTIMECMPH = next_hi;
    MTIMECMP = next_lo;
  }

  __asm__ volatile ("csrs mie, %0" : : "r"(MIE_MTIE | MIE_MEIE));

#if defined(port_smp_init)
  port_smp_init(oip);
#endif
}

/**
 * @brief   Checks for and performs a context switch triggered by an ISR.
 * @details Called from __port_switch_from_isr in assembly with the spinlock
 *          held. Checks whether preemption is actually required before doing
 *          the context switch, providing an early-out when the flag was set
 *          speculatively by __port_irq_epilogue() but no preemption is needed.
 */
void __port_do_preemption(void) {

  if (chSchIsPreemptionRequired()) {
#if CH_DBG_SYSTEM_STATE_CHECK
    __dbg_check_lock();
#endif

    chSchDoPreemption();

#if CH_DBG_SYSTEM_STATE_CHECK
    __dbg_check_unlock();
#endif
  }
}

/** @} */
