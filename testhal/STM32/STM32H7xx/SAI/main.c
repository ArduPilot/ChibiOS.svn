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

#include "wm8994.h"
#include <math.h>

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
 * I2C configuration
 * According to WM8994 codec Timing parameters
 * SCLK frequency  max  400 KHz
 * SCLK low width  >=  1300 ns
 * SCLK high widt  >=   600 ns
 * Data Setup Time >=   100 ns
 * Data Hold Time  <=   900 ns
 *
 * PCLK4 = 120 MHz
 * T_presc = 120.000.000 Hz / (0x4 + 0x1) = 24.000.000 Hz
 * T_scll  = (0x28 + 0x1) / 24 MHz = 1,7 ns
 * T_sclh  = (0x12 + 0x1) / 24 MHz = 0,79 ns
 * SCLK freq = 1 / (1,7 + 0.79) = 401,60 KHz
 *
 */
static const I2CConfig i2ccfg = {
#if 0
  STM32_TIMINGR_PRESC(0x4U) |
  STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0xBU) |
  STM32_TIMINGR_SCLH(0x12U)  | STM32_TIMINGR_SCLL(0x28U)
#endif
  0x00B045E1,
  0,
  0
};

/*
 * SAI configuration
 * F_ref_clk_sai = PLL2P
 * PLL2_VCO Input = HSE_VALUE/PLL2M = 1 Mhz
 *  PLL2_VCO Output = PLL2_VCO Input * PLL2N = 429 Mhz
 * SAI_CLK_x = PLL2_VCO Output/PLL2P = 429/38 = 11.289 Mhz
 * MCKDIV = 0, OSR = 0, Fs = SAI_CLK / 256.
 * Fs = 44,099 KHz
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
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(50);
    palSetLine(LINE_LED_RED);
    chThdSleepMilliseconds(200);
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(50);
    palClearLine(LINE_LED_RED);
    chThdSleepMilliseconds(200);
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

  generate_stereo_sine_wave();

  i2cStart(&I2CD4, &i2ccfg);

  saiStart(&SAID2, &saicfg);
  saiStartExchange(&SAID2);

  wm8994Init(&I2CD4);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+1, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
