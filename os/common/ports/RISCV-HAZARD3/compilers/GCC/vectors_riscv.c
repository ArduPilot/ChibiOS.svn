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
 * @file    RISCV-HAZARD3/compilers/GCC/vectors_riscv.c
 * @brief   Software vector table and external interrupt dispatcher for
 *          Hazard3 Xh3irq extension.
 * @details This file provides:
 *          - A default unhandled IRQ handler (weak, infinite loop)
 *          - 52 weak VectorXX symbols aliased to the default handler
 *          - A function pointer table indexed by IRQ number
 *          - The _external_interrupt_handler() that reads MEINEXT and
 *            dispatches to the appropriate VectorXX handler
 *
 *          The VectorXX names match the ARM NVIC convention used by HAL
 *          drivers, so handlers defined with OSAL_IRQ_HANDLER(VectorXX)
 *          automatically provide strong symbols that override the weak
 *          defaults at link time.
 *
 * @addtogroup RISCV_HAZARD3_VECTORS
 * @{
 */

#include <stdint.h>

#include "hazard3_irq.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/**
 * @brief   Default handler for unhandled external interrupts.
 */
__attribute__((weak))
void _unhandled_irq(void) {
  while (1)
    ;
}

/*===========================================================================*/
/* Weak VectorXX declarations.                                               */
/* Each is aliased to _unhandled_irq so HAL drivers can override them.       */
/*===========================================================================*/

/* IRQ  0 */ void Vector40(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  1 */ void Vector44(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  2 */ void Vector48(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  3 */ void Vector4C(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  4 */ void Vector50(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  5 */ void Vector54(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  6 */ void Vector58(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  7 */ void Vector5C(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  8 */ void Vector60(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ  9 */ void Vector64(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 10 */ void Vector68(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 11 */ void Vector6C(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 12 */ void Vector70(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 13 */ void Vector74(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 14 */ void Vector78(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 15 */ void Vector7C(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 16 */ void Vector80(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 17 */ void Vector84(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 18 */ void Vector88(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 19 */ void Vector8C(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 20 */ void Vector90(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 21 */ void Vector94(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 22 */ void Vector98(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 23 */ void Vector9C(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 24 */ void VectorA0(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 25 */ void VectorA4(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 26 */ void VectorA8(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 27 */ void VectorAC(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 28 */ void VectorB0(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 29 */ void VectorB4(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 30 */ void VectorB8(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 31 */ void VectorBC(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 32 */ void VectorC0(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 33 */ void VectorC4(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 34 */ void VectorC8(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 35 */ void VectorCC(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 36 */ void VectorD0(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 37 */ void VectorD4(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 38 */ void VectorD8(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 39 */ void VectorDC(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 40 */ void VectorE0(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 41 */ void VectorE4(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 42 */ void VectorE8(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 43 */ void VectorEC(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 44 */ void VectorF0(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 45 */ void VectorF4(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 46 */ void VectorF8(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 47 */ void VectorFC(void)  __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 48 */ void Vector100(void) __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 49 */ void Vector104(void) __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 50 */ void Vector108(void) __attribute__((weak, alias("_unhandled_irq")));
/* IRQ 51 */ void Vector10C(void) __attribute__((weak, alias("_unhandled_irq")));

/*===========================================================================*/
/* Software vector table.                                                    */
/*===========================================================================*/

/**
 * @brief   External interrupt vector table.
 * @details Indexed by IRQ number (0-51). Each entry points to a VectorXX
 *          handler function. HAL drivers provide strong overrides via
 *          OSAL_IRQ_HANDLER(VectorXX).
 */
void (* const _ext_vectors[RISCV_NUM_INTERRUPTS])(void) = {
  Vector40,  Vector44,  Vector48,  Vector4C,   /*  0- 3 */
  Vector50,  Vector54,  Vector58,  Vector5C,   /*  4- 7 */
  Vector60,  Vector64,  Vector68,  Vector6C,   /*  8-11 */
  Vector70,  Vector74,  Vector78,  Vector7C,   /* 12-15 */
  Vector80,  Vector84,  Vector88,  Vector8C,   /* 16-19 */
  Vector90,  Vector94,  Vector98,  Vector9C,   /* 20-23 */
  VectorA0,  VectorA4,  VectorA8,  VectorAC,   /* 24-27 */
  VectorB0,  VectorB4,  VectorB8,  VectorBC,   /* 28-31 */
  VectorC0,  VectorC4,  VectorC8,  VectorCC,   /* 32-35 */
  VectorD0,  VectorD4,  VectorD8,  VectorDC,   /* 36-39 */
  VectorE0,  VectorE4,  VectorE8,  VectorEC,   /* 40-43 */
  VectorF0,  VectorF4,  VectorF8,  VectorFC,   /* 44-47 */
  Vector100, Vector104, Vector108, Vector10C,   /* 48-51 */
};

/*===========================================================================*/
/* External interrupt dispatcher.                                            */
/*===========================================================================*/

/**
 * @brief   External interrupt dispatcher for Xh3irq.
 * @details Called from vectors_hazard3.S when mcause indicates an external
 *          interrupt (mcause == 11 | INTERRUPT_BIT). Dispatches to the
 *          corresponding VectorXX handler via the software vector table.
 *
 * @note    The initial MEINEXT value is passed from the assembly handler
 *          via a0 to avoid a redundant read. Reading MEINEXT acknowledges
 *          the reported IRQ (clears force bits), so re-reading would lose
 *          it. After dispatching, MEINEXT is re-read to check for
 *          additional pending interrupts.
 *
 * @param[in] meinext   Initial MEINEXT value from the assembly handler
 *
 * @note    This function overrides the weak _external_interrupt_handler
 *          defined in vectors_hazard3.S.
 */
void _external_interrupt_handler(uint32_t meinext) {

  while (1) {
    /* Bit 31 set means no more pending interrupts */
    if (meinext & MEINEXT_NOIRQ)
      break;

    /* IRQ number is in bits [10:2] */
    uint32_t irq = (meinext >> 2) & 0x1FFU;

    if (irq < RISCV_NUM_INTERRUPTS)
      _ext_vectors[irq]();

    /* Check for more pending interrupts */
    meinext = hazard3_irq_get_next();
  }
}

/** @} */
