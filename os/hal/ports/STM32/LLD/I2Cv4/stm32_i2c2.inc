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
 * @file    I2Cv4/stm32_i2c2.inc
 * @brief   Shared I2C2 handler.
 *
 * @addtogroup STM32_I2C2_HANDLER
 * @{
 */

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Registry checks for robustness.*/
#if !defined(STM32_HAS_I2C2)
#error "STM32_HAS_I2C2 not defined in registry"
#endif

#if STM32_HAS_I2C2

/* Priority settings checks.*/
#if !defined(STM32_IRQ_I2C2_PRIORITY)
#error "STM32_IRQ_I2C2_PRIORITY not defined in mcuconf.h"
#endif

#if !OSAL_IRQ_IS_VALID_PRIORITY(STM32_IRQ_I2C2_PRIORITY)
#error "Invalid IRQ priority assigned to STM32_IRQ_I2C2_PRIORITY"
#endif

#endif /* STM32_HAS_I2C2 */

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static inline void i2c2_irq_init(void) {
#if defined(STM32_I2C2_IS_USED)
#if (STM32_I2C_SINGLE_IRQ == TRUE) || defined(__DOXYGEN__)
  nvicEnableVector(STM32_I2C2_GLOBAL_NUMBER, STM32_IRQ_I2C2_PRIORITY);
#else
  nvicEnableVector(STM32_I2C2_EV_NUMBER, STM32_IRQ_I2C2_PRIORITY);
  nvicEnableVector(STM32_I2C2_ER_NUMBER, STM32_IRQ_I2C2_PRIORITY);
#endif
#endif /* STM32_I2C2_IS_USED */
}

static inline void i2c2_irq_deinit(void) {
#if defined(STM32_I2C2_IS_USED)
#if (STM32_I2C_SINGLE_IRQ == TRUE) || defined(__DOXYGEN__)
  nvicDisableVector(STM32_I2C2_GLOBAL_NUMBER);
#else
  nvicDisableVector(STM32_I2C2_EV_NUMBER);
  nvicDisableVector(STM32_I2C2_ER_NUMBER);
#endif
#endif /* STM32_I2C2_IS_USED */
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if defined(STM32_I2C2_IS_USED) || defined(__DOXYGEN__)
/**
 * @brief   I2C2 interrupt handler.
 *
 * @isr
 */
#if (STM32_I2C_SINGLE_IRQ == TRUE) || defined(__DOXYGEN__)
/**
 * @brief   I2C2 event interrupt handler.
 *
 * @notapi
 */
OSAL_IRQ_HANDLER(STM32_I2C2_GLOBAL_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  i2c_lld_serve_global_interrupt(&I2CD2);

  OSAL_IRQ_EPILOGUE();
}

#else
OSAL_IRQ_HANDLER(STM32_I2C2_EV_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  i2c_lld_serve_ev_interrupt(&I2CD2);

  OSAL_IRQ_EPILOGUE();
}

OSAL_IRQ_HANDLER(STM32_I2C2_ER_HANDLER) {

  OSAL_IRQ_PROLOGUE();

  i2c_lld_serve_er_interrupt(&I2CD2);

  OSAL_IRQ_EPILOGUE();
}
#endif
#endif /* STM32_I2C2_IS_USED */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/** @} */
