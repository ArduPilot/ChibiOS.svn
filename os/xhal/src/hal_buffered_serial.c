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
 * @file        hal_buffered_serial.c
 * @brief       Generated Buffered Serial Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  HAL_BUFFERED_SERIAL
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

static size_t __bs_stm_write_impl(void *ip, const uint8_t *bp, size_t n) {

  (void)ip;
  (void)bp;
  (void)n;

  return 0;
}

static size_t __bs_stm_read_impl(void *ip, uint8_t *bp, size_t n) {

  (void)ip;
  (void)bp;
  (void)n;

  return 0;
}

static msg_t __bs_stm_put_impl(void *ip, uint8_t b) {

  (void)ip;
  (void)b;

  return 0;
}

static msg_t __bs_stm_get_impl(void *ip) {

  (void)ip;

  return 0;
}

static size_t __bs_chn_writet_impl(void *ip, const uint8_t *bp, size_t n,
                                   sysinterval_t timeout) {

  (void)ip;
  (void)bp;
  (void)n;
  (void)timeout;

  return 0;
}

static size_t __bs_chn_readt_impl(void *ip, uint8_t *bp, size_t n,
                                  sysinterval_t timeout) {

  (void)ip;
  (void)bp;
  (void)n;
  (void)timeout;

  return 0;
}

static msg_t __bs_chn_putt_impl(void *ip, uint8_t b, sysinterval_t timeout) {

  (void)ip;
  (void)b;
  (void)timeout;

  return 0;
}

static msg_t __bs_chn_gett_impl(void *ip, sysinterval_t timeout) {

  (void)ip;
  (void)timeout;

  return 0;
}

static eventflags_t __bs_chn_getclrevt_impl(void *ip) {

  (void)ip;

  return 0;
}

static msg_t __bs_chn_ctl_impl(void *ip, unsigned int operation, void *arg) {

  (void)ip;
  (void)operation;
  (void)arg;

  return 0;
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module class "hal_buffered_serial_c" methods.                             */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of hal_buffered_serial_c
 * @{
 */
/**
 * @memberof    hal_buffered_serial_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p hal_buffered_serial_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     ib            Pointer to the input buffer
 * @param[in]     ibsize        Size of the input buffer
 * @param[in]     inotify       Pointer to a callback function that is invoked
 *                              when some data is read from the input queue.
 *                              The value can be @p NULL
 * @param[in]     iarg          Parameter for the input notification callback
 * @param[in]     ob            Pointer to the output buffer
 * @param[in]     obsize        Size of the output buffer
 * @param[in]     onotify       Pointer to a callback function that is invoked
 *                              when some data is written to the output queue.
 *                              The value can be @p NULL
 * @param[in]     oarg          Parameter for the output notification callback
 * @return                      A new reference to the object.
 */
void *__bs_objinit_impl(void *ip, const void *vmt, uint8_t *ib, size_t ibsize,
                        qnotify_t inotify, void *iarg, uint8_t *ob,
                        size_t obsize, qnotify_t onotify, void *oarg) {
  hal_buffered_serial_c *self = (hal_buffered_serial_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __drv_objinit_impl(self, vmt);

  /* Implementation of interface asynchronous_channel_i.*/
  {
    static const struct asynchronous_channel_vmt bs_chn_vmt = {
      __chn_vmt_init(bs, offsetof(hal_buffered_serial_c, bs.chn))
    };
    oopIfObjectInit(&self->bs.chn, &bs_chn_vmt);
  }

  /* Initialization code.*/

  osalEventObjectInit(&self->bs.event);
  iqObjectInit(&self->bs.iqueue, ib, ibsize, inotify, iarg);
  oqObjectInit(&self->bs.oqueue, ob, obsize, onotify, oarg);

  return self;
}

/**
 * @memberof    hal_buffered_serial_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p hal_buffered_serial_c instance
 *                              to be disposed.
 */
void __bs_dispose_impl(void *ip) {
  hal_buffered_serial_c *self = (hal_buffered_serial_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __drv_dispose_impl(self);
}
/** @} */

/** @} */
