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
 * @file    RISCV-HAZARD3/chcore.h
 * @brief   RISC-V Hazard3 port macros and structures.
 *
 * @addtogroup RISCV_HAZARD3_CORE
 * @{
 */

#ifndef CHCORE_H
#define CHCORE_H

/* Inclusion of the RISC-V Hazard3 implementation specific parameters.*/
#include "rvparams.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/* The following code is not processed when the file is included from an
   asm module because those intrinsic macros are not necessarily defined
   by the assembler too.*/
#if !defined(_FROM_ASM_)

/**
 * @brief   Compiler name and version.
 */
#if defined(__GNUC__) || defined(__DOXYGEN__)
#define PORT_COMPILER_NAME              "GCC " __VERSION__

#else
#error "unsupported compiler"
#endif

#endif /* !defined(_FROM_ASM_) */
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   Stack size for the system idle thread.
 * @details This size depends on the idle thread implementation, usually
 *          the idle thread should take no more space than those reserved
 *          by @p PORT_INT_REQUIRED_STACK.
 * @note    In this port it is set to 64 because the idle thread does have
 *          a stack frame when compiling without optimizations.
 */
#if !defined(PORT_IDLE_THREAD_STACK_SIZE) || defined(__DOXYGEN__)
#define PORT_IDLE_THREAD_STACK_SIZE     256
#endif

/**
 * @brief   Per-thread stack overhead for interrupts servicing.
 * @details This constant is used in the calculation of the correct working
 *          area size.
 * @note    In this port this value is conservatively set to 256 because the
 *          trap handler saves all caller-saved registers plus some extra.
 */
#if !defined(PORT_INT_REQUIRED_STACK) || defined(__DOXYGEN__)
#define PORT_INT_REQUIRED_STACK         384
#endif

/**
 * @brief   Enables the use of the WFI instruction in the idle thread loop.
 */
#if !defined(RISCV_ENABLE_WFI_IDLE)
#define RISCV_ENABLE_WFI_IDLE           TRUE
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/**
 * @name    Port Capabilities and Constants
 * @{
 */
/**
 * @brief   This port supports a realtime counter.
 */
#define PORT_SUPPORTS_RT                TRUE

/**
 * @brief   Natural alignment constant.
 * @note    It is the minimum alignment for pointer-size variables.
 */
#define PORT_NATURAL_ALIGN              sizeof (void *)

/**
 * @brief   Stack initial alignment constant.
 * @note    It is the alignment required for the initial stack pointer,
 *          must be a multiple of sizeof (port_stkline_t).
 * @note    RISC-V ABI requires 16-byte stack alignment.
 */
#define PORT_STACK_ALIGN                16U

/**
 * @brief   Working Areas alignment constant.
 * @note    It is the alignment to be enforced for thread working areas,
 *          must be a multiple of sizeof (port_stkline_t).
 */
#define PORT_WORKING_AREA_ALIGN         16U

/**
 * @brief   Hazard3 has 4 interrupt priority levels (0-3).
 */
#define RISCV_HAZARD3_PRIORITY_LEVELS   4U

/**
 * @brief   Checks if a priority value is valid for external interrupts.
 *
 * @param[in] n         the priority value
 * @return              The validity check result.
 * @retval false        invalid priority.
 * @retval true         valid priority.
 */
#define PORT_IRQ_IS_VALID_PRIORITY(n)                                       \
  (((n) >= 0U) && ((n) < RISCV_HAZARD3_PRIORITY_LEVELS))

/**
 * @brief   Checks if a priority value is valid for kernel-level interrupts.
 *
 * @param[in] n         the priority value
 * @return              The validity check result.
 * @retval false        invalid priority.
 * @retval true         valid priority.
 */
#define PORT_IRQ_IS_VALID_KERNEL_PRIORITY(n)                                \
  (((n) >= 0U) && ((n) < RISCV_HAZARD3_PRIORITY_LEVELS))
/** @} */

/**
 * @name    Architecture
 * @{
 */
/**
 * @brief   Macro defining the specific RISC-V architecture.
 */
#define PORT_ARCHITECTURE_RISCV_HAZARD3

/**
 * @brief   Name of the implemented architecture.
 */
#define PORT_ARCHITECTURE_NAME          "RISC-V Hazard3"

/**
 * @brief   Macro defining a generic RISC-V architecture.
 */
#define PORT_ARCHITECTURE_RISCV

/**
 * @brief   Name of the architecture variant.
 */
#define PORT_CORE_VARIANT_NAME          "Hazard3 RV32IMAC"

/**
 * @brief   Port-specific information string.
 */
#define PORT_INFO                       "Compact kernel mode"
/** @} */

/*===========================================================================*/
/* SMP support.                                                              */
/*===========================================================================*/

/* Inclusion of SMP support, if enabled.*/
#if (CH_CFG_SMP_MODE == TRUE) || defined(__DOXYGEN__)
#if !defined(_FROM_ASM_)
#if !defined(__CHIBIOS_RT__)
#error "SMP is supported in RT only"
#endif

#include "chcoresmp.h"

#if !defined(PORT_CORES_NUMBER)
#error "PORT_CORES_NUMBER not defined in chcoresmp.h"
#endif

#endif
#else /* CH_CFG_SMP_MODE != TRUE */
#endif /* CH_CFG_SMP_MODE != TRUE */

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/* The following code is not processed when the file is included from an
   asm module.*/
#if !defined(_FROM_ASM_)

/**
 * @brief   Interrupt saved context.
 * @details Stack frame saved during a preemption-capable interrupt handler.
 * @note    Caller-saved regs + mepc/mstatus. The meicontext slot saves the
 *          Xh3irq priority stack for hardware mret pop across context switches.
 */
struct port_extctx {
  uint32_t              ra;
  uint32_t              t0;
  uint32_t              t1;
  uint32_t              t2;
  uint32_t              a0;
  uint32_t              a1;
  uint32_t              a2;
  uint32_t              a3;
  uint32_t              a4;
  uint32_t              a5;
  uint32_t              a6;
  uint32_t              a7;
  uint32_t              t3;
  uint32_t              t4;
  uint32_t              t5;
  uint32_t              t6;
  uint32_t              mepc;
  uint32_t              meicontext;
  uint32_t              mstatus;
  uint32_t              _pad;     /* Pad to 20 words (80 bytes, 16-byte aligned) */
};

/**
 * @brief   System saved context.
 * @details This structure represents the inner stack frame during a context
 *          switch. It contains callee-saved registers.
 * @note    RISC-V calling convention: callee saved registers are s0-s11 and ra.
 */
struct port_intctx {
  /* To allow use of zcmp cm.push {ra, s0-s11}, -64:
     padding at bottom, then ra, s0-s11 in ascending address order. */
  uint32_t              _pad[3];
  uint32_t              ra;
  uint32_t              s0;
  uint32_t              s1;
  uint32_t              s2;
  uint32_t              s3;
  uint32_t              s4;
  uint32_t              s5;
  uint32_t              s6;
  uint32_t              s7;
  uint32_t              s8;
  uint32_t              s9;
  uint32_t              s10;
  uint32_t              s11;
};

/**
 * @brief   Platform dependent part of the @p thread_t structure.
 * @details In this port the structure just holds a pointer to the
 *          @p port_intctx structure representing the stack pointer
 *          at context switch time.
 */
struct port_context {
  struct port_intctx    *sp;
};

#endif /* !defined(_FROM_ASM_) */

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Optimized thread function declaration macro.
 */
#define PORT_THD_FUNCTION(tname, arg) void tname(void *arg)

/**
 * @brief   Platform dependent part of the @p chThdCreateI() API.
 * @details This code usually setup the context switching frame represented
 *          by an @p port_intctx structure.
 */
#define PORT_SETUP_CONTEXT(tp, wbase, wtop, pf, arg) do {                   \
  (tp)->ctx.sp = (struct port_intctx *)(void *)                             \
                   ((uint8_t *)(wtop) - sizeof (struct port_intctx));       \
  (tp)->ctx.sp->s0 = (uint32_t)(pf);                                        \
  (tp)->ctx.sp->s1 = (uint32_t)(arg);                                       \
  (tp)->ctx.sp->ra = (uint32_t)__port_thread_start;                         \
} while (false)

/**
 * @brief   Computes the thread working area global size.
 * @note    There is no need to perform alignments in this macro.
 */
#define PORT_WA_SIZE(n) (sizeof (struct port_intctx) +                      \
                         sizeof (struct port_extctx) +                      \
                         (size_t)(n) +                                      \
                         (size_t)PORT_INT_REQUIRED_STACK)

/**
 * @brief   IRQ prologue code.
 * @details This macro must be inserted at the start of all IRQ handlers
 *          enabled to invoke system APIs.
 */
#define PORT_IRQ_PROLOGUE()

/**
 * @brief   IRQ epilogue code.
 * @details This macro must be inserted at the end of all IRQ handlers
 *          enabled to invoke system APIs.
 */
#define PORT_IRQ_EPILOGUE() __port_irq_epilogue()

/**
 * @brief   IRQ handler function declaration.
 * @note    @p id can be a function name or a vector number depending on the
 *          port implementation.
 */
#ifdef __cplusplus
  #define PORT_IRQ_HANDLER(id) extern "C" void id(void)

#else
  #define PORT_IRQ_HANDLER(id) void id(void)
#endif

/**
 * @brief   Fast IRQ handler function declaration.
 * @note    @p id can be a function name or a vector number depending on the
 *          port implementation.
 */
#ifdef __cplusplus
  #define PORT_FAST_IRQ_HANDLER(id) extern "C" void id(void)

#else
  #define PORT_FAST_IRQ_HANDLER(id) void id(void)
#endif

/**
 * @brief   Performs a context switch between two threads.
 * @details This is the most critical code in any port, this function
 *          is responsible for the context switch between 2 threads.
 * @note    The implementation of this code affects <b>directly</b> the context
 *          switch performance so optimize here as much as you can.
 *
 * @param[in] ntp       the thread to be switched in
 * @param[in] otp       the thread to be switched out
 */
#define port_switch(ntp, otp) __port_switch(ntp, otp)

/**
 * @brief   Returns a word representing a critical section status.
 *
 * @return              The critical section status.
 */
#define port_get_lock_status() __port_get_irq_status()

/**
 * @brief   Determines if in a critical section.
 *
 * @param[in] sts       status word returned by @p port_get_lock_status()
 * @return              The current status.
 * @retval false        if running outside a critical section.
 * @retval true         if running within a critical section.
 */
#define port_is_locked(sts) !__port_irq_enabled(sts)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)

/*
 * Port variables accessed from assembly and inline functions.
 */
#if CH_CFG_SMP_MODE == TRUE
extern volatile bool port_preemption_pending[];
extern volatile uint8_t port_isr_nesting[];
#else
extern volatile bool port_preemption_pending;
extern volatile uint8_t port_isr_nesting;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void port_init(os_instance_t *oip);
  void __port_switch(thread_t *ntp, thread_t *otp);
  void __port_thread_start(void);
  void __port_switch_from_isr(void);
  void __port_exit_from_isr(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @brief   Read the mstatus CSR.
 *
 * @return              The mstatus value.
 */
static inline uint32_t __port_read_mstatus(void) {
  uint32_t result;
  __asm__ volatile ("csrr %0, mstatus" : "=r"(result));
  return result;
}

/**
 * @brief   Write the mstatus CSR.
 *
 * @param[in] value     The value to write.
 */
static inline void __port_write_mstatus(uint32_t value) {
  __asm__ volatile ("csrw mstatus, %0" : : "r"(value));
}

/**
 * @brief   Set bits in mstatus CSR.
 *
 * @param[in] bits      The bits to set.
 */
static inline void __port_set_mstatus(uint32_t bits) {
  __asm__ volatile ("csrs mstatus, %0" : : "r"(bits));
}

/**
 * @brief   Clear bits in mstatus CSR.
 *
 * @param[in] bits      The bits to clear.
 */
static inline void __port_clear_mstatus(uint32_t bits) {
  __asm__ volatile ("csrc mstatus, %0" : : "r"(bits));
}

/**
 * @brief   Returns a word encoding the current interrupts status.
 *
 * @return              The interrupts status.
 */
static inline syssts_t __port_get_irq_status(void) {
  return (syssts_t)__port_read_mstatus();
}

/**
 * @brief   Checks the interrupt status.
 *
 * @param[in] sts       the interrupt status word
 *
 * @return              The interrupt status.
 * @retval false        the word specified a disabled interrupts status.
 * @retval true         the word specified an enabled interrupts status.
 */
static inline bool __port_irq_enabled(syssts_t sts) {
  return (sts & MSTATUS_MIE) != 0U;
}

/**
 * @brief   Determines the current execution context.
 *
 * @return              The execution context.
 * @retval false        not running in ISR mode.
 * @retval true         running in ISR mode.
 *
 * @note    Uses a per-core ISR nesting counter maintained by the trap
 *          handler in vectors_hazard3.S. The previous mstatus-based
 *          heuristic (MIE=0 && MPIE=1) gave false positives when
 *          interrupts were disabled via port_lock().
 */
static inline bool port_is_isr_context(void) {
#if CH_CFG_SMP_MODE == TRUE
  return port_isr_nesting[SIO->CPUID] != 0U;
#else
  return port_isr_nesting != 0U;
#endif
}

/**
 * @brief   Exception exit redirection to @p __port_switch_from_isr().
 * @details Sets the preemption pending flag unconditionally. The actual
 *          preemption check happens later in @p __port_switch_from_isr()
 *          under the spinlock.
 *
 * @note    Inlined to avoid function call overhead on every interrupt exit.
 */
static inline void __port_irq_epilogue(void) {
#if CH_CFG_SMP_MODE == TRUE
  port_preemption_pending[SIO->CPUID] = true;
#else
  port_preemption_pending = true;
#endif
}

/**
 * @brief   Kernel-lock action.
 * @details In this port this function disables interrupts globally.
 */
static inline void port_lock(void) {
  __port_clear_mstatus(MSTATUS_MIE);
  __asm__ volatile ("" : : : "memory");
#if CH_CFG_SMP_MODE == TRUE
  port_spinlock_take();
#endif
}

/**
 * @brief   Kernel-unlock action.
 * @details In this port this function enables interrupts globally.
 */
static inline void port_unlock(void) {
#if CH_CFG_SMP_MODE == TRUE
  port_spinlock_release();
#endif
  __asm__ volatile ("" : : : "memory");
  __port_set_mstatus(MSTATUS_MIE);
}

/**
 * @brief   Kernel-lock action from an interrupt handler.
 * @details Clears MIE to prevent same-core preemption during I-class API calls.
 *          SMP mode additionally takes the spinlock for cross-core exclusion.
 */
static inline void port_lock_from_isr(void) {
  __port_clear_mstatus(MSTATUS_MIE);
  __asm__ volatile ("" : : : "memory");
#if CH_CFG_SMP_MODE == TRUE
  port_spinlock_take();
#endif
}

/**
 * @brief   Kernel-unlock action from an interrupt handler.
 * @details Re-enables MIE for preemptive nesting. Timer/software IRQs remain
 *          masked by clearts inside the external IRQ dispatcher.
 */
static inline void port_unlock_from_isr(void) {
#if CH_CFG_SMP_MODE == TRUE
  port_spinlock_release();
#endif
  __asm__ volatile ("" : : : "memory");
  __port_set_mstatus(MSTATUS_MIE);
}

/**
 * @brief   Disables all the interrupt sources.
 * @note    In this port it disables all the interrupt sources by clearing
 *          the MIE bit in mstatus.
 */
static inline void port_disable(void) {
  __port_clear_mstatus(MSTATUS_MIE);
  __asm__ volatile ("" : : : "memory");
}

/**
 * @brief   Disables the interrupt sources below kernel-level priority.
 * @note    In this port it disables all the interrupt sources.
 */
static inline void port_suspend(void) {
  __port_clear_mstatus(MSTATUS_MIE);
  __asm__ volatile ("" : : : "memory");
}

/**
 * @brief   Enables all the interrupt sources.
 * @note    In this port it enables all the interrupt sources by setting
 *          the MIE bit in mstatus.
 */
static inline void port_enable(void) {
  __asm__ volatile ("" : : : "memory");
  __port_set_mstatus(MSTATUS_MIE);
}

/**
 * @brief   Enters an architecture-dependent IRQ-waiting mode.
 * @details The function is meant to return when an interrupt becomes pending.
 *          The simplest implementation is an empty function or macro but this
 *          would not take advantage of architecture-specific power saving
 *          modes.
 * @note    Implemented as an inlined @p WFI instruction.
 */
static inline void port_wait_for_interrupt(void) {
#if RISCV_ENABLE_WFI_IDLE == TRUE
  __asm__ volatile ("wfi");
#endif
}

/**
 * @brief   Returns the current value of the realtime counter.
 *
 * @return              The realtime counter value.
 */
#if !defined(port_rt_get_counter_value)
static inline rtcnt_t port_rt_get_counter_value(void) {
  /* Read MTIME from SIO */
  return *((volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIME_OFFSET));
}
#endif

#endif /* !defined(_FROM_ASM_) */

/*===========================================================================*/
/* Module late inclusions.                                                   */
/*===========================================================================*/

#if !defined(_FROM_ASM_)

#if CH_CFG_ST_TIMEDELTA > 0
#include "chcore_timer_hazard3.h"
#endif /* CH_CFG_ST_TIMEDELTA > 0 */

#endif /* !defined(_FROM_ASM_) */

#endif /* CHCORE_H */

/** @} */
