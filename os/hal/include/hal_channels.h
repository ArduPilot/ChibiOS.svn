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
 * @file    hal_channels.h
 * @brief   Generated HAL_CHANNELS header.
 *
 * @addtogroup HAL_CHANNELS
 * @brief   Sequential data streams interface.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef HAL_CHANNELS_H
#define HAL_CHANNELS_H

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Default control operation codes
 * @{
 */
/**
 * @brief   Invalid operation code.
 */
#define CHN_CTL_INVALID                     0

/**
 * @brief   Does nothing.
 */
#define CHN_CTL_NOP                         1

/**
 * @brief   Wait for TX completion.
 */
#define CHN_CTL_TX_WAIT                     2
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @name    Replicated stream functions
 * @{
 */
/**
 * @brief   Channel blocking write.
 * @details This function writes data from a buffer to a channel. If the
 *          channel is not ready to accept data then the calling thread is
 *          suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @param[in]     bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred.
 */
#define chnWrite(ip, bp, n)                                                 \
  streamWrite(ip, bp, n)

/**
 * @brief   Channel blocking read with timeout.
 * @details The function reads data from a channel into a buffer. If the data
 *          is not available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @param[out]    bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred.
 */
#define chnRead(ip, bp, n)                                                  \
  streamRead(ip, bp, n)

/**
 * @brief   Channel blocking byte write with timeout.
 * @details This function writes a byte value to a channel. If the channel is
 *          not ready to accept data then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @param[in]     b             The byte value to be written to the channel.
 * @return                      The operation status.
 */
#define chnPut(ip, b)                                                       \
  streamPut(ip, b)

/**
 * @brief   Channel blocking byte read with timeout.
 * @details This function reads a byte value from a channel. If the data is not
 *          available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @return                      A byte value from the channel.
 */
#define chnGet(ip)                                                          \
  streamGet(ip)
/** @} */

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module interface base_channel_i                                           */
/*===========================================================================*/

/**
 * @brief   Type of a base I/O channel interface.
 */
typedef struct base_channel base_channel_i;

/**
 * @brief   @p base_channel_i methods as a structure.
 */
struct chn_methods {
  size_t (*writet)(void *ip, const uint8_t *bp, size_t n, sysinterval_t timeout);
  size_t (*readt)(void *ip, uint8_t *bp, size_t n, sysinterval_t timeout);
  msg_t (*putt)(void *ip, uint8_t b, sysinterval_t timeout);
  msg_t (*gett)(void *ip, sysinterval_t timeout);
  msg_t (*ctl)(void *ip, unsigned int operation, void *arg);
};

/**
 * @brief   @p base_channel_i methods.
 */
#define __chn_methods                                                       \
  __stm_methods                                                             \
  struct chn_methods                        chn;

/**
 * @brief   @p base_channel_i VMT initializer.
 */
#define __chn_vmt_init(ns)                                                  \
  __stm_vmt_init(ns)                                                        \
  .chn.writet                               = __##ns##_writet_impl,         \
  .chn.readt                                = __##ns##_readt_impl,          \
  .chn.putt                                 = __##ns##_putt_impl,           \
  .chn.gett                                 = __##ns##_gett_impl,           \
  .chn.ctl                                  = __##ns##_ctl_impl,

/**
 * @brief   @p base_channel_i virtual methods table.
 */
struct base_channel_vmt {
  __chn_methods
};

/**
 * @brief   Structure representing a base I/O channel.
 */
struct base_channel {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct base_channel_vmt             *vmt;
};

/**
 * @name    Interface methods of @p base_channel_i
 * @{
 */
/**
 * @brief   Channel blocking write with timeout.
 * @details This function writes data from a buffer to a channel. If the
 *          channel is not ready to accept data then the calling thread is
 *          suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_i, or derived,
 *                              interface.
 * @param[in]     bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @param[in]     timeout       The number of ticks before the operation
 *                              timeouts, the following special values are
 *                              allowed:
 *                              - @a TIME_IMMEDIATE immediate timeout.
 *                              - @a TIME_INFINITE no timeout.
 *                              .
 * @return                      The number of bytes transferred.
 */
CC_FORCE_INLINE
static inline size_t chnWriteTimeout(void *ip, const uint8_t *bp, size_t n,
                                     sysinterval_t timeout) {
  base_channel_i *self = (base_channel_i *)ip;

  return self->vmt->chn.writet(ip, bp, n, timeout);
}

/**
 * @brief   Channel blocking read with timeout.
 * @details The function reads data from a channel into a buffer. If the data
 *          is not available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_i, or derived,
 *                              interface.
 * @param[in]     bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @param[in]     timeout       The number of ticks before the operation
 *                              timeouts, the following special values are
 *                              allowed:
 *                              - @a TIME_IMMEDIATE immediate timeout.
 *                              - @a TIME_INFINITE no timeout.
 *                              .
 * @return                      The number of bytes transferred.
 */
CC_FORCE_INLINE
static inline size_t chnReadTimeout(void *ip, uint8_t *bp, size_t n,
                                    sysinterval_t timeout) {
  base_channel_i *self = (base_channel_i *)ip;

  return self->vmt->chn.readt(ip, bp, n, timeout);
}

/**
 * @brief   Channel blocking byte write with timeout.
 * @details This function writes a byte value to a channel. If the channel is
 *          not ready to accept data then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_i, or derived,
 *                              interface.
 * @param[in]     b             The byte value to be written to the channel.
 * @param[in]     timeout       The number of ticks before the operation
 *                              timeouts, the following special values are
 *                              allowed:
 *                              - @a TIME_IMMEDIATE immediate timeout.
 *                              - @a TIME_INFINITE no timeout.
 *                              .
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline msg_t chnPutTimeout(void *ip, uint8_t b, sysinterval_t timeout) {
  base_channel_i *self = (base_channel_i *)ip;

  return self->vmt->chn.putt(ip, b, timeout);
}

/**
 * @brief   Channel blocking byte read with timeout.
 * @details This function reads a byte value from a channel. If the data is not
 *          available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_i, or derived,
 *                              interface.
 * @param[in]     timeout       The number of ticks before the operation
 *                              timeouts, the following special values are
 *                              allowed:
 *                              - @a TIME_IMMEDIATE immediate timeout.
 *                              - @a TIME_INFINITE no timeout.
 *                              .
 * @return                      A byte value from the channel.
 */
CC_FORCE_INLINE
static inline msg_t chnGetTimeout(void *ip, sysinterval_t timeout) {
  base_channel_i *self = (base_channel_i *)ip;

  return self->vmt->chn.gett(ip, timeout);
}

/**
 * @brief   Control operation on a channel.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_i, or derived,
 *                              interface.
 * @param[in]     operation     Control operation code
 * @param[in,out] arg           Operation argument
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline msg_t chnControl(void *ip, unsigned int operation, void *arg) {
  base_channel_i *self = (base_channel_i *)ip;

  return self->vmt->chn.ctl(ip, operation, arg);
}
/** @} */

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

#endif /* HAL_CHANNELS_H */

/** @} */
