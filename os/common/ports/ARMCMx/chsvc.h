/*
    ChibiOS - Copyright (C) 2006..20189 Giovanni Di Sirio.

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
 * @file    ARMCMx/chsvc.h
 * @brief   ARM Cortex-Mx port syscalls macros and structures.
 *
 * @addtogroup ARMCMx_CORE
 * @{
 */

#ifndef CHCSVC_H
#define CHCSVC_H

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

/**
 * @brief   Type of a syscall handler.
 */
typedef uint32_t (*port_syscall_t)(struct port_extctx *ctx);

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*
 * All handlers defaulted to a common function.
 */
#if !defined(PORT_SVC1_HANDLER)
#define PORT_SVC1_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC2_HANDLER)
#define PORT_SVC2_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC3_HANDLER)
#define PORT_SVC3_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC4_HANDLER)
#define PORT_SVC4_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC5_HANDLER)
#define PORT_SVC5_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC6_HANDLER)
#define PORT_SVC6_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC7_HANDLER)
#define PORT_SVC7_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC8_HANDLER)
#define PORT_SVC8_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC9_HANDLER)
#define PORT_SVC9_HANDLER       port_und_handler
#endif
#if !defined(PORT_SVC10_HANDLER)
#define PORT_SVC10_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC11_HANDLER)
#define PORT_SVC11_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC12_HANDLER)
#define PORT_SVC12_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC13_HANDLER)
#define PORT_SVC13_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC14_HANDLER)
#define PORT_SVC14_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC15_HANDLER)
#define PORT_SVC15_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC16_HANDLER)
#define PORT_SVC16_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC17_HANDLER)
#define PORT_SVC17_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC18_HANDLER)
#define PORT_SVC18_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC19_HANDLER)
#define PORT_SVC19_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC20_HANDLER)
#define PORT_SVC20_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC21_HANDLER)
#define PORT_SVC21_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC22_HANDLER)
#define PORT_SVC22_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC23_HANDLER)
#define PORT_SVC23_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC24_HANDLER)
#define PORT_SVC24_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC25_HANDLER)
#define PORT_SVC25_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC26_HANDLER)
#define PORT_SVC26_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC27_HANDLER)
#define PORT_SVC27_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC28_HANDLER)
#define PORT_SVC28_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC29_HANDLER)
#define PORT_SVC29_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC30_HANDLER)
#define PORT_SVC30_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC31_HANDLER)
#define PORT_SVC31_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC32_HANDLER)
#define PORT_SVC32_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC33_HANDLER)
#define PORT_SVC33_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC34_HANDLER)
#define PORT_SVC34_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC35_HANDLER)
#define PORT_SVC35_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC36_HANDLER)
#define PORT_SVC36_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC37_HANDLER)
#define PORT_SVC37_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC38_HANDLER)
#define PORT_SVC38_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC39_HANDLER)
#define PORT_SVC39_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC40_HANDLER)
#define PORT_SVC40_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC41_HANDLER)
#define PORT_SVC41_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC42_HANDLER)
#define PORT_SVC42_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC43_HANDLER)
#define PORT_SVC43_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC44_HANDLER)
#define PORT_SVC44_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC45_HANDLER)
#define PORT_SVC45_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC46_HANDLER)
#define PORT_SVC46_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC47_HANDLER)
#define PORT_SVC47_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC48_HANDLER)
#define PORT_SVC48_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC49_HANDLER)
#define PORT_SVC49_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC50_HANDLER)
#define PORT_SVC50_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC51_HANDLER)
#define PORT_SVC51_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC52_HANDLER)
#define PORT_SVC52_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC53_HANDLER)
#define PORT_SVC53_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC54_HANDLER)
#define PORT_SVC54_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC55_HANDLER)
#define PORT_SVC55_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC56_HANDLER)
#define PORT_SVC56_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC57_HANDLER)
#define PORT_SVC57_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC58_HANDLER)
#define PORT_SVC58_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC59_HANDLER)
#define PORT_SVC59_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC60_HANDLER)
#define PORT_SVC60_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC61_HANDLER)
#define PORT_SVC61_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC62_HANDLER)
#define PORT_SVC62_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC63_HANDLER)
#define PORT_SVC63_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC64_HANDLER)
#define PORT_SVC64_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC65_HANDLER)
#define PORT_SVC65_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC66_HANDLER)
#define PORT_SVC66_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC67_HANDLER)
#define PORT_SVC67_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC68_HANDLER)
#define PORT_SVC68_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC69_HANDLER)
#define PORT_SVC69_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC70_HANDLER)
#define PORT_SVC70_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC71_HANDLER)
#define PORT_SVC71_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC72_HANDLER)
#define PORT_SVC72_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC73_HANDLER)
#define PORT_SVC73_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC74_HANDLER)
#define PORT_SVC74_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC75_HANDLER)
#define PORT_SVC75_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC76_HANDLER)
#define PORT_SVC76_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC77_HANDLER)
#define PORT_SVC77_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC78_HANDLER)
#define PORT_SVC78_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC79_HANDLER)
#define PORT_SVC79_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC80_HANDLER)
#define PORT_SVC80_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC81_HANDLER)
#define PORT_SVC81_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC82_HANDLER)
#define PORT_SVC82_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC83_HANDLER)
#define PORT_SVC83_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC84_HANDLER)
#define PORT_SVC84_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC85_HANDLER)
#define PORT_SVC85_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC86_HANDLER)
#define PORT_SVC86_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC87_HANDLER)
#define PORT_SVC87_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC88_HANDLER)
#define PORT_SVC88_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC89_HANDLER)
#define PORT_SVC89_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC90_HANDLER)
#define PORT_SVC90_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC91_HANDLER)
#define PORT_SVC91_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC92_HANDLER)
#define PORT_SVC92_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC93_HANDLER)
#define PORT_SVC93_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC94_HANDLER)
#define PORT_SVC94_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC95_HANDLER)
#define PORT_SVC95_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC96_HANDLER)
#define PORT_SVC96_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC97_HANDLER)
#define PORT_SVC97_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC98_HANDLER)
#define PORT_SVC98_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC99_HANDLER)
#define PORT_SVC99_HANDLER      port_und_handler
#endif
#if !defined(PORT_SVC100_HANDLER)
#define PORT_SVC100_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC101_HANDLER)
#define PORT_SVC101_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC102_HANDLER)
#define PORT_SVC102_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC103_HANDLER)
#define PORT_SVC103_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC104_HANDLER)
#define PORT_SVC104_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC105_HANDLER)
#define PORT_SVC105_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC106_HANDLER)
#define PORT_SVC106_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC107_HANDLER)
#define PORT_SVC107_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC108_HANDLER)
#define PORT_SVC108_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC109_HANDLER)
#define PORT_SVC109_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC110_HANDLER)
#define PORT_SVC110_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC111_HANDLER)
#define PORT_SVC111_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC112_HANDLER)
#define PORT_SVC112_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC113_HANDLER)
#define PORT_SVC113_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC114_HANDLER)
#define PORT_SVC114_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC115_HANDLER)
#define PORT_SVC115_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC116_HANDLER)
#define PORT_SVC116_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC117_HANDLER)
#define PORT_SVC117_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC118_HANDLER)
#define PORT_SVC118_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC119_HANDLER)
#define PORT_SVC119_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC120_HANDLER)
#define PORT_SVC120_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC121_HANDLER)
#define PORT_SVC121_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC122_HANDLER)
#define PORT_SVC122_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC123_HANDLER)
#define PORT_SVC123_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC124_HANDLER)
#define PORT_SVC124_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC125_HANDLER)
#define PORT_SVC125_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC126_HANDLER)
#define PORT_SVC126_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC127_HANDLER)
#define PORT_SVC127_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC128_HANDLER)
#define PORT_SVC128_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC129_HANDLER)
#define PORT_SVC129_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC130_HANDLER)
#define PORT_SVC130_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC131_HANDLER)
#define PORT_SVC131_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC132_HANDLER)
#define PORT_SVC132_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC133_HANDLER)
#define PORT_SVC133_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC134_HANDLER)
#define PORT_SVC134_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC135_HANDLER)
#define PORT_SVC135_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC136_HANDLER)
#define PORT_SVC136_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC137_HANDLER)
#define PORT_SVC137_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC138_HANDLER)
#define PORT_SVC138_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC139_HANDLER)
#define PORT_SVC139_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC140_HANDLER)
#define PORT_SVC140_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC141_HANDLER)
#define PORT_SVC141_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC142_HANDLER)
#define PORT_SVC142_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC143_HANDLER)
#define PORT_SVC143_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC144_HANDLER)
#define PORT_SVC144_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC145_HANDLER)
#define PORT_SVC145_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC146_HANDLER)
#define PORT_SVC146_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC147_HANDLER)
#define PORT_SVC147_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC148_HANDLER)
#define PORT_SVC148_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC149_HANDLER)
#define PORT_SVC149_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC150_HANDLER)
#define PORT_SVC150_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC151_HANDLER)
#define PORT_SVC151_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC152_HANDLER)
#define PORT_SVC152_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC153_HANDLER)
#define PORT_SVC153_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC154_HANDLER)
#define PORT_SVC154_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC155_HANDLER)
#define PORT_SVC155_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC156_HANDLER)
#define PORT_SVC156_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC157_HANDLER)
#define PORT_SVC157_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC158_HANDLER)
#define PORT_SVC158_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC159_HANDLER)
#define PORT_SVC159_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC160_HANDLER)
#define PORT_SVC160_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC161_HANDLER)
#define PORT_SVC161_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC162_HANDLER)
#define PORT_SVC162_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC163_HANDLER)
#define PORT_SVC163_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC164_HANDLER)
#define PORT_SVC164_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC165_HANDLER)
#define PORT_SVC165_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC166_HANDLER)
#define PORT_SVC166_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC167_HANDLER)
#define PORT_SVC167_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC168_HANDLER)
#define PORT_SVC168_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC169_HANDLER)
#define PORT_SVC169_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC170_HANDLER)
#define PORT_SVC170_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC171_HANDLER)
#define PORT_SVC171_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC172_HANDLER)
#define PORT_SVC172_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC173_HANDLER)
#define PORT_SVC173_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC174_HANDLER)
#define PORT_SVC174_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC175_HANDLER)
#define PORT_SVC175_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC176_HANDLER)
#define PORT_SVC176_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC177_HANDLER)
#define PORT_SVC177_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC178_HANDLER)
#define PORT_SVC178_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC179_HANDLER)
#define PORT_SVC179_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC180_HANDLER)
#define PORT_SVC180_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC181_HANDLER)
#define PORT_SVC181_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC182_HANDLER)
#define PORT_SVC182_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC183_HANDLER)
#define PORT_SVC183_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC184_HANDLER)
#define PORT_SVC184_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC185_HANDLER)
#define PORT_SVC185_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC186_HANDLER)
#define PORT_SVC186_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC187_HANDLER)
#define PORT_SVC187_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC188_HANDLER)
#define PORT_SVC188_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC189_HANDLER)
#define PORT_SVC189_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC190_HANDLER)
#define PORT_SVC190_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC191_HANDLER)
#define PORT_SVC191_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC192_HANDLER)
#define PORT_SVC192_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC193_HANDLER)
#define PORT_SVC193_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC194_HANDLER)
#define PORT_SVC194_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC195_HANDLER)
#define PORT_SVC195_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC196_HANDLER)
#define PORT_SVC196_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC197_HANDLER)
#define PORT_SVC197_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC198_HANDLER)
#define PORT_SVC198_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC199_HANDLER)
#define PORT_SVC199_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC200_HANDLER)
#define PORT_SVC200_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC201_HANDLER)
#define PORT_SVC201_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC202_HANDLER)
#define PORT_SVC202_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC203_HANDLER)
#define PORT_SVC203_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC204_HANDLER)
#define PORT_SVC204_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC205_HANDLER)
#define PORT_SVC205_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC206_HANDLER)
#define PORT_SVC206_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC207_HANDLER)
#define PORT_SVC207_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC208_HANDLER)
#define PORT_SVC208_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC209_HANDLER)
#define PORT_SVC209_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC210_HANDLER)
#define PORT_SVC210_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC211_HANDLER)
#define PORT_SVC211_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC212_HANDLER)
#define PORT_SVC212_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC213_HANDLER)
#define PORT_SVC213_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC214_HANDLER)
#define PORT_SVC214_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC215_HANDLER)
#define PORT_SVC215_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC216_HANDLER)
#define PORT_SVC216_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC217_HANDLER)
#define PORT_SVC217_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC218_HANDLER)
#define PORT_SVC218_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC219_HANDLER)
#define PORT_SVC219_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC220_HANDLER)
#define PORT_SVC220_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC221_HANDLER)
#define PORT_SVC221_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC222_HANDLER)
#define PORT_SVC222_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC223_HANDLER)
#define PORT_SVC223_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC224_HANDLER)
#define PORT_SVC224_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC225_HANDLER)
#define PORT_SVC225_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC226_HANDLER)
#define PORT_SVC226_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC227_HANDLER)
#define PORT_SVC227_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC228_HANDLER)
#define PORT_SVC228_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC229_HANDLER)
#define PORT_SVC229_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC230_HANDLER)
#define PORT_SVC230_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC231_HANDLER)
#define PORT_SVC231_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC232_HANDLER)
#define PORT_SVC232_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC233_HANDLER)
#define PORT_SVC233_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC234_HANDLER)
#define PORT_SVC234_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC235_HANDLER)
#define PORT_SVC235_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC236_HANDLER)
#define PORT_SVC236_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC237_HANDLER)
#define PORT_SVC237_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC238_HANDLER)
#define PORT_SVC238_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC239_HANDLER)
#define PORT_SVC239_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC240_HANDLER)
#define PORT_SVC240_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC241_HANDLER)
#define PORT_SVC241_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC242_HANDLER)
#define PORT_SVC242_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC243_HANDLER)
#define PORT_SVC243_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC244_HANDLER)
#define PORT_SVC244_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC245_HANDLER)
#define PORT_SVC245_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC246_HANDLER)
#define PORT_SVC246_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC247_HANDLER)
#define PORT_SVC247_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC248_HANDLER)
#define PORT_SVC248_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC249_HANDLER)
#define PORT_SVC249_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC250_HANDLER)
#define PORT_SVC250_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC251_HANDLER)
#define PORT_SVC251_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC252_HANDLER)
#define PORT_SVC252_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC253_HANDLER)
#define PORT_SVC253_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC254_HANDLER)
#define PORT_SVC254_HANDLER     port_und_handler
#endif
#if !defined(PORT_SVC255_HANDLER)
#define PORT_SVC255_HANDLER     port_und_handler
#endif

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void port_syscall(struct port_extctx *ctxp, uint32_t n);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* CHCSVC_H */

/** @} */
