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

/* Stringify helpers for CSR numbers in inline asm.*/
#define _PORT_XSTR(s)   _PORT_STR(s)
#define _PORT_STR(s)    #s

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
 * @details Incremented on ISR entry, decremented on exit. Supports preemptive
 *          nesting (max ~4 levels with Xh3irq priorities).
 * @note    Non-static: accessed from assembly in vectors_hazard3.S.
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

#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) && (PORT_ENABLE_GUARD_PAGES == TRUE)
/**
 * @brief   One-time PMP guard region configuration.
 * @details Sets the PMPADDR, PMPCFG (NAPOT, no permissions), and PMPCFGM0
 *          bit for the chosen guard region. Called once per core in port_init.
 *
 * @param[in] base_addr   32-byte aligned base address of the guard region.
 */
static void __port_pmp_configure_guard(uint32_t base_addr) {
  uint32_t cfg;

  /* Set PMPADDR for the guard region. RP2350 hardwires 2 LSBs to 1,
     giving NAPOT 32-byte granule automatically.*/
  __asm__ volatile ("csrw " _PORT_XSTR(PORT_GUARD_PMPADDR_CSR) ", %0"
                    : : "r"(base_addr >> 2));

  /* Read-modify-write PMPCFG: set NAPOT, no permissions for our entry.*/
  __asm__ volatile ("csrr %0, " _PORT_XSTR(PORT_GUARD_PMPCFG_CSR)
                    : "=r"(cfg));
  cfg &= ~(0xFFU << PORT_GUARD_PMPCFG_SHIFT);
  cfg |= (uint32_t)PMP_CFG_A_NAPOT << PORT_GUARD_PMPCFG_SHIFT;
  __asm__ volatile ("csrw " _PORT_XSTR(PORT_GUARD_PMPCFG_CSR) ", %0"
                    : : "r"(cfg));

  /* Enable M-mode enforcement for this region via PMPCFGM0.*/
  __asm__ volatile ("csrs " _PORT_XSTR(CSR_PMPCFGM0) ", %0"
                    : : "r"(1U << PORT_USE_GUARD_PMP_REGION));
}
#endif

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

#if CH_CFG_ST_TIMEDELTA == 0
/**
 * @brief   Tick interval in MTIME counts (periodic mode only).
 */
#define TICK_INTERVAL   (RISCV_MTIME_FREQUENCY / OSAL_ST_FREQUENCY)
#endif

#if CH_CFG_ST_TIMEDELTA == 0
/**
 * @brief   Machine timer interrupt handler (periodic mode).
 */
void _timer_interrupt_handler(void) {
  uint32_t current_lo;
  uint32_t current_hi;
  uint32_t next_lo;
  uint32_t next_hi;

  /* Read MTIME (atomic 64-bit). */
  do {
    current_hi = MTIMEH;
    current_lo = MTIME;
  } while (current_hi != MTIMEH);

  /* Next tick (64-bit add). */
  next_lo = current_lo + TICK_INTERVAL;
  next_hi = current_hi + (next_lo < current_lo ? 1U : 0U);

  /* Safe MTIMECMP write sequence (avoids spurious interrupts). */
  MTIMECMP = 0xFFFFFFFFU;
  MTIMECMPH = next_hi;
  MTIMECMP = next_lo;

  osalSysLockFromISR();
  osalOsTimerHandlerI();
  osalSysUnlockFromISR();

  __port_irq_epilogue();
}
#else /* CH_CFG_ST_TIMEDELTA > 0 */
/**
 * @brief   Machine timer interrupt handler (tickless mode).
 * @note    Kernel reprograms MTIMECMP via port_timer_set_alarm().
 *          Level-sensitive: auto-clears when MTIMECMP > MTIME.
 */
void _timer_interrupt_handler(void) {

  osalSysLockFromISR();
  osalOsTimerHandlerI();
  osalSysUnlockFromISR();

  __port_irq_epilogue();
}
#endif /* CH_CFG_ST_TIMEDELTA */

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

  /* Per-core ISR stack pointer.*/
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

#if CH_CFG_ST_TIMEDELTA == 0
  /* Periodic mode: arm first tick. */
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
#else
  /* Tickless mode: alarm disabled until kernel arms it. */
  port_timer_stop_alarm();
#endif

  __asm__ volatile ("csrs mie, %0" : : "r"(MIE_MTIE | MIE_MEIE));

#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) && (PORT_ENABLE_GUARD_PAGES == TRUE)
  /* Configure PMP guard page for the main thread's stack base.*/
  {
#if CH_CFG_SMP_MODE == TRUE
    extern stkline_t __main_thread_stack_base__;
    extern stkline_t __c1_main_thread_stack_base__;
    uint32_t guard_base = (SIO->CPUID == 0U)
                        ? (uint32_t)&__main_thread_stack_base__
                        : (uint32_t)&__c1_main_thread_stack_base__;
#else
    extern stkline_t __main_thread_stack_base__;
    uint32_t guard_base = (uint32_t)&__main_thread_stack_base__;
#endif
    __port_pmp_configure_guard(guard_base);
  }
#endif

#if defined(port_smp_init)
  port_smp_init(oip);
#endif
}

#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) && (PORT_ENABLE_GUARD_PAGES == TRUE)
/**
 * @brief   Updates the PMP guard region for the current thread.
 * @details Called on every context switch to protect the switched-in thread's
 *          stack base. Only the PMPADDR is updated; PMPCFG and PMPCFGM0 are
 *          set once in port_init().
 */
void __port_set_region(void) {
  uint32_t addr = (uint32_t)chThdGetSelfX()->wabase >> 2;
  __asm__ volatile ("csrw " _PORT_XSTR(PORT_GUARD_PMPADDR_CSR) ", %0"
                    : : "r"(addr));
}
#endif

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
