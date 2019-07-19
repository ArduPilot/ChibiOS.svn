/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    chcore_v7m.c
 * @brief   ARMv7-M architecture port code.
 *
 * @addtogroup ARMCMx_V7M_CORE
 * @{
 */

#include "ch.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module interrupt handlers.                                                */
/*===========================================================================*/

#if (PORT_USE_SYSCALL == TRUE) || defined(__DOXYGEN__)
__attribute__((weak))
void port_syscall(struct port_extctx *ctxp, uint32_t n) {

  (void)ctxp;
  (void)n;

  chSysHalt("svc");
}
#endif

#if (CORTEX_SIMPLIFIED_PRIORITY == FALSE) || defined(__DOXYGEN__)
/**
 * @brief   SVC vector.
 * @details The SVC vector is used for exception mode re-entering after a
 *          context switch and, optionally, for system calls.
 * @note    The SVC vector is only used in advanced kernel mode.
 */
/*lint -save -e9075 [8.4] All symbols are invoked from asm context.*/
void SVC_Handler(void) {
/*lint -restore*/
  uint32_t psp = __get_PSP();

  chDbgAssert(((uint32_t)__builtin_return_address(0) & 4U) == 0U,
              "not process");

#if PORT_USE_SYSCALL == TRUE
  struct port_extctx *ctxp = (struct port_extctx *)psp;
  uint32_t n = (uint32_t)*(((const uint16_t *)ctxp->pc) - 1U) & 255U;

  /* SVC0 is used for unstacking, all other codes are used for
     system calls.*/
  if (n != 0U) {
    struct port_extctx *newctxp;

#if PORT_PRESERVE_CONTROL_REGISTER == TRUE
    {
      /* Saving CONTROL into a port_midctx structure.*/
      uint32_t control = __get_CONTROL();
      struct port_midctx *mctxp;

      psp -= sizeof (struct port_midctx);
      mctxp = (struct port_midctx *)psp;
      mctxp->control = (regarm_t)control;

      /* Enforcing privileged mode before returning.*/
      __set_CONTROL(control & ~1U);
    }
#endif

    /* Building an artificial return context, we need to make this
       return in the syscall dispatcher in privileged mode.*/
    psp -= sizeof (struct port_extctx);
    newctxp = (struct port_extctx *)psp;
    newctxp->r0     = (regarm_t)ctxp;
    newctxp->r1     = (regarm_t)n;
    newctxp->pc     = (regarm_t)port_syscall;
    newctxp->xpsr   = (regarm_t)0x01000000;
#if CORTEX_USE_FPU == TRUE
    newctxp->fpscr  = (regarm_t)FPU->FPDSCR;
#endif
  }
  else
#endif
  {
    /* Unstacking procedure, discarding the current exception context and
       positioning the stack to point to the real one.*/
    psp += sizeof (struct port_extctx);

#if CORTEX_USE_FPU == TRUE
    /* Enforcing unstacking of the FP part of the context.*/
    FPU->FPCCR &= ~FPU_FPCCR_LSPACT_Msk;
#endif

#if PORT_PRESERVE_CONTROL_REGISTER == TRUE
    {
      /* Restoring previous privileges by restoring CONTROL.*/
      struct port_midctx *mctxp = (struct port_midctx *)psp;
      __set_CONTROL((uint32_t)mctxp->control);
      psp += sizeof (struct port_midctx);
    }
#endif

    /* Restoring real position of the original stack frame.*/
    __set_PSP(psp);

    /* Restoring the normal interrupts status.*/
    port_unlock_from_isr();
  }
}
#endif /* CORTEX_SIMPLIFIED_PRIORITY == FALSE */

#if (CORTEX_SIMPLIFIED_PRIORITY == TRUE) || defined(__DOXYGEN__)
/**
 * @brief   PendSV vector.
 * @details The PendSV vector is used for exception mode re-entering after a
 *          context switch.
 * @note    The PendSV vector is only used in compact kernel mode.
 */
/*lint -save -e9075 [8.4] All symbols are invoked from asm context.*/
void PendSV_Handler(void) {
/*lint -restore*/
  uint32_t psp = __get_PSP();

#if CORTEX_USE_FPU
  /* Enforcing unstacking of the FP part of the context.*/
  FPU->FPCCR &= ~FPU_FPCCR_LSPACT_Msk;
#endif

  /* Discarding the current exception context and positioning the stack to
     point to the real one.*/
  psp += sizeof (struct port_extctx);

#if PORT_PRESERVE_CONTROL_REGISTER == TRUE
  {
    /* Restoring previous privileges by restoring CONTROL.*/
    struct port_midctx *mctxp = (struct port_midctx *)psp;
    __set_CONTROL((uint32_t)mctxp->control);
    psp += sizeof (struct port_midctx);
  }
#endif

  /* Restoring real position of the original stack frame.*/
  __set_PSP(psp);
}
#endif /* CORTEX_SIMPLIFIED_PRIORITY == TRUE */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Port-related initialization code.
 *
 * @param[in, out] oip  pointer to the @p os_instance_t structure
 */
void port_init(os_instance_t *oip) {

  (void)oip;

  /* Starting in a known IRQ configuration.*/
  __set_BASEPRI(CORTEX_BASEPRI_DISABLED);
  __enable_irq();

  /* Initializing priority grouping.*/
  NVIC_SetPriorityGrouping(CORTEX_PRIGROUP_INIT);

  /* DWT cycle counter enable, note, the M7 requires DWT unlocking.*/
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
#if CORTEX_MODEL == 7
  DWT->LAR = 0xC5ACCE55U;
#endif
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

  /* Initialization of the system vectors used by the port.*/
#if CORTEX_SIMPLIFIED_PRIORITY == FALSE
  NVIC_SetPriority(SVCall_IRQn, CORTEX_PRIORITY_SVCALL);
#endif
  NVIC_SetPriority(PendSV_IRQn, CORTEX_PRIORITY_PENDSV);

#if PORT_ENABLE_GUARD_PAGES == TRUE
  {
    extern stkalign_t __main_thread_stack_base__;

    /* Setting up the guard page on the main() function stack base
       initially.*/
    mpuConfigureRegion(PORT_USE_MPU_REGION,
                       &__main_thread_stack_base__,
                       MPU_RASR_ATTR_AP_NA_NA |
                       MPU_RASR_ATTR_NON_CACHEABLE |
                       MPU_RASR_SIZE_32 |
                       MPU_RASR_ENABLE);

    /* MPU is enabled.*/
    mpuEnable(MPU_CTRL_PRIVDEFENA);
  }
#endif
}

#if ((CH_DBG_ENABLE_STACK_CHECK == TRUE) &&                                 \
     (PORT_ENABLE_GUARD_PAGES == TRUE)) ||                                  \
    defined(__DOXYGEN__)
/**
 * @brief   Setting up MPU region for the current thread.
 */
void _port_set_region(void) {

  mpuSetRegionAddress(PORT_USE_MPU_REGION,
                      chThdGetSelfX()->wabase);
}
#endif

/**
 * @brief   Exception exit redirection to _port_switch_from_isr().
 */
void _port_irq_epilogue(void) {

  port_lock_from_isr();
  if ((SCB->ICSR & SCB_ICSR_RETTOBASE_Msk) != 0U) {
    struct port_extctx *ctxp;
    uint32_t psp = __get_PSP();

#if CORTEX_USE_FPU == TRUE
    /* Enforcing a lazy FPU state save by accessing the FPCSR register.*/
    (void) __get_FPSCR();
#endif

#if PORT_PRESERVE_CONTROL_REGISTER == TRUE
    {
      /* Saving CONTROL into a port_midctx structure.*/
      uint32_t control = __get_CONTROL();
      struct port_midctx *mctxp;

      psp -= sizeof (struct port_midctx);
      mctxp = (struct port_midctx *)psp;
      mctxp->control = (regarm_t)control;

      /* Enforcing privileged mode during the context switch because
         it is performed in thread state.*/
      __set_CONTROL(control & ~1U);
    }
#endif

    /* Adding an artificial exception return context, there is no need to
       populate it fully.*/
    psp -= sizeof (struct port_extctx);

    /* The port_extctx structure is pointed by the PSP register.*/
    ctxp = (struct port_extctx *)psp;

    /* Setting up a fake XPSR register value.*/
    ctxp->xpsr = (regarm_t)0x01000000;
#if CORTEX_USE_FPU == TRUE
    ctxp->fpscr = (regarm_t)FPU->FPDSCR;
#endif

    /* Writing back the modified PSP value.*/
    __set_PSP(psp);

    /* The exit sequence is different depending on if a preemption is
       required or not.*/
    if (chSchIsPreemptionRequired()) {
      /* Preemption is required we need to enforce a context switch.*/
      ctxp->pc = (regarm_t)_port_switch_from_isr;
    }
    else {
      /* Preemption not required, we just need to exit the exception
         atomically.*/
      ctxp->pc = (regarm_t)_port_exit_from_isr;
    }

    /* Note, returning without unlocking is intentional, this is done in
       order to keep the rest of the context switch atomic.*/
    return;
  }
  port_unlock_from_isr();
}

/** @} */
