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
/* Module exported functions.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module class "hal_base_driver_c" methods.                                 */
/*===========================================================================*/

/**
 * @name    Virtual methods implementations of hal_base_driver_c
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p hal_base_driver_c structure to
 *                              be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__drv_objinit_impl(void *ip, const void *vmt) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __bo_objinit_impl(self, vmt);

  /* Initialization code.*/
  self->drv.state   = HAL_DRV_STATE_STOP;
  self->drv.opencnt = 0U;
  self->drv.owner   = NULL;
  osalMutexObjectInit(&self->drv.mutex);
#if HAL_USE_REGISTRY == TRUE
  self->drv.id      = 0U;
#endif

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure to
 *                              be disposed.
 */
void __drv_dispose_impl(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  __bo_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}
/** @} */

/**
 * @name    Regular methods of hal_base_driver_c
 * @{
 */
/**
 * @brief   Driver open.
 * @details Returns a reference to the driver, on the 1st open the peripheral
 *          is physically initialized. An implementation-dependent default
 *          configuration is used for initialization.
 *
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 * @return                      The operation status.
 */
msg_t drvOpen(hal_base_driver_c *self) {
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
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 */
void drvClose(hal_base_driver_c *self) {
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
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 * @return                      The driver state.
 */
driver_state_t drvGetStateX(hal_base_driver_c *self) {
  return self->drv.state;
}

/**
 * @brief   Driver state set.
 *
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 * @param         state         New driver state.
 */
void drvSetStateX(hal_base_driver_c *self, driver_state_t state) {
  self->drv.state = state;
}

/**
 * @brief   Driver owner get.
 *
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 * @return                      The driver owner.
 */
void * drvGetOwnerX(hal_base_driver_c *self) {
  return self->drv.owner;
}

/**
 * @brief   Driver owner set.
 *
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 * @param         owner         New driver owner.
 */
void drvSetOwnerX(hal_base_driver_c *self, void *owner) {
  self->drv.owner = owner;
}

#if (HAL_USE_MUTUAL_EXCLUSION == TRUE) || defined (__DOXYGEN__)
/**
 * @brief   Driver lock.
 *
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 */
void drvLock(hal_base_driver_c *self) {
  osalMutexLock(&self->drv.mutex);
}

/**
 * @brief   Driver unlock.
 *
 * @param[in,out] self          Pointer to a @p hal_base_driver_c instance.
 */
void drvUnlock(hal_base_driver_c *self) {
  osalMutexUnlock(&self->drv.mutex);
}
#endif /* HAL_USE_MUTUAL_EXCLUSION == TRUE */
/** @} */

/** @} */
