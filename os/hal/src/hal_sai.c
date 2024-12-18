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
 * @file    hal_sai.c
 * @brief   SAI Driver code.
 *
 * @addtogroup SAI
 * @{
 */

#include "hal.h"

#if (HAL_USE_SAI == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   SAI Driver initialization.
 * @note    This function is implicitly invoked by @p halInit(), there is
 *          no need to explicitly initialize the driver.
 *
 * @init
 */
void saiInit(void) {

  sai_lld_init();
}

/**
 * @brief   Initializes the standard part of a @p SAIDriver structure.
 *
 * @param[out] saip     pointer to the @p SAIDriver object
 *
 * @init
 */
void saiObjectInit(SAIDriver *saip) {

  saip->state  = SAI_STOP;
  saip->config = NULL;
  /*
   * TODO for to initialize?
   */
  saip->blocks[0].config = NULL;
  saip->blocks[0].state = SAI_SUB_STOP;
  saip->blocks[1].config = NULL;
  saip->blocks[1].state = SAI_SUB_STOP;
}

/**
 * @brief   Configures and activates the SAI peripheral.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 * @param[in] config    pointer to the @p SAIConfig object
 *
 * @api
 */
void saiStart(SAIDriver *saip, const SAIConfig *config) {

  osalDbgCheck((saip != NULL) && (config != NULL));

  osalSysLock();
  osalDbgAssert((saip->state == SAI_STOP) || (saip->state == SAI_READY),
                "invalid state");
  saip->config = config;
  saip->blocks[0].config = &config->blocks[0];
  saip->blocks[1].config = &config->blocks[1];
  sai_lld_start(saip);
  saip->state = SAI_READY;
  saip->blocks[0].state = SAI_SUB_READY;
  saip->blocks[1].state = SAI_SUB_READY;
  osalSysUnlock();
}

/**
 * @brief   Deactivates the SAI peripheral.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @api
 */
void saiStop(SAIDriver *saip) {

  osalDbgCheck(saip != NULL);

  osalSysLock();

  osalDbgAssert((saip->state == SAI_STOP) || (saip->state == SAI_READY),
                "invalid state");

  sai_lld_stop(saip);
  saip->config = NULL;
  saip->state  = SAI_STOP;
  saip->blocks[0].config = NULL;
  saip->blocks[0].state = SAI_SUB_STOP;
  saip->blocks[1].config = NULL;
  saip->blocks[1].state = SAI_SUB_STOP;

  osalSysUnlock();
}

/**
 * @brief   Starts a SAI data exchange.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @api
 */
void saiStartExchange(SAIDriver *saip) {

  osalDbgCheck(saip != NULL);

  osalSysLock();
  osalDbgAssert(saip->state == SAI_READY, "not ready");
  osalDbgAssert(saip->blocks[0].state == SAI_SUB_READY, "not ready");
  osalDbgAssert(saip->blocks[1].state == SAI_SUB_READY, "not ready");
  saiStartExchangeI(saip);
  osalSysUnlock();
}

/**
 * @brief   Stops the ongoing data exchange.
 * @details The ongoing data exchange, if any, is stopped, if the driver
 *          was not active the function does nothing.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @api
 */
void saiStopExchange(SAIDriver *saip) {

  osalDbgCheck((saip != NULL));

  osalSysLock();
  osalDbgAssert((saip->state == SAI_READY) ||
                (saip->blocks[0].state == SAI_SUB_READY) ||
                (saip->blocks[1].state == SAI_SUB_READY) ||
                (saip->blocks[0].state == SAI_SUB_ACTIVE) ||
                (saip->blocks[1].state == SAI_SUB_ACTIVE) ||
                (saip->blocks[0].state == SAI_SUB_COMPLETE) ||
                (saip->blocks[1].state == SAI_SUB_COMPLETE),
                "invalid state");
  saiStopExchangeI(saip);
  osalSysUnlock();
}

#endif /* HAL_USE_SAI == TRUE */

/** @} */
