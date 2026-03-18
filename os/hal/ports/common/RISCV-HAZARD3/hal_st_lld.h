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
 * @file    RISCV-HAZARD3/hal_st_lld.h
 * @brief   RISC-V Hazard3 ST Driver subsystem low level driver header.
 * @details For RISC-V Hazard3, the system timer is handled directly by the
 *          port code using MTIME/MTIMECMP registers. This header provides
 *          the minimal definitions required by the HAL ST abstraction layer.
 *
 * @addtogroup ST
 * @{
 */

#ifndef HAL_ST_LLD_H
#define HAL_ST_LLD_H

#include "rvparams.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Number of supported alarms.
 * @note    0: timer managed by port_timer_* in chcore_timer_hazard3.h.
 */
#define ST_LLD_NUM_ALARMS                   0

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void st_lld_init(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Driver inline functions.                                                  */
/*===========================================================================*/

/**
 * @brief   Returns the time counter value.
 * @note    For RISC-V Hazard3, this returns the MTIME value.
 *
 * @return  The counter value.
 *
 * @notapi
 */
__STATIC_INLINE systime_t st_lld_get_counter(void) {
  return (systime_t)(*(volatile uint32_t *)(RISCV_SIO_BASE + RISCV_SIO_MTIME_OFFSET));
}

/**
 * @brief   Starts the alarm.
 * @note    Not used in periodic mode.
 *
 * @param[in] abstime   the time to be set for the first alarm
 *
 * @notapi
 */
__STATIC_INLINE void st_lld_start_alarm(systime_t abstime) {
  (void)abstime;
}

/**
 * @brief   Stops the alarm interrupt.
 * @note    Not used in periodic mode.
 *
 * @notapi
 */
__STATIC_INLINE void st_lld_stop_alarm(void) {
}

/**
 * @brief   Sets the alarm time.
 * @note    Not used in periodic mode.
 *
 * @param[in] abstime   the time to be set for the next alarm
 *
 * @notapi
 */
__STATIC_INLINE void st_lld_set_alarm(systime_t abstime) {
  (void)abstime;
}

/**
 * @brief   Returns the current alarm time.
 * @note    Not used in periodic mode.
 *
 * @return  The current alarm time.
 *
 * @notapi
 */
__STATIC_INLINE systime_t st_lld_get_alarm(void) {
  return (systime_t)0;
}

/**
 * @brief   Determines if the alarm is active.
 * @note    Not used in periodic mode.
 *
 * @return The alarm status.
 * @retval false if the alarm is not active.
 * @retval true if the alarm is active
 *
 * @notapi
 */
__STATIC_INLINE bool st_lld_is_alarm_active(void) {
  return false;
}

#endif /* HAL_ST_LLD_H */

/** @} */
