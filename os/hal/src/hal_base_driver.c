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
 * @file        hal_base_driver.c
 * @brief       Generated HAL_BASE_DRIVER source.
 *
 * @addtogroup  HAL_BASE_DRIVER
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
 * @memberof    hal_base_driver_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p hal_base_driver_c instance to
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
 * @memberof    hal_base_driver_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance to
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
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver open.
 * @details     Returns a reference to the driver, on the 1st open the
 *              peripheral is physically initialized. An
 *              implementation-dependent default configuration is used for
 *              initialization.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 * @return                      The operation status.
 */
msg_t drvOpen(void *ip) {
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
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver close.
 * @details     Releases a reference to the driver, when the count reaches zero
 *              then the peripheral is physically uninitialized.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 */
void drvClose(void *ip) {
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
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver state get.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 * @return                      The driver state.
 */
driver_state_t drvGetStateX(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  return self->drv.state;
}

/**
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver state set.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 * @param         state         New driver state.
 */
void drvSetStateX(void *ip, driver_state_t state) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  self->drv.state = state;
}

/**
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver owner get.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 * @return                      The driver owner.
 */
void * drvGetOwnerX(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  return self->drv.owner;
}

/**
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver owner set.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 * @param         owner         New driver owner.
 */
void drvSetOwnerX(void *ip, void *owner) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  self->drv.owner = owner;
}

#if (HAL_USE_MUTUAL_EXCLUSION == TRUE) || defined (__DOXYGEN__)
/**
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver lock.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 */
void drvLock(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  osalMutexLock(&self->drv.mutex);
}

/**
 * @memberof    hal_base_driver_c
 * @public
 *
 * @brief       Driver unlock.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c instance.
 */
void drvUnlock(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  osalMutexUnlock(&self->drv.mutex);
}
#endif /* HAL_USE_MUTUAL_EXCLUSION == TRUE */
/** @} */

/** @} */
