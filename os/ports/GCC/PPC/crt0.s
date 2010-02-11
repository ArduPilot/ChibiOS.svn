/*
    ChibiOS/RT - Copyright (C) 2006-2007 Giovanni Di Sirio.

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
 * @file    PPC/crt0.s
 * @brief   Generic PowerPC startup file for ChibiOS/RT.
 *
 * @addtogroup PPC_CORE
 * @{
 */
/** @cond never */

        /*
         * BAM info, SWT off, WTE off, VLE off.
         */
        .section    .bam
        .long       0x005A0000
        .long       boot_address

        .section    .text
        .align		2
        .globl      boot_address
boot_address:
        /*
         * Stack setup.
         */
        lis         %r1, __ram_end__@ha
        ori         %r1, %r1, __ram_end__@l
        li          %r0, 0
        stwu        %r0, -8(%r1)
        /*
        * Early initialization.
        */
        bl          hwinit0
        /*
         * BSS clearing.
         */
        lis         %r4, __bss_start__@ha
        ori         %r4, %r4, __bss_start__@l
        lis         %r5, __bss_end__@ha
        ori         %r5, %r5, __bss_end__@l
        li          %r7, 0
.bssloop:
        cmpl        cr0, %r4, %r5
        bge         cr0, .bssend
        stw         %r7, 0(%r4)
        addi        %r4, %r4, 4
        b           .bssloop
.bssend:
        /*
         * DATA initialization.
         */
        lis         %r4, __romdata_start__@ha
        ori         %r4, %r4, __romdata_start__@l
        lis         %r5, __data_start__@ha
        ori         %r5, %r5, __data_start__@l
        lis         %r6, __data_end__@ha
        ori         %r6, %r6, __data_end__@l
.dataloop:
        cmpl        cr0, %r5, %r6
        bge         cr0, .dataend
        lwz         %r7, 0(%r4)
        addi        %r4, %r4, 4
        stw         %r7, 0(%r5)
        addi        %r5, %r5, 4
        b           .dataloop
.dataend:
        /*
         * Small sections registers initialization.
         */
        lis         %r2, __sdata2_start__@ha
        ori         %r2, %r2, __sdata2_start__@l
        lis         %r13, __sdata_start__@ha
        ori         %r13, %r13, __sdata_start__@l
        /*
         * IVPR initialization.
         */
        lis         %r4, __ivpr_table__@ha
        mtivpr      %r4    
        /*
         * Late initialization.
         */
        bl          hwinit1
        li          %r3, 0
        li          %r4, 0
        bl          main
        b           main_exit

        /*
         * Default main exit code, infinite loop.
         */
        .weak       main_exit
        .globl      main_exit
main_exit:
forever:
        b           forever

        /*
         * Default initialization code, none.
         */
        .weak       hwinit0
        .globl      hwinit0
hwinit0:
        .weak       hwinit1
        .globl      hwinit1
hwinit1:
        blr

/** @endcond */
/** @} */
