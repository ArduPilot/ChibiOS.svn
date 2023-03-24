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
 * @file        hal_sio.c
 * @brief       Generated SIO Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  HAL_SIO
 * @{
 */

#include "hal.h"

#if (HAL_USE_SIO == TRUE) || defined(__DOXYGEN__)

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

static void __sio_bo_dispose_impl(void *ip) {

  __sio_dispose_impl(ip);
}

static msg_t __sio_drv_start_impl(void *ip) {
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

  return msg;
}

static void __sio_drv_stop_impl(void *ip) {
  hal_sio_driver_c *siop = (hal_sio_driver_c *)ip;

  sio_lld_stop(siop);
  siop->cb      = NULL;
  siop->enabled = (sioevents_t)0;

#if SIO_USE_SYNCHRONIZATION == TRUE
  /* Informing waiting threads, if any.*/
  osalThreadResumeI(&siop->sync_rx, MSG_RESET);
  osalThreadResumeI(&siop->sync_rxidle, MSG_RESET);
  osalThreadResumeI(&siop->sync_tx, MSG_RESET);
  osalThreadResumeI(&siop->sync_txend, MSG_RESET);
  osalOsRescheduleS();
#endif
}

static msg_t __sio_drv_configure_impl(void *ip, const void *config) {
  hal_sio_driver_c *siop = (hal_sio_driver_c *)ip;

  return sio_lld_configure(siop, (const hal_sio_config_t *)config);
}

#if (SIO_USE_STREAMS_INTERFACE == TRUE) || defined (__DOXYGEN__)
static size_t sio_sync_write(hal_sio_driver_c *siop, const uint8_t *bp,
                             size_t n, sysinterval_t timeout) {
  size_t i;

  i = 0U;
  while (i < n) {
    size_t written;
    msg_t msg;

    msg = sioSynchronizeTX(siop, timeout);
    if (msg != MSG_OK) {
      break;
    }

    written = sioAsyncWriteX(siop, bp, n - i);
    i += written;
    bp += written;
  }
  return i;
}

static size_t sio_sync_read(hal_sio_driver_c *siop, uint8_t *bp, size_t n,
                            sysinterval_t timeout) {
  size_t i;

  i = 0U;
  while (i < n) {
    size_t read;
    msg_t msg;

    msg = sioSynchronizeRX(siop, timeout);
    if (msg != MSG_OK) {
      break;
    }

    read = sioAsyncReadX(siop, bp, n - i);
    i += read;
    bp += read;
  }
  return i;
}

static size_t __sio_stm_write_impl(void *ip, const uint8_t *bp, size_t n) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);

  return sio_sync_write(siop, bp, n, TIME_INFINITE);
}

static size_t __sio_stm_read_impl(void *ip, uint8_t *bp, size_t n) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);

  return sio_sync_read(siop, bp, n, TIME_INFINITE);
}

static msg_t __sio_stm_put_impl(void *ip, uint8_t b) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);
  msg_t msg;

  msg = sioSynchronizeTX(siop, TIME_INFINITE);
  if (msg != MSG_OK) {
    return msg;
  }

  sioPutX(siop, b);
  return MSG_OK;
}

static msg_t __sio_stm_get_impl(void *ip) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);
  msg_t msg;

  msg = sioSynchronizeRX(siop, TIME_INFINITE);
  if (msg != MSG_OK) {
    return msg;
  }

  return sioGetX(siop);
}

static size_t __sio_chn_writet_impl(void *ip, const uint8_t *bp, size_t n,
                                    sysinterval_t timeout) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);

  return sio_sync_write(siop, bp, n, timeout);
}

static size_t __sio_chn_readt_impl(void *ip, uint8_t *bp, size_t n,
                                   sysinterval_t timeout) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);

  return sio_sync_read(siop, bp, n, timeout);
}

static msg_t __sio_chn_putt_impl(void *ip, uint8_t b, sysinterval_t timeout) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);
  msg_t msg;

  msg = sioSynchronizeTX(siop, timeout);
  if (msg != MSG_OK) {
    return msg;
  }

  sioPutX(siop, b);
  return MSG_OK;
}

static msg_t __sio_chn_gett_impl(void *ip, sysinterval_t timeout) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);
  msg_t msg;

  msg = sioSynchronizeRX(siop, timeout);
  if (msg != MSG_OK) {
    return msg;
  }

  return sioGetX(siop);
}

static chnflags_t __sio_chn_getclr_impl(void *ip, chnflags_t mask) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);

  return (chnflags_t)sioGetAndClearEventsX(siop, (sioevents_t)mask);
}

static msg_t __sio_chn_ctl_impl(void *ip, unsigned int operation, void *arg) {
  hal_sio_driver_c *siop = oopIfGetOwner(hal_sio_driver_c, ip);

  switch (operation) {
  case CHN_CTL_NOP:
    osalDbgCheck(arg == NULL);
    break;
  case CHN_CTL_INVALID:
    return HAL_RET_UNKNOWN_CTL;
  default:
    /* Delegating to the LLD if supported.*/
    return sio_lld_control(siop, operation, arg);
  }
  return HAL_RET_SUCCESS;
}
#endif /* SIO_USE_STREAMS_INTERFACE == TRUE */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief       SIO Driver initialization.
 * @note        This function is implicitly invoked by @p halInit(), there is
 *              no need to explicitly initialize the driver.
 *
 * @init
 */
void sioInit(void) {

  sio_lld_init();
}

/*===========================================================================*/
/* Module class "hal_sio_driver_c" methods.                                  */
/*===========================================================================*/

/**
 * @brief       VMT structure of SIO driver class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct hal_sio_driver_vmt __hal_sio_driver_vmt = {
  .dispose                                  = __sio_dispose_impl,
  .start                                    = __sio_start_impl,
  .stop                                     = __sio_stop_impl,
  .configure                                = __sio_configure_impl
};

/**
 * @name        Methods implementations of hal_sio_driver_c
 * @{
 */
/**
 * @memberof    hal_sio_driver_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p hal_sio_driver_c instance to be
 *                              initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__sio_objinit_impl(void *ip, const void *vmt) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __drv_objinit_impl(self, vmt);

#if (SIO_USE_STREAMS_INTERFACE == TRUE) || defined (__DOXYGEN__)
  /* Implementation of interface asynchronous_channel_i.*/
  {
    static const struct asynchronous_channel_vmt sio_chn_vmt = {
      __asynchronous_channel_vmt_init(sio, offsetof(hal_sio_driver_c, sio.chn))
    };
    oopIfObjectInit(&self->sio.chn, &sio_chn_vmt);
  }
#endif /* SIO_USE_STREAMS_INTERFACE == TRUE */

  /* Initialization code.*/
  self->enabled     = (sioevents_t)0;
  self->cb          = NULL;
#if SIO_USE_SYNCHRONIZATION == TRUE
  self->sync_rx     = NULL;
  self->sync_rxidle = NULL;
  self->sync_tx     = NULL;
  self->sync_txend  = NULL;
#endif

  /* Optional, user-defined initializer.*/
#if defined(SIO_DRIVER_EXT_INIT_HOOK)
  SIO_DRIVER_EXT_INIT_HOOK(self);
#endif

  return self;
}

/**
 * @memberof    hal_sio_driver_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance to be
 *                              disposed.
 */
void __sio_dispose_impl(void *ip) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __drv_dispose_impl(self);
}
/** @} */

/**
 * @name        Regular methods of hal_sio_driver_c
 * @{
 */
/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Writes the enabled events flags mask.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param         mask          Enabled events mask to be written
 *
 * @api
 */
void sioWriteEnableFlags(void *ip, sioevents_t mask) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  osalDbgCheck(self != NULL);

  osalSysLock();
  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");
  sioWriteEnableFlagsX(self, mask);
  osalSysUnlock();
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Sets flags into the enabled events flags mask.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param         mask          Enabled events mask to be set
 *
 * @api
 */
void sioSetEnableFlags(void *ip, sioevents_t mask) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  osalDbgCheck(self != NULL);

  osalSysLock();
  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");
  sioSetEnableFlagsX(self, mask);
  osalSysUnlock();
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Clears flags from the enabled events flags mask.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param         mask          Enabled events mask to be cleared
 *
 * @api
 */
void sioClearEnableFlags(void *ip, sioevents_t mask) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;

  osalDbgCheck(self != NULL);

  osalSysLock();
  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");
  sioClearEnableFlagsX(self, mask);
  osalSysUnlock();
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Get and clears SIO error event flags.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @return                      The pending error event flags.
 *
 * @api
 */
sioevents_t sioGetAndClearErrors(void *ip) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  sioevents_t errors;

  osalDbgCheck(self != NULL);

  osalSysLock();
  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");
  errors = sioGetAndClearErrorsX(self);
  osalSysUnlock();

  return errors;
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Get and clears SIO event flags.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param[in]     mask          Mask of events to be returned and cleared.
 * @return                      The pending event flags.
 *
 * @api
 */
sioevents_t sioGetAndClearEvents(void *ip, sioevents_t mask) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  sioevents_t events;

  osalDbgCheck(self != NULL);

  osalSysLock();
  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");
  events = sioGetAndClearEventsX(self, mask);
  osalSysUnlock();

  return events;
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Returns the pending SIO event flags.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @return                      The pending event flags.
 *
 * @api
 */
sioevents_t sioGetEvents(void *ip) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  sioevents_t events;

  osalDbgCheck(self != NULL);

  osalSysLock();
  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");
  events = sioGetEventsX(self);
  osalSysUnlock();

  return events;
}

#if (SIO_USE_SYNCHRONIZATION == TRUE) || defined (__DOXYGEN__)
/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Synchronizes with RX FIFO data availability.
 * @note        The exact behavior depends on low level FIFO settings such as
 *              thresholds, etc.
 * @note        This function can only be called by a single thread at time.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param[in]     timeout       Synchronization timeout.
 * @return                      The synchronization result.
 * @retval MSG_OK               If there is data in the RX FIFO.
 * @retval MSG_TIMEOUT          If synchronization timed out.
 * @retval MSG_RESET            It the driver has been stopped while waiting.
 * @retval SIO_MSG_ERRORS       It RX errors occurred before or during wait.
 *
 * @api
 */
msg_t sioSynchronizeRX(void *ip, sysinterval_t timeout) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  msg_t msg;

  osalDbgCheck(self != NULL);

  osalSysLock();

  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");

  /* Checking for errors before going to sleep.*/
  if (sioHasRXErrorsX(self)) {
    osalSysUnlock();
    return SIO_MSG_ERRORS;
  }

  msg = MSG_OK;
  /*lint -save -e506 -e681 [2.1] Silencing this error because it is
    tested with a template implementation of sio_lld_is_rx_empty() which
    is constant.*/
  while (sioIsRXEmptyX(self)) {
  /*lint -restore*/
    msg = osalThreadSuspendTimeoutS(&self->sync_rx, timeout);
    if (msg != MSG_OK) {
      break;
    }
  }

  osalSysUnlock();

  return msg;
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Synchronizes with RX going idle.
 * @note        This function can only be called by a single thread at time.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param[in]     timeout       Synchronization timeout.
 * @return                      The synchronization result.
 * @retval MSG_OK               If there is data in the RX FIFO.
 * @retval MSG_TIMEOUT          If synchronization timed out.
 * @retval MSG_RESET            It the driver has been stopped while waiting.
 * @retval SIO_MSG_ERRORS       It RX errors occurred before or during wait.
 *
 * @api
 */
msg_t sioSynchronizeRXIdle(void *ip, sysinterval_t timeout) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  msg_t msg;

  osalDbgCheck(self != NULL);

  osalSysLock();

  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");

  /* Checking for errors before going to sleep.*/
  if (sioHasRXErrorsX(self)) {
    osalSysUnlock();
    return SIO_MSG_ERRORS;
  }

  msg = MSG_OK;
  /*lint -save -e506 -e681 [2.1] Silencing this error because it is
    tested with a template implementation of sio_lld_is_rx_empty() which
    is constant.*/
  while (!sioIsRXIdleX(self)) {
  /*lint -restore*/
    msg = osalThreadSuspendTimeoutS(&self->sync_rxidle, timeout);
    if (msg != MSG_OK) {
      break;
    }
  }

  osalSysUnlock();

  return msg;
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Synchronizes with TX FIFO space availability.
 * @note        The exact behavior depends on low level FIFO settings such as
 *              thresholds, etc.
 * @note        This function can only be called by a single thread at time.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param[in]     timeout       Synchronization timeout.
 * @return                      The synchronization result.
 * @retval MSG_OK               If there is space in the TX FIFO.
 * @retval MSG_TIMEOUT          If synchronization timed out.
 * @retval MSG_RESET            It the driver has been stopped while waiting.
 *
 * @api
 */
msg_t sioSynchronizeTX(void *ip, sysinterval_t timeout) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  msg_t msg;

  osalDbgCheck(self != NULL);

  osalSysLock();

  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");

  msg = MSG_OK;
  /*lint -save -e506 -e681 [2.1] Silencing this error because it is
    tested with a template implementation of sio_lld_is_tx_full() which
    is constant.*/
  while (sioIsTXFullX(self)) {
  /*lint -restore*/
    msg = osalThreadSuspendTimeoutS(&self->sync_tx, timeout);
    if (msg != MSG_OK) {
      break;
    }
  }

  osalSysUnlock();

  return msg;
}

/**
 * @memberof    hal_sio_driver_c
 * @public
 *
 * @brief       Synchronizes with TX completion.
 * @note        This function can only be called by a single thread at time.
 *
 * @param[in,out] ip            Pointer to a @p hal_sio_driver_c instance.
 * @param[in]     timeout       Synchronization timeout.
 * @return                      The synchronization result.
 * @retval MSG_OK               If there is space in the TX FIFO.
 * @retval MSG_TIMEOUT          If synchronization timed out.
 * @retval MSG_RESET            It the driver has been stopped while waiting.
 *
 * @api
 */
msg_t sioSynchronizeTXEnd(void *ip, sysinterval_t timeout) {
  hal_sio_driver_c *self = (hal_sio_driver_c *)ip;
  msg_t msg;

  osalDbgCheck(self != NULL);

  osalSysLock();

  osalDbgAssert(self->drv.state == HAL_DRV_STATE_READY, "invalid state");

  /*lint -save -e506 -e774 [2.1, 14.3] Silencing this error because
    it is tested with a template implementation of sio_lld_is_tx_ongoing()
    which is constant.*/
  if (sioIsTXOngoingX(self)) {
  /*lint -restore*/
    msg = osalThreadSuspendTimeoutS(&self->sync_txend, timeout);
  }
  else {
    msg = MSG_OK;
  }

  osalSysUnlock();

  return msg;
}
#endif /* SIO_USE_SYNCHRONIZATION == TRUE */
/** @} */

#endif /* HAL_USE_SIO == TRUE */

/** @} */
