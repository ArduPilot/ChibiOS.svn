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
 * @file    RISCV-HAZARD3/chcore_timer_hazard3.h
 * @brief   System timer header file using MTIME/MTIMECMP.
 *
 * @addtogroup RISCV_HAZARD3_TIMER
 * @{
 */

#ifndef CHCORE_TIMER_HAZARD3_H
#define CHCORE_TIMER_HAZARD3_H

#include "rvparams.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Pointer to MTIME register (64-bit, lower 32 bits).
 */
#define MTIME_LO    (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIME_OFFSET))

/**
 * @brief   Pointer to MTIME register (64-bit, upper 32 bits).
 */
#define MTIME_HI    (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIME_OFFSET + 4U))

/**
 * @brief   Pointer to MTIMECMP register (64-bit, lower 32 bits).
 */
#define MTIMECMP_LO (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIMECMP_OFFSET))

/**
 * @brief   Pointer to MTIMECMP register (64-bit, upper 32 bits).
 */
#define MTIMECMP_HI (*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIMECMP_OFFSET + 4U))

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
 * @brief   Enables the timer for this OS instance (no-op, MTIMECMP is per-core).
 */
#define port_timer_enable(oip)

/**
 * @brief   Disables the timer for this OS instance (no-op, MTIMECMP is per-core).
 */
#define port_timer_disable(oip)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @brief   Sets the alarm time.
 * @note    MTIMECMP is 64-bit; writing the halves non-atomically can cause
 *          a spurious match. Safe sequence per RP2350 datasheet 3.1.8:
 *          1. Write 0xFFFFFFFF to high word (makes compare always false)
 *          2. Write new low word
 *          3. Write new high word (matching target MTIME epoch)
 *
 * @param[in] time      the time to be set for the next alarm
 *
 * @notapi
 */
static inline void port_timer_set_alarm(systime_t time) {
  uint32_t hi, lo;

  /* Stable 64-bit read: if MTIME_LO rolls over between the HI and LO
     reads, MTIME_HI will have incremented and the loop retries. */
  do {
    hi = MTIME_HI;
    lo = MTIME_LO;
  } while (hi != MTIME_HI);

  /* If alarm time wraps past current MTIME_LO, it fires after the
     next low-word rollover. */
  if ((uint32_t)time < lo) {
    hi++;
  }

  MTIMECMP_HI = 0xFFFFFFFFU;
  MTIMECMP_LO = (uint32_t)time;
  MTIMECMP_HI = hi;
}

/**
 * @brief   Starts the alarm.
 * @note    Same behavior as @p port_timer_set_alarm. Kept as a distinct
 *          symbol because some kernels (OSAL, NIL) distinguish "first arm"
 *          from "reprogram".
 *
 * @param[in] time      the time to be set for the first alarm
 *
 * @notapi
 */
static inline void port_timer_start_alarm(systime_t time) {

  port_timer_set_alarm(time);
}

/**
 * @brief   Stops the alarm interrupt (sets MTIMECMP to max).
 *
 * @notapi
 */
static inline void port_timer_stop_alarm(void) {

  MTIMECMP_LO = 0xFFFFFFFFU;
  MTIMECMP_HI = 0xFFFFFFFFU;
}

/**
 * @brief   Returns the system time.
 *
 * @return              The system time.
 *
 * @notapi
 */
static inline systime_t port_timer_get_time(void) {

  return (systime_t)MTIME_LO;
}

/**
 * @brief   Returns the current alarm time.
 *
 * @return The currently set alarm time.
 *
 * @notapi
 */
static inline systime_t port_timer_get_alarm(void) {

  return (systime_t)MTIMECMP_LO;
}

#endif /* CHCORE_TIMER_HAZARD3_H */

/** @} */
