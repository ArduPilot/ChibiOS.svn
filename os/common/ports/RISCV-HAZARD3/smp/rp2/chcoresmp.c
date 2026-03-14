/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3 of the License.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    RISCV-HAZARD3/smp/rp2/chcoresmp.c
 * @brief   RISC-V Hazard3 RP2 SMP code.
 *
 * @addtogroup RISCV_HAZARD3_CORE_SMP_RP2
 * @{
 */

#include "ch.h"
#include "hazard3_irq.h"

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

static void port_local_halt(void) {
  const char *reason = "remote panic";

  port_disable();

  __trace_halt("remote panic");

  currcore->dbg.panic_msg = reason;

  CH_CFG_SYSTEM_HALT_HOOK(reason);

  while (true) {
  }
}

/*===========================================================================*/
/* Module interrupt handlers.                                                */
/*===========================================================================*/

/**
 * @brief   Single FIFO interrupt handler for both cores.
 * @note    RP2350 uses a shared SIO_IRQ_FIFO IRQ 25
 *
 * @isr
 */
CH_IRQ_HANDLER(VectorA4) {

  CH_IRQ_PROLOGUE();

  SIO->FIFO_ST = SIO_FIFO_ST_ROE | SIO_FIFO_ST_WOF;

  while ((SIO->FIFO_ST & SIO_FIFO_ST_VLD) != 0U) {
    uint32_t message = SIO->FIFO_RD;
    /* Core 1 checks for panic from Core 0.*/
    if ((message == PORT_FIFO_PANIC_MESSAGE) && (port_get_core_id() == 1U)) {
      port_local_halt();
    }
#if defined(PORT_HANDLE_FIFO_MESSAGE)
    if (message != PORT_FIFO_RESCHEDULE_MESSAGE) {
      PORT_HANDLE_FIFO_MESSAGE(port_get_core_id() ^ 1U, message);
    }
#else
    (void)message;
#endif
  }

  __SEV();

  CH_IRQ_EPILOGUE();
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   SMP-related port initialization.
 *
 * @param[in, out] oip  pointer to the @p os_instance_t structure
 */
void __port_smp_init(os_instance_t *oip) {

#if CH_CFG_ST_TIMEDELTA > 0
  /* Activating timer for this instance.*/
  port_timer_enable(oip);
#endif

#if CH_CFG_SMP_MODE == TRUE
  SIO->FIFO_ST = SIO_FIFO_ST_ROE | SIO_FIFO_ST_WOF;
  hazard3_irq_set_priority(25U, PORT_FIFO_IRQ_PRIORITY);
  hazard3_irq_enable(25U);
#endif

  (void)oip;
}

/**
 * @brief   Takes the kernel spinlock.
 */
void __port_spinlock_take(void) {

  port_spinlock_take();
}

/**
 * @brief   Releases the kernel spinlock.
 */
void __port_spinlock_release(void) {

  port_spinlock_release();
}

/** @} */
