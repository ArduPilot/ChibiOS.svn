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
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return oqWriteTimeout(&bsp->oqueue, bp, n, TIME_INFINITE);
}

static size_t __bs_stm_read_impl(void *ip, uint8_t *bp, size_t n) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return iqReadTimeout(&bsp->iqueue, bp, n, TIME_INFINITE);
}

static msg_t __bs_stm_put_impl(void *ip, uint8_t b) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return oqPutTimeout(&bsp->oqueue, b, TIME_INFINITE);
}

static msg_t __bs_stm_get_impl(void *ip) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return iqGetTimeout(&bsp->iqueue, TIME_INFINITE);
}

static size_t __bs_chn_writet_impl(void *ip, const uint8_t *bp, size_t n,
                                   sysinterval_t timeout) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return oqWriteTimeout(&bsp->oqueue, bp, n, timeout);
}

static size_t __bs_chn_readt_impl(void *ip, uint8_t *bp, size_t n,
                                  sysinterval_t timeout) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return iqReadTimeout(&bsp->iqueue, bp, n, timeout);
}

static msg_t __bs_chn_putt_impl(void *ip, uint8_t b, sysinterval_t timeout) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return oqPutTimeout(&bsp->oqueue, b, timeout);
}

static msg_t __bs_chn_gett_impl(void *ip, sysinterval_t timeout) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  return iqGetTimeout(&bsp->iqueue, timeout);
}

static eventflags_t __bs_chn_getclr_impl(void *ip, eventflags_t mask) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  (void)bsp;
  (void)mask;

  return 0;
}

static msg_t __bs_chn_ctl_impl(void *ip, unsigned int operation, void *arg) {
  hal_buffered_serial_c *bsp = oopIfGetOwner(hal_buffered_serial_c, ip);

  (void)bsp;
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
 * @name        Methods implementations of hal_buffered_serial_c
 * @{
 */
/** @} */

/**
 * @name        Regular methods of hal_buffered_serial_c
 * @{
 */
/**
 * @memberof    hal_buffered_serial_c
 * @public
 *
 * @brief       Handles incoming data.
 * @details     This function must be called from the input interrupt service
 *              routine in order to enqueue incoming data and generate the
 *              related events.
 * @note        The incoming data event is only generated when the input queue
 *              becomes non-empty.
 *
 * @param[in,out] ip            Pointer to a @p hal_buffered_serial_c instance.
 * @param[in]     b             The byte to be written to the driver's Input
 *                              Queue
 */
void bsIncomingDataI(void *ip, uint8_t b) {
  hal_buffered_serial_c *self = (hal_buffered_serial_c *)ip;

  osalDbgCheckClassI();
  osalDbgCheck(self != NULL);

  if (iqIsEmptyI(&self->iqueue)) {
    bsAddFlagsI(self, CHN_FL_RX_NOTEMPTY);
  }

  if (iqPutI(&self->iqueue, b) < MSG_OK) {
    bsAddFlagsI(self, CHN_FL_BUFFER_FULL_ERR);
  }
}

/**
 * @memberof    hal_buffered_serial_c
 * @public
 *
 * @brief       Handles outgoing data.
 * @details     Must be called from the output interrupt service routine in
 *              order to get the next byte to be transmitted.
 *
 * @param[in,out] ip            Pointer to a @p hal_buffered_serial_c instance.
 * @return                      The byte value read from the driver's output
 *                              queue.
 * @retval MSG_TIMEOUT          If the queue is empty.
 */
msg_t bsRequestDataI(void *ip) {
  hal_buffered_serial_c *self = (hal_buffered_serial_c *)ip;
  msg_t  b;

  osalDbgCheckClassI();
  osalDbgCheck(self != NULL);

  b = oqGetI(&self->oqueue);
  if (b < MSG_OK) {
    /* Note, this event is only added when the buffer becomes fully empty in
       order to avoid continuous reporting.*/
    bsAddFlagsI(self, CHN_FL_TX_NOTFULL);
  }

  return b;
}
/** @} */

/** @} */
