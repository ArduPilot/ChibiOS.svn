/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio

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

/**
 * @file    RP2350/rvparams.h
 * @brief   RISC-V Hazard3 parameters for the RP2350.
 *
 * @defgroup RISCV_HAZARD3_RP2350 RP2350 RISC-V Hazard3 Specific Parameters
 * @ingroup RISCV_HAZARD3_SPECIFIC
 * @details This file contains the RISC-V Hazard3 specific parameters for the
 *          RP2350 platform.
 * @{
 */

#ifndef RVPARAMS_H
#define RVPARAMS_H

/* Standard RISC-V CSR definitions shared across all RISC-V ports.*/
#include "riscv_csr.h"

/**
 * @brief   RISC-V architecture identifier.
 * @note    Hazard3 implements RV32IMAC.
 */
#define RISCV_ARCH                  rv32imac

/**
 * @brief   Hazard3 core identifier.
 */
#define RISCV_HAZARD3               1

/**
 * @brief   Number of external interrupt sources.
 * @note    RP2350 has 52 external interrupts (IRQ 0-51).
 */
#define RISCV_NUM_INTERRUPTS        52

/**
 * @brief   SIO base address for MTIME registers.
 * @note    Hazard3 uses memory-mapped MTIME/MTIMECMP in SIO, not CSRs.
 */
#define RISCV_SIO_BASE              0xD0000000U

/**
 * @brief   MTIME_CTRL register offset from SIO base.
 */
#define RISCV_SIO_MTIME_CTRL_OFFSET 0x1A4U

/**
 * @brief   MTIME register offset from SIO base (low 32 bits).
 */
#define RISCV_SIO_MTIME_OFFSET      0x1B0U

/**
 * @brief   MTIMEH register offset from SIO base (high 32 bits).
 */
#define RISCV_SIO_MTIMEH_OFFSET     0x1B4U

/**
 * @brief   MTIMECMP register offset from SIO base (low 32 bits).
 */
#define RISCV_SIO_MTIMECMP_OFFSET   0x1B8U

/**
 * @brief   MTIMECMPH register offset from SIO base (high 32 bits).
 */
#define RISCV_SIO_MTIMECMPH_OFFSET  0x1BCU

/**
 * @brief   MTIME_CTRL bit definitions.
 */
#define MTIME_CTRL_EN               (1U << 0)   /* Timer enable */
#define MTIME_CTRL_FULLSPEED        (1U << 1)   /* Run at CLK_SYS instead of 1MHz */
#define MTIME_CTRL_DBGPAUSE_CORE0   (1U << 2)   /* Pause when core0 halted */
#define MTIME_CTRL_DBGPAUSE_CORE1   (1U << 3)   /* Pause when core1 halted */

/**
 * @brief   System timer frequency.
 * @note    RP2350 MTIME runs at 1 MHz by default (when FULLSPEED=0).
 */
#define RISCV_MTIME_FREQUENCY       1000000U

/**
 * @brief   Hazard3 uses custom Xh3irq extension for interrupts.
 */
#define RISCV_HAS_XH3IRQ            1

/**
 * @brief   Xh3irq custom CSR addresses.
 * @note    These are accessed via .word directives since GCC doesn't know them.
 */
#define CSR_MEIEA                   0xBE0   /* External interrupt enable array */
#define CSR_MEIPA                   0xBE1   /* External interrupt pending array */
#define CSR_MEIFA                   0xBE2   /* External interrupt force array */
#define CSR_MEIPRA                  0xBE3   /* External interrupt priority array */
#define CSR_MEINEXT                 0xBE4   /* Next external interrupt to service */
#define CSR_MEICONTEXT              0xBE5   /* External interrupt context save */

/**
 * @brief   Hazard3 has PMP support.
 */
#define RISCV_PMP_PRESENT           1

/**
 * @brief   Hazard3/RP2350 custom CSR: PMPCFGM0.
 * @details Enables PMP enforcement for M-mode without using the L (lock) bit.
 *          Each bit corresponds to a PMP entry; setting bit N enforces entry N
 *          on M-mode accesses.
 */
#define CSR_PMPCFGM0                0xBD0

/**
 * @name    PMP configuration field constants (RP2350-E6 erratum corrected).
 * @details RP2350-E6 erratum: PMP R/W/X permission bits are reversed in
 *          hardware. Standard encoding: R=bit0, W=bit1, X=bit2.
 *          RP2350 hardware: X=bit0, W=bit1, R=bit2.
 *          These constants use the hardware (erratum) encoding.
 * @{
 */
#define PMP_CFG_X                   (1U << 0)   /**< Execute permission     */
#define PMP_CFG_W                   (1U << 1)   /**< Write permission       */
#define PMP_CFG_R                   (1U << 2)   /**< Read permission        */
#define PMP_CFG_A_OFF               (0U << 3)   /**< Addr matching: OFF     */
#define PMP_CFG_A_TOR               (1U << 3)   /**< Addr matching: TOR     */
#define PMP_CFG_A_NA4               (2U << 3)   /**< Addr matching: NA4     */
#define PMP_CFG_A_NAPOT             (3U << 3)   /**< Addr matching: NAPOT   */
#define PMP_CFG_L                   (1U << 7)   /**< Lock                   */
/** @} */

/* Standard RISC-V CSR addresses, MSTATUS/MIE/MCAUSE bit definitions are
   provided by riscv_csr.h (included above).*/

/* If the device type is not externally defined, for example from the Makefile,
   then a file named board.h is included. This file must contain a device
   definition compatible with the vendor include file.*/
#if !defined(RP2350)
#include "board.h"
#endif

/* The following code is not processed when the file is included from an
   asm module.*/
#if !defined(_FROM_ASM_)

/* Including the device header.*/
#include "rp2350.h"

#endif /* !defined(_FROM_ASM_) */

#endif /* RVPARAMS_H */

/** @} */
