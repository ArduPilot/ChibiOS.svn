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
 * @file    SAIv3/hal_sai_lld.h
 * @brief   STM32 SAI subsystem low level driver header.
 * @author  Edoardo Lombardi
 *
 * @addtogroup SAI
 * @{
 */

#ifndef HAL_SAI_LLD_H
#define HAL_SAI_LLD_H

#if HAL_USE_SAI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/
/**
 * @name    Static SAI sync mode
 * TODO only no sync mode supported for now
 * @{
 */
#define STM32_SAI_NO_OUT_SYNC               0
#define STM32_SAI_NO_IN_SYNC                0

/** @} */

/**
 * @name    Static SAI subblock modes
 * @{
 */
#define STM32_SAI_BLOCK_MODE_SLAVE          0
#define STM32_SAI_BLOCK_MODE_MASTER         1
#define STM32_SAI_BLOCK_MODE_TX             2
#define STM32_SAI_BLOCK_MODE_RX             4

/** @} */

/**
 * @name    Mode checks
 * @{
 */
#define STM32_SAI_BLOCK_IS_MASTER(mode)     ((mode) & STM32_SAI_BLOCK_MODE_MASTER)
#define STM32_SAI_BLOCK_RX_ENABLED(mode)    ((mode) & STM32_SAI_BLOCK_MODE_RX)
#define STM32_SAI_BLOCK_TX_ENABLED(mode)    ((mode) & STM32_SAI_BLOCK_MODE_TX)
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   SAI1A driver enable switch.
 * @details If set to @p TRUE the support for SAI1A is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI1A) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI1A                 FALSE
#endif

/**
 * @brief   SAI1B driver enable switch.
 * @details If set to @p TRUE the support for SAI1B is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI1B) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI1B                 FALSE
#endif

/**
 * @brief   SAI2A driver enable switch.
 * @details If set to @p TRUE the support for SAI2A is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI2A) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI2A                 FALSE
#endif

/**
 * @brief   SAI2B driver enable switch.
 * @details If set to @p TRUE the support for SAI2B is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI2B) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI2B                 FALSE
#endif

/**
 * @brief   SAI3A driver enable switch.
 * @details If set to @p TRUE the support for SAI3A is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI3A) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI3A                 FALSE
#endif

/**
 * @brief   SAI3B driver enable switch.
 * @details If set to @p TRUE the support for SAI3B is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI3B) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI3B                 FALSE
#endif

/**
 * @brief   SAI4A driver enable switch.
 * @details If set to @p TRUE the support for SAI4A is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI4A) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI4A                 FALSE
#endif

/**
 * @brief   SAI4B driver enable switch.
 * @details If set to @p TRUE the support for SAI4B is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI4B) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI4B                 FALSE
#endif

/**
 * @brief   SAI1 sub block A mode.
 */
#if !defined(STM32_SAI_SAI1_SUB_A_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI1_SUB_A_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_TX)
#endif

/**
 * @brief   SAI1 sub block B mode.
 */
#if !defined(STM32_SAI_SAI1_SUB_B_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI1_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_RX)
#endif

/**
 * @brief   SAI2 sub block A mode.
 */
#if !defined(STM32_SAI_SAI2_SUB_A_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI2_SUB_A_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_TX)
#endif

/**
 * @brief   SAI2 sub block B mode.
 */
#if !defined(STM32_SAI_SAI2_SUB_B_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI2_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_RX)
#endif

/**
 * @brief   SAI3 sub block A mode.
 */
#if !defined(STM32_SAI_SAI3_SUB_A_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI3_SUB_A_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_TX)
#endif

/**
 * @brief   SAI3 sub block B mode.
 */
#if !defined(STM32_SAI_SAI3_SUB_B_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI3_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_RX)
#endif

/**
 * @brief   SAI4 sub block A mode.
 */
#if !defined(STM32_SAI_SAI4_SUB_A_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI4_SUB_A_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_TX)
#endif

/**
 * @brief   SAI4 sub block B mode.
 */
#if !defined(STM32_SAI_SAI4_SUB_B_MODE) || defined(__DOXYGEN__)
#define STM32_SAI_SAI4_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_MASTER |  \
                                             STM32_SAI_BLOCK_MODE_RX)
#endif

/**
 * @brief   SAI1 interrupt priority level setting.
 */
#if !defined(STM32_SAI_SAI1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI1_IRQ_PRIORITY         10
#endif

/**
 * @brief   SAI2 interrupt priority level setting.
 */
#if !defined(STM32_SAI_SAI2_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI2_IRQ_PRIORITY         10
#endif

/**
 * @brief   SAI3 interrupt priority level setting.
 */
#if !defined(STM32_SAI_SAI3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI3_IRQ_PRIORITY         10
#endif

/**
 * @brief   SAI4 interrupt priority level setting.
 */
#if !defined(STM32_SAI_SAI4_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI4_IRQ_PRIORITY         10
#endif

/**
 * @brief   SAI1 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_SAI_SAI1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI1_DMA_PRIORITY         1
#endif

/**
 * @brief   SAI2 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_SAI_SAI2_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI2_DMA_PRIORITY         1
#endif

/**
 * @brief   SAI3 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_SAI_SAI3_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI3_DMA_PRIORITY         1
#endif

/**
 * @brief   SAI4 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_SAI_SAI4_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_SAI_SAI4_DMA_PRIORITY         1
#endif

/**
 * @brief   SAI DMA error hook.
 */
#if !defined(STM32_SAI_DMA_ERROR_HOOK) || defined(__DOXYGEN__)
#define STM32_SAI_DMA_ERROR_HOOK(saip)      osalSysHalt("DMA failure")
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if STM32_SAI_USE_SAI1A && !STM32_HAS_SAI1_A
#error "SAI1 block A not present in the selected device"
#endif

#if STM32_SAI_USE_SAI1B && !STM32_HAS_SAI1B
#error "SAI1 block B not present in the selected device"
#endif

#if STM32_SAI_USE_SAI2A && !STM32_HAS_SAI2A
#error "SAI2 block A not present in the selected device"
#endif

#if STM32_SAI_USE_SAI2B && !STM32_HAS_SAI2B
#error "SAI2 block B not present in the selected device"
#endif

#if STM32_SAI_USE_SAI3A && !STM32_HAS_SAI3A
#error "SAI3 block A not present in the selected device"
#endif

#if STM32_SAI_USE_SAI3B && !STM32_HAS_SAI3B
#error "SAI3 block B not present in the selected device"
#endif

#if STM32_SAI_USE_SAI4A && !STM32_HAS_SAI4A
#error "SAI4 block A not present in the selected device"
#endif

#if STM32_SAI_USE_SAI4B && !STM32_HAS_SAI4B
#error "SAI4 block B not present in the selected device"
#endif

#if !STM32_SAI_USE_SAI1A && !STM32_SAI_USE_SAI1B &&                         \
    !STM32_SAI_USE_SAI2A && !STM32_SAI_USE_SAI2B &&                         \
    !STM32_SAI_USE_SAI3A && !STM32_SAI_USE_SAI3B &&                         \
    !STM32_SAI_USE_SAI4A && !STM32_SAI_USE_SAI4B
#error "SAI driver activated but no SAI peripheral assigned"
#endif

#if (STM32_SAI_USE_SAI1A || STM32_SAI_USE_SAI1B) &&                         \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI1"
#endif

#if (STM32_SAI_USE_SAI2A || STM32_SAI_USE_SAI2B) &&                         \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI2"
#endif

#if (STM32_SAI_USE_SAI3A || STM32_SAI_USE_SAI3B) &&                         \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI3_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI3"
#endif

#if (STM32_SAI_USE_SAI4A || STM32_SAI_USE_SAI4B) &&                         \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI4_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI4"
#endif

#if (STM32_SAI_USE_SAI1A || STM32_SAI_USE_SAI1B) &&                         \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI1_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI1"
#endif

#if (STM32_SAI_USE_SAI2A || STM32_SAI_USE_SAI2B) &&                         \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI2_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI2"
#endif

#if (STM32_SAI_USE_SAI3A || STM32_SAI_USE_SAI3B) &&                         \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI3_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI3"
#endif

#if (STM32_SAI_USE_SAI4A || STM32_SAI_USE_SAI4B) &&                         \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI4_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI4"
#endif

/* Check on the presence of the DMA streams settings in mcuconf.h.*/
#if STM32_SAI_USE_SAI1A && (!defined(STM32_SAI_SAI1A_DMA_STREAM))
#error "SAI1 block A DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI1B && (!defined(STM32_SAI_SAI1B_DMA_STREAM))
#error "SAI1 block B DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI2A && (!defined(STM32_SAI_SAI2A_DMA_STREAM))
#error "SAI2 block A DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI2B && (!defined(STM32_SAI_SAI2B_DMA_STREAM))
#error "SAI2 block B DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI3A && (!defined(STM32_SAI_SAI3A_DMA_STREAM))
#error "SAI3 block A DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI3B && (!defined(STM32_SAI_SAI3B_DMA_STREAM))
#error "SAI3 block B DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI4A && (!defined(STM32_SAI_SAI4A_DMA_STREAM))
#error "SAI4 block A DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI4B && (!defined(STM32_SAI_SAI4B_DMA_STREAM))
#error "SAI4 block B DMA streams not defined"
#endif

/* Check on the validity of the assigned DMA streams.*/
#if STM32_SAI_USE_SAI1A &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI1A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI1 block A"
#endif

#if STM32_SAI_USE_SAI1B &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI1B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI1 block B"
#endif

#if STM32_SAI_USE_SAI2A &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI2A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI2 block A"
#endif

#if STM32_SAI_USE_SAI2B &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI2B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI2 block B"
#endif

#if STM32_SAI_USE_SAI3A &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI3A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI3 block A"
#endif

#if STM32_SAI_USE_SAI3B &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI3B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI3 block B"
#endif

#if STM32_SAI_USE_SAI4A &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI4A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI4 block A"
#endif

#if STM32_SAI_USE_SAI4B &&                                                  \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI4B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI4 block B"
#endif

#if !defined(STM32_DMA_REQUIRED)
#define STM32_DMA_REQUIRED
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Low level fields of the SAI driver structure.
 */
#define sai_lld_driver_fields                                               \
  /* Pointer to the SAIx registers block.*/                                 \
  SAI_TypeDef               *sai;                                           \
  SAI_Block_TypeDef         *saiblock;                                      \
  /* DMA stream or @p NULL.*/                                               \
  const stm32_dma_stream_t  *dma;                                           \
  /* DMA mode bit mask.*/                                                   \
  uint32_t                  dmamode;

/**
 * @brief   Low level fields of the SAI block configuration structure.
 */
#define sai_lld_config_fields                                               \
  uint32_t                  gcr;                                            \
  uint32_t                  saicr1;                                         \
  uint32_t                  saicr2;                                         \
  uint32_t                  saifrcr;                                        \
  uint32_t                  saislotr;

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_SAI_USE_SAI1A && !defined(__DOXYGEN__)
extern SAIDriver SAIAD1;
#endif

#if STM32_SAI_USE_SAI1B && !defined(__DOXYGEN__)
extern SAIDriver SAIBD1;
#endif

#if STM32_SAI_USE_SAI2A && !defined(__DOXYGEN__)
extern SAIDriver SAIAD2;
#endif

#if STM32_SAI_USE_SAI2B && !defined(__DOXYGEN__)
extern SAIDriver SAIBD2;
#endif

#if STM32_SAI_USE_SAI3A && !defined(__DOXYGEN__)
extern SAIDriver SAIAD3;
#endif

#if STM32_SAI_USE_SAI3B && !defined(__DOXYGEN__)
extern SAIDriver SAIBD3;
#endif

#if STM32_SAI_USE_SAI4A && !defined(__DOXYGEN__)
extern SAIDriver SAIAD4;
#endif

#if STM32_SAI_USE_SAI4B && !defined(__DOXYGEN__)
extern SAIDriver SAIBD4;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void sai_lld_init(void);
  void sai_lld_start(SAIDriver *saip);
  void sai_lld_stop(SAIDriver *saip);
  void sai_lld_start_exchange(SAIDriver *saip);
  void sai_lld_stop_exchange(SAIDriver *saip);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_SAI */

#endif /* HAL_SAI_LLD_H */

/** @} */
