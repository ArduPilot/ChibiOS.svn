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

#define I2S_BUF_SIZE            256

static uint16_t i2s_tx_buf[I2S_BUF_SIZE];

static void i2scallback(I2SDriver *i2sp);

/*
 * I2S configuration.
 * i2s_clock is 75MHz (see mcuconf.h)
 * 16 bit I2S philips standard, falling edge at 48KHz.
 * ODD = 1, I2SDIV = 24, CKPOL = 0, CHLEN = 0, DATALEN = 0, I2SSTD = 0.
 */
static const I2SConfig i2scfg = {
  i2s_tx_buf,
  NULL,
  I2S_BUF_SIZE,
  i2scallback,
  SPI_I2SCFGR_ODD |
  (24 << SPI_I2SCFGR_I2SDIV_Pos)   /* CFGR register */
};

static void i2scallback(I2SDriver *i2sp) {

  if (i2sIsBufferComplete(i2sp)) {
    palSetLine(LINE_LED_RED);
  }
  else {
    /* 1st buffer half processing.*/
    palClearLine(LINE_LED_RED);
  }
}

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}

/*
 * Application entry point.
 */
int main(void) {

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
   * TODO: Handling cache
   */
  SCB_DisableDCache();
  SCB_DisableICache();

  uint16_t i;

  /* Fill buffer */
  for (i = 0; i < I2S_BUF_SIZE; i++) {
    i2s_tx_buf[i] = i;
  }

  /*
   * Starting and configuring the I2S driver 2.
   */
  i2sStart(&I2SD2, &i2scfg);

  /* I2S PLL MCO1 */
  palSetPadMode(GPIOA, 8, PAL_MODE_ALTERNATE(0));

  /* I2S CK */
  palSetPadMode(GPIOD, 3, PAL_MODE_ALTERNATE(5));

  /* I2S SDO/MOSI */
  palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5));

  /* I2S SDI/MISO */
  palSetPadMode(GPIOI, 12, PAL_MODE_ALTERNATE(5));

  /* I2S WS */
  palSetPadMode(GPIOB, 4, PAL_MODE_ALTERNATE(7));

  /*
   * Starting continuous I2S transfer.
   */
  i2sStartExchange(&I2SD2);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+1, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE) {
    if (palReadLine(LINE_BUTTON)) {
      i2sStopExchange(&I2SD2);
    }
    chThdSleepMilliseconds(500);
  }
}
