/*
    ChibiOS - Copyright (C) 2006..2019 Giovanni Di Sirio.

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
 * @file    ARMCMx/chsvc.c
 * @brief   ARM Cortex-Mx port syscalls code.
 *
 * @addtogroup ARMCMx_CORE
 * @{
 */

#include "ch.h"

#if (PORT_USE_SYSCALL == TRUE) || defined(__DOXYGEN___)

#include "chsvc.h"

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
/* Module exported functions.                                                */
/*===========================================================================*/

__attribute__((weak))
uint32_t port_und_handler(struct port_extctx *ctxp) {

  (void)ctxp;

  return 0xFFFFFFFFU;
}

__attribute__((weak))
void port_syscall(struct port_extctx *ctxp, uint32_t n) {

  static const port_syscall_t syscalls[256] = {
    port_und_handler,    PORT_SVC1_HANDLER,   PORT_SVC2_HANDLER,   PORT_SVC3_HANDLER,
    PORT_SVC4_HANDLER,   PORT_SVC5_HANDLER,   PORT_SVC6_HANDLER,   PORT_SVC7_HANDLER,
    PORT_SVC8_HANDLER,   PORT_SVC9_HANDLER,   PORT_SVC10_HANDLER,  PORT_SVC11_HANDLER,
    PORT_SVC12_HANDLER,  PORT_SVC13_HANDLER,  PORT_SVC14_HANDLER,  PORT_SVC15_HANDLER,
    PORT_SVC16_HANDLER,  PORT_SVC17_HANDLER,  PORT_SVC18_HANDLER,  PORT_SVC19_HANDLER,
    PORT_SVC20_HANDLER,  PORT_SVC21_HANDLER,  PORT_SVC22_HANDLER,  PORT_SVC23_HANDLER,
    PORT_SVC24_HANDLER,  PORT_SVC25_HANDLER,  PORT_SVC26_HANDLER,  PORT_SVC27_HANDLER,
    PORT_SVC28_HANDLER,  PORT_SVC29_HANDLER,  PORT_SVC30_HANDLER,  PORT_SVC31_HANDLER,
    PORT_SVC32_HANDLER,  PORT_SVC33_HANDLER,  PORT_SVC34_HANDLER,  PORT_SVC35_HANDLER,
    PORT_SVC36_HANDLER,  PORT_SVC37_HANDLER,  PORT_SVC38_HANDLER,  PORT_SVC39_HANDLER,
    PORT_SVC40_HANDLER,  PORT_SVC41_HANDLER,  PORT_SVC42_HANDLER,  PORT_SVC43_HANDLER,
    PORT_SVC44_HANDLER,  PORT_SVC45_HANDLER,  PORT_SVC46_HANDLER,  PORT_SVC47_HANDLER,
    PORT_SVC48_HANDLER,  PORT_SVC49_HANDLER,  PORT_SVC50_HANDLER,  PORT_SVC51_HANDLER,
    PORT_SVC52_HANDLER,  PORT_SVC53_HANDLER,  PORT_SVC54_HANDLER,  PORT_SVC55_HANDLER,
    PORT_SVC56_HANDLER,  PORT_SVC57_HANDLER,  PORT_SVC58_HANDLER,  PORT_SVC59_HANDLER,
    PORT_SVC60_HANDLER,  PORT_SVC61_HANDLER,  PORT_SVC62_HANDLER,  PORT_SVC63_HANDLER,
    PORT_SVC64_HANDLER,  PORT_SVC65_HANDLER,  PORT_SVC66_HANDLER,  PORT_SVC67_HANDLER,
    PORT_SVC68_HANDLER,  PORT_SVC69_HANDLER,  PORT_SVC70_HANDLER,  PORT_SVC71_HANDLER,
    PORT_SVC72_HANDLER,  PORT_SVC73_HANDLER,  PORT_SVC74_HANDLER,  PORT_SVC75_HANDLER,
    PORT_SVC76_HANDLER,  PORT_SVC77_HANDLER,  PORT_SVC78_HANDLER,  PORT_SVC79_HANDLER,
    PORT_SVC80_HANDLER,  PORT_SVC81_HANDLER,  PORT_SVC82_HANDLER,  PORT_SVC83_HANDLER,
    PORT_SVC84_HANDLER,  PORT_SVC85_HANDLER,  PORT_SVC86_HANDLER,  PORT_SVC87_HANDLER,
    PORT_SVC88_HANDLER,  PORT_SVC89_HANDLER,  PORT_SVC90_HANDLER,  PORT_SVC91_HANDLER,
    PORT_SVC92_HANDLER,  PORT_SVC93_HANDLER,  PORT_SVC94_HANDLER,  PORT_SVC95_HANDLER,
    PORT_SVC96_HANDLER,  PORT_SVC97_HANDLER,  PORT_SVC98_HANDLER,  PORT_SVC99_HANDLER,
    PORT_SVC100_HANDLER, PORT_SVC101_HANDLER, PORT_SVC102_HANDLER, PORT_SVC103_HANDLER,
    PORT_SVC104_HANDLER, PORT_SVC105_HANDLER, PORT_SVC106_HANDLER, PORT_SVC107_HANDLER,
    PORT_SVC108_HANDLER, PORT_SVC109_HANDLER, PORT_SVC110_HANDLER, PORT_SVC111_HANDLER,
    PORT_SVC112_HANDLER, PORT_SVC113_HANDLER, PORT_SVC114_HANDLER, PORT_SVC115_HANDLER,
    PORT_SVC116_HANDLER, PORT_SVC117_HANDLER, PORT_SVC118_HANDLER, PORT_SVC119_HANDLER,
    PORT_SVC120_HANDLER, PORT_SVC121_HANDLER, PORT_SVC122_HANDLER, PORT_SVC123_HANDLER,
    PORT_SVC124_HANDLER, PORT_SVC125_HANDLER, PORT_SVC126_HANDLER, PORT_SVC127_HANDLER,
    PORT_SVC128_HANDLER, PORT_SVC129_HANDLER, PORT_SVC130_HANDLER, PORT_SVC131_HANDLER,
    PORT_SVC132_HANDLER, PORT_SVC133_HANDLER, PORT_SVC134_HANDLER, PORT_SVC135_HANDLER,
    PORT_SVC136_HANDLER, PORT_SVC137_HANDLER, PORT_SVC138_HANDLER, PORT_SVC139_HANDLER,
    PORT_SVC140_HANDLER, PORT_SVC141_HANDLER, PORT_SVC142_HANDLER, PORT_SVC143_HANDLER,
    PORT_SVC144_HANDLER, PORT_SVC145_HANDLER, PORT_SVC146_HANDLER, PORT_SVC147_HANDLER,
    PORT_SVC148_HANDLER, PORT_SVC149_HANDLER, PORT_SVC150_HANDLER, PORT_SVC151_HANDLER,
    PORT_SVC152_HANDLER, PORT_SVC153_HANDLER, PORT_SVC154_HANDLER, PORT_SVC155_HANDLER,
    PORT_SVC156_HANDLER, PORT_SVC157_HANDLER, PORT_SVC158_HANDLER, PORT_SVC159_HANDLER,
    PORT_SVC160_HANDLER, PORT_SVC161_HANDLER, PORT_SVC162_HANDLER, PORT_SVC163_HANDLER,
    PORT_SVC164_HANDLER, PORT_SVC165_HANDLER, PORT_SVC166_HANDLER, PORT_SVC167_HANDLER,
    PORT_SVC168_HANDLER, PORT_SVC169_HANDLER, PORT_SVC170_HANDLER, PORT_SVC171_HANDLER,
    PORT_SVC172_HANDLER, PORT_SVC173_HANDLER, PORT_SVC174_HANDLER, PORT_SVC175_HANDLER,
    PORT_SVC176_HANDLER, PORT_SVC177_HANDLER, PORT_SVC178_HANDLER, PORT_SVC179_HANDLER,
    PORT_SVC180_HANDLER, PORT_SVC181_HANDLER, PORT_SVC182_HANDLER, PORT_SVC183_HANDLER,
    PORT_SVC184_HANDLER, PORT_SVC185_HANDLER, PORT_SVC186_HANDLER, PORT_SVC187_HANDLER,
    PORT_SVC188_HANDLER, PORT_SVC189_HANDLER, PORT_SVC190_HANDLER, PORT_SVC191_HANDLER,
    PORT_SVC192_HANDLER, PORT_SVC193_HANDLER, PORT_SVC194_HANDLER, PORT_SVC195_HANDLER,
    PORT_SVC196_HANDLER, PORT_SVC197_HANDLER, PORT_SVC198_HANDLER, PORT_SVC199_HANDLER,
    PORT_SVC200_HANDLER, PORT_SVC201_HANDLER, PORT_SVC202_HANDLER, PORT_SVC203_HANDLER,
    PORT_SVC204_HANDLER, PORT_SVC205_HANDLER, PORT_SVC206_HANDLER, PORT_SVC207_HANDLER,
    PORT_SVC208_HANDLER, PORT_SVC209_HANDLER, PORT_SVC210_HANDLER, PORT_SVC211_HANDLER,
    PORT_SVC212_HANDLER, PORT_SVC213_HANDLER, PORT_SVC214_HANDLER, PORT_SVC215_HANDLER,
    PORT_SVC216_HANDLER, PORT_SVC217_HANDLER, PORT_SVC218_HANDLER, PORT_SVC219_HANDLER,
    PORT_SVC220_HANDLER, PORT_SVC221_HANDLER, PORT_SVC222_HANDLER, PORT_SVC223_HANDLER,
    PORT_SVC224_HANDLER, PORT_SVC225_HANDLER, PORT_SVC226_HANDLER, PORT_SVC227_HANDLER,
    PORT_SVC228_HANDLER, PORT_SVC229_HANDLER, PORT_SVC230_HANDLER, PORT_SVC231_HANDLER,
    PORT_SVC232_HANDLER, PORT_SVC233_HANDLER, PORT_SVC234_HANDLER, PORT_SVC235_HANDLER,
    PORT_SVC236_HANDLER, PORT_SVC237_HANDLER, PORT_SVC238_HANDLER, PORT_SVC239_HANDLER,
    PORT_SVC240_HANDLER, PORT_SVC241_HANDLER, PORT_SVC242_HANDLER, PORT_SVC243_HANDLER,
    PORT_SVC244_HANDLER, PORT_SVC245_HANDLER, PORT_SVC246_HANDLER, PORT_SVC247_HANDLER,
    PORT_SVC248_HANDLER, PORT_SVC249_HANDLER, PORT_SVC250_HANDLER, PORT_SVC251_HANDLER,
    PORT_SVC252_HANDLER, PORT_SVC253_HANDLER, PORT_SVC254_HANDLER, PORT_SVC255_HANDLER
  };

  ctxp->r0 = (regarm_t)syscalls[n](ctxp);
}

#endif /* PORT_USE_SYSCALL == TRUE */

/** @} */