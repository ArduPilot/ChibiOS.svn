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

#include "ch.h"
#include "hal.h"

#include "portab.h"

/*
 * SPI TX and RX buffers.
 */
CC_ALIGN_DATA(32) static uint8_t txbuf[512];
CC_ALIGN_DATA(32) static uint8_t rxbuf[512];

#if SPI_SUPPORTS_CIRCULAR == TRUE
/*
 * SPI callback for circular operations.
 */
void spi_circular_cb(void *ip) {
  hal_spi_driver_c *spip = (hal_spi_driver_c *)ip;
  size_t n;

  /* Stopping circular transfer on button press.*/
  if (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED) {
    osalSysLockFromISR();
    spiStopTransferI(&PORTAB_SPI1, &n);
    osalSysUnlockFromISR();
  }

  switch (drvGetStateX(spip)) {
  case HAL_DRV_STATE_HALF:
    /* 1st half buffer filled.*/
#if defined(PORTAB_LINE_LED1)
    palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_ON);
#endif
    break;

  case HAL_DRV_STATE_FULL:
    /* 2nd half buffer filled.*/
#if defined(PORTAB_LINE_LED1)
    palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_OFF);
#endif
    break;

  case HAL_DRV_STATE_COMPLETE:
    /* Transfer completed.*/
    break;

  default:
    /* Must be HAL_DRV_STATE_ERROR.*/
    chSysHalt("SPI error");
  }
}
#endif

/*
 * SPI bus contender 1.
 */
static THD_WORKING_AREA(spi_thread_1_wa, 256);
static THD_FUNCTION(spi_thread_1, p) {

  (void)p;
  chRegSetThreadName("SPI thread 1");
  while (true) {
    drvLock(&PORTAB_SPI1);          /* Acquire ownership of the bus.    */
#if defined(PORTAB_LINE_LED1)
    palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_ON);
#endif
    drvStart(&PORTAB_SPI1);
    drvSelectCfgX(&PORTAB_SPI1,
                  SPI_CFG_HIGH_SPEED);  /* Setup transfer parameters.       */
    spiSelectX(&PORTAB_SPI1);           /* Slave Select assertion.          */
    spiExchange(&PORTAB_SPI1, 512,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiExchange(&PORTAB_SPI1, 127,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiExchange(&PORTAB_SPI1, 64,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiExchange(&PORTAB_SPI1, 1,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiUnselectX(&PORTAB_SPI1);         /* Slave Select de-assertion.       */
    cacheBufferInvalidate(&rxbuf[0],    /* Cache invalidation over the      */
                          sizeof rxbuf);/* buffer.                          */
    drvUnlock(&PORTAB_SPI1);            /* Ownership release.               */
  }
}

/*
 * SPI bus contender 2.
 */
static THD_WORKING_AREA(spi_thread_2_wa, 256);
static THD_FUNCTION(spi_thread_2, p) {

  (void)p;
  chRegSetThreadName("SPI thread 2");
  while (true) {
    drvLock(&PORTAB_SPI1);              /* Acquire ownership of the bus.    */
#if defined(PORTAB_LINE_LED1)
    palWriteLine(PORTAB_LINE_LED1, PORTAB_LED_OFF);
#endif
    drvStart(&PORTAB_SPI1);
    drvSelectCfgX(&PORTAB_SPI1,
                  SPI_CFG_LOW_SPEED);   /* Setup transfer parameters.       */
    spiSelectX(&PORTAB_SPI1);           /* Slave Select assertion.          */
    spiExchange(&PORTAB_SPI1, 512,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiExchange(&PORTAB_SPI1, 127,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiExchange(&PORTAB_SPI1, 64,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiExchange(&PORTAB_SPI1, 1,
                txbuf, rxbuf);          /* Atomic transfer operations.      */
    spiUnselectX(&PORTAB_SPI1);         /* Slave Select de-assertion.       */
    cacheBufferInvalidate(&rxbuf[0],    /* Cache invalidation over the      */
                          sizeof rxbuf);/* buffer.                          */
    drvUnlock(&PORTAB_SPI1);            /* Ownership release.               */
  }
}

/*
 * LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 256);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    bool key_pressed = palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED;
    systime_t time = key_pressed ? 250 : 500;
#if defined(PORTAB_LINE_LED2)
    palToggleLine(PORTAB_LINE_LED2);
#endif
    chThdSleepMilliseconds(time);
  }
}

/*
 * Application entry point.
 */
int main(void) {
  unsigned i;

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Board-dependent GPIO setup code.
   */
  portab_setup();

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Prepare transmit pattern.
   */
  for (i = 0; i < sizeof(txbuf); i++)
    txbuf[i] = (uint8_t)i;
  cacheBufferFlush(&txbuf[0], sizeof txbuf);

#if (SPI_SUPPORTS_SLAVE_MODE == TRUE) && defined(PORTAB_SPI2)
  drvStart(&PORTAB_SPI1);
  drvSelectCfgX(&PORTAB_SPI1, SPI_CFG_HIGH_SPEED);  /* Master transfer.     */
  drvStart(&PORTAB_SPI2);
  drvSelectCfgX(&PORTAB_SPI2, SPI_CFG_SLAVE);       /* Slave transfer.      */
  do {
    size_t size;

    /* Starting asynchronous SPI slave 512 frames receive.*/
    spiStartReceive(&PORTAB_SPI2, 512, rxbuf);

    /* Starting synchronous master 256 frames send.*/
    spiSelectX(&PORTAB_SPI1);
    spiSend(&PORTAB_SPI1, 256, txbuf);
    spiUnselectX(&PORTAB_SPI1);

    /* Stopping slave and getting slave status, it should still be
       ongoing because the master sent just 256 frames.*/
    spiStopTransfer(&PORTAB_SPI2, &size);

    /* Toggle the LED, wait a little bit and repeat.*/
#if defined(PORTAB_LINE_LED1)
    palToggleLine(PORTAB_LINE_LED1);
#endif
    chThdSleepMilliseconds(100);
  } while (palReadLine(PORTAB_LINE_BUTTON) != PORTAB_BUTTON_PRESSED);

  /* Waiting button release.*/
  while (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED) {
    chThdSleepMilliseconds(100);
  }
#endif

  /*
   * Transfers of various sizes.
   */
  drvStart(&PORTAB_SPI1);
  drvSelectCfgX(&PORTAB_SPI1, SPI_CFG_LOW_SPEED);
  do {
     /* Starting synchronous master 256 frames send.*/
     spiSelectX(&PORTAB_SPI1);
     spiIgnore(&PORTAB_SPI1, 1);
     spiExchange(&PORTAB_SPI1, 4, txbuf, rxbuf);
     spiSend(&PORTAB_SPI1, 7, txbuf+3);
     spiReceive(&PORTAB_SPI1, 16, rxbuf);
     spiUnselectX(&PORTAB_SPI1);

     /* Toggle the LED, wait a little bit and repeat.*/
 #if defined(PORTAB_LINE_LED1)
     palToggleLine(PORTAB_LINE_LED1);
 #endif
     chThdSleepMilliseconds(50);
   } while (palReadLine(PORTAB_LINE_BUTTON) != PORTAB_BUTTON_PRESSED);

   /* Waiting button release.*/
   while (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED) {
     chThdSleepMilliseconds(100);
   }

#if SPI_SUPPORTS_CIRCULAR == TRUE
  /*
   * Starting a continuous operation for test.
   */
  drvSetCallbackX(&PORTAB_SPI1, spi_circular_cb);
  drvStart(&PORTAB_SPI1);
  drvSelectCfgX(&PORTAB_SPI1, SPI_CFG_CIRCULAR);
  spiSelectX(&PORTAB_SPI1);           /* Slave Select assertion.          */
  spiSend(&PORTAB_SPI1, 512, txbuf);  /* Atomic transfer operations.      */
  spiUnselectX(&PORTAB_SPI1);         /* Slave Select de-assertion.       */
  cacheBufferInvalidate(&rxbuf[0],    /* Cache invalidation over the      */
                        sizeof rxbuf);/* buffer.                          */

  /* Waiting button release.*/
  while (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED) {
    chThdSleepMilliseconds(100);
  }
#endif

#if 0
  /*
   * Testing polled mixed with DMA transfers.
   */
  drvStart(&PORTAB_SPI1);
  drvSelectCfgX(&PORTAB_SPI1, SPI_CFG_LOW_SPEED);
  do {
     /* Starting synchronous master 256 frames send.*/
     spiSelectX(&PORTAB_SPI1);
     spiPolledExchange(&PORTAB_SPI1, txbuf[0x55]);
     spiPolledExchange(&PORTAB_SPI1, txbuf[0xAA]);
     spiPolledExchange(&PORTAB_SPI1, txbuf[0x33]);
     spiPolledExchange(&PORTAB_SPI1, txbuf[0xCC]);
     spiExchange(&PORTAB_SPI1, 4, txbuf, rxbuf);
     spiExchange(&PORTAB_SPI1, 3, txbuf+8, rxbuf);
     spiUnselectX(&PORTAB_SPI1);

     /* Toggle the LED, wait a little bit and repeat.*/
 #if defined(PORTAB_LINE_LED1)
     palToggleLine(PORTAB_LINE_LED1);
 #endif
     chThdSleepMilliseconds(100);
   } while (palReadLine(PORTAB_LINE_BUTTON) != PORTAB_BUTTON_PRESSED);
#endif

   /* Waiting button release.*/
   while (palReadLine(PORTAB_LINE_BUTTON) == PORTAB_BUTTON_PRESSED) {
     chThdSleepMilliseconds(100);
   }

  /*
   * Starting the transmitter and receiver threads.
   */
  chThdCreateStatic(spi_thread_1_wa, sizeof(spi_thread_1_wa),
                    NORMALPRIO + 1, spi_thread_1, NULL);
  chThdCreateStatic(spi_thread_2_wa, sizeof(spi_thread_2_wa),
                    NORMALPRIO + 1, spi_thread_2, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
  return 0;
}
