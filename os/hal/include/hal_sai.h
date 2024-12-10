/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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
 * @file    hal_sai.h
 * @brief   SAI Driver macros and structures.
 *
 * @addtogroup SAI
 * @{
 */

#ifndef HAL_SAI_H
#define HAL_SAI_H

#if (HAL_USE_SAI == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    SAI modes
 * @{
 */
#define SAI_MODE_SLAVE          0
#define SAI_MODE_MASTER         1
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  SAI_UNINIT = 0,                   /**< Not initialized.                   */
  SAI_STOP = 1,                     /**< Stopped.                           */
  SAI_READY = 2,                    /**< Ready.                             */
  SAI_ACTIVE = 3,                   /**< Active.                            */
  SAI_COMPLETE = 4                  /**< Transmission complete.             */
} saistate_t;

/**
 * @brief   Type of a structure representing an SAI driver.
 */
typedef struct hal_sai_driver SAIDriver;

/**
 * @brief   Type of a structure representing an SAI driver configuration.
 */
typedef struct hal_sai_config SAIConfig;

/**
 * @brief   SAI notification callback type.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 */
typedef void (*saicallback_t)(SAIDriver *saip);

/* Including the low level driver header, it exports information required
   for completing types.*/
#include "hal_sai_lld.h"

/**
 * @brief   Structure representing an SAI driver.
 */
struct hal_sai_driver {
  /**
   * @brief   Driver state.
   */
  saistate_t                state;
  /**
   * @brief   Current configuration data.
   */
  const SAIConfig           *config;
  /* End of the mandatory fields.*/
  sai_lld_driver_fields;
};

/**
 * @brief   Driver sai configuration structure.
 */
struct hal_sai_config {
  /**
   * @brief   Buffer pointer.
   */
  void                      *buffer;
  /**
   * @brief   Buffers size as number of samples.
   */
  size_t                    size;
  /**
   * @brief   Callback function called during streaming.
   */
  saicallback_t             end_cb;
  /* End of the mandatory fields.*/
  sai_lld_config_fields;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    Macro Functions
 * @{
 */
/**
 * @brief   Buffer state.
 * @note    This function is meant to be called from the SPI callback only.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 * @return              The buffer state.
 * @retval              false if the driver filled/sent the first half of the
 *                      buffer.
 * @retval              true if the driver filled/sent the second half of the
 *                      buffer.
 *
 * @special
 */
#define saiIsBufferComplete(saip) ((bool)((saip)->state == SAI_COMPLETE))

/**
 * @brief   Starts a SAI data exchange.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @iclass
 */
#define saiStartExchangeI(saip) {                                           \
  sai_lld_start_exchange(saip);                                             \
  (saip)->state = SAI_ACTIVE;                                               \
}

/**
 * @brief   Stops the ongoing data exchange.
 * @details The ongoing data exchange, if any, is stopped, if the driver
 *          was not active the function does nothing.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @iclass
 */
#define saiStopExchangeI(saip) {                                            \
  sai_lld_stop_exchange(saip);                                              \
  (saip)->state = SAI_READY;                                                \
}

/**
 * @brief   Common ISR code, half buffer event.
 * @details This code handles the portable part of the ISR code:
 *          - Callback invocation.
 *          .
 * @note    This macro is meant to be used in the low level drivers
 *          implementation only.
 *
 * @param[in] blockp    pointer to the @p SAI SubBlock
 *
 * @notapi
 */
#define _sai_isr_half_code(saip) {                                          \
  if ((saip)->config->end_cb != NULL) {                                     \
    (saip)->config->end_cb(saip);                                           \
  }                                                                         \
}

/**
 * @brief   Common ISR code.
 * @details This code handles the portable part of the ISR code:
 *          - Callback invocation.
 *          - Driver state transitions.
 *          .
 * @note    This macro is meant to be used in the low level drivers
 *          implementation only.
 *
 * @param[in] saip      pointer to the @p I2CDriver object
 *
 * @notapi
 */
#define _sai_isr_full_code(saip) {                                          \
  if ((saip)->config->end_cb) {                                             \
    (saip)->state = SAI_COMPLETE;                                           \
    (saip)->config->end_cb(saip);                                           \
    if ((saip)->state == SAI_COMPLETE) {                                    \
      (saip)->state = SAI_ACTIVE;                                           \
    }                                                                       \
  }                                                                         \
}
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void saiInit(void);
  void saiObjectInit(SAIDriver *saip);
  void saiStart(SAIDriver *saip, const SAIConfig *config);
  void saiStop(SAIDriver *saip);
  void saiStartExchange(SAIDriver *saip);
  void saiStopExchange(SAIDriver *saip);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SAI == TRUE */

#endif /* HAL_SAI_H */

/** @} */
