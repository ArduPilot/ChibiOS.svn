/*
    ChibiOS - Copyright (C) 2006..2021 Giovanni Di Sirio

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
 * @file    UARTv1/hal_sio_lld.c
 * @brief   RP SIO subsystem low level driver source.
 *
 * @addtogroup SIO
 * @{
 */

#include "hal.h"

#if (HAL_USE_SIO == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#define UART_LCRH_CFG_FORBIDDEN     (UART_UARTLCR_H_BRK)
#define UART_CR_CFG_FORBIDDEN       (UART_UARTCR_RXE    |                   \
                                     UART_UARTCR_TXE    |                   \
                                     UART_UARTCR_SIRLP  |                   \
                                     UART_UARTCR_SIREN  |                   \
                                     UART_UARTCR_UARTEN)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   UART0 SIO driver identifier.
 */
#if (RP_SIO_USE_UART0 == TRUE) || defined(__DOXYGEN__)
SIODriver SIOD0;
#endif

/**
 * @brief   UART1 SIO driver identifier.
 */
#if (RP_SIO_USE_UART1 == TRUE) || defined(__DOXYGEN__)
SIODriver SIOD1;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver default configuration.
 * @note    In this implementation it is: 38400-8-N-1.
 */
static const SIOConfig default_config = {
  .baud         = SIO_DEFAULT_BITRATE,
  .UARTLCR_H    = UART_UARTLCR_H_WLEN_8BITS | UART_UARTLCR_H_FEN,
  .UARTCR       = 0U,
  .UARTIFLS     = UART_UARTIFLS_RXIFLSEL_1_2F | UART_UARTIFLS_TXIFLSEL_1_2E,
  .UARTDMACR    = 0U
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

__STATIC_INLINE void uart_enable_rx_irq(SIODriver *siop) {

  if ((siop->enabled & SIO_FL_RXNOTEMPY) != 0U) {
    siop->uart->UARTIMSC |= UART_UARTIMSC_RXIM;
  }
  if ((siop->enabled & SIO_FL_RXIDLE) != 0U) {
    siop->uart->UARTIMSC |= UART_UARTIMSC_RTIM;
  }
}

__STATIC_INLINE void usart_enable_rx_errors_irq(SIODriver *siop) {

  if ((siop->enabled & SIO_FL_ALL_ERRORS) != 0U) {
  siop->uart->UARTIMSC |= UART_UARTIMSC_OEIM | UART_UARTIMSC_BEIM |
                          UART_UARTIMSC_PEIM | UART_UARTIMSC_FEIM;
  }
}

__STATIC_INLINE void usart_enable_tx_irq(SIODriver *siop) {

  if ((siop->enabled & SIO_FL_TXNOTFULL) != 0U) {
    siop->uart->UARTIMSC |= UART_UARTIMSC_TXIM;
  }
}

/**
 * @brief   UART initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] siop       pointer to a @p SIODriver object
 */
__STATIC_INLINE void uart_init(SIODriver *siop) {
  uint32_t div, idiv, fdiv;
  halfreq_t clock;

  clock = halClockGetPointX(clk_peri);

  osalDbgAssert(clock > 0U, "no clock");

  div = (8U * (uint32_t)clock) / siop->config->baud;
  idiv = div >> 7;
  fdiv = ((div & 0x7FU) + 1U) / 2U;

  osalDbgAssert((idiv > 0U) && (idiv <= 0xFFFFU), "invalid baud rate");

  siop->uart->UARTIBRD = idiv;
  siop->uart->UARTFBRD = fdiv;

  /* Registers settings, the LCR_H write also latches dividers values.*/
  siop->uart->UARTLCR_H = siop->config->UARTLCR_H & ~UART_LCRH_CFG_FORBIDDEN;
  siop->uart->UARTCR    = siop->config->UARTCR    & ~UART_CR_CFG_FORBIDDEN;
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level SIO driver initialization.
 *
 * @notapi
 */
void sio_lld_init(void) {

  /* Driver instances initialization.*/
#if RP_SIO_USE_UART0 == TRUE
  sioObjectInit(&SIOD0);
  SIOD0.uart = UART0;
  hal_lld_peripheral_reset(RESETS_ALLREG_UART0);
#endif
#if RP_SIO_USE_UART1 == TRUE
  sioObjectInit(&SIOD1);
  SIOD1.uart = UART1;
  hal_lld_peripheral_reset(RESETS_ALLREG_UART1);
#endif
}

/**
 * @brief   Configures and activates the SIO peripheral.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The operation status.
 *
 * @notapi
 */
msg_t sio_lld_start(SIODriver *siop) {

  /* Using the default configuration if the application passed a
     NULL pointer.*/
  if (siop->config == NULL) {
    siop->config = &default_config;
  }

  if (siop->state == SIO_STOP) {

  /* Enables the peripheral.*/
    if (false) {
    }
#if RP_SIO_USE_UART0 == TRUE
    else if (&SIOD0 == siop) {
      hal_lld_peripheral_unreset(RESETS_ALLREG_UART0);
      nvicEnableVector(RP_UART0_IRQ_NUMBER, RP_IRQ_UART0_PRIORITY);
    }
#endif
#if RP_SIO_USE_UART1 == TRUE
    else if (&SIOD1 == siop) {
      hal_lld_peripheral_unreset(RESETS_ALLREG_UART1);
      nvicEnableVector(RP_UART1_IRQ_NUMBER, RP_IRQ_UART1_PRIORITY);
    }
#endif
    else {
      osalDbgAssert(false, "invalid SIO instance");
    }

    /* Driver object low level initializations.*/
#if SIO_USE_SYNCHRONIZATION
    siop->sync_rx      = NULL;
    siop->sync_tx      = NULL;
    siop->sync_txend   = NULL;
#endif
  }

  /* Configures the peripheral.*/
  uart_init(siop);

  return HAL_RET_SUCCESS;
}

/**
 * @brief   Deactivates the SIO peripheral.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 *
 * @notapi
 */
void sio_lld_stop(SIODriver *siop) {

  if (siop->state == SIO_READY) {
    /* Resets the peripheral.*/

    /* Disables the peripheral.*/
    if (false) {
    }
#if RP_SIO_USE_UART0 == TRUE
    else if (&SIOD0 == siop) {
      nvicDisableVector(RP_UART0_IRQ_NUMBER);
      hal_lld_peripheral_reset(RESETS_ALLREG_UART0);
    }
#endif
#if RP_SIO_USE_UART1 == TRUE
    else if (&SIOD1 == siop) {
      nvicDisableVector(RP_UART1_IRQ_NUMBER);
      hal_lld_peripheral_reset(RESETS_ALLREG_UART1);
    }
#endif
    else {
      osalDbgAssert(false, "invalid SIO instance");
    }
  }
}

/**
 * @brief   Starts a SIO operation.
 *
 * @param[in] siop          pointer to an @p SIODriver structure
 *
 * @api
 */
void sio_lld_start_operation(SIODriver *siop) {

  /* Setting up the operation.*/
  siop->uart->UARTICR   = siop->uart->UARTRIS;
  siop->uart->UARTCR    = siop->config->UARTCR |
                          UART_UARTCR_RXE | UART_UARTCR_TXE | UART_UARTCR_UARTEN;
}

/**
 * @brief   Stops an ongoing SIO operation, if any.
 *
 * @param[in] siop      pointer to an @p SIODriver structure
 *
 * @api
 */
void sio_lld_stop_operation(SIODriver *siop) {

  /* Stop operation.*/
  siop->uart->UARTIMSC = 0U;
  siop->uart->UARTCR   = siop->config->UARTCR & ~UART_CR_CFG_FORBIDDEN;
}

/**
 * @brief   Enable flags change notification.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 */
void sio_lld_update_enable_flags(SIODriver *siop) {
  uint32_t cr1irq, cr2irq, cr3irq;

  cr1irq = siop->usart->CR1 & ~(USART_CR1_IDLEIE | USART_CR1_TCIE | USART_CR1_PEIE);
  cr2irq = siop->usart->CR2 & ~(USART_CR2_LBDIE);
  cr3irq = siop->usart->CR3 & ~(USART_CR3_RXFTIE | USART_CR3_TXFTIE | USART_CR3_EIE);

  cr1irq |= __sio_reloc_field(siop->enabled, SIO_FL_RXIDLE,     SIO_FL_RXIDLE_POS,     USART_CR1_IDLEIE_Pos) |
            __sio_reloc_field(siop->enabled, SIO_FL_TXDONE,     SIO_FL_TXDONE_POS,     USART_CR1_TCIE_Pos)   |
            __sio_reloc_field(siop->enabled, SIO_FL_ALL_ERRORS, SIO_FL_ALL_ERRORS_POS, USART_CR1_PEIE_Pos);
  cr2irq |= __sio_reloc_field(siop->enabled, SIO_FL_ALL_ERRORS, SIO_FL_ALL_ERRORS_POS, USART_CR2_LBDIE_Pos);
  cr3irq |= __sio_reloc_field(siop->enabled, SIO_FL_RXNOTEMPY,  SIO_FL_RXNOTEMPY_POS,  USART_CR3_RXFTIE_Pos) |
            __sio_reloc_field(siop->enabled, SIO_FL_TXNOTFULL,  SIO_FL_TXNOTFULL_POS,  USART_CR3_TXFTIE_Pos) |
            __sio_reloc_field(siop->enabled, SIO_FL_ALL_ERRORS, SIO_FL_ALL_ERRORS_POS, USART_CR3_EIE_Pos);

  /* Setting up the operation.*/
  siop->usart->CR1 = cr1irq;
  siop->usart->CR2 = cr2irq;
  siop->usart->CR3 = cr3irq;
}

/**
 * @brief   Get and clears SIO error event flags.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The pending event flags.
 *
 * @notapi
 */
sioevents_t sio_lld_get_and_clear_errors(SIODriver *siop) {
  uint32_t isr;
  sioevents_t errors = (sioevents_t)0;

  /* Getting all error ISR flags (and only those).
     NOTE: Do not trust the position of other bits in ISR/ICR because
           some scientist decided to use different positions for some
           of them.*/
  isr = siop->usart->ISR & SIO_LLD_ISR_RX_ERRORS;

  /* Clearing captured events.*/
  siop->usart->ICR = isr;

  /* Status flags cleared, now the RX errors-related interrupts can be
     enabled again.*/
  usart_enable_rx_errors_irq(siop);

  /* Translating the status flags in SIO events.*/
  errors |= __sio_reloc_field(isr, USART_ISR_LBDF_Msk, USART_ISR_LBDF_Pos, SIO_EV_BREAK_POS)       |
            __sio_reloc_field(isr, USART_ISR_PE_Msk,   USART_ISR_PE_Pos,   SIO_EV_PARITY_ERR_POS)  |
            __sio_reloc_field(isr, USART_ISR_FE_Msk,   USART_ISR_FE_Pos,   SIO_EV_FRAMING_ERR_POS) |
            __sio_reloc_field(isr, USART_ISR_NE_Msk,   USART_ISR_NE_Pos,   SIO_EV_NOISE_ERR_POS)   |
            __sio_reloc_field(isr, USART_ISR_ORE_Msk,  USART_ISR_ORE_Pos,  SIO_EV_OVERRUN_ERR_POS);

  return errors;
}

/**
 * @brief   Get and clears SIO event flags.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The pending event flags.
 *
 * @notapi
 */
sioevents_t sio_lld_get_and_clear_events(SIODriver *siop) {
  uint32_t isr;
  sioevents_t events = (sioevents_t)0;

  /* Getting all ISR flags.
     NOTE: Do not trust the position of other bits in ISR/ICR because
           some scientist decided to use different positions for some
           of them.*/
  isr = siop->usart->ISR & (SIO_LLD_ISR_RX_ERRORS |
                            USART_ISR_RXNE_RXFNE |
                            USART_ISR_TXE_TXFNF);

  /* Clearing captured events.*/
  siop->usart->ICR = isr;

  /* Status flags cleared, now the RX-related interrupts can be
     enabled again.*/
  usart_enable_rx_irq(siop);
  usart_enable_rx_errors_irq(siop);

  /* Translating the status flags in SIO events.*/
  events |= __sio_reloc_field(isr, USART_ISR_RXNE_RXFNE_Msk, USART_ISR_RXNE_RXFNE_Pos, SIO_EV_RXNOTEMPY_POS) |
            __sio_reloc_field(isr, USART_ISR_TXE_TXFNF_Msk,  USART_ISR_TXE_TXFNF_Pos,  SIO_EV_TXNOTFULL_POS) |
            __sio_reloc_field(isr, USART_ISR_IDLE_Msk, USART_ISR_IDLE_Pos, SIO_EV_RXIDLE_POS)      |
            __sio_reloc_field(isr, USART_ISR_TC_Msk,   USART_ISR_TC_Pos,   SIO_EV_TXDONE_POS)      |
            __sio_reloc_field(isr, USART_ISR_LBDF_Msk, USART_ISR_LBDF_Pos, SIO_EV_BREAK_POS)       |
            __sio_reloc_field(isr, USART_ISR_PE_Msk,   USART_ISR_PE_Pos,   SIO_EV_PARITY_ERR_POS)  |
            __sio_reloc_field(isr, USART_ISR_FE_Msk,   USART_ISR_FE_Pos,   SIO_EV_FRAMING_ERR_POS) |
            __sio_reloc_field(isr, USART_ISR_NE_Msk,   USART_ISR_NE_Pos,   SIO_EV_NOISE_ERR_POS)   |
            __sio_reloc_field(isr, USART_ISR_ORE_Msk,  USART_ISR_ORE_Pos,  SIO_EV_OVERRUN_ERR_POS);

  return events;
}

/**
 * @brief   Reads data from the RX FIFO.
 * @details The function is not blocking, it writes frames until there
 *          is space available without waiting.
 *
 * @param[in] siop          pointer to an @p SIODriver structure
 * @param[in] buffer        pointer to the buffer for read frames
 * @param[in] n             maximum number of frames to be read
 * @return                  The number of frames copied from the buffer.
 * @retval 0                if the TX FIFO is full.
 */
size_t sio_lld_read(SIODriver *siop, uint8_t *buffer, size_t n) {
  size_t rd;

  rd = 0U;
  while (true) {

    /* If the RX FIFO has been emptied then the RX FIFO and IDLE interrupts
       are enabled again.*/
    if (sio_lld_is_rx_empty(siop)) {
      uart_enable_rx_irq(siop);
      break;
    }

    /* Buffer filled condition.*/
    if (rd >= n) {
      break;
    }

    *buffer++ = (uint8_t)siop->uart->UARTDR;
    rd++;
  }

  return rd;
}

/**
 * @brief   Writes data into the TX FIFO.
 * @details The function is not blocking, it writes frames until there
 *          is space available without waiting.
 *
 * @param[in] siop          pointer to an @p SIODriver structure
 * @param[in] buffer        pointer to the buffer for read frames
 * @param[in] n             maximum number of frames to be written
 * @return                  The number of frames copied from the buffer.
 * @retval 0                if the TX FIFO is full.
 */
size_t sio_lld_write(SIODriver *siop, const uint8_t *buffer, size_t n) {
  size_t wr;

  wr = 0U;
  while (true) {

    /* If the TX FIFO has been filled then the interrupt is enabled again.*/
    if (sio_lld_is_tx_full(siop)) {
      uart_enable_tx_irq(siop);
      break;
    }

    /* Buffer emptied condition.*/
    if (wr >= n) {
      break;
    }

    siop->uart->UARTDR = (uint32_t)*buffer++;
    wr++;
  }

  /* The transmit complete interrupt is always re-enabled on write.*/
  /* none */

  return wr;
}

/**
 * @brief   Returns one frame from the RX FIFO.
 * @note    If the FIFO is empty then the returned value is unpredictable.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @return              The frame from RX FIFO.
 *
 * @notapi
 */
msg_t sio_lld_get(SIODriver *siop) {
  msg_t msg;

  msg = (msg_t)(siop->uart->UARTDR & 0xFFU);

  /* If the RX FIFO has been emptied then the interrupt is enabled again.*/
  if (sio_lld_is_rx_empty(siop)) {
    uart_enable_rx_irq(siop);
  }

  return msg;
}

/**
 * @brief   Pushes one frame into the TX FIFO.
 * @note    If the FIFO is full then the behavior is unpredictable.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @param[in] data      frame to be written
 *
 * @notapi
 */
void sio_lld_put(SIODriver *siop, uint_fast16_t data) {

  siop->uart->UARTDR = data;

  /* If the TX FIFO has been filled then the interrupt is enabled again.*/
  if (sio_lld_is_tx_full(siop)) {
    uart_enable_tx_irq(siop);
  }

  /* The transmit complete interrupt is always re-enabled on write.*/
  /* none */
}

/**
 * @brief   Control operation on a serial port.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 * @param[in] operation control operation code
 * @param[in,out] arg   operation argument
 *
 * @return              The control operation status.
 * @retval MSG_OK       in case of success.
 * @retval MSG_TIMEOUT  in case of operation timeout.
 * @retval MSG_RESET    in case of operation reset.
 *
 * @notapi
 */
msg_t sio_lld_control(SIODriver *siop, unsigned int operation, void *arg) {

  (void)siop;
  (void)operation;
  (void)arg;

  return MSG_OK;
}

/**
 * @brief   Serves an USART interrupt.
 *
 * @param[in] siop      pointer to the @p SIODriver object
 *
 * @notapi
 */
void sio_lld_serve_interrupt(SIODriver *siop) {
  UART_TypeDef *u = siop->uart;
  uint32_t mis, imsc, evtmask;

  osalDbgAssert(siop->state == SIO_ACTIVE, "invalid state");

  /* Note, ISR flags are just read but not cleared, ISR sources are
     disabled instead.*/
  mis = u->UARTMIS;

  /* Read on control registers.*/
  imsc = u->UARTIMSC;

  /* Enabled errors/events handling.*/
  evtmask = mis & (UART_UARTMIS_OEMIS | UART_UARTMIS_BEMIS |
                   UART_UARTMIS_PEMIS | UART_UARTMIS_FEMIS);

  if (evtmask != 0U) {
    /* Disabling event sources.*/
    u->UARTIMSC = imsc & ~(UART_UARTIMSC_OEIM | UART_UARTIMSC_BEIM |
             UART_UARTIMSC_PEIM | UART_UARTIMSC_FEIM);

    /* The callback is invoked if defined.*/
    __sio_callback_rx_evt(siop);

    /* Waiting thread woken, if any.*/
    __sio_wakeup_rx(siop, SIO_MSG_ERRORS);

    /* Values could have been changed by the callback. */
    imsc = u->UARTIMSC;
  }

  /* RX FIFO is non-empty.*/
  if (((mis & UART_UARTMIS_RXMIS) != 0U)) {
    /* Called once then the interrupt source is disabled.*/
    u->UARTIMSC = imsc & ~UART_UARTIMSC_RXIM;

    /* The callback is invoked if defined.*/
    __sio_callback_rx(siop);

    /* Waiting thread woken, if any.*/
    __sio_wakeup_rx(siop, MSG_OK);

    /* Values could have been changed by the callback. */
    imsc = u->UARTIMSC;
  }

  /* RX idle condition.*/
  if ((mis & UART_UARTMIS_RTMIS) != 0U) {
    /* Called once then the interrupt source is disabled.*/
     u->UARTIMSC = imsc & ~UART_UARTIMSC_RTIM;

    /* The callback is invoked if defined.*/
    __sio_callback_rx_idle(siop);

    /* Waiting thread woken, if any.*/
    __sio_wakeup_rx(siop, SIO_MSG_IDLE);

    /* Values could have been changed by the callback. */
    imsc = u->UARTIMSC;
  }

  /* TX FIFO is non-full.*/
  if ((mis & UART_UARTMIS_TXMIS) != 0U) {
    /* Called once then the interrupt source is disabled.*/
    u->UARTIMSC = imsc & ~UART_UARTIMSC_TXIM;

    /* The callback is invoked if defined.*/
    __sio_callback_tx(siop);

    /* Waiting thread woken, if any.*/
    __sio_wakeup_tx(siop, MSG_OK);
  }
}

#endif /* HAL_USE_SIO == TRUE */

/** @} */
