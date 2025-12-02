*****************************************************************************
** ChibiOS/RT X-Shell Demo for STM32.                                      **
*****************************************************************************

** TARGET **

The demo supports multiple STM32 target boards:
- STM32 Nucleo144-H563ZI board (stm32h563zi_nucleo144.make)
- STM32 Nucleo144-U575ZI board (stm32u575zi_nucleo144.make)
- STM32 Nucleo64-C071RB board (stm32c071rb_nucleo64.make)
- STM32 Nucleo64-G474RE board (stm32g474re_nucleo64.make)
- STM32 Nucleo64-U083RC board (stm32u083rc_nucleo64.make)
- STM32 Nucleo64-U385RG board (stm32u385rg_nucleo64.make)

** The Demo **

This demo demonstrates the X-Shell (extended shell) functionality on various
STM32 boards. X-Shell provides an interactive command-line interface with
features like command history, editing, and various built-in commands.

The shell is accessible via the serial port (typically mapped on USB virtual
COM port or STLink v2-1 Virtual COM Port, depending on the board).

Available shell commands include:
- halt: Halts the system
- write: Write test command
- clock: Clock-related commands
- test: Run system tests (RT and OSLIB test suites)
- systime: Display system time
- mem: Display memory information
- threads: List running threads
- And other standard X-Shell commands

** Build Procedure **

The demo can be built for different target boards by using the corresponding
makefile in the make/ directory:

  make -f make/stm32h563zi_nucleo144.make
  make -f make/stm32u575zi_nucleo144.make
  make -f make/stm32g474re_nucleo64.make
  make -f make/stm32c071rb_nucleo64.make
  make -f make/stm32u083rc_nucleo64.make
  make -f make/stm32u385rg_nucleo64.make

Alternatively, run 'make' at the root to build all targets.

The demo has been tested using the free GCC ARM embedded toolchain.

** Notes **

Some files used by the demo are not part of ChibiOS/RT but are copyright of
ST Microelectronics and are licensed under a different license.
Also note that not all the files present in the ST library are distributed
with ChibiOS/RT, you can find the whole library on the ST web site:

                             http://www.st.com
