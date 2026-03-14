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
 * @brief   Starts the alarm.
 * @note    Makes sure that no spurious alarms are triggered after
 *          this call.
 *
 * @param[in] time      the time to be set for the first alarm
 *
 * @notapi
 */
static inline void port_timer_start_alarm(systime_t time) {

  /* Set MTIMECMP without triggering spurious interrupts */
  MTIMECMP_HI = 0xFFFFFFFFU;
  MTIMECMP_LO = (uint32_t)time;
  MTIMECMP_HI = 0U;
}

/**
 * @brief   Stops the alarm interrupt.
 * @note    Sets MTIMECMP to maximum value to prevent triggering.
 *
 * @notapi
 */
static inline void port_timer_stop_alarm(void) {

  /* Set MTIMECMP to maximum to prevent further interrupts */
  MTIMECMP_LO = 0xFFFFFFFFU;
  MTIMECMP_HI = 0xFFFFFFFFU;
}

/**
 * @brief   Sets the alarm time.
 *
 * @param[in] time      the time to be set for the next alarm
 *
 * @notapi
 */
static inline void port_timer_set_alarm(systime_t time) {

  MTIMECMP_HI = 0xFFFFFFFFU;
  MTIMECMP_LO = (uint32_t)time;
  MTIMECMP_HI = 0U;
}

/**
 * @brief   Returns the system time.
 *
 * @return              The system time.
 *
 * @notapi
 */
static inline systime_t port_timer_get_time(void) {

  /* For 32-bit systime_t we just return the lower 32 bits. */
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
