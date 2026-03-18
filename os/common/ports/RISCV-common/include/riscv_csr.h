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
 * @file    RISCV-common/include/riscv_csr.h
 * @brief   Standard RISC-V CSR definitions.
 * @details Defines CSR addresses and bit fields from the RISC-V privileged
 *          specification. These are identical across all RISC-V cores.
 *
 * @addtogroup RISCV_COMMON_CSR
 * @{
 */

#ifndef RISCV_CSR_H
#define RISCV_CSR_H

/*===========================================================================*/
/* Standard RISC-V CSR addresses (privileged specification).                 */
/*===========================================================================*/

/**
 * @name    Machine-level CSR addresses
 * @{
 */
#define CSR_MSTATUS                 0x300   /**< Machine status             */
#define CSR_MISA                    0x301   /**< Machine ISA                */
#define CSR_MIE                     0x304   /**< Machine interrupt enable   */
#define CSR_MTVEC                   0x305   /**< Machine trap vector        */
#define CSR_MSCRATCH                0x340   /**< Machine scratch            */
#define CSR_MEPC                    0x341   /**< Machine exception PC       */
#define CSR_MCAUSE                  0x342   /**< Machine trap cause         */
#define CSR_MTVAL                   0x343   /**< Machine trap value         */
#define CSR_MIP                     0x344   /**< Machine interrupt pending  */
/** @} */

/*===========================================================================*/
/* MSTATUS bit definitions.                                                  */
/*===========================================================================*/

/**
 * @name    MSTATUS register fields
 * @{
 */
#define MSTATUS_MIE                 (1U << 3)   /**< Machine Interrupt Enable       */
#define MSTATUS_MPIE                (1U << 7)   /**< Machine Prior Interrupt Enable */
#define MSTATUS_MPP_MASK            (3U << 11)  /**< Machine Prior Privilege mask   */
#define MSTATUS_MPP_M               (3U << 11)  /**< M-mode                         */
/** @} */

/*===========================================================================*/
/* MIE/MIP bit definitions.                                                  */
/*===========================================================================*/

/**
 * @name    Machine interrupt enable/pending fields
 * @{
 */
#define MIE_MSIE                    (1U << 3)   /**< Machine Software Interrupt */
#define MIE_MTIE                    (1U << 7)   /**< Machine Timer Interrupt    */
#define MIE_MEIE                    (1U << 11)  /**< Machine External Interrupt */
/** @} */

/*===========================================================================*/
/* MCAUSE values.                                                            */
/*===========================================================================*/

/**
 * @name    Machine cause register values
 * @{
 */
#define MCAUSE_INTERRUPT            (1UL << (__riscv_xlen - 1))  /**< Interrupt flag in mcause */
#define MCAUSE_M_SOFT_INT           3           /**< Machine software interrupt */
#define MCAUSE_M_TIMER_INT          7           /**< Machine timer interrupt    */
#define MCAUSE_M_EXT_INT            11          /**< Machine external interrupt */
/** @} */

/*===========================================================================*/
/* PMP CSR addresses.                                                        */
/*===========================================================================*/

/**
 * @name    Physical Memory Protection CSR addresses
 * @{
 */
#define CSR_PMPCFG0                 0x3A0   /**< PMP config (entries 0-3)   */
#define CSR_PMPCFG1                 0x3A1   /**< PMP config (entries 4-7)   */
#define CSR_PMPCFG2                 0x3A2   /**< PMP config (entries 8-11)  */
#define CSR_PMPCFG3                 0x3A3   /**< PMP config (entries 12-15) */
#define CSR_PMPADDR0                0x3B0   /**< PMP address register 0    */
#define CSR_PMPADDR1                0x3B1   /**< PMP address register 1    */
#define CSR_PMPADDR2                0x3B2   /**< PMP address register 2    */
#define CSR_PMPADDR3                0x3B3   /**< PMP address register 3    */
#define CSR_PMPADDR4                0x3B4   /**< PMP address register 4    */
#define CSR_PMPADDR5                0x3B5   /**< PMP address register 5    */
#define CSR_PMPADDR6                0x3B6   /**< PMP address register 6    */
#define CSR_PMPADDR7                0x3B7   /**< PMP address register 7    */
/** @} */

#endif /* RISCV_CSR_H */

/** @} */
