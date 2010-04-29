/*
    ChibiOS/RT - Copyright (C) 2009 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file COLDFIRE/coldfire_serial.c
 * @brief ColdFire low level serial driver code.
 * @addtogroup COLDFIRE_SERIAL
 * @{
 */



#include "ch.h"
#include "hal.h"

#if CH_HAL_USE_SERIAL || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/** @brief UART1 serial driver identifier.*/
#if USE_COLDFIRE_UART1 || defined(__DOXYGEN__)
SerialDriver SD1;
#endif

/** @brief UART2 serial driver identifier.*/
#if USE_COLDFIRE_UART2 || defined(__DOXYGEN__)
SerialDriver SD2;
#endif

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/** @brief Driver default configuration.*/
static const SerialConfig default_config =
{
  SERIAL_DEFAULT_BITRATE,
  mcf5206e_UART_UCSR_RX_TIMER|mcf5206e_UART_UCSR_TX_TIMER,
  mcf5206e_UART_UMR1_PM_NONE|mcf5206e_UART_UMR1_BC_8
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

CH_IRQ_HANDLER(UART1IrqHandler);
CH_IRQ_HANDLER(UART2IrqHandler);

/**
 * @brief UART initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] sdp pointer to a @p SerialDriver object
 */
static void uart_init(SerialDriver *sdp) {

  uint32_t b;

  b = F_CPU*10/32L;
  if (sdp->config->sc_speed)
    b /= sdp->config->sc_speed;
  if ((b % 10) >= 5)
    b += 10;
  b /= 10;

#if USE_COLDFIRE_UART1 || defined(__DOXYGEN__)
  if (sdp == &SD1)
  {
    sdp->uart1->UCR = mcf5206e_UART_UCR_RESET_TX;
    sdp->uart1->UCR = mcf5206e_UART_UCR_RESET_RX;
    sdp->uart1->UCR = mcf5206e_UART_UCR_RESET_MR;
    sdp->uart1->UBG1 = b>>8;
    sdp->uart1->UBG2 = b&0xFF;
    sdp->uart1->USR = mcf5206e_UART_UCSR_RX_TIMER|mcf5206e_UART_UCSR_TX_TIMER;
    sdp->uart1->UMR = mcf5206e_UART_UMR1_PM_NONE|mcf5206e_UART_UMR1_BC_8;
    sdp->uart1->UCR = mcf5206e_UART_UCR_TX_ENABLED|mcf5206e_UART_UCR_RX_ENABLED;
    sdp->uart1->UIR = mcf5206e_UART_UIMR_FFULL;

    sdp->uart1->UIR = mcf5206e_UART_UIMR_FFULL;
    *(volatile uint32_t *)(VBR+0x78) = (uint32_t)UART1IrqHandler;
    sim->sim.ICR12 = mcf5206e_SIM_ICR_AVEC|
                     mcf5206e_SIM_ICR_IL(6)|
                     mcf5206e_SIM_ICR_IP(COLDFIRE_UART1_PRIORITY);
    sim->sim.IMR &= ~mcf5206e_SIM_IMR_UART1;
  }
#endif

#if USE_COLDFIRE_UART2 || defined(__DOXYGEN__)
#error CODE NOT TESTED
  if (sdp == &SD2)
  {
    sdp->uart2->UCR = mcf5206e_UART_UCR_RESET_TX;
    sdp->uart2->UCR = mcf5206e_UART_UCR_RESET_RX;
    sdp->uart2->UCR = mcf5206e_UART_UCR_RESET_MR;
    sdp->uart2->UBG1 = b>>8;
    sdp->uart2->UBG2 = b&0xFF;
    sdp->uart2->USR = mcf5206e_UART_UCSR_RX_TIMER|mcf5206e_UART_UCSR_TX_TIMER;
    sdp->uart2->UMR = mcf5206e_UART_UMR1_PM_NONE|mcf5206e_UART_UMR1_BC_8;
    sdp->uart2->UCR = mcf5206e_UART_UCR_TX_ENABLED|mcf5206e_UART_UCR_RX_ENABLED;
    sdp->uart2->UIR = mcf5206e_UART_UIMR_FFULL;

    sdp->uart2->UIR = mcf5206e_UART_UIMR_FFULL;
//    *(volatile uint32_t *)(VBR+0x70) = (uint32_t)UART2IrqHandler;
//    sim->sim.ICR13 = mcf5206e_SIM_ICR_AVEC|
//                     mcf5206e_SIM_ICR_IL(4)|
//                     mcf5206e_SIM_ICR_IP(COLDFIRE_UART1_PRIORITY);
//    sim->sim.IMR &= ~mcf5206e_SIM_IMR_UART2;
  }
#endif

}

/**
 * @brief UART de-initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] sdp pointer to a @p SerialDriver object
 */
static void uart_deinit(SerialDriver *sdp) {

#if USE_COLDFIRE_UART1 || defined(__DOXYGEN__)
  if (sdp == &SD1)
  {
    sdp->uart1->UCR = mcf5206e_UART_UCR_RESET_TX;
    sdp->uart1->UCR = mcf5206e_UART_UCR_RESET_RX;
    sdp->uart1->UCR = mcf5206e_UART_UCR_RESET_MR;
    sim->sim.IMR |= mcf5206e_SIM_IMR_UART1;
  }
#endif

#if USE_COLDFIRE_UART2 || defined(__DOXYGEN__)
  if (sdp == &SD2)
  {
    sdp->uart2->UCR = mcf5206e_UART_UCR_RESET_TX;
    sdp->uart2->UCR = mcf5206e_UART_UCR_RESET_RX;
    sdp->uart2->UCR = mcf5206e_UART_UCR_RESET_MR;
    sim->sim.IMR |= mcf5206e_SIM_IMR_UART2;
  }
#endif

}

#if USE_COLDFIRE_UART1 || defined(__DOXYGEN__)
static void uart_notify1(void) {

  sim->uart1.UIR = mcf5206e_UART_UIMR_FFULL | mcf5206e_UART_UIMR_TXRDY;
}
#endif

#if USE_COLDFIRE_UART2 || defined(__DOXYGEN__)
static void uart_notify2(void) {

  sim->uart2.UIR = mcf5206e_UART_UIMR_FFULL | mcf5206e_UART_UIMR_TXRDY;
}
#endif

/**
 * @brief Error handling routine.
 *
 * @param[in] sdp pointer to a @p SerialDriver object
 * @param[in] sr UART SR register value
 */
static void set_error(SerialDriver *sdp, uint8_t usr) {
  sdflags_t sts = 0;

  if (usr & mcf5206e_UART_USR_RB)
    sts |= SD_BREAK_DETECTED;
  if (usr & mcf5206e_UART_USR_OE)
    sts |= SD_OVERRUN_ERROR;
  if (usr & mcf5206e_UART_USR_PE)
    sts |= SD_PARITY_ERROR;
  if (usr & mcf5206e_UART_USR_FE)
    sts |= SD_FRAMING_ERROR;
  chSysLockFromIsr();
  sdAddFlagsI(sdp, sts);
  chSysUnlockFromIsr();

}

/**
 * @brief Common IRQ handler.
 *
 * @param[in] sdp pointer to a @p UART1 SerialDriver object
 */
void serve_interrupt1(SerialDriver *sdp)
{
  uint8_t usr = sdp->uart1->USR;

// TODO: test it
  if (usr & (mcf5206e_UART_USR_RB | mcf5206e_UART_USR_FE | mcf5206e_UART_USR_PE | mcf5206e_UART_USR_OE)) {
    set_error(sdp, usr);
  }
  if (usr & mcf5206e_UART_USR_RXRDY)
  {
    chSysLockFromIsr();
    sdIncomingDataI(sdp, (uint8_t)sdp->uart1->UBUF);
    chSysUnlockFromIsr();
  }
  if (usr & mcf5206e_UART_USR_TXRDY)
  {
    msg_t b;

    chSysLockFromIsr();
    b = chOQGetI(&sdp->oqueue);
    if (b < Q_OK) {
      chEvtBroadcastI(&sdp->oevent);
      sdp->uart1->UIR = mcf5206e_UART_UIMR_FFULL;
    }
    else
      sdp->uart1->UBUF = b;
    chSysUnlockFromIsr();
  }
}

/**
 * @brief Common IRQ handler.
 *
 * @param[in] sdp pointer to a @p UART2 SerialDriver object
 */
void serve_interrupt2(SerialDriver *sdp)
{
  uint8_t usr = sdp->uart2->USR;

/*
  TODO: test it
  if (usr & (mcf5206e_UART_USR_RB | mcf5206e_UART_USR_FE | mcf5206e_UART_USR_PE | mcf5206e_UART_USR_OE)) {
    set_error(sdp, usr);
  }
*/
  if (usr & mcf5206e_UART_USR_RXRDY)
  {
    chSysLockFromIsr();
    sdIncomingDataI(sdp, (uint8_t)sdp->uart2->UBUF);
    chSysUnlockFromIsr();
  }
  if (usr & mcf5206e_UART_USR_TXRDY)
  {
    msg_t b;

    chSysLockFromIsr();
    b = chOQGetI(&sdp->oqueue);
    if (b < Q_OK) {
      chEvtBroadcastI(&sdp->oevent);
      sdp->uart2->UIR = mcf5206e_UART_UIMR_FFULL;
    }
    else
      sdp->uart2->UBUF = b;
    chSysUnlockFromIsr();
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if USE_COLDFIRE_UART1 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(UART1IrqHandler) {

	CH_IRQ_PROLOGUE();

	serve_interrupt1(&SD1);

	CH_IRQ_EPILOGUE();
}
#endif

#if USE_COLDFIRE_UART2 || defined(__DOXYGEN__)
CH_IRQ_HANDLER(UART2rqHandler) {

	CH_IRQ_PROLOGUE();

	serve_interrupt2(&SD2);

	CH_IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * Low level serial driver initialization.
 */
void sd_lld_init(void) {

#if USE_COLDFIRE_UART1
  sdObjectInit(&SD1, NULL, uart_notify1);
  SD1.uart1 = &sim->uart1;
#endif

#if USE_COLDFIRE_UART2
  sdObjectInit(&SD2, NULL, uart_notify2);
  SD2.uart2 = &sim->uart2;
#endif

}

/**
 * @brief Low level serial driver configuration and (re)start.
 *
 * @param[in] sdp pointer to a @p SerialDriver object
 */
void sd_lld_start(SerialDriver *sdp) {

  if (sdp->config == NULL)
    sdp->config = &default_config;
  if (sdp->state == SD_STOP) {
	  uart_init(sdp);
  }
}

/**
 * @brief Low level serial driver stop.
 * @details De-initializes the USART, stops the associated clock, resets the
 *          interrupt vector.
 *
 * @param[in] sdp pointer to a @p SerialDriver object
 */
void sd_lld_stop(SerialDriver *sdp) {

  if (sdp->state == SD_READY) {
    uart_deinit(sdp);
  }
}

#endif /* CH_HAL_USE_SERIAL */

/** @} */
