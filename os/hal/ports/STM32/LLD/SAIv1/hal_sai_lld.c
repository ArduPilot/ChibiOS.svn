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
 * @file    SAIv1/hal_sai_lld.c
 * @brief   STM32 SAI subsystem low level driver source.
 *
 * @author  Edoardo Lombardi
 *
 * TODO: bdma support
 *       Handling communication errors
 *
 * @addtogroup SAI
 * @{
 */

#include "hal.h"

#if HAL_USE_SAI || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
/*
 * FIXME EL wrong macros usage. Refer to MODE of CR1, not GCR.
 */
/*
 * Static SAI settings for SAI1 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_A_MODE) */

/*
 * Static SAI settings for SAI1 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_B_MODE) */

/*
 * Static SAI settings for SAI2 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_A_MODE) */

/*
 * Static SAI settings for SAI2 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_B_MODE) */

/*
 * Static SAI settings for SAI3 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_A_MODE) */

/*
 * Static SAI settings for SAI3 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_B_MODE) */

/*
 * Static SAI settings for SAI4 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_A_MODE) */

/*
 * Static SAI settings for SAI4 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     SAI_GCR_SYNCIN_1
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     (SAI_GCR_SYNCIN_1 |             \
                                             SAI_GCR_SYNCIN_0)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     0
#endif
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     SAI_GCR_SYNCIN_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_B_MODE) */

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief SAI1A driver identifier.*/
#if STM32_SAI_USE_SAI1A || defined(__DOXYGEN__)
SAIDriver SAIAD1;
#endif

/** @brief SAI1B driver identifier.*/
#if STM32_SAI_USE_SAI1B || defined(__DOXYGEN__)
SAIDriver SAIBD1;
#endif

/** @brief SAI2A driver identifier.*/
#if STM32_SAI_USE_SAI2A || defined(__DOXYGEN__)
SAIDriver SAIAD2;
#endif

/** @brief SAI2B driver identifier.*/
#if STM32_SAI_USE_SAI2B || defined(__DOXYGEN__)
SAIDriver SAIBD2;
#endif

/** @brief SAI3A driver identifier.*/
#if STM32_SAI_USE_SAI3A || defined(__DOXYGEN__)
SAIDriver SAIAD3;
#endif

/** @brief SAI3B driver identifier.*/
#if STM32_SAI_USE_SAI3B || defined(__DOXYGEN__)
SAIDriver SAIBD3;
#endif

/** @brief SAI4A driver identifier.*/
#if STM32_SAI_USE_SAI4A || defined(__DOXYGEN__)
SAIDriver SAIAD4;
#endif

/** @brief SAI4B driver identifier.*/
#if STM32_SAI_USE_SAI4B || defined(__DOXYGEN__)
SAIDriver SAIBD4;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE) ||                \
    defined(__DOXYGEN__)
/**
 * @brief   Shared end-of-rx service routine.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void sai_lld_serve_rx_interrupt(SAIDriver *saip, uint32_t flags) {

  (void)saip;

  /* DMA errors handling.*/
#if defined(STM32_SAI_DMA_ERROR_HOOK)
  if ((flags & (STM32_DMA_ISR_TEIF | STM32_DMA_ISR_DMEIF)) != 0) {
    STM32_SAI_DMA_ERROR_HOOK(saip);
  }
#endif

  /* Callbacks handling, note it is portable code defined in the high
     level driver.*/
  if ((flags & STM32_DMA_ISR_TCIF) != 0) {
    /* Transfer complete processing.*/
    _sai_isr_full_code(saip);
  }
  else if ((flags & STM32_DMA_ISR_HTIF) != 0) {
    /* Half transfer processing.*/
    _sai_isr_half_code(saip);
  }
}
#endif

#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE) ||                \
    STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE) ||                \
    defined(__DOXYGEN__)
/**
 * @brief   Shared block a end-of-tx service routine.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void sai_lld_serve_tx_interrupt(SAIDriver *saip, uint32_t flags) {

  (void)saip;

  /* DMA errors handling.*/
#if defined(STM32_SAI_DMA_ERROR_HOOK)
  if ((flags & (STM32_DMA_ISR_TEIF | STM32_DMA_ISR_DMEIF)) != 0) {
    STM32_SAI_DMA_ERROR_HOOK(saip);
  }
#endif

  /* Callbacks handling, note it is portable code defined in the high
     level driver.*/
  if ((flags & STM32_DMA_ISR_TCIF) != 0) {
    /* Transfer complete processing.*/
    _sai_isr_full_code(saip);
  }
  else if ((flags & STM32_DMA_ISR_HTIF) != 0) {
    /* Half transfer processing.*/
    _sai_isr_half_code(saip);
  }
}
#endif

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level SAI driver initialization.
 *
 * @notapi
 */
void sai_lld_init(void) {

#if STM32_SAI_USE_SAI1A
  saiObjectInit(&SAIAD1);
  SAIAD1.sai      = SAI1;
  SAIAD1.saiblock = SAI1_Block_A;
  SAIAD1.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
  SAIAD1.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIAD1.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE) */
#endif /* STM32_SAI_USE_SAI1A */

#if STM32_SAI_USE_SAI1B
  saiObjectInit(&SAIBD1);
  SAIBD1.sai      = SAI1;
  SAIBD1.saiblock = SAI1_Block_B;
  SAIBD1.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
  SAIBD1.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIBD1.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE) */
#endif /* STM32_SAI_USE_SAI1B */

#if STM32_SAI_USE_SAI2A
  saiObjectInit(&SAIAD2);
  SAIAD2.sai      = SAI2;
  SAIAD2.saiblock = SAI2_Block_A;
  SAIAD2.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
  SAIAD2.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIAD2.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE) */
#endif /* STM32_SAI_USE_SAI2A */

#if STM32_SAI_USE_SAI2B
  saiObjectInit(&SAIBD2);
  SAIBD2.sai      = SAI2;
  SAIBD2.saiblock = SAI2_Block_B;
  SAIBD2.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
  SAIBD2.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIBD2.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE) */
#endif /* STM32_SAI_USE_SAI2B */

#if STM32_SAI_USE_SAI3A
  saiObjectInit(&SAIAD3);
  SAIAD3.sai      = SAI3;
  SAIAD3.saiblock = SAI3_Block_A;
  SAIAD3.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
  SAIAD3.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIAD3.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE) */
#endif /* STM32_SAI_USE_SAI3A */

#if STM32_SAI_USE_SAI3B
  saiObjectInit(&SAIBD3);
  SAIBD3.sai      = SAI3;
  SAIBD3.saiblock = SAI3_Block_B;
  SAIBD3.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
  SAIBD3.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIBD3.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE) */
#endif /* STM32_SAI_USE_SAI3B */

#if STM32_SAI_USE_SAI4A
  saiObjectInit(&SAIAD4);
  SAIAD4.sai      = SAI4;
  SAIAD4.saiblock = SAI4_Block_A;
  SAIAD4.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
  SAIAD4.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIAD4.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE) */
#endif /* STM32_SAI_USE_SAI4A */

#if STM32_SAI_USE_SAI4B
  saiObjectInit(&SAIBD4);
  SAIBD4.sai      = SAI4;
  SAIBD4.saiblock = SAI4_Block_B;
  SAIBD4.dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
  SAIBD4.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_P2M |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#else
  SAIBD4.dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
                                    STM32_DMA_CR_PSIZE_HWORD |
                                    STM32_DMA_CR_MSIZE_HWORD |
                                    STM32_DMA_CR_DIR_M2P |
                                    STM32_DMA_CR_MINC |
                                    STM32_DMA_CR_CIRC |
                                    STM32_DMA_CR_HTIE |
                                    STM32_DMA_CR_TCIE |
                                    STM32_DMA_CR_DMEIE |
                                    STM32_DMA_CR_TEIE;
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE) */
#endif /* STM32_SAI_USE_SAI4B */

}

/**
 * @brief   Configures and activates the SAI peripheral.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @notapi
 */
void sai_lld_start(SAIDriver *saip) {

  /* If in stopped state then enables the SAI and DMA clocks.*/
  if (saip->state == SAI_STOP) {

#if STM32_SAI_USE_SAI1A
    if (&SAIAD1 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI1(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI1A_DMA_STREAM,
                                  STM32_SAI_SAI1_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI1A_DMA_STREAM,
                                  STM32_SAI_SAI1_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI1_A);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI1_ACR1;
    }
#endif /* STM32_SAI_USE_SAI1A */

#if STM32_SAI_USE_SAI1B
    if (&SAIBD1 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI1(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI1B_DMA_STREAM,
                                  STM32_SAI_SAI1_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI1B_DMA_STREAM,
                                  STM32_SAI_SAI1_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI1_B);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI1_ACR1;
    }
#endif /* STM32_SAI_USE_SAI1B */

#if STM32_SAI_USE_SAI2A
    if (&SAIAD2 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI2(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI2A_DMA_STREAM,
                                  STM32_SAI_SAI2_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI2A_DMA_STREAM,
                                  STM32_SAI_SAI2_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI2_A);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI2_ACR1;
    }
#endif /* STM32_SAI_USE_SAI2A */

#if STM32_SAI_USE_SAI2B
    if (&SAIBD2 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI2(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI2B_DMA_STREAM,
                                  STM32_SAI_SAI2_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI2B_DMA_STREAM,
                                  STM32_SAI_SAI2_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI2_B);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI2_ACR1;
    }
#endif /* STM32_SAI_USE_SAI2B */

#if STM32_SAI_USE_SAI3A
    if (&SAIAD3 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI3(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI3A_DMA_STREAM,
                                  STM32_SAI_SAI3_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI3A_DMA_STREAM,
                                  STM32_SAI_SAI3_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI3_A);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI3_ACR1;
    }
#endif /* STM32_SAI_USE_SAI3A */

#if STM32_SAI_USE_SAI1B
    if (&SAIBD3 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI3(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI3B_DMA_STREAM,
                                  STM32_SAI_SAI3_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI3B_DMA_STREAM,
                                  STM32_SAI_SAI3_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI3_B);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI3_ACR1;
    }
#endif /* STM32_SAI_USE_SAI3B */

#if STM32_SAI_USE_SAI4A
    if (&SAIAD4 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI4(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI4A_DMA_STREAM,
                                  STM32_SAI_SAI4_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI4A_DMA_STREAM,
                                  STM32_SAI_SAI4_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI4_A);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI4_ACR1;
    }
#endif /* STM32_SAI_USE_SAI1A */

#if STM32_SAI_USE_SAI1B
    if (&SAIBD4 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI4(true);

#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI4B_DMA_STREAM,
                                  STM32_SAI_SAI4_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                  (void *)saip);
#else
      saip->dma = dmaStreamAllocI(STM32_SAI_SAI4B_DMA_STREAM,
                                  STM32_SAI_SAI4_IRQ_PRIORITY,
                                  (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                  (void *)saip);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE) */

      osalDbgAssert(saip->dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->dma, STM32_DMAMUX1_SAI4_B);

      /* SAI (re)configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->saiblock->CR2   = saip->config->saicr2;
      saip->saiblock->FRCR  = saip->config->saifrcr;
      saip->saiblock->SLOTR = saip->config->saislotr;

      saip->saiblock->CR1  |= saip->config->saicr1 | SAI_xCR1_DMAEN |
                              SAI_xCR1_SAIEN | STM32_SAI4_ACR1;
    }
#endif /* STM32_SAI_USE_SAI4B */
  }

  /* Clear IFCR */
  //saip->sai->IFCR = 0x0FF8;

  /*
   * TODO: handle?
   * Now fixed at MSB
   */
  //saip->sai->CFG2 = SAI_CFG2_LSBFRST;
}

/**
 * @brief   Deactivates the SAI peripheral.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @notapi
 */
void sai_lld_stop(SAIDriver *saip) {
  /* If in ready state then disables the SAI clock.*/
  if (saip->state == SAI_READY) {

    /* SAI disable.*/
    saip->saiblock->CR1 = 0;
    saip->saiblock->CR2 = 0;

    if (NULL != saip->dma) {
      dmaStreamFreeI(saip->dma);
      saip->dma = NULL;
    }

#if (STM32_SAI_USE_SAI1A || STM32_SAI_USE_SAI1B)
    /*
     * FIXME EDO
     */
    if (&SAIAD1 == saip)
      rccDisableSAI1();
#endif

#if (STM32_SAI_USE_SAI2A || STM32_SAI_USE_SAI2B)
    if (&SAIAD2 == saip || &SAIBD2 == saip)
      rccDisableSAI2();
#endif

#if (STM32_SAI_USE_SAI3A || STM32_SAI_USE_SAI3B)
    if (&SAIAD3 == saip || &SAIBD3 == saip)
      rccDisableSAI3();
#endif

#if (STM32_SAI_USE_SAI4A || STM32_SAI_USE_SAI4B)
    if (&SAIAD4 == saip || &SAIBD4 == saip)
      rccDisableSAI4();
#endif
  }
}

/**
 * @brief   Starts a SAI data exchange.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @notapi
 */
void sai_lld_start_exchange(SAIDriver *saip) {
  size_t size = saip->config->size;

  /* DMA setup.*/
  if (NULL != saip->dma) {
    dmaStreamSetMode(saip->dma, saip->dmamode);
    dmaStreamSetPeripheral(saip->dma, &saip->saiblock->DR);
    dmaStreamSetMemory0(saip->dma, saip->config->buffer);
    dmaStreamSetTransactionSize(saip->dma, size);
    dmaStreamEnable(saip->dma);
  }

  /* Starting transfer.*/
  saip->saiblock->IMR |=  SAI_xIMR_WCKCFGIE;
}

/**
 * @brief   Stops the ongoing data exchange.
 * @details The ongoing data exchange, if any, is stopped, if the driver
 *          was not active the function does nothing.
 *
 * @param[in] saip      pointer to the @p SAIDriver object
 *
 * @notapi
 */
void sai_lld_stop_exchange(SAIDriver *saip) {
  /* Stop SAI/SAI peripheral.*/
  saip->saiblock->IMR &=  ~SAI_xIMR_WCKCFGIE;

  /* Stop DMA, if enabled.*/
  if (NULL != saip->dma)
    dmaStreamDisable(saip->dma);
}

#endif /* HAL_USE_SAI */

/** @} */
