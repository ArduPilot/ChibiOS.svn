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
 * @brief   SAI1 driver enable switch.
 * @details If set to @p TRUE the support for SAI1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI1) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI1                  FALSE
#endif

/**
 * @brief   SAI2 driver enable switch.
 * @details If set to @p TRUE the support for SAI2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI2) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI2                  FALSE
#endif

/**
 * @brief   SAI3 driver enable switch.
 * @details If set to @p TRUE the support for SAI3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI3) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI3                  FALSE
#endif

/**
 * @brief   SAI4 driver enable switch.
 * @details If set to @p TRUE the support for SAI4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(STM32_SAI_USE_SAI4) || defined(__DOXYGEN__)
#define STM32_SAI_USE_SAI4                  FALSE
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
#define STM32_SAI_SAI1_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_SLAVE  |  \
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
#define STM32_SAI_SAI2_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_SLAVE  |  \
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
#define STM32_SAI_SAI3_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_SLAVE  |  \
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
#define STM32_SAI_SAI4_SUB_B_MODE           (STM32_SAI_BLOCK_MODE_SLAVE  |  \
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

#if STM32_SAI_USE_SAI1 && !STM32_HAS_SAI1
#error "SAI1 not present in the selected device"
#endif

#if STM32_SAI_USE_SAI2 && !STM32_HAS_SAI2
#error "SAI2 not present in the selected device"
#endif

#if STM32_SAI_USE_SAI3 && !STM32_HAS_SAI3
#error "SAI3 not present in the selected device"
#endif

#if STM32_SAI_USE_SAI4 && !STM32_HAS_SAI4
#error "SAI4 not present in the selected device"
#endif

#if !STM32_SAI_USE_SAI1 && !STM32_SAI_USE_SAI2 &&                           \
    !STM32_SAI_USE_SAI3 && !STM32_SAI_USE_SAI4
#error "SAI driver activated but no SAI peripheral assigned"
#endif

#if STM32_SAI_USE_SAI1 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI1_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI1"
#endif

#if STM32_SAI_USE_SAI2  &&                                                  \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI2_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI2"
#endif

#if STM32_SAI_USE_SAI3 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI3_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI3"
#endif

#if STM32_SAI_USE_SAI4 &&                                                   \
    !OSAL_IRQ_IS_VALID_PRIORITY(STM32_SAI_SAI4_IRQ_PRIORITY)
#error "Invalid IRQ priority assigned to SAI4"
#endif

#if STM32_SAI_USE_SAI1 &&                                                   \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI1_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI1"
#endif

#if STM32_SAI_USE_SAI2 &&                                                   \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI2_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI2"
#endif

#if STM32_SAI_USE_SAI3 &&                                                   \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI3_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI3"
#endif

#if STM32_SAI_USE_SAI4 &&                                                  \
    !STM32_DMA_IS_VALID_PRIORITY(STM32_SAI_SAI4_DMA_PRIORITY)
#error "Invalid DMA priority assigned to SAI4"
#endif

/* Check on the presence of the DMA streams settings in mcuconf.h.*/
#if STM32_SAI_USE_SAI1 && (!defined(STM32_SAI_SAI1A_DMA_STREAM) ||          \
                           !defined(STM32_SAI_SAI1B_DMA_STREAM))
#error "SAI1 DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI2 && (!defined(STM32_SAI_SAI2A_DMA_STREAM) ||          \
                           !defined(STM32_SAI_SAI2B_DMA_STREAM))
#error "SAI2 DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI3 && (!defined(STM32_SAI_SAI3A_DMA_STREAM) ||          \
                           !defined(STM32_SAI_SAI3B_DMA_STREAM))
#error "SAI3 DMA streams not defined"
#endif

#if STM32_SAI_USE_SAI4 && (!defined(STM32_SAI_SAI4A_DMA_STREAM) ||          \
                           !defined(STM32_SAI_SAI4B_DMA_STREAM))
#error "SAI4 DMA streams not defined"
#endif

/* Check on the validity of the assigned DMA streams.*/
#if STM32_SAI_USE_SAI1 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI1A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI1 block A"
#endif

#if STM32_SAI_USE_SAI1 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI1B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI1 block B"
#endif

#if STM32_SAI_USE_SAI2 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI2A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI2 block A"
#endif

#if STM32_SAI_USE_SAI2 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI2B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI2 block B"
#endif

#if STM32_SAI_USE_SAI3 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI3A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI3 block A"
#endif

#if STM32_SAI_USE_SAI3 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI3B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI3 block B"
#endif

#if STM32_SAI_USE_SAI4 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI4A_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI4 block A"
#endif

#if STM32_SAI_USE_SAI4 &&                                                   \
    !STM32_DMA_IS_VALID_STREAM(STM32_SAI_SAI4B_DMA_STREAM)
#error "Invalid DMA stream assigned to SAI4 block B"
#endif

/* Devices without DMAMUX require an additional check.*/
#if STM32_ADVANCED_DMA && !STM32_DMA_SUPPORTS_DMAMUX
#error "To be implemented"
#endif /* STM32_ADVANCED_DMA && !STM32_DMA_SUPPORTS_DMAMUX */

#if !defined(STM32_DMA_REQUIRED)
#define STM32_DMA_REQUIRED
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/
/**
 * @brief   Number of SAI blocks per SAI driver.
 */
#define SAI_BLOCKS                              0x2U

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
/**
 * @brief   Type of a SAIBlock driver configuration structure.
 */
struct hal_sai_block_config {
  /**
   * @brief   buffer pointer.
   * @note    Can be @p NULL is not required.
   */
  void                      *buffer;

  /**
   * @brief   buffer size.
   */
  size_t                    size;

  /**
   * @brief   Callback function called during streaming.
   */
  saiblockcallback_t        end_cb;

  /**
   * @brief   Register CR1.
   */
  uint32_t                  cr1;

  /**
   * @brief   Register CR2.
   */
  uint32_t                  cr2;

  /**
   * @brief   Register FRCR.
   */
  uint32_t                  frcr;

  /**
   * @brief   Register SLOTR.
   */
  uint32_t                  slotr;
};

/**
 * @brief   Structure representing an SAI driver.
 */
struct hal_sai_block_driver {
  /**
   * @brief   Driver state.
   */
  saiblockstate_t           state;

  /**
   * @brief   Current configuration data.
   */
  const SAIBlockConfig      *config;

  /**
   * @brief Pointer to the SAIx SubBlockx registers.
   */
  SAI_Block_TypeDef         *saiblock;

  /* DMA stream or @p NULL.*/
  const stm32_dma_stream_t  *dma;

  /* DMA mode bit mask.*/
  uint32_t                  dmamode;
};

/**
 * @brief   Structure representing an SAI driver.
 */
struct hal_sai_driver {
  /**
   * @brief   Driver state.
   */
  saistate_t                state;

  /**
   * @brief Pointer to the SAIx registers block.
   */
  SAI_TypeDef               *sai;

  /**
   * @brief   Current configuration data.
   */
  const SAIConfig           *config;

  /**
   * @brief   blocks driver.
   */
  SAIBlockDriver            blocks[SAI_BLOCKS];
};

/**
 * @brief   Driver sai configuration structure.
 */
struct hal_sai_config {
  uint32_t                  gcr;
  /**
   * @brief Blocks configurations.
   */
  SAIBlockConfig            blocks[SAI_BLOCKS];
};

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_SAI_USE_SAI1 && !defined(__DOXYGEN__)
extern SAIDriver SAID1;
#endif

#if STM32_SAI_USE_SAI2 && !defined(__DOXYGEN__)
extern SAIDriver SAID2;
#endif

#if STM32_SAI_USE_SAI3 && !defined(__DOXYGEN__)
extern SAIDriver SAID3;
#endif

#if STM32_SAI_USE_SAI4 && !defined(__DOXYGEN__)
extern SAIDriver SAID4;
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
