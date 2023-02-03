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
 * @file    hal_sio.c
 * @brief   Generated HAL_SIO source.
 *
 * @addtogroup HAL_SIO
 * @{
 */

#include "hal.h"

#if (HAL_USE_SIO == TRUE) || defined (__DOXYGEN__)

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

static void __sio_start(void *ip) {
  hal_sio_driver_c *siop = (hal_sio_driver_c *)ip;
  msg_t msg;

  msg = sio_lld_start(siop);
  if (msg == HAL_RET_SUCCESS) {
#if SIO_USE_SYNCHRONIZATION == TRUE
    /* If synchronization is enabled then all events by default.*/
    sioWriteEnableFlagsX(siop, SIO_EV_ALL_EVENTS);
#else
    /* If synchronization is disabled then no events by default.*/
    sioWriteEnableFlagsX(siop, SIO_EV_NONE);
#endif
  }
}

/*===========================================================================*/
/* Module class "hal_sio_driver_c" methods.                                  */
/*===========================================================================*/

/**
 * @name    Virtual methods implementations (hal_sio_driver_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p hal_sio_driver_c structure to
 *                              be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__sio_objinit_impl(void *ip, const void *vmt) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __drv_objinit_impl(self, vmt);

  /* Initialization code.*/

#if SIO_USE_STREAMS_INTERFACE == TRUE
  oopInterfaceObjectInit(&self->sio.chn, &channel_vmt);
#endif
  self->sio.enabled     = (sioevents_t)0;
  self->sio.cb          = NULL;
#if SIO_USE_SYNCHRONIZATION == TRUE
  self->sio.sync_rx     = NULL;
  self->sio.sync_rxidle = NULL;
  self->sio.sync_tx     = NULL;
  self->sio.sync_txend  = NULL;
#endif

  /* Optional, user-defined initializer.*/
#if defined(SIO_DRIVER_EXT_INIT_HOOK)
  SIO_DRIVER_EXT_INIT_HOOK(self);
#endif

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c structure to
 *                              be disposed.
 */
void __sio_dispose_impl(void *ip) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  __drv_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}
/** @} */

/**
 * @brief   VMT structure of SIO driver class.
 */
static const struct hal_sio_driver_vmt sio_vmt = {
  __sio_vmt_init(sio)
};

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   SIO Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is no
 *          need to explicitly initialize the driver.
 */
void sioInit(void) {

  sio_lld_init();
}

#endif /* HAL_USE_SIO == TRUE */

/** @} */
