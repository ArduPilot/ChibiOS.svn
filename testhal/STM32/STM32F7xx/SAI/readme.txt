*****************************************************************************
** ChibiOS/RT port for ARM-Cortex-M7 STM32F746G.                           **
*****************************************************************************

** TARGET **

The demo runs on an ST STM32F769I-Discovery board.

** The Demo **


** Build Procedure **

The demo has been tested by using the free Codesourcery GCC-based toolchain
and YAGARTO. just modify the TRGT line in the makefile in order to use
different GCC toolchains.

** Notes **

Codec Audio I2C1

I2C1 AUDIO_SDA PB7
I2C1 AUDIO_SCL PD12

Code Audio SAI1

Core 216 MHz
APB1  54 MHz



Some files used by the demo are not part of ChibiOS/RT but are copyright of
ST Microelectronics and are licensed under a different license.
Also note that not all the files present in the ST library are distributed
with ChibiOS/RT, you can find the whole library on the ST web site:

                             http://www.st.com
