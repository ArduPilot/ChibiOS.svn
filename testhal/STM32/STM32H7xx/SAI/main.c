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

#if 0
.size=MP3_BUFF_SIZE,
.tx_buffer=wave_buf,
.CR1=SAI_CCR1
.CR2=0x1
.SR=0x0
.SLOTR=0x30100
.FRCR=0x50f1f
.GCR=0
#endif

void tx_cb (SAIBlockDriver *saibp) {
  if (saiIsBufferComplete(saibp)) {
    full++;
  }
  else {
    half++;
  }
}

/*
 * F_ref_clk_sai = PLL1Q (60 MHz)
 * NOMCK = 1, FRL = 33, MCKDIV = 40
 * Fs = 44,117 KHz
 * 16 bit audio
 */
static const SAIConfig saicfg = {
  0,                                           /* GCR   */
  {
   /* Sub block A configuration */
   {
    (uint8_t *)stereo_sine_wave,
    sizeof (stereo_sine_wave),
    tx_cb,
    SAI_xCR1_NOMCK | SAI_xCR1_DS_2 |           /* CR1   */
    SAI_xCR1_MCKDIV_3 | SAI_xCR1_MCKDIV_5 ,
    SAI_xCR2_FTH_0,                            /* CR2   */
    SAI_xFRCR_FRL_0 | SAI_xFRCR_FRL_5,         /* FRCR  */
    SAI_xSLOTR_NBSLOT_0 | SAI_xSLOTR_SLOTEN    /* SLOTR */
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

  saiStart(&SAID2, &saicfg);
  saiStartExchange(&SAID2);

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
