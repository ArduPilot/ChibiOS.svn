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
 * @file    RISCV-HAZARD3/hazard3_irq.h
 * @brief   Hazard3 Xh3irq extension support.
 * @details Provides macros and functions for accessing the custom Xh3irq
 *          CSRs for external interrupt control on the Hazard3 core.
 *
 * @note    The Xh3irq array CSRs (MEIEA, MEIPA, MEIFA, MEIPRA) use a
 *          windowed access scheme:
 *          - Written value: bits[4:0] = window index, bits[31:16] = data
 *          - Read returns: {window_data[15:0], 16'h0}
 *          - CSRRS sets bits, CSRRC clears bits (both use windowing)
 *
 *          MEIEA/MEIPA/MEIFA: 1 bit per IRQ, 16 IRQs per window.
 *          MEIPRA: 4-bit priority per IRQ, 4 IRQs per window.
 *
 * @addtogroup RISCV_HAZARD3_IRQ
 * @{
 */

#ifndef HAZARD3_IRQ_H
#define HAZARD3_IRQ_H

#include <stdbool.h>

#include "rvparams.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/* Xh3irq CSR addresses (CSR_MEIEA, CSR_MEIPA, etc.) are defined in
   rvparams.h which is included above. */

/**
 * @name    MEINEXT register fields
 * @{
 */
#define MEINEXT_NOIRQ           (1U << 31)  /**< No IRQ pending flag       */
/** @} */

/**
 * @name    Interrupt priority levels
 * @note    Hazard3 supports 4 priority levels.
 *          Higher number = higher priority.
 * @{
 */
#define HAZARD3_IRQ_PRIO_0      0U  /** Lowest priority  */
#define HAZARD3_IRQ_PRIO_1      1U  /** Medium-low       */
#define HAZARD3_IRQ_PRIO_2      2U  /** Medium-high      */
#define HAZARD3_IRQ_PRIO_3      3U  /** Highest priority */
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @name    Xh3irq array CSR access macros
 * @{
 */

/**
 * @brief   Set bits in an Xh3irq array CSR window.
 * @details Uses CSRRS to atomically set bits. The written value encodes
 *          the window index in bits[4:0] and the bit mask in bits[31:16].
 *
 * @param[in] csr_num   CSR number e.g. 0xBE0 for MEIEA
 * @param[in] index     Window index IRQ/16 for 1-bit arrays
 * @param[in] mask      Bit mask to set in upper 16 bits of window
 */
#define HAZARD3_IRQARRAY_SET(csr_num, index, mask) do {                \
  uint32_t __val = ((uint32_t)(mask) << 16) | (uint32_t)(index);       \
  __asm__ volatile ("csrrs zero, " #csr_num ", %0"                     \
    : : "r"(__val) : "memory");                                        \
} while (0)

/**
 * @brief   Clear bits in an Xh3irq array CSR window.
 * @details Uses CSRRC to atomically clear bits.
 *
 * @param[in] csr_num   CSR number e.g. 0xBE0 for MEIEA
 * @param[in] index     Window index
 * @param[in] mask      Bit mask to clear in upper 16 bits of window
 */
#define HAZARD3_IRQARRAY_CLEAR(csr_num, index, mask) do {              \
  uint32_t __val = ((uint32_t)(mask) << 16) | (uint32_t)(index);       \
  __asm__ volatile ("csrrc zero, " #csr_num ", %0"                     \
    : : "r"(__val) : "memory");                                        \
} while (0)

/**
 * @brief   Read an Xh3irq array CSR window non-destructive.
 * @details Uses CSRRS with the window index to read without modifying.
 *
 * @param[in] csr_num   CSR number e.g. 0xBE1 for MEIPA
 * @param[in] index     Window index
 * @return              The 16-bit window data
 */
#define HAZARD3_IRQARRAY_READ(csr_num, index) ({                       \
  uint32_t __val = (uint32_t)(index);                                  \
  uint32_t __result;                                                   \
  __asm__ volatile ("csrrs %0, " #csr_num ", %1"                       \
    : "=r"(__result) : "r"(__val) : "memory");                         \
  __result >> 16;                                                      \
})

/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @brief   Enable an external interrupt.
 *
 * @param[in] irq       IRQ number
 */
__STATIC_FORCEINLINE void hazard3_irq_enable(uint32_t irq) {
  uint32_t window = irq / 16U;
  uint32_t bit    = 1U << (irq % 16U);
  HAZARD3_IRQARRAY_SET(0xBE0, window, bit);
}

/**
 * @brief   Disable an external interrupt.
 *
 * @param[in] irq       IRQ number
 */
__STATIC_FORCEINLINE void hazard3_irq_disable(uint32_t irq) {
  uint32_t window = irq / 16U;
  uint32_t bit    = 1U << (irq % 16U);
  HAZARD3_IRQARRAY_CLEAR(0xBE0, window, bit);
}

/**
 * @brief   Check if an external interrupt is pending.
 *
 * @param[in] irq       IRQ number
 * @return              true if the interrupt is pending
 */
__STATIC_FORCEINLINE bool hazard3_irq_is_pending(uint32_t irq) {
  uint32_t window = irq / 16U;
  uint32_t bit    = 1U << (irq % 16U);
  return (HAZARD3_IRQARRAY_READ(0xBE1, window) & bit) != 0U;
}

/**
 * @brief   Force an external interrupt
 *
 * @param[in] irq       IRQ number
 */
__STATIC_FORCEINLINE void hazard3_irq_force(uint32_t irq) {
  uint32_t window = irq / 16U;
  uint32_t bit    = 1U << (irq % 16U);
  HAZARD3_IRQARRAY_SET(0xBE2, window, bit);
}

/**
 * @brief   Clear a forced external interrupt.
 *
 * @param[in] irq       IRQ number
 */
__STATIC_FORCEINLINE void hazard3_irq_force_clear(uint32_t irq) {
  uint32_t window = irq / 16U;
  uint32_t bit    = 1U << (irq % 16U);
  HAZARD3_IRQARRAY_CLEAR(0xBE2, window, bit);
}

/**
 * @brief   Set the priority of an external interrupt.
 * @details MEIPRA uses 4-bit priority fields, 4 IRQs per window.
 *          Window index = IRQ / 4, field position = (IRQ % 4) * 4.
 *
 * @param[in] irq       IRQ number
 * @param[in] priority  Priority level
 */
__STATIC_FORCEINLINE void hazard3_irq_set_priority(uint32_t irq, uint32_t priority) {
  uint32_t window = irq / 4U;
  uint32_t shift  = (irq % 4U) * 4U;
  uint32_t mask   = 0xFU << shift;

  /* Clear old priority then set new one */
  HAZARD3_IRQARRAY_CLEAR(0xBE3, window, mask);
  HAZARD3_IRQARRAY_SET(0xBE3, window, (priority & 0x3U) << shift);
}

/**
 * @brief   Get the priority of an external interrupt.
 * @details MEIPRA uses 4-bit priority fields, 4 IRQs per window.
 *          Window index = IRQ / 4, field position = (IRQ % 4) * 4.
 *
 * @param[in] irq       IRQ number
 * @return              Priority level (0-3)
 */
__STATIC_FORCEINLINE uint32_t hazard3_irq_get_priority(uint32_t irq) {
  uint32_t window = irq / 4U;
  uint32_t shift  = (irq % 4U) * 4U;
  return (HAZARD3_IRQARRAY_READ(0xBE3, window) >> shift) & 0x3U;
}

/**
 * @brief   Get the next pending external interrupt.
 * @details Reads the MEINEXT CSR. The IRQ number is in bits[10:2].
 *          Bit 31 is set if no interrupt is pending.
 *
 * @return  Raw MEINEXT value; check bit 31 for NOIRQ
 */
__STATIC_FORCEINLINE uint32_t hazard3_irq_get_next(void) {
  uint32_t val;
  __asm__ volatile ("csrr %0, 0xBE4"
    : "=r"(val) : : "memory");
  return val;
}

/**
 * @brief   Save external interrupt context and raise preemption threshold.
 * @details Must be called after hazard3_irq_get_next() returns a valid IRQ.
 *          Atomically reads MEICONTEXT committing the pending IRQ selection
 *          and raising the priority threshold and writes zero. The returned
 *          value must be passed to hazard3_irq_context_restore() after the
 *          handler returns.
 *
 * @return  Saved context value (pass to context_restore)
 */
__STATIC_FORCEINLINE uint32_t hazard3_irq_context_save(void) {
  uint32_t ctx;
  __asm__ volatile ("csrr %0, 0xBE5"
    : "=r"(ctx) : : "memory");
  return ctx;
}

/**
 * @brief   Restore external interrupt context.
 * @details Writes back a previously saved MEICONTEXT value restoring the
 *          preemption priority to what it was before the IRQ was serviced.
 *
 * @param[in] ctx       Context value from hazard3_irq_context_save()
 */
__STATIC_FORCEINLINE void hazard3_irq_context_restore(uint32_t ctx) {
  __asm__ volatile ("csrw 0xBE5, %0"
    : : "r"(ctx) : "memory");
}

/**
 * @brief   Initialize the Xh3irq interrupt controller.
 * @details Puts the controller in a known clean state by disabling all
 *          external interrupts (MEIEA), clearing all forced-pending bits
 *          (MEIFA), and resetting all priorities to zero (MEIPRA).
 * @note    Does not touch mie; the port layer (port_init) is responsible
 *          for setting mie.MEIE and mie.MTIE.
 */
__STATIC_FORCEINLINE void hazard3_irq_init(void) {
  unsigned i;

  /* Disable all external interrupts (MEIEA, 16 IRQs per window). */
  for (i = 0U; i < ((RISCV_NUM_INTERRUPTS + 15U) / 16U); i++) {
    HAZARD3_IRQARRAY_CLEAR(CSR_MEIEA, i, 0xFFFFU);
  }

  /* Clear all forced-pending bits (MEIFA, 16 IRQs per window). */
  for (i = 0U; i < ((RISCV_NUM_INTERRUPTS + 15U) / 16U); i++) {
    HAZARD3_IRQARRAY_CLEAR(CSR_MEIFA, i, 0xFFFFU);
  }

  /* Reset all priorities to zero (MEIPRA, 4 IRQs per window). */
  for (i = 0U; i < ((RISCV_NUM_INTERRUPTS + 3U) / 4U); i++) {
    HAZARD3_IRQARRAY_CLEAR(CSR_MEIPRA, i, 0xFFFFU);
  }
}

#endif /* HAZARD3_IRQ_H */

/** @} */
