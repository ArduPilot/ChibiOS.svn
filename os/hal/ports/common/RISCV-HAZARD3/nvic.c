/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio

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
 * @file    common/RISCV-HAZARD3/nvic.c
 * @brief   RISC-V Hazard3 interrupt controller implementation.
 * @details This is a bit of a hack to provide NVIC compatible function
 *          declarations for the Xh3irq interrupt controller.
 *
 * @addtogroup COMMON_RISCV_HAZARD3_IRQ
 * @{
 */

#include "hal.h"
#include "hazard3_irq.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local types.                                                       */
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
 * @brief   Hazard3 IRQ controller initialization.
 * @details Disables all external interrupts and sets default priorities.
 */
void nvicInit(void) {
  hazard3_irq_init();
}

/**
 * @brief   Enables an external interrupt with specified priority.
 *
 * @param[in] n         The IRQ number
 * @param[in] prio      The priority level
 */
void nvicEnableVector(uint32_t n, uint32_t prio) {
  if (n >= HAZARD3_NUM_EXTERNAL_IRQS) {
    return;
  }

  /* Set priority first, then enable */
  hazard3_irq_set_priority(n, prio & 0x3U);
  hazard3_irq_enable(n);
}

/**
 * @brief   Disables an external interrupt.
 *
 * @param[in] n         The IRQ number
 */
void nvicDisableVector(uint32_t n) {
  if (n >= HAZARD3_NUM_EXTERNAL_IRQS) {
    return;
  }

  hazard3_irq_disable(n);
}

/**
 * @brief   Sets system handler priority.
 * @note    This is a no-op on RISC-V Hazard3.
 *
 * @param[in] handler   The handler number
 * @param[in] prio      The priority level
 */
void nvicSetSystemHandlerPriority(uint32_t handler, uint32_t prio) {
  (void)handler;
  (void)prio;
  /* No-op on RISC-V as system handlers don't have configurable priorities */
}

/**
 * @brief   Clears a pending interrupt.
 * @note    On Hazard3 clearing pending state is handled by the interrupt
 *          source or by clearing the force bit.
 *
 * @param[in] n         The IRQ number
 */
void nvicClearPending(uint32_t n) {
  if (n >= HAZARD3_NUM_EXTERNAL_IRQS) {
    return;
  }

  /* Clear any forced pending state */
  hazard3_irq_force_clear(n);
}

/**
 * @brief   Sets a pending interrupt (forces interrupt).
 *
 * @param[in] n         The IRQ number
 */
void nvicSetPending(uint32_t n) {
  if (n >= HAZARD3_NUM_EXTERNAL_IRQS) {
    return;
  }

  hazard3_irq_force(n);
}

/** @} */
