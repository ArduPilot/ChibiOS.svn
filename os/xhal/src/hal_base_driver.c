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
 * @brief       Generated Base Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  HAL_BASE_DRIVER
 * @{
 */

#include <string.h>
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

#if (HAL_USE_REGISTRY == TRUE) || defined (__DOXYGEN__)
/**
 * @brief       List header for the HAL registry.
 */
hal_regent_t                hal_registry;
#endif /* HAL_USE_REGISTRY == TRUE */

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

#if (HAL_USE_REGISTRY == TRUE) || defined (__DOXYGEN__)
/**
 * @brief       Driver insertion in the HAL registry.
 * @note        This function is only available when HAL registry is enabled.
 *
 * @param[in,out] drvp          Pointer to the @p hal_base_driver_c instance to
 *                              be inserted.
 */
static void drv_reg_insert(hal_base_driver_c *drvp) {

  drvp->regent.next       = &hal_registry;
  drvp->regent.prev       = hal_registry.prev;
  drvp->regent.prev->next = &drvp->regent;
  hal_registry.prev       = &drvp->regent;
}

/**
 * @brief       Driver removal from the HAL registry.
 *
 * @param[in,out] drvp          Pointer to the @p hal_base_driver_c instance to
 *                              be inserted.
 */
static void drv_reg_remove(hal_base_driver_c *drvp) {

  drvp->regent.prev->next = drvp->regent.next;
  drvp->regent.next->prev = drvp->regent.prev;
}
#endif /* HAL_USE_REGISTRY == TRUE */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief       Drivers manager initialization.
 *
 * @init
 */
void drvInit(void) {

#if HAL_USE_REGISTRY == TRUE
  /* Registry list initialization.*/
  hal_registry.next = &hal_registry;
  hal_registry.prev = &hal_registry;
#endif
}

#if (HAL_USE_REGISTRY == TRUE) || defined (__DOXYGEN__)
/**
 * @brief       Return the first driver in the HAL registry.
 *
 * @return                      A pointer to the first driver object.
 * @retval NULL                 If the registry is empty.
 *
 * @api
 */
hal_base_driver_c *drvRegGetFirstX(void) {
  hal_regent_t *rep;

  rep = hal_registry.next;
  if (rep == &hal_registry) {
    return NULL;
  }

  return oopGetOwner(hal_base_driver_c, drv.regent, rep);
}

/**
 * @brief       Return the next driver in the HAL registry.
 * @note        This function is only available when HAL registry is enabled.
 *
 * @param[in]     drvp          Previously found driver.
 * @return                      A pointer to the next driver object.
 * @retval NULL                 If there is no next driver.
 *
 * @api
 */
hal_base_driver_c *drvRegGetNextX(hal_base_driver_c *drvp) {
  hal_regent_t *rep;

  rep = drvp->regent.next;
  if (rep == &hal_registry) {
    return NULL;
  }

  return oopGetOwner(hal_base_driver_c, drv.regent, rep);
}

/**
 * @brief       Driver open by name.
 * @details     Returns a reference to the driver, on the 1st open the
 *              peripheral is physically initialized. An
 *              implementation-dependent default configuration is used for
 *              initialization.
 * @note        This function is only available when HAL registry is enabled.
 *
 * @param[in]     name          Driver name.
 * @param[out]    msgp          Pointer to store the error code or @p NULL.
 *                              Note that in case of driver not found the
 *                              returned code is @p HAL_RET_SUCCESS.
 * @return                      A reference to the driver.
 * @retval NULL                 If an error occurred.
 *
 * @api
 */
hal_base_driver_c *drvOpenByName(const char *name, msg_t *msgp) {
  msg_t msg = HAL_RET_SUCCESS;
  hal_base_driver_c *drvp;

  osalSysLock();

  drvp = drvRegGetFirstX();
  while (drvp != NULL) {
    if (strcmp(drvGetNameX(drvp), name) ==0) {

      msg = drvOpen(drvp);
      if (msg != HAL_RET_SUCCESS) {
        drvp = NULL;
      }
      break;
    }
    drvp = drvRegGetNextX(drvp);
  }

  if (msgp != NULL) {
    *msgp = msg;
  }

  osalSysUnlock();

  return drvp;
}
#endif /* HAL_USE_REGISTRY == TRUE */

/*===========================================================================*/
/* Module class "hal_base_driver_c" methods.                                 */
/*===========================================================================*/

/**
 * @name        Methods implementations of hal_base_driver_c
 * @{
 */


/** @} */

/**
 * @name        Regular methods of hal_base_driver_c
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
 *
 * @api
 */
msg_t drvOpen(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;
  msg_t msg;

  osalDbgCheck(self != NULL);

  osalSysLock();

  if (self->opencnt == 0U) {
    /* Physically starting the peripheral.*/
    msg = __drv_start(self);
    if (msg == HAL_RET_SUCCESS) {
      self->opencnt++;
      self->state = HAL_DRV_STATE_READY;
    }
    else {
      self->state = HAL_DRV_STATE_STOP;
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
 *
 * @api
 */
void drvClose(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  osalDbgCheck(self != NULL);

  osalSysLock();

  osalDbgAssert(self->opencnt > 0U, "not opened");

  if (--self->opencnt == 0U) {
    self->state = HAL_DRV_STATE_STOP;
    __drv_stop(self);
  }

  osalSysUnlock();
}
/** @} */

/** @} */
