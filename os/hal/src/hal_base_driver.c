/*
    ChibiOS - Copyright (C) 2006..2023 Giovanni Di Sirio

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
 * @file    hal_base_driver.c
 * @brief   Generated HAL_BASE_DRIVER source.
 *
 * @addtogroup HAL_BASE_DRIVER
 * @{
 */

#include "hal.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module local macros.                                                      */
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

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module class "hal_base_driver_c" methods.                                 */
/*===========================================================================*/

/**
 * @name    Regular methods of (hal_base_driver_c)
 * @{
 */
/**
 * @brief   Driver open.
 * @details Returns a reference to the driver, on the 1st open the peripheral
 *          is physically initialized. An implementation-dependent default
 *          configuration is used for initialization.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @return                      The operation status.
 */
msg_t drvOpen(const void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  msg_t msg;

  osalDbgCheck(self != NULL);

  osalSysLock();

  if (self->drv.opencnt == 0U) {
    /* Physically starting the peripheral.*/
    msg = __drv_start_protected(self);
    if (msg == HAL_RET_SUCCESS) {
      self->drv.opencnt++;
      self->drv.state = HAL_DRV_STATE_READY;
    }
    else {
      self->drv.state = HAL_DRV_STATE_STOP;
    }
  }
  else {
    msg = HAL_RET_SUCCESS;
  }

  osalSysUnlock();

  return msg;
}

/**
 * @brief   Driver close.
 * @details Releases a reference to the driver, when the count reaches zero
 *          then the peripheral is physically uninitialized.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 */
void drvClose(const void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  osalDbgCheck(self != NULL);

  osalSysLock();

  osalDbgAssert(self->drv.opencnt > 0U, "not opened");

  if (--self->drv.opencnt == 0U) {
    self->drv.state = HAL_DRV_STATE_STOP;
    __drv_stop_protected(self);
  }

  osalSysUnlock();
}

/**
 * @brief   Driver state get.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @return                      The driver state.
 */
driver_state_t drvGetStateX(const void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  return self->drv.state;
}

/**
 * @brief   Driver state set.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @param         state         New driver state.
 */
void drvSetStateX(const void *ip, driver_state_t state) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  self->drv.state = state;
}

/**
 * @brief   Driver owner get.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @return                      The driver owner.
 */
void * drvGetOwnerX(const void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  return self->drv.owner;
}

/**
 * @brief   Driver owner set.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @param         owner         New driver owner.
 */
void drvSetOwnerX(const void *ip, void *owner) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  self->drv.owner = owner;
}

#if (HAL_USE_MUTUAL_EXCLUSION == TRUE) || defined (__DOXYGEN__)
/**
 * @brief   Driver lock.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 */
void drvLock(const void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  osalMutexLock(&self->drv.mutex);
}

/**
 * @brief   Driver unlock.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 */
void drvUnlock(const void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  osalMutexUnlock(&self->drv.mutex);
}
#endif /* HAL_USE_MUTUAL_EXCLUSION == TRUE */
/** @} */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/** @} */
