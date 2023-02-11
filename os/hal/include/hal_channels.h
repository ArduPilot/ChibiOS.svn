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
 * @file        hal_channels.h
 * @brief       Generated I/O Channels header.
 *
 * @addtogroup  HAL_CHANNELS
 * @brief       Sequential data streams interface.
 * @note        This is a generated file, do not edit directly.
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
 * @brief       Invalid operation code.
 */
#define CHN_CTL_INVALID                     0

/**
 * @brief       Does nothing.
 */
#define CHN_CTL_NOP                         1

/**
 * @brief       Wait for TX completion.
 */
#define CHN_CTL_TX_WAIT                     2
/** @} */

/**
 * @name    SIO events offsets
 * @{
 */
#define CHN_CONNECTED_POS                   0
#define CHN_DISCONNECTED_POS                1
#define CHN_INPUT_AVAILABLE_POS             2
#define CHN_OUTPUT_EMPTY_POS                2
#define CHN_TRANSMISSION_END_POS            4
#define CHN_ALL_ERRORS_POS                  5
#define CHN_PARITY_ERROR_POS                5
#define CHN_FRAMING_ERROR_POS               6
#define CHN_NOISE_ERROR_POS                 7
#define CHN_OVERRUN_ERROR_POS               8
#define CHN_IDLE_DETECTED_POS               9
#define CHN_BREAK_DETECTED_POS              10
#define CHN_BUFFER_FULL_ERROR_POS           11
/** @} */

/**
 * @name    SIO events masks
 * @{
 */
#define CHN_NO_ERROR                        0U
#define CHN_CONNECTED                       (1U << CHN_CONNECTED_POS)
#define CHN_DISCONNECTED                    (1U << CHN_DISCONNECTED_POS)
#define CHN_INPUT_AVAILABLE                 (1U << CHN_INPUT_AVAILABLE_POS)
#define CHN_OUTPUT_EMPTY                    (1U << CHN_OUTPUT_EMPTY_POS)
#define CHN_TRANSMISSION_END                (1U << CHN_TRANSMISSION_END_POS)
#define CHN_ALL_ERRORS                      (15U << CHN_ALL_ERRORS_POS)
#define CHN_PARITY_ERROR                    (1U << CHN_PARITY_ERROR_POS)
#define CHN_FRAMING_ERROR                   (1U << CHN_FRAMING_ERROR_POS)
#define CHN_NOISE_ERROR                     (1U << CHN_NOISE_ERROR_POS)
#define CHN_OVERRUN_ERROR                   (1U << CHN_OVERRUN_ERROR_POS)
#define CHN_IDLE_DETECTED                   (1U << CHN_IDLE_DETECTED_POS)
#define CHN_BREAK_DETECTED                  (1U << CHN_BREAK_DETECTED_POS)
#define CHN_BUFFER_FULL_ERROR               (1U << CHN_BUFFER_FULL_ERROR_POS)
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
 * @brief       Channel blocking write.
 * @details     This function writes data from a buffer to a channel. If the
 *              channel is not ready to accept data then the calling thread is
 *              suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @param[in]     bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred.
 */
#define chnWrite(ip, bp, n)                                                 \
  streamWrite(ip, bp, n)

/**
 * @brief       Channel blocking read with timeout.
 * @details     The function reads data from a channel into a buffer. If the
 *              data is not available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @param[out]    bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred.
 */
#define chnRead(ip, bp, n)                                                  \
  streamRead(ip, bp, n)

/**
 * @brief       Channel blocking byte write with timeout.
 * @details     This function writes a byte value to a channel. If the channel
 *              is not ready to accept data then the calling thread is
 *              suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @param[in]     b             The byte value to be written to the channel.
 * @return                      The operation status.
 * @retval STM_OK               If the operation succeeded."
 * @retval STM_RESET            If the channel was reset."
 */
#define chnPut(ip, b)                                                       \
  streamPut(ip, b)

/**
 * @brief       Channel blocking byte read with timeout.
 * @details     This function reads a byte value from a channel. If the data is
 *              not available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_channel_c structure.
 * @return                      A byte value from the channel.
 * @retval STM_RESET            If the channel was reset."
 */
#define chnGet(ip)                                                          \
  streamGet(ip)
/** @} */

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module interface asynchronous_channel_i                                   */
/*===========================================================================*/

/**
 * @interface   asynchronous_channel_i
 * @extends     sequential_stream_i
 *
 * @brief       Base I/O channel interface.
 * @details     This header defines an abstract interface useful to access
 *              generic I/O serial devices in a standardized way.
 * @note        The interface namespace is <tt>chn</tt>, access to an
 *              implemented interface is done using:
 *              <tt>&<objp>-><classnamespace>.chn</tt>.
 */

/**
 * @brief       Type of a base I/O channel interface.
 */
typedef struct asynchronous_channel asynchronous_channel_i;

/**
 * @brief       @p asynchronous_channel_i methods as a structure.
 */
struct chn_methods {
  size_t (*writet)(void *ip, const uint8_t *bp, size_t n, sysinterval_t timeout);
  size_t (*readt)(void *ip, uint8_t *bp, size_t n, sysinterval_t timeout);
  msg_t (*putt)(void *ip, uint8_t b, sysinterval_t timeout);
  msg_t (*gett)(void *ip, sysinterval_t timeout);
  msg_t (*ctl)(void *ip, unsigned int operation, void *arg);
};

/**
 * @brief       @p asynchronous_channel_i methods.
 */
#define __chn_methods                                                       \
  __stm_methods                                                             \
  struct chn_methods                        chn;

/**
 * @brief       @p asynchronous_channel_i VMT initializer.
 */
#define __chn_vmt_init(ns)                                                  \
  __stm_vmt_init(ns)                                                        \
  .chn.writet                               = __##ns##_writet_impl,         \
  .chn.readt                                = __##ns##_readt_impl,          \
  .chn.putt                                 = __##ns##_putt_impl,           \
  .chn.gett                                 = __##ns##_gett_impl,           \
  .chn.ctl                                  = __##ns##_ctl_impl,

/**
 * @brief       @p asynchronous_channel_i virtual methods table.
 */
struct asynchronous_channel_vmt {
  __chn_methods
};

/**
 * @brief       Structure representing a base I/O channel.
 */
struct asynchronous_channel {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct asynchronous_channel_vmt     *vmt;
};

/**
 * @name        Interface methods of asynchronous_channel_i
 * @{
 */
/**
 * @memberof    asynchronous_channel_i
 * @public
 *
 * @brief       Channel blocking write with timeout.
 * @details     This function writes data from a buffer to a channel. If the
 *              channel is not ready to accept data then the calling thread is
 *              suspended.
 *
 * @param[in,out] ip            Pointer to a @p asynchronous_channel_i, or
 *                              derived, interface.
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
  asynchronous_channel_i *self = (asynchronous_channel_i *)ip;
  return self->vmt->chn.writet(ip, bp, n, timeout);
}

/**
 * @memberof    asynchronous_channel_i
 * @public
 *
 * @brief       Channel blocking read with timeout.
 * @details     The function reads data from a channel into a buffer. If the
 *              data is not available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p asynchronous_channel_i, or
 *                              derived, interface.
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
  asynchronous_channel_i *self = (asynchronous_channel_i *)ip;
  return self->vmt->chn.readt(ip, bp, n, timeout);
}

/**
 * @memberof    asynchronous_channel_i
 * @public
 *
 * @brief       Channel blocking byte write with timeout.
 * @details     This function writes a byte value to a channel. If the channel
 *              is not ready to accept data then the calling thread is
 *              suspended.
 *
 * @param[in,out] ip            Pointer to a @p asynchronous_channel_i, or
 *                              derived, interface.
 * @param[in]     b             The byte value to be written to the channel.
 * @param[in]     timeout       The number of ticks before the operation
 *                              timeouts, the following special values are
 *                              allowed:
 *                              - @a TIME_IMMEDIATE immediate timeout.
 *                              - @a TIME_INFINITE no timeout.
 *                              .
 * @return                      The operation status.
 * @retval STM_OK               If the operation succeeded."
 * @retval STM_TIMEOUT          If the specified time expired."
 * @retval STM_RESET            If the channel was reset."
 */
CC_FORCE_INLINE
static inline msg_t chnPutTimeout(void *ip, uint8_t b, sysinterval_t timeout) {
  asynchronous_channel_i *self = (asynchronous_channel_i *)ip;
  return self->vmt->chn.putt(ip, b, timeout);
}

/**
 * @memberof    asynchronous_channel_i
 * @public
 *
 * @brief       Channel blocking byte read with timeout.
 * @details     This function reads a byte value from a channel. If the data is
 *              not available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p asynchronous_channel_i, or
 *                              derived, interface.
 * @param[in]     timeout       The number of ticks before the operation
 *                              timeouts, the following special values are
 *                              allowed:
 *                              - @a TIME_IMMEDIATE immediate timeout.
 *                              - @a TIME_INFINITE no timeout.
 *                              .
 * @return                      A byte value from the channel.
 * @retval STM_TIMEOUT          If the specified time expired."
 * @retval STM_RESET            If the channel was reset."
 */
CC_FORCE_INLINE
static inline msg_t chnGetTimeout(void *ip, sysinterval_t timeout) {
  asynchronous_channel_i *self = (asynchronous_channel_i *)ip;
  return self->vmt->chn.gett(ip, timeout);
}

/**
 * @memberof    asynchronous_channel_i
 * @public
 *
 * @brief       Control operation on a channel.
 *
 * @param[in,out] ip            Pointer to a @p asynchronous_channel_i, or
 *                              derived, interface.
 * @param[in]     operation     Control operation code
 * @param[in,out] arg           Operation argument
 * @return                      The operation status.
 * @retval STM_OK               If the operation succeeded."
 * @retval STM_TIMEOUT          If the specified time expired."
 * @retval STM_RESET            If the channel was reset."
 */
CC_FORCE_INLINE
static inline msg_t chnControl(void *ip, unsigned int operation, void *arg) {
  asynchronous_channel_i *self = (asynchronous_channel_i *)ip;
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
