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
 * Static SAI settings for SAI1 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
#define STM32_SAI1_ACR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_A_MODE) */

/*
 * Static SAI settings for SAI1 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
#define STM32_SAI1_BCR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI1_SUB_B_MODE) */

/*
 * Static SAI settings for SAI2 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
#define STM32_SAI2_ACR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_A_MODE) */

/*
 * Static SAI settings for SAI2 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
#define STM32_SAI2_BCR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI2_SUB_B_MODE) */

/*
 * Static SAI settings for SAI3 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
#define STM32_SAI3_ACR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_A_MODE) */

/*
 * Static SAI settings for SAI3 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
#define STM32_SAI3_BCR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI3_SUB_B_MODE) */

/*
 * Static SAI settings for SAI4 block A.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_A_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_A_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
#define STM32_SAI4_ACR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_A_MODE) */

/*
 * Static SAI settings for SAI4 block B.
 */
#if !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_B_MODE)
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     SAI_xCR1_MODE_1
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     (SAI_xCR1_MODE_0 |              \
                                             SAI_xCR1_MODE_1)
#endif
#else /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_B_MODE) */
#if STM32_SAI_BLOCK_TX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     0
#elif STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
#define STM32_SAI4_BCR1                     SAI_xCR1_MODE_0
#endif
#endif /* !STM32_SAI_BLOCK_IS_MASTER(STM32_SAI_SAI4_SUB_B_MODE) */

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief SAI1 driver identifier.*/
#if STM32_SAI_USE_SAI1 || defined(__DOXYGEN__)
SAIDriver SAID1;
#endif

/** @brief SAI2 driver identifier.*/
#if STM32_SAI_USE_SAI2 || defined(__DOXYGEN__)
SAIDriver SAID2;
#endif

/** @brief SAI3 driver identifier.*/
#if STM32_SAI_USE_SAI3 || defined(__DOXYGEN__)
SAIDriver SAID3;
#endif

/** @brief SAI4 driver identifier.*/
#if STM32_SAI_USE_SAI4 || defined(__DOXYGEN__)
SAIDriver SAID4;
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
 * @param[in] saibp     pointer to the @p SAIBlockDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void sai_lld_serve_rx_interrupt(SAIBlockDriver *saibp, uint32_t flags) {

  (void)saibp;

  /* DMA errors handling.*/
#if defined(STM32_SAI_DMA_ERROR_HOOK)
  if ((flags & (STM32_DMA_ISR_TEIF | STM32_DMA_ISR_DMEIF)) != 0) {
    STM32_SAI_DMA_ERROR_HOOK(saibp);
  }
#endif

  /* Callbacks handling, note it is portable code defined in the high
     level driver.*/
  if ((flags & STM32_DMA_ISR_TCIF) != 0) {
    /* Transfer complete processing.*/
    _sai_isr_full_code(saibp);
  }
  else if ((flags & STM32_DMA_ISR_HTIF) != 0) {
    /* Half transfer processing.*/
    _sai_isr_half_code(saibp);
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
 * @param[in] saip      pointer to the @p SAIBlockDriver object
 * @param[in] flags     pre-shifted content of the ISR register
 */
static void sai_lld_serve_tx_interrupt(SAIBlockDriver *saibp, uint32_t flags) {

  (void)saibp;

  /* DMA errors handling.*/
#if defined(STM32_SAI_DMA_ERROR_HOOK)
  if ((flags & (STM32_DMA_ISR_TEIF | STM32_DMA_ISR_DMEIF)) != 0) {
    STM32_SAI_DMA_ERROR_HOOK(saibp);
  }
#endif

  /* Callbacks handling, note it is portable code defined in the high
     level driver.*/
  if ((flags & STM32_DMA_ISR_TCIF) != 0) {
    /* Transfer complete processing.*/
    _sai_isr_full_code(saibp);
  }
  else if ((flags & STM32_DMA_ISR_HTIF) != 0) {
    /* Half transfer processing.*/
    _sai_isr_half_code(saibp);
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

#if STM32_SAI_USE_SAI1
  saiObjectInit(&SAID1);
  SAID1.sai                = SAI1;
  SAID1.blocks[0].saiblock = SAI1_Block_A;
  SAID1.blocks[0].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
  SAID1.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
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
  SAID1.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
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
  SAID1.blocks[1].saiblock = SAI1_Block_B;
  SAID1.blocks[1].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
  SAID1.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
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
  SAID1.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI1_DMA_PRIORITY) |
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
#endif /* STM32_SAI_USE_SAI1 */

#if STM32_SAI_USE_SAI2
  saiObjectInit(&SAID2);
  SAID2.sai                = SAI2;
  SAID2.blocks[0].saiblock = SAI2_Block_A;
  SAID2.blocks[0].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
  SAID2.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
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
  SAID2.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
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
  SAID2.blocks[1].saiblock = SAI2_Block_B;
  SAID2.blocks[1].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
  SAID2.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
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
  SAID2.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI2_DMA_PRIORITY) |
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
#endif /* STM32_SAI_USE_SAI2 */

#if STM32_SAI_USE_SAI3
  saiObjectInit(&SAID3);
  SAID3.sai                = SAI3;
  SAID3.blocks[0].saiblock = SAI3_Block_A;
  SAID3.blocks[0].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
  SAID3.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
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
  SAID3.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
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
  SAID3.blocks[1].saiblock = SAI3_Block_B;
  SAID3.blocks[1].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
  SAID3.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
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
  SAID3.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI3_DMA_PRIORITY) |
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
#endif /* STM32_SAI_USE_SAI3 */

#if STM32_SAI_USE_SAI4
  saiObjectInit(&SAID4);
  SAID4.sai                = SAI4;
  SAID4.blocks[0].saiblock = SAI4_Block_A;
  SAID4.blocks[0].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
  SAID4.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
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
  SAID4.blocks[0].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
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
  SAID4.blocks[1].saiblock = SAI4_Block_B;
  SAID4.blocks[1].dma      = NULL;
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
  SAID4.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
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
  SAID4.blocks[1].dmamode  = STM32_DMA_CR_PL(STM32_SAI_SAI4_DMA_PRIORITY) |
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
#endif /* STM32_SAI_USE_SAI4 */

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

#if STM32_SAI_USE_SAI1
    if (&SAID1 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI1(true);

      /* SAI configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* Enable Subclocks only if buffer is not NULL */
      if (saip->blocks[0].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE)
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI1A_DMA_STREAM,
                                              STM32_SAI_SAI1_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#else
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI1A_DMA_STREAM,
                                              STM32_SAI_SAI1_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_A_MODE) */

      osalDbgAssert(saip->blocks[0].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[0].dma, STM32_DMAMUX1_SAI1_A);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[0].saiblock->CR2   = saip->blocks[0].config->cr2;
      saip->blocks[0].saiblock->FRCR  = saip->blocks[0].config->frcr;
      saip->blocks[0].saiblock->SLOTR = saip->blocks[0].config->slotr;

      saip->blocks[0].saiblock->CR1  |= saip->blocks[0].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI1_ACR1;
      }

      if (saip->blocks[1].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE)
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI1B_DMA_STREAM,
                                              STM32_SAI_SAI1_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#else
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI1B_DMA_STREAM,
                                              STM32_SAI_SAI1_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI1_SUB_B_MODE) */

      osalDbgAssert(saip->blocks[1].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[1].dma, STM32_DMAMUX1_SAI1_B);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[1].saiblock->CR2   = saip->blocks[1].config->cr2;
      saip->blocks[1].saiblock->FRCR  = saip->blocks[1].config->frcr;
      saip->blocks[1].saiblock->SLOTR = saip->blocks[1].config->slotr;

      saip->blocks[1].saiblock->CR1  |= saip->blocks[1].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI1_BCR1;
      }
    }
#endif /* STM32_SAI_USE_SAI1 */

#if STM32_SAI_USE_SAI2
    if (&SAID2 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI2(true);

      /* SAI configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* Enable Subclocks only if buffer is not NULL */
      if (saip->blocks[0].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE)
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI2A_DMA_STREAM,
                                              STM32_SAI_SAI2_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#else
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI2A_DMA_STREAM,
                                              STM32_SAI_SAI2_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_A_MODE) */

      osalDbgAssert(saip->blocks[0].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[0].dma, STM32_DMAMUX1_SAI2_A);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[0].saiblock->CR2   = saip->blocks[0].config->cr2;
      saip->blocks[0].saiblock->FRCR  = saip->blocks[0].config->frcr;
      saip->blocks[0].saiblock->SLOTR = saip->blocks[0].config->slotr;

      saip->blocks[0].saiblock->CR1  |= saip->blocks[0].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI2_ACR1;
      }

      if (saip->blocks[1].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE)
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI2B_DMA_STREAM,
                                              STM32_SAI_SAI2_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#else
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI2B_DMA_STREAM,
                                              STM32_SAI_SAI2_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI2_SUB_B_MODE) */

      osalDbgAssert(saip->blocks[1].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[1].dma, STM32_DMAMUX1_SAI2_B);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[1].saiblock->CR2   = saip->blocks[1].config->cr2;
      saip->blocks[1].saiblock->FRCR  = saip->blocks[1].config->frcr;
      saip->blocks[1].saiblock->SLOTR = saip->blocks[1].config->slotr;

      saip->blocks[1].saiblock->CR1  |= saip->blocks[1].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI2_BCR1;
      }
    }
#endif /* STM32_SAI_USE_SAI2 */

#if STM32_SAI_USE_SAI3
    if (&SAID3 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI3(true);

      /* SAI configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* Enable Subclocks only if buffer is not NULL */
      if (saip->blocks[0].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE)
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI3A_DMA_STREAM,
                                              STM32_SAI_SAI3_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#else
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI3A_DMA_STREAM,
                                              STM32_SAI_SAI3_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_A_MODE) */

      osalDbgAssert(saip->blocks[0].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[0].dma, STM32_DMAMUX1_SAI3_A);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[0].saiblock->CR2   = saip->blocks[0].config->cr2;
      saip->blocks[0].saiblock->FRCR  = saip->blocks[0].config->frcr;
      saip->blocks[0].saiblock->SLOTR = saip->blocks[0].config->slotr;

      saip->blocks[0].saiblock->CR1  |= saip->blocks[0].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI3_ACR1;
      }

      if (saip->blocks[1].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE)
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI3B_DMA_STREAM,
                                              STM32_SAI_SAI3_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#else
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI3B_DMA_STREAM,
                                              STM32_SAI_SAI3_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI3_SUB_B_MODE) */

      osalDbgAssert(saip->blocks[1].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[1].dma, STM32_DMAMUX1_SAI3_B);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[1].saiblock->CR2   = saip->blocks[1].config->cr2;
      saip->blocks[1].saiblock->FRCR  = saip->blocks[1].config->frcr;
      saip->blocks[1].saiblock->SLOTR = saip->blocks[1].config->slotr;

      saip->blocks[1].saiblock->CR1  |= saip->blocks[1].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI3_BCR1;
      }
    }
#endif /* STM32_SAI_USE_SAI3 */

#if STM32_SAI_USE_SAI4
    if (&SAID4 == saip) {

      /* Enabling SAI unit clock.*/
      rccEnableSAI4(true);

      /* SAI configuration.*/
      saip->sai->GCR = saip->config->gcr;

      /* Enable Subclocks only if buffer is not NULL */
      if (saip->blocks[0].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE)
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI4A_DMA_STREAM,
                                              STM32_SAI_SAI4_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#else
        saip->blocks[0].dma = dmaStreamAllocI(STM32_SAI_SAI4A_DMA_STREAM,
                                              STM32_SAI_SAI4_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[0].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_A_MODE) */

      osalDbgAssert(saip->blocks[0].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[0].dma, STM32_DMAMUX2_SAI4_A);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[0].saiblock->CR2   = saip->blocks[0].config->cr2;
      saip->blocks[0].saiblock->FRCR  = saip->blocks[0].config->frcr;
      saip->blocks[0].saiblock->SLOTR = saip->blocks[0].config->slotr;

      saip->blocks[0].saiblock->CR1  |= saip->blocks[0].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI4_ACR1;
      }

      if (saip->blocks[1].config->buffer != NULL) {
#if STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE)
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI4B_DMA_STREAM,
                                              STM32_SAI_SAI4_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_rx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#else
        saip->blocks[1].dma = dmaStreamAllocI(STM32_SAI_SAI4B_DMA_STREAM,
                                              STM32_SAI_SAI4_IRQ_PRIORITY,
                                              (stm32_dmaisr_t)sai_lld_serve_tx_interrupt,
                                              (void *)saip->blocks[1].saiblock);
#endif /* STM32_SAI_BLOCK_RX_ENABLED(STM32_SAI_SAI4_SUB_B_MODE) */

      osalDbgAssert(saip->blocks[1].dma != NULL, "unable to allocate stream");
      dmaSetRequestSource(saip->blocks[1].dma, STM32_DMAMUX2_SAI4_B);

      /* CRs settings are done here because those never changes until
         the driver is stopped.*/
      saip->blocks[1].saiblock->CR2   = saip->blocks[1].config->cr2;
      saip->blocks[1].saiblock->FRCR  = saip->blocks[1].config->frcr;
      saip->blocks[1].saiblock->SLOTR = saip->blocks[1].config->slotr;

      saip->blocks[1].saiblock->CR1  |= saip->blocks[1].config->cr1 |
                                       SAI_xCR1_DMAEN | STM32_SAI4_BCR1;
      }
    }
#endif /* STM32_SAI_USE_SAI4 */
  }

  /* Clear IMR */
  saip->blocks[0].saiblock->IMR = 0;
  saip->blocks[1].saiblock->IMR = 0;

  /* Clear status */
  saip->blocks[0].saiblock->CLRFR = 0x7F;
  saip->blocks[1].saiblock->CLRFR = 0x7F;

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
    saip->blocks[0].saiblock->CR1 = 0;
    saip->blocks[0].saiblock->CR2 = 0;

    saip->blocks[1].saiblock->CR1 = 0;
    saip->blocks[1].saiblock->CR2 = 0;

    if (NULL != saip->blocks[0].dma) {
      dmaStreamFreeI(saip->blocks[0].dma);
      saip->blocks[0].dma = NULL;
    }

    if (NULL != saip->blocks[1].dma) {
      dmaStreamFreeI(saip->blocks[1].dma);
      saip->blocks[1].dma = NULL;
    }

#if (STM32_SAI_USE_SAI1)
    if (&SAID1 == saip)
      rccDisableSAI1();
#endif

#if (STM32_SAI_USE_SAI2)
    if (&SAID2 == saip)
      rccDisableSAI2();
#endif

#if (STM32_SAI_USE_SAI3)
    if (&SAID3 == saip)
      rccDisableSAI3();
#endif

#if (STM32_SAI_USE_SAI4)
    if (&SAID4 == saip)
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
  size_t size = 0;

  /* DMA setup.*/
  if (NULL != saip->blocks[0].dma) {
    size = saip->blocks[0].config->size;
    dmaStreamSetMode(saip->blocks[0].dma, saip->blocks[0].dmamode);
    dmaStreamSetPeripheral(saip->blocks[0].dma, &saip->blocks[0].saiblock->DR);
    dmaStreamSetMemory0(saip->blocks[0].dma, saip->blocks[0].config->buffer);
    dmaStreamSetTransactionSize(saip->blocks[0].dma, size);
    dmaStreamEnable(saip->blocks[0].dma);

    /* Starting transfer.*/
    saip->blocks[0].saiblock->CR1 |=  SAI_xCR1_SAIEN;
  }

  /* DMA setup.*/
  if (NULL != saip->blocks[1].dma) {
    size = saip->blocks[1].config->size;
    dmaStreamSetMode(saip->blocks[1].dma, saip->blocks[1].dmamode);
    dmaStreamSetPeripheral(saip->blocks[1].dma, &saip->blocks[1].saiblock->DR);
    dmaStreamSetMemory0(saip->blocks[1].dma, saip->blocks[1].config->buffer);
    dmaStreamSetTransactionSize(saip->blocks[1].dma, size);
    dmaStreamEnable(saip->blocks[1].dma);

    /* Starting transfer.*/
    saip->blocks[1].saiblock->CR1 |=  SAI_xCR1_SAIEN;
  }
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
  saip->blocks[0].saiblock->CR1 &=  ~SAI_xCR1_SAIEN;
  saip->blocks[1].saiblock->CR1 &=  ~SAI_xCR1_SAIEN;

  /* Stop DMA, if enabled.*/
  if (NULL != saip->blocks[0].dma) {
    dmaStreamDisable(saip->blocks[0].dma);
  }

  if (NULL != saip->blocks[1].dma) {
    dmaStreamDisable(saip->blocks[1].dma);
  }
}

#endif /* HAL_USE_SAI */

/** @} */
