/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011 Giovanni Di Sirio.

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
*/

/**
 * @file    STM32/pwm_lld.c
 * @brief   STM32 PWM subsystem low level driver header.
 *
 * @addtogroup PWM
 * @{
 */

#include "ch.h"
#include "hal.h"

#if HAL_USE_PWM || defined(__DOXYGEN__)

/* There are differences in vector names in the ST header for devices
   including TIM15, TIM16, TIM17.*/
#if STM32_HAS_TIM15
#define TIM1_BRK_IRQn       TIM1_BRK_TIM15_IRQn
#endif
#if STM32_HAS_TIM16
#define TIM1_UP_IRQn        TIM1_UP_TIM16_IRQn
#endif
#if STM32_HAS_TIM17
#define TIM1_TRG_COM_IRQn   TIM1_TRG_COM_TIM17_IRQn
#endif

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   PWMD1 driver identifier.
 * @note    The driver PWMD1 allocates the complex timer TIM1 when enabled.
 */
#if STM32_PWM_USE_TIM1 || defined(__DOXYGEN__)
PWMDriver PWMD1;
#endif

/**
 * @brief   PWMD2 driver identifier.
 * @note    The driver PWMD2 allocates the timer TIM2 when enabled.
 */
#if STM32_PWM_USE_TIM2 || defined(__DOXYGEN__)
PWMDriver PWMD2;
#endif

/**
 * @brief   PWMD3 driver identifier.
 * @note    The driver PWMD3 allocates the timer TIM3 when enabled.
 */
#if STM32_PWM_USE_TIM3 || defined(__DOXYGEN__)
PWMDriver PWMD3;
#endif

/**
 * @brief   PWMD4 driver identifier.
 * @note    The driver PWMD4 allocates the timer TIM4 when enabled.
 */
#if STM32_PWM_USE_TIM4 || defined(__DOXYGEN__)
PWMDriver PWMD4;
#endif

/**
 * @brief   PWMD5 driver identifier.
 * @note    The driver PWMD5 allocates the timer TIM5 when enabled.
 */
#if STM32_PWM_USE_TIM5 || defined(__DOXYGEN__)
PWMDriver PWMD5;
#endif

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if STM32_PWM_USE_TIM2 || STM32_PWM_USE_TIM3 || STM32_PWM_USE_TIM4 ||       \
    STM32_PWM_USE_TIM5 || defined(__DOXYGEN__)
/**
 * @brief   Common TIM2...TIM5 IRQ handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 */
static void serve_interrupt(PWMDriver *pwmp) {
  uint16_t sr;

  sr  = pwmp->tim->SR;
  sr &= pwmp->tim->DIER;
  pwmp->tim->SR = ~(TIM_SR_CC1IF | TIM_SR_CC2IF | TIM_SR_CC3IF |
                    TIM_SR_CC4IF | TIM_SR_UIF);
  if ((sr & TIM_SR_CC1IF) != 0)
    pwmp->config->channels[0].callback(pwmp);
  if ((sr & TIM_SR_CC2IF) != 0)
    pwmp->config->channels[1].callback(pwmp);
  if ((sr & TIM_SR_CC3IF) != 0)
    pwmp->config->channels[2].callback(pwmp);
  if ((sr & TIM_SR_CC4IF) != 0)
    pwmp->config->channels[3].callback(pwmp);
  if ((sr & TIM_SR_UIF) != 0)
    pwmp->config->callback(pwmp);
}
#endif /* STM32_PWM_USE_TIM2 || ... || STM32_PWM_USE_TIM5 */

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if STM32_PWM_USE_TIM1
/**
 * @brief   TIM1 update interrupt handler.
 * @note    It is assumed that this interrupt is only activated if the callback
 *          pointer is not equal to @p NULL in order to not perform an extra
 *          check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(TIM1_UP_IRQHandler) {

  CH_IRQ_PROLOGUE();

  TIM1->SR = ~TIM_SR_UIF;
  PWMD1.config->callback(&PWMD1);

  CH_IRQ_EPILOGUE();
}

/**
 * @brief   TIM1 compare interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(TIM1_CC_IRQHandler) {
  uint16_t sr;

  CH_IRQ_PROLOGUE();

  sr = TIM1->SR & TIM1->DIER;
  TIM1->SR = ~(TIM_SR_CC1IF | TIM_SR_CC2IF | TIM_SR_CC3IF | TIM_SR_CC4IF);
  if ((sr & TIM_SR_CC1IF) != 0)
    PWMD1.config->channels[0].callback(&PWMD1);
  if ((sr & TIM_SR_CC2IF) != 0)
    PWMD1.config->channels[1].callback(&PWMD1);
  if ((sr & TIM_SR_CC3IF) != 0)
    PWMD1.config->channels[2].callback(&PWMD1);
  if ((sr & TIM_SR_CC4IF) != 0)
    PWMD1.config->channels[3].callback(&PWMD1);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_PWM_USE_TIM1 */

#if STM32_PWM_USE_TIM2
/**
 * @brief   TIM2 interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(TIM2_IRQHandler) {

  CH_IRQ_PROLOGUE();

  serve_interrupt(&PWMD2);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_PWM_USE_TIM2 */

#if STM32_PWM_USE_TIM3
/**
 * @brief   TIM3 interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(TIM3_IRQHandler) {

  CH_IRQ_PROLOGUE();

  serve_interrupt(&PWMD3);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_PWM_USE_TIM3 */

#if STM32_PWM_USE_TIM4
/**
 * @brief   TIM4 interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(TIM4_IRQHandler) {

  CH_IRQ_PROLOGUE();

  serve_interrupt(&PWMD4);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_PWM_USE_TIM4 */

#if STM32_PWM_USE_TIM5
/**
 * @brief   TIM5 interrupt handler.
 *
 * @isr
 */
CH_IRQ_HANDLER(TIM5_IRQHandler) {

  CH_IRQ_PROLOGUE();

  serve_interrupt(&PWMD5);

  CH_IRQ_EPILOGUE();
}
#endif /* STM32_PWM_USE_TIM5 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level PWM driver initialization.
 *
 * @notapi
 */
void pwm_lld_init(void) {

#if STM32_PWM_USE_TIM1
  /* Driver initialization.*/
  pwmObjectInit(&PWMD1);
  PWMD1.enabled_channels = 0;
  PWMD1.tim = TIM1;
#endif

#if STM32_PWM_USE_TIM2
  /* Driver initialization.*/
  pwmObjectInit(&PWMD2);
  PWMD2.enabled_channels = 0;
  PWMD2.tim = TIM2;
#endif

#if STM32_PWM_USE_TIM3
  /* Driver initialization.*/
  pwmObjectInit(&PWMD3);
  PWMD3.enabled_channels = 0;
  PWMD3.tim = TIM3;
#endif

#if STM32_PWM_USE_TIM4
  /* Driver initialization.*/
  pwmObjectInit(&PWMD4);
  PWMD4.enabled_channels = 0;
  PWMD4.tim = TIM4;
#endif

#if STM32_PWM_USE_TIM5
  /* Driver initialization.*/
  pwmObjectInit(&PWMD5);
  PWMD5.enabled_channels = 0;
  PWMD5.tim = TIM5;
#endif
}

/**
 * @brief   Configures and activates the PWM peripheral.
 * @note    Starting a driver that is already in the @p PWM_READY state
 *          disables all the active channels.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_start(PWMDriver *pwmp) {
  uint32_t clock, psc;
  uint16_t ccer;

  /* Reset channels.*/
  pwmp->enabled_channels = 0;               /* All channels disabled.       */

  if (pwmp->state == PWM_STOP) {
    /* Clock activation and timer reset.*/
#if STM32_PWM_USE_TIM1
    if (&PWMD1 == pwmp) {
      RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
      RCC->APB2RSTR = RCC_APB2RSTR_TIM1RST;
      RCC->APB2RSTR = 0;
      NVICEnableVector(TIM1_UP_IRQn,
                       CORTEX_PRIORITY_MASK(STM32_PWM_TIM1_IRQ_PRIORITY));
      NVICEnableVector(TIM1_CC_IRQn,
                       CORTEX_PRIORITY_MASK(STM32_PWM_TIM1_IRQ_PRIORITY));
      clock = STM32_TIMCLK2;
    }
#endif
#if STM32_PWM_USE_TIM2
    if (&PWMD2 == pwmp) {
      RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
      RCC->APB1RSTR = RCC_APB1RSTR_TIM2RST;
      RCC->APB1RSTR = 0;
      NVICEnableVector(TIM2_IRQn,
                       CORTEX_PRIORITY_MASK(STM32_PWM_TIM2_IRQ_PRIORITY));
      clock = STM32_TIMCLK1;
    }
#endif
#if STM32_PWM_USE_TIM3
    if (&PWMD3 == pwmp) {
      RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
      RCC->APB1RSTR = RCC_APB1RSTR_TIM3RST;
      RCC->APB1RSTR = 0;
      NVICEnableVector(TIM3_IRQn,
                       CORTEX_PRIORITY_MASK(STM32_PWM_TIM3_IRQ_PRIORITY));
      clock = STM32_TIMCLK1;
    }
#endif
#if STM32_PWM_USE_TIM4
    if (&PWMD4 == pwmp) {
      RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
      RCC->APB1RSTR = RCC_APB1RSTR_TIM4RST;
      RCC->APB1RSTR = 0;
      NVICEnableVector(TIM4_IRQn,
                       CORTEX_PRIORITY_MASK(STM32_PWM_TIM4_IRQ_PRIORITY));
      clock = STM32_TIMCLK1;
    }
#endif

#if STM32_PWM_USE_TIM5
    if (&PWMD5 == pwmp) {
      RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
      RCC->APB1RSTR = RCC_APB1RSTR_TIM5RST;
      RCC->APB1RSTR = 0;
      NVICEnableVector(TIM5_IRQn,
                       CORTEX_PRIORITY_MASK(STM32_PWM_TIM5_IRQ_PRIORITY));
      clock = STM32_TIMCLK1;
    }
#endif

    /* All channels configured in PWM1 mode with preload enabled and will
       stay that way until the driver is stopped.*/
    pwmp->tim->CCMR1 = TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 |
                       TIM_CCMR1_OC1PE |
                       TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 |
                       TIM_CCMR1_OC2PE;
    pwmp->tim->CCMR2 = TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 |
                       TIM_CCMR2_OC3PE |
                       TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 |
                       TIM_CCMR2_OC4PE;
  }
  else {
    /* Driver re-configuration scenario, it must be stopped first.*/
    pwmp->enabled_channels = 0;             /* All channels disabled.       */
    pwmp->tim->CR1  = 0;                    /* Timer disabled.              */
    pwmp->tim->DIER = 0;                    /* All IRQs disabled.           */
    pwmp->tim->SR   = 0;                    /* Clear eventual pending IRQs. */
    pwmp->tim->CCR1 = 0;                    /* Comparator 1 disabled.       */
    pwmp->tim->CCR2 = 0;                    /* Comparator 2 disabled.       */
    pwmp->tim->CCR3 = 0;                    /* Comparator 3 disabled.       */
    pwmp->tim->CCR4 = 0;                    /* Comparator 4 disabled.       */
    pwmp->tim->CNT  = 0;                    /* Counter reset to zero.       */
  }

  /* Timer configuration.*/
  psc = (clock / pwmp->config->frequency) - 1;
  chDbgAssert((psc <= 0xFFFF) &&
              ((psc + 1) * pwmp->config->frequency) == clock,
              "pwm_lld_start(), #1", "invalid frequency");
  pwmp->tim->PSC  = (uint16_t)psc;
  pwmp->tim->ARR  = (uint16_t)(pwmp->period - 1);
  pwmp->tim->CR2  = pwmp->config->cr2;

  /* Output enables and polarities setup.*/
  ccer = 0;
  switch (pwmp->config->channels[0].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= TIM_CCER_CC1P;
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= TIM_CCER_CC1E;
  default:
    ;
  }
  switch (pwmp->config->channels[1].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= TIM_CCER_CC2P;
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= TIM_CCER_CC2E;
  default:
    ;
  }
  switch (pwmp->config->channels[2].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= TIM_CCER_CC3P;
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= TIM_CCER_CC3E;
  default:
    ;
  }
  switch (pwmp->config->channels[3].mode & PWM_OUTPUT_MASK) {
  case PWM_OUTPUT_ACTIVE_LOW:
    ccer |= TIM_CCER_CC4P;
  case PWM_OUTPUT_ACTIVE_HIGH:
    ccer |= TIM_CCER_CC4E;
  default:
    ;
  }
#if STM32_PWM_USE_ADVANCED
  if (&PWMD1 == pwmp) {
    switch (pwmp->config->channels[0].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= TIM_CCER_CC1NP;
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= TIM_CCER_CC1NE;
    default:
      ;
    }
    switch (pwmp->config->channels[1].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= TIM_CCER_CC2NP;
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= TIM_CCER_CC2NE;
    default:
      ;
    }
    switch (pwmp->config->channels[2].mode & PWM_COMPLEMENTARY_OUTPUT_MASK) {
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW:
      ccer |= TIM_CCER_CC3NP;
    case PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH:
      ccer |= TIM_CCER_CC3NE;
    default:
      ;
    }
  }
#endif /* STM32_PWM_USE_ADVANCED*/

  pwmp->tim->CCER = ccer;
  pwmp->tim->EGR  = TIM_EGR_UG;             /* Update event.                */
  pwmp->tim->SR   = 0;                      /* Clear pending IRQs.          */
  pwmp->tim->DIER = pwmp->config->callback == NULL ? 0 : TIM_DIER_UIE;
#if STM32_PWM_USE_ADVANCED
  pwmp->tim->BDTR = pwmp->config->bdtr | TIM_BDTR_MOE;
#else
  pwmp->tim->BDTR = TIM_BDTR_MOE;
#endif
  /* Timer configured and started.*/
  pwmp->tim->CR1  = TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CEN;
}

/**
 * @brief   Deactivates the PWM peripheral.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 *
 * @notapi
 */
void pwm_lld_stop(PWMDriver *pwmp) {

  /* If in ready state then disables the PWM clock.*/
  if (pwmp->state == PWM_READY) {
    pwmp->enabled_channels = 0;             /* All channels disabled.       */
    pwmp->tim->CR1  = 0;                    /* Timer disabled.              */
    pwmp->tim->DIER = 0;                    /* All IRQs disabled.           */
    pwmp->tim->SR   = 0;                    /* Clear eventual pending IRQs. */
    pwmp->tim->BDTR  = 0;

#if STM32_PWM_USE_TIM1
    if (&PWMD1 == pwmp) {
      NVICDisableVector(TIM1_UP_IRQn);
      NVICDisableVector(TIM1_CC_IRQn);
      RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
    }
#endif
#if STM32_PWM_USE_TIM2
    if (&PWMD2 == pwmp) {
      NVICDisableVector(TIM2_IRQn);
      RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
    }
#endif
#if STM32_PWM_USE_TIM3
    if (&PWMD3 == pwmp) {
      NVICDisableVector(TIM3_IRQn);
      RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
    }
#endif
#if STM32_PWM_USE_TIM4
    if (&PWMD4 == pwmp) {
      NVICDisableVector(TIM4_IRQn);
      RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
    }
#endif
#if STM32_PWM_USE_TIM5
    if (&PWMD5 == pwmp) {
      NVICDisableVector(TIM5_IRQn);
      RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;
    }
#endif
  }
}

/**
 * @brief   Changes the period the PWM peripheral.
 * @details This function changes the period of a PWM unit that has already
 *          been activated using @p pwmStart().
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The PWM unit period is changed to the new value.
 * @post    Any active channel is disabled by this function and must be
 *          activated explicitly using @p pwmEnableChannel().
 * @note    The function has effect at the next cycle start.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] period    new cycle time in ticks
 *
 * @api
 */
void pwm_lld_change_period(PWMDriver *pwmp, pwmcnt_t period) {

  pwmp->enabled_channels = 0;           /* All channels disabled.           */
  pwmp->tim->DIER &= ~(TIM_DIER_CC1IE |
                       TIM_DIER_CC2IE |
                       TIM_DIER_CC3IE |
                       TIM_DIER_CC4IE); /* Channels sources disabled.       */
  pwmp->tim->SR    = ~(TIM_SR_CC1IF |
                       TIM_SR_CC1IF |
                       TIM_SR_CC1IF |
                       TIM_SR_CC1IF);   /* Clears eventual pending IRQs.    */
  pwmp->tim->ARR   = (uint16_t)(period - 1);
}

/**
 * @brief   Enables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The channel is active using the specified configuration.
 * @note    The function has effect at the next cycle start.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...PWM_CHANNELS-1)
 * @param[in] width     PWM pulse width as clock pulses number
 *
 * @notapi
 */
void pwm_lld_enable_channel(PWMDriver *pwmp,
                            pwmchannel_t channel,
                            pwmcnt_t width) {

  *(&pwmp->tim->CCR1 + (channel * 2)) = width;      /* New duty cycle.      */
  if ((pwmp->enabled_channels & (1 << channel)) == 0) {
    /* The channel is not enabled yet.*/
    pwmp->enabled_channels |= (1 << channel);
    /* If there is a callback associated to the channel then the proper
       interrupt is cleared and enabled.*/
    if (pwmp->config->channels[channel].callback) {
      pwmp->tim->SR    = ~(2 << channel);
      pwmp->tim->DIER |= (2 << channel);
    }
  }
}

/**
 * @brief   Disables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The channel is disabled and its output line returned to the
 *          idle state.
 * @note    The function has effect at the next cycle start.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier (0...PWM_CHANNELS-1)
 *
 * @notapi
 */
void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t channel) {

  *(&pwmp->tim->CCR1 + (channel * 2)) = 0;
  pwmp->tim->DIER &= ~(2 << channel);
  pwmp->enabled_channels &= ~(1 << channel);
}

#endif /* HAL_USE_PWM */

/** @} */
