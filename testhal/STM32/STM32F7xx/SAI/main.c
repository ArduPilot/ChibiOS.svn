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

#include "chprintf.h"
#include "wm8994.h"

#include <math.h>

/*
 * ANSI escape code:
 * The first one (\033[2J) clears the entire screen (J) from top to bottom (2).
 * The second code (\033[1;1H) positions the cursor at row 1, column 1.
 */
#define CLEAR_TERMINAL             "\033[2J\033[1;1H"

#define SAMPLE_RATE 44100  // Frequenza di campionamento in Hz
#define FREQUENCY 440      // Frequenza della sinusoide in Hz
#define AMPLITUDE 32767    // Amplitudine massima per int16_t (16 bit PCM)
#define CHANNELS 2         // Numero di canali (stereo)

#define PERIOD_SAMPLES (SAMPLE_RATE / FREQUENCY) // Campioni per un periodo

static uint32_t full, half;

static int16_t stereo_sine_wave[PERIOD_SAMPLES * CHANNELS];

void generate_stereo_sine_wave(void) {
    for (int i = 0; i < PERIOD_SAMPLES; i++) {
        // Calcola la sinusoide per il campione corrente
        float t = (float)i / SAMPLE_RATE;  // Tempo corrente in secondi
        float sample = sinf(2.0f * M_PI * FREQUENCY * t) * AMPLITUDE;

        // Scrive il campione nei due canali stereo
        stereo_sine_wave[i * 2] = (int16_t)sample;      // Canale sinistro
        stereo_sine_wave[i * 2 + 1] = (int16_t)sample; // Canale destro
    }
}

void tx_cb (SAIBlockDriver *saibp) {
  if (saiIsBufferComplete(saibp)) {
    full++;
  }
  else {
    half++;
  }
}

/*
 * SAI configuration
 * F_ref_clk_sai = PLL2SAIQ
 * PLL2SAIQ Input = HSE_VALUE/PLLM = 1 Mhz
 * PLL2SAIQ Output = PLL2SAIQ Input * PLLSAIN = 271 Mhz
 * SAI_CLK_x = PLL2SAIQ Output/PLLSAIQ = 429/38 = 45.16 Mhz
 * MCKDIV = 3 -> SAI_CL_x = 45.16 / 4 = 11.2915 MHz (0.002% error)
 * OSR = 0, Fs = SAI_CLK / 256.
 * Fs = 44,108 KHz
 * 16 bit audio
 */
static const SAIConfig saicfg = {
  0,                                           /* GCR   */
  {
   /* Sub block A configuration */
   {
    stereo_sine_wave,
    PERIOD_SAMPLES * CHANNELS,
    tx_cb,
    SAI_xCR1_MCKDIV_0 | SAI_xCR1_MCKDIV_1 |
    SAI_xCR1_DS_2 | SAI_xCR1_CKSTR,            /* CR1   */
    SAI_xCR2_FTH_0,                            /* CR2   */
    0x50f1f,//SAI_xFRCR_FRL_0 | SAI_xFRCR_FRL_5,         /* FRCR  */
    0x30100,//SAI_xSLOTR_NBSLOT_0 | SAI_xSLOTR_SLOTEN    /* SLOTR */
   },
   /* Sub Block B configuration */
   {
    NULL,
    0,
    NULL,
    0,                                         /* CR1   */
    0,                                         /* CR2   */
    0,                                         /* FRCR  */
    0                                          /* SLOTR */
   }
  }
};

/*
 * I2C configuration
 * According to WM8994 codec Timing parameters
 * SCLK frequency  max  400 KHz
 * SCLK low width  >=  1300 ns
 * SCLK high widt  >=   600 ns
 * Data Setup Time >=   100 ns
 * Data Hold Time  <=   900 ns
 *
 * PCLK4 = 54 MHz
 * Fast Mode configuration
 *
 */
static const I2CConfig i2ccfg = {
  0x6000030D,
  0,
  0
};

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetLine(LINE_LED2_GREEN);
    chThdSleepMilliseconds(500);
    palClearLine(LINE_LED2_GREEN);
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

  SCB_DisableICache();
  SCB_DisableDCache();

  generate_stereo_sine_wave();

  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sdStart(&SD1, NULL);

  /*
   * Activates the I2CD4.
   */
  i2cStart(&I2CD4, &i2ccfg);

  /*
   * Configures I2CD4 pins.
   */
  palSetPadMode(GPIOD, GPIOD_AUDIO_SCL, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                PAL_STM32_PUPDR_PULLUP);
  palSetPadMode(GPIOB, GPIOB_AUDIO_SDA, PAL_MODE_ALTERNATE(11) | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_OSPEED_HIGHEST |
                PAL_STM32_PUPDR_PULLUP);

  saiStart(&SAID1, &saicfg);
  saiStartExchange(&SAID1);

  wm8994Init(&I2CD4);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
