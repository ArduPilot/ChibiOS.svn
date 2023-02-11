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
 * @file        hal_sio.h
 * @brief       Generated SIO Driver header.
 *
 * @addtogroup  HAL_SIO
 * @brief       SIO Driver macros and structures.
 * @note        This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef HAL_SIO_H
#define HAL_SIO_H

#if (HAL_USE_SIO == TRUE) || defined (__DOXYGEN__)

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    SIO masks offsets
 * @{
 */
#define SIO_EV_RXNOTEMPY_POS                CHN_INPUT_AVAILABLE_POS
#define SIO_EV_TXNOTFULL_POS                CHN_OUTPUT_EMPTY_POS
#define SIO_EV_TXDONE_POS                   CHN_TRANSMISSION_END_POS
#define SIO_EV_ALL_ERRORS_POS               CHN_PARITY_ERROR_POS
#define SIO_EV_PARITY_ERR_POS               CHN_PARITY_ERROR_POS
#define SIO_EV_FRAMING_ERR_POS              CHN_FRAMING_ERROR_POS
#define SIO_EV_NOISE_ERR_POS                CHN_NOISE_ERROR_POS
#define SIO_EV_OVERRUN_ERR_POS              CHN_OVERRUN_ERROR_POS
#define SIO_EV_RXIDLE_POS                   CHN_IDLE_DETECTED_POS
#define SIO_EV_RXBREAK_POS                  CHN_BREAK_DETECTED_POS
/** @} */

/**
 * @name    SIO event flags
 * @{
 */
#define SIO_EV_NONE                         0U
#define SIO_EV_RXNOTEMPY                    CHN_INPUT_AVAILABLE
#define SIO_EV_TXNOTFULL                    CHN_OUTPUT_EMPTY
#define SIO_EV_ALL_DATA                     (SIO_EV_RXNOTEMPY | SIO_EV_TXNOTFULL)
#define SIO_EV_TXDONE                       CHN_TRANSMISSION_END
#define SIO_EV_ALL_ERRORS                   CHN_ALL_ERRORS
#define SIO_EV_PARITY_ERR                   CHN_PARITY_ERROR
#define SIO_EV_FRAMING_ERR                  CHN_FRAMING_ERROR
#define SIO_EV_NOISE_ERR                    CHN_NOISE_ERROR
#define SIO_EV_OVERRUN_ERR                  CHN_OVERRUN_ERROR
#define SIO_EV_RXIDLE                       CHN_IDLE_DETECTED
#define SIO_EV_RXBREAK                      CHN_BREAK_DETECTED
#define SIO_EV_ALL_EVENTS                   (SIO_EV_ALL_DATA | SIO_EV_ALL_ERRORS | SIO_EV_TXDONE | SIO_EV_RXIDLE)
/** @} */

/**
 * @name    Additional messages
 * @{
 */
#define SIO_MSG_ERRORS                      1
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief       Default bit rate.
 * @details     Configuration parameter, this is the baud rate selected for the
 *              default configuration.
 */
#if !defined(SIO_DEFAULT_BITRATE) || defined(__DOXYGEN__)
#define SIO_DEFAULT_BITRATE                 38400
#endif

/**
 * @brief       Support for thread synchronization API.
 */
#if !defined(SIO_USE_SYNCHRONIZATION) || defined(__DOXYGEN__)
#define SIO_USE_SYNCHRONIZATION             TRUE
#endif

/**
 * @brief       Support for streams interface.
 */
#if !defined(SIO_USE_STREAMS_INTERFACE) || defined(__DOXYGEN__)
#define SIO_USE_STREAMS_INTERFACE           SIO_USE_SYNCHRONIZATION
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Checks on SIO_DEFAULT_BITRATE configuration.*/
#if SIO_DEFAULT_BITRATE <= 0
#error "invalid SIO_DEFAULT_BITRATE value"
#endif

/* Checks on SIO_USE_SYNCHRONIZATION configuration.*/
#if (SIO_USE_SYNCHRONIZATION != FALSE) && (SIO_USE_SYNCHRONIZATION != TRUE)
#error "invalid SIO_USE_SYNCHRONIZATION value"
#endif

/* Checks on SIO_USE_STREAMS_INTERFACE configuration.*/
#if (SIO_USE_STREAMS_INTERFACE != FALSE) && (SIO_USE_STREAMS_INTERFACE != TRUE)
#error "invalid SIO_USE_STREAMS_INTERFACE value"
#endif

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief       Associates a callback to the SIO instance.
 *
 * @param[out]    siop          Pointer to the @p hal_sio_driver_c object
 * @param         f             Callback function to be associated.
 *
 * @xclass
 */
#define sioSetCallbackX(siop, f)                                            \
  (siop)->sio.cb = (f)

/**
 * @brief       Determines the state of the RX FIFO.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The RX FIFO state.
 *
 * @xclass
 */
#define sioIsRXEmptyX(siop)                                                 \
  sio_lld_is_rx_empty(siop)

/**
 * @brief       Determines the activity state of the receiver.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The RX activity state.
 *
 * @xclass
 */
#define sioIsRXIdleX(siop)                                                  \
  sio_lld_is_rx_idle(siop)

/**
 * @brief       Determines if RX has pending errors to be read and cleared.
 * @note        Only error flags are handled, data and idle flags are not
 *              considered.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The RX error events.
 *
 * @xclass
 */
#define sioHasRXErrorsX(siop)                                               \
  sio_lld_has_rx_errors(siop)

/**
 * @brief       Determines the state of the TX FIFO.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The TX FIFO state.
 *
 * @xclass
 */
#define sioIsTXFullX(siop)                                                  \
  sio_lld_is_tx_full(siop)

/**
 * @brief       Determines the transmission state.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The transmission state.
 *
 * @xclass
 */
#define sioIsTXOngoingX(siop)                                               \
  sio_lld_is_tx_ongoing(siop)

/**
 * @brief       Writes the enabled events mask.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     mask          Enabled events mask to be written.
 *
 * @xclass
 */
#define sioWriteEnableFlagsX(siop, mask)                                    \
  do {                                                                      \
    (siop)->sio.enabled = (mask);                                           \
    sio_lld_update_enable_flags(siop);                                      \
  } while (false)

/**
 * @brief       Sets flags into the enabled events flags mask.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     mask          Enabled events mask to be set.
 *
 * @xclass
 */
#define sioSetEnableFlagsX(siop, mask)                                      \
  do {                                                                      \
    (siop)->sio.enabled |= (mask);                                          \
    sio_lld_update_enable_flags(siop);                                      \
  } while (false)

/**
 * @brief       Clears flags from the enabled events flags mask.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     mask          Enabled events mask to be cleared.
 *
 * @xclass
 */
#define sioClearEnableFlagsX(siop, mask)                                    \
  do {                                                                      \
    (siop)->sio.enabled &= ~(mask);                                         \
    sio_lld_update_enable_flags(siop);                                      \
  } while (false)

/**
 * @brief       Gets the enabled condition flags mask.
 *
 * @param[in]     siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The enabled event flags.
 *
 * @xclass
 */
#define sioGetEnableFlagsX(siop)                                            \
  (siop)->sio.enabled

/**
 * @brief       Gets and clears SIO error flags.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The pending error flags.
 *
 * @xclass
 */
#define sioGetAndClearErrorsX(siop)                                         \
  sio_lld_get_and_clear_errors(siop)

/**
 * @brief       Gets and clears SIO event flags.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The pending event flags.
 *
 * @xclass
 */
#define sioGetAndClearEventsX(siop)                                         \
  sio_lld_get_and_clear_events(siop)

/**
 * @brief       Returns all SIO event flags.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The pending event flags.
 *
 * @xclass
 */
#define sioGetEventsX(siop)                                                 \
  sio_lld_get_events(siop)

/**
 * @brief       Returns one frame from the RX FIFO.
 * @note        If the FIFO is empty then the returned value is unpredictable.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The frame from RX FIFO.
 *
 * @xclass
 */
#define sioGetX(siop)                                                       \
  sio_lld_get(siop)

/**
 * @brief       Pushes one frame into the TX FIFO.
 * @note        If the FIFO is full then the behavior is unpredictable.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     data          Frame to be written.
 *
 * @xclass
 */
#define sioPutX(siop, data)                                                 \
  sio_lld_put(siop, data)

/**
 * @brief       Reads data from the RX FIFO.
 * @details     This function is non-blocking, data is read if present and the
 *              effective amount is returned.
 * @note        This function can be called from any context but it is meant to
 *              be called from the @p cb callback handler.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     size          Maximum number of frames to read.
 * @param[out]    buffer        Buffer for the received data.
 * @return                      The number of received frames.
 * @retval 0                    RX FIFO is empty.
 *
 * @xclass
 */
#define sioAsyncReadX(siop, size, buffer)                                   \
  sio_lld_read(siop, size, buffer)

/**
 * @brief       Writes data into the TX FIFO.
 * @details     This function is non-blocking, data is written if there is
 *              space in the FIFO and the effective amount is returned.
 * @note        This function can be called from any context but it is meant to
 *              be called from the @p cb callback handler.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     size          Maximum number of frames to read.
 * @param[in]     buffer        Buffer containing the data to be transmitted
 * @return                      The number of transmitted frames.
 * @retval 0                    TX FIFO is full.
 *
 * @xclass
 */
#define sioAsyncWriteX(siop, size, buffer)                                  \
  sio_lld_write(siop, size, buffer)

/**
 * @brief       Control operation on a serial port.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @param[in]     operation     Control operation code.
 * @param[in,out] arg           Operation argument.
 * @return                      The control operation status.
 *
 * @xclass
 */
#define sioControlX(siop, operation, arg)                                   \
  sio_lld_control(siop, operation, arg)

/**
 * @name    Low level driver helper macros
 * @{
 */
/**
 * @brief       SIO callback.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 * @return                      The control operation status.
 *
 * @notapi
 */
#define __sio_callback(siop)                                                \
  do {                                                                      \
    if ((siop)->sio.cb != NULL) {                                           \
      (siop)->sio.cb(siop);                                                 \
    }                                                                       \
  } while (false)

#if (SIO_USE_SYNCHRONIZATION == TRUE) || defined (__DOXYGEN__)
/**
 * @brief       Wakes up because RX errors.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 *
 * @notapi
 */
#define __sio_wakeup_errors(siop)                                           \
  do {                                                                      \
    osalSysLockFromISR();                                                   \
    osalThreadResumeI(&(siop)->sio.sync_rx, SIO_MSG_ERRORS);                \
    osalThreadResumeI(&(siop)->sio.sync_rxidle, SIO_MSG_ERRORS);            \
    osalSysUnlockFromISR();                                                 \
  } while (false)

/**
 * @brief       Wakes up the RX-waiting thread.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 *
 * @notapi
 */
#define __sio_wakeup_rx(siop)                                               \
  do {                                                                      \
    osalSysLockFromISR();                                                   \
    osalThreadResumeI(&(siop)->sio.sync_rx, MSG_OK);                        \
    osalSysUnlockFromISR();                                                 \
  } while (false)

/**
 * @brief       Wakes up the RX-idle-waiting thread.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 *
 * @notapi
 */
#define __sio_wakeup_rxidle(siop)                                           \
  do {                                                                      \
    osalSysLockFromISR();                                                   \
    osalThreadResumeI(&(siop)->sio.sync_rxidle, MSG_OK);                    \
    osalSysUnlockFromISR();                                                 \
  } while (false)

/**
 * @brief       Wakes up the TX-waiting thread.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 *
 * @notapi
 */
#define __sio_wakeup_tx(siop)                                               \
  do {                                                                      \
    osalSysLockFromISR();                                                   \
    osalThreadResumeI(&(siop)->sio.sync_tx, MSG_OK);                        \
    osalSysUnlockFromISR();                                                 \
  } while (false)

/**
 * @brief       Wakes up the TXend-waiting thread.
 *
 * @param[in,out] siop          Pointer to the @p hal_sio_driver_c object
 *
 * @notapi
 */
#define __sio_wakeup_txend(siop)                                            \
  do {                                                                      \
    osalSysLockFromISR();                                                   \
    osalThreadResumeI(&(siop)->sio.sync_txend, MSG_OK);                     \
    osalSysUnlockFromISR();                                                 \
  } while (false)

#else
#define __sio_wakeup_errors(siop)
#define __sio_wakeup_rx(siop)
#define __sio_wakeup_rxidle(siop)
#define __sio_wakeup_tx(siop)
#define __sio_wakeup_txend(siop)
#endif /* SIO_USE_SYNCHRONIZATION == TRUE */
/** @} */

/**
 * @brief       Relocates a bit field.
 *
 * @param[in]     v             Value.
 * @param[in]     m             Mask of the bit field.
 * @param[in]     s             Source bit offset.
 * @param[in]     d             Destination bit offset.
 */
#define __sio_reloc_field(v, m, s, d)                                       \
  ((((v) & m) >> (s)) << (d))

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief       Type of SIO event flags.
 */
typedef eventflags_t sioevents_t;

/**
 * @brief       Type of structure representing a SIO configuration.
 */
typedef struct hal_sio_config hal_sio_config_t;

/**
 * @brief       Type of structure representing a SIO configuration (legacy).
 */
typedef struct hal_sio_config SIOConfig;

/**
 * @brief       Type of structure representing a SIO driver (legacy).
 */
typedef struct hal_sio_driver SIODriver;

/**
 * @brief       Generic SIO notification callback type.
 */
typedef void (*siocb_t)(struct hal_sio_driver *siop);

/* Inclusion of LLD header.*/
#include "hal_sio_lld.h"

/**
 * @brief       Driver configuration structure.
 * @note        Implementations may extend this structure to contain more,
 *              architecture dependent, fields.
 */
struct hal_sio_config {
  /* End of the mandatory fields.*/
  sio_lld_config_fields;
#if (defined(SIO_CONFIG_EXT_FIELS)) || defined (__DOXYGEN__)
  SIO_CONFIG_EXT_FIELDS
#endif /* defined(SIO_CONFIG_EXT_FIELS) */
};

/*===========================================================================*/
/* Module class hal_sio_driver_c                                             */
/*===========================================================================*/

/**
 * @class       hal_sio_driver_c
 * @extends     hal_base_driver_c
 * @implements  asynchronous_channel_i
 *
 * @brief       Class of a SIO (Serial I/O) driver.
 * @note        The class namespace is <tt>sio</tt>, access to class fields is
 *              done using: <tt><objp>->sio.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 */

/**
 * @brief       Type of a SIO driver class.
 */
typedef struct hal_sio_driver hal_sio_driver_c;

/**
 * @brief       @p hal_sio_driver_c data as a structure.
 */
struct sio_data {
#if (SIO_USE_STREAMS_INTERFACE == TRUE) || defined (__DOXYGEN__)
  /**
   * @brief       Channel interface.
   */
  asynchronous_channel_i                    chn;
#endif /* SIO_USE_STREAMS_INTERFACE == TRUE */
  /**
   * @brief       Enabled event flags.
   */
  sioevents_t                               enabled;
  /**
   * @brief       Events callback.
   * @note        Can be @p NULL.
   */
  siocb_t                                   cb;
#if (HAL_USE_MUTUAL_EXCLUSION == TRUE) || defined (__DOXYGEN__)
  /**
   * @brief       Synchronization point for RX.
   */
  thread_reference_t                        sync_rx;
  /**
   * @brief       Synchronization point for RX idle.
   */
  thread_reference_t                        sync_rxidle;
  /**
   * @brief       Synchronization point for TX.
   */
  thread_reference_t                        sync_tx;
  /**
   * @brief       Synchronization point for TX-end.
   */
  thread_reference_t                        sync_txend;
#endif /* HAL_USE_MUTUAL_EXCLUSION == TRUE */
#if defined(SIO_DRIVER_EXT_FIELS)
  SIO_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  sio_lld_driver_fields;
};

/**
 * @brief       @p hal_sio_driver_c methods.
 */
#define __sio_methods                                                       \
  __drv_methods                                                             \
  /* No methods.*/

/**
 * @brief       @p hal_sio_driver_c data.
 */
#define __sio_data                                                          \
  __drv_data                                                                \
  struct sio_data                           sio;

/**
 * @brief       @p hal_sio_driver_c VMT initializer.
 */
#define __sio_vmt_init(ns)                                                  \
  __drv_vmt_init(ns)

/**
 * @brief       @p hal_sio_driver_c virtual methods table.
 */
struct hal_sio_driver_vmt {
  __sio_methods
};

/**
 * @brief       Structure representing a SIO driver class.
 */
struct hal_sio_driver {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct hal_sio_driver_vmt           *vmt;
  __sio_data
};

/**
 * @memberof    hal_sio_driver_c
 *
 * @brief       Access macro for hal_sio_driver_c interfaces.
 *
 * @param[in]     ip            Pointer to the class instance.
 * @param         ifns          Implemented interface namespace.
 * @return                      A void pointer to the interface within the
 *                              class instance.
 *
 * @api
 */
#define sioGetIf(ip, ifns)                                                  \
  boGetIf(ip, ifns, sio)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of hal_sio_driver_c.*/
  hal_sio_driver_c *sioObjectInit(hal_sio_driver_c *self);
  void sioDispose(hal_sio_driver_c *self);
  void sioWriteEnableFlags(void *ip, sioevents_t mask);
  void sioSetEnableFlags(void *ip, sioevents_t mask);
  void sioClearEnableFlags(void *ip, sioevents_t mask);
  sioevents_t sioGetAndClearErrors(void *ip);
  sioevents_t sioGetAndClearEvents(void *ip);
  sioevents_t sioGetEvents(void *ip);
#if (SIO_USE_SYNCHRONIZATION == TRUE) || defined (__DOXYGEN__)
  msg_t sioSynchronizeRX(void *ip, sysinterval_t timeout);
  msg_t sioSynchronizeRXIdle(void *ip, sysinterval_t timeout);
  msg_t sioSynchronizeTX(void *ip, sysinterval_t timeout);
  msg_t sioSynchronizeTXEnd(void *ip, sysinterval_t timeout);
#endif /* SIO_USE_SYNCHRONIZATION == TRUE */
  void *__sio_objinit_impl(void *ip, const void *vmt);
  void __sio_dispose_impl(void *ip);
  /* Regular functions.*/
  void sioInit(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* HAL_USE_SIO == TRUE */

#endif /* HAL_SIO_H */

/** @} */
