################################################
# Make file generated by HEW
#

############################
# Toolchain directory define
# If incorrect, change to the location of the KPIT GNURX [ELF] Toolchain toolchain
TC_INSTALL_DIR = c:\hew\tools\kpit cummins\gnurx-elf\v10.03

#####################################################
#
# Details:
#   Project: ch
#   Configuration: Debug
#   Toolchain: KPIT GNURX [ELF] Toolchain
#
#####################################################

################
# Main Defines

# GNU Library Generator01 phase

CH_DEBUG_LIBRARY_GENERATOR01_EXE=rx-elf-libgen-wrapper.exe
CH_DEBUG_LIBRARY_GENERATOR01_OUTFILESC0="..\ch\Debug\libch.a"

# GNU Compiler02 phase

CH_DEBUG_COMPILER02_EXE=rx-elf-gcc-wrapper.exe
CH_DEBUG_COMPILER02_OUTFILESC2="..\ch\Debug\main.o"
CH_DEBUG_COMPILER02_OUTFILESC5="..\ch\Debug\chcond.o"
CH_DEBUG_COMPILER02_OUTFILESC6="..\ch\Debug\chdebug.o"
CH_DEBUG_COMPILER02_OUTFILESC7="..\ch\Debug\chdynamic.o"
CH_DEBUG_COMPILER02_OUTFILESC8="..\ch\Debug\chevents.o"
CH_DEBUG_COMPILER02_OUTFILESC9="..\ch\Debug\chheap.o"
CH_DEBUG_COMPILER02_OUTFILESC10="..\ch\Debug\chlists.o"
CH_DEBUG_COMPILER02_OUTFILESC11="..\ch\Debug\chmboxes.o"
CH_DEBUG_COMPILER02_OUTFILESC12="..\ch\Debug\chmemcore.o"
CH_DEBUG_COMPILER02_OUTFILESC13="..\ch\Debug\chmempools.o"
CH_DEBUG_COMPILER02_OUTFILESC14="..\ch\Debug\chmsg.o"
CH_DEBUG_COMPILER02_OUTFILESC15="..\ch\Debug\chmtx.o"
CH_DEBUG_COMPILER02_OUTFILESC16="..\ch\Debug\chqueues.o"
CH_DEBUG_COMPILER02_OUTFILESC17="..\ch\Debug\chregistry.o"
CH_DEBUG_COMPILER02_OUTFILESC18="..\ch\Debug\chschd.o"
CH_DEBUG_COMPILER02_OUTFILESC19="..\ch\Debug\chsem.o"
CH_DEBUG_COMPILER02_OUTFILESC20="..\ch\Debug\chsys.o"
CH_DEBUG_COMPILER02_OUTFILESC21="..\ch\Debug\chthreads.o"
CH_DEBUG_COMPILER02_OUTFILESC22="..\ch\Debug\chvt.o"
CH_DEBUG_COMPILER02_OUTFILESC23="..\ch\Debug\chcore.o"

# GNU Assembler03 phase

CH_DEBUG_ASSEMBLER03_EXE=rx-elf-as-wrapper.exe
CH_DEBUG_ASSEMBLER03_OUTFILESC0="..\ch\Debug\crt0.o"

# GNU Linker04 phase

CH_DEBUG_LINKER04_EXE=rx-elf-ld-wrapper.exe
CH_DEBUG_LINKER04_INFILESC0="..\ch\Debug\chcond.o" "..\ch\Debug\chcore.o" "..\ch\Debug\chdebug.o" "..\ch\Debug\chdynamic.o" \
	"..\ch\Debug\chevents.o" "..\ch\Debug\chheap.o" "..\ch\Debug\chlists.o" "..\ch\Debug\chmboxes.o" \
	"..\ch\Debug\chmemcore.o" "..\ch\Debug\chmempools.o" "..\ch\Debug\chmsg.o" "..\ch\Debug\chmtx.o" \
	"..\ch\Debug\chqueues.o" "..\ch\Debug\chregistry.o" "..\ch\Debug\chschd.o" "..\ch\Debug\chsem.o" \
	"..\ch\Debug\chsys.o" "..\ch\Debug\chthreads.o" "..\ch\Debug\chvt.o" "..\ch\Debug\crt0.o" \
	"..\ch\Debug\main.o"
CH_DEBUG_LINKER04_OUTFILESC0="..\ch\Debug\ch.mot" "..\ch\Debug\ch.x"

#######################
# nmake "all" statement

ALL:	CH_DEBUG_LIBRARY_GENERATOR01_ENVC0 \
	$(CH_DEBUG_LIBRARY_GENERATOR01_OUTFILESC0) \
	ch_Debug_Compiler02_EXECUTEC0 \
	ch_Debug_Compiler02_EXECUTEC1 \
	$(CH_DEBUG_COMPILER02_OUTFILESC2) \
	ch_Debug_Compiler02_EXECUTEC3 \
	ch_Debug_Compiler02_EXECUTEC4 \
	$(CH_DEBUG_COMPILER02_OUTFILESC5) \
	$(CH_DEBUG_COMPILER02_OUTFILESC6) \
	$(CH_DEBUG_COMPILER02_OUTFILESC7) \
	$(CH_DEBUG_COMPILER02_OUTFILESC8) \
	$(CH_DEBUG_COMPILER02_OUTFILESC9) \
	$(CH_DEBUG_COMPILER02_OUTFILESC10) \
	$(CH_DEBUG_COMPILER02_OUTFILESC11) \
	$(CH_DEBUG_COMPILER02_OUTFILESC12) \
	$(CH_DEBUG_COMPILER02_OUTFILESC13) \
	$(CH_DEBUG_COMPILER02_OUTFILESC14) \
	$(CH_DEBUG_COMPILER02_OUTFILESC15) \
	$(CH_DEBUG_COMPILER02_OUTFILESC16) \
	$(CH_DEBUG_COMPILER02_OUTFILESC17) \
	$(CH_DEBUG_COMPILER02_OUTFILESC18) \
	$(CH_DEBUG_COMPILER02_OUTFILESC19) \
	$(CH_DEBUG_COMPILER02_OUTFILESC20) \
	$(CH_DEBUG_COMPILER02_OUTFILESC21) \
	$(CH_DEBUG_COMPILER02_OUTFILESC22) \
	$(CH_DEBUG_COMPILER02_OUTFILESC23) \
	$(CH_DEBUG_ASSEMBLER03_OUTFILESC0) \
	$(CH_DEBUG_LINKER04_OUTFILESC0)

####################
# Description blocks

!MESSAGE
!MESSAGE Executing GNU Library Generator01 phase
!MESSAGE

CH_DEBUG_LIBRARY_GENERATOR01_ENVC0 : 
	set TARGET_LIB=$(TC_INSTALL_DIR)\rx-elf\rx-elf\lib
	set MAKE_MODE=unix
	set PATH=$(TC_INSTALL_DIR)\rx-elf\bin;$(TC_INSTALL_DIR)\rx-elf\rx-elf\bin;$(TC_INSTALL_DIR)\rx-elf\libexec\gcc\rx-elf\4.5-GNURX_v10.03
	set TARGET_M2_LIB=$(TC_INSTALL_DIR)\rx-elf\rx-elf\lib\
	set LIB_TARGET_INCLUDE=$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include
	set TARGET_INCLUDE=$(TC_INSTALL_DIR)\rx-elf\rx-elf\include
	set LIB_M2_LIB=$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\
	set INCLUDE=$(TC_INSTALL_DIR)\rx-elf\include

$(CH_DEBUG_LIBRARY_GENERATOR01_OUTFILESC0) : 
	"$(EXEDIR)\$(CH_DEBUG_LIBRARY_GENERATOR01_EXE)" -subcommand=<<
--compiler-options=-mcpu=rx600,-mlittle-endian-data,-mint-register=0,-Os,-fdata-sections,-ffunction-sections,-falign-jumps,-fno-function-cse,-funit-at-a-time
--output="..\ch\Debug\libch.a"
--select-lib=newlib
--header-files=all
<<

!MESSAGE
!MESSAGE Executing GNU Compiler02 phase
!MESSAGE

ch_Debug_Compiler02_EXECUTEC0 : "C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\hardware_setup.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-g
-g3
-o "$(CONFIGDIR)\$(FILELEAF).o"
-O2
"C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\hardware_setup.c"
<<

ch_Debug_Compiler02_EXECUTEC1 : "C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\interrupt_handlers.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-g
-g3
-o "$(CONFIGDIR)\$(FILELEAF).o"
-O2
"C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\interrupt_handlers.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC2) : "C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\main.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\main.o"
"C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\main.c"
<<

ch_Debug_Compiler02_EXECUTEC3 : "C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\reset_program.asm"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-g
-g3
-o "$(CONFIGDIR)\$(FILELEAF).o"
-O2
"C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\reset_program.asm"
<<

ch_Debug_Compiler02_EXECUTEC4 : "C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\vector_table.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-g
-g3
-o "$(CONFIGDIR)\$(FILELEAF).o"
-O2
"C:\rtos\fujitsu_dev\demos\RX600_RX62N_GCC\vector_table.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC5) : "C:\rtos\fujitsu_dev\os\kernel\src\chcond.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chcond.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chcond.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC6) : "C:\rtos\fujitsu_dev\os\kernel\src\chdebug.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chdebug.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chdebug.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC7) : "C:\rtos\fujitsu_dev\os\kernel\src\chdynamic.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chdynamic.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chdynamic.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC8) : "C:\rtos\fujitsu_dev\os\kernel\src\chevents.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chevents.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chevents.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC9) : "C:\rtos\fujitsu_dev\os\kernel\src\chheap.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chheap.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chheap.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC10) : "C:\rtos\fujitsu_dev\os\kernel\src\chlists.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chlists.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chlists.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC11) : "C:\rtos\fujitsu_dev\os\kernel\src\chmboxes.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chmboxes.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chmboxes.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC12) : "C:\rtos\fujitsu_dev\os\kernel\src\chmemcore.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chmemcore.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chmemcore.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC13) : "C:\rtos\fujitsu_dev\os\kernel\src\chmempools.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chmempools.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chmempools.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC14) : "C:\rtos\fujitsu_dev\os\kernel\src\chmsg.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chmsg.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chmsg.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC15) : "C:\rtos\fujitsu_dev\os\kernel\src\chmtx.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chmtx.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chmtx.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC16) : "C:\rtos\fujitsu_dev\os\kernel\src\chqueues.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chqueues.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chqueues.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC17) : "C:\rtos\fujitsu_dev\os\kernel\src\chregistry.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chregistry.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chregistry.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC18) : "C:\rtos\fujitsu_dev\os\kernel\src\chschd.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chschd.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chschd.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC19) : "C:\rtos\fujitsu_dev\os\kernel\src\chsem.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chsem.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chsem.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC20) : "C:\rtos\fujitsu_dev\os\kernel\src\chsys.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chsys.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chsys.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC21) : "C:\rtos\fujitsu_dev\os\kernel\src\chthreads.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chthreads.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chthreads.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC22) : "C:\rtos\fujitsu_dev\os\kernel\src\chvt.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chvt.o"
"C:\rtos\fujitsu_dev\os\kernel\src\chvt.c"
<<

$(CH_DEBUG_COMPILER02_OUTFILESC23) : "C:\rtos\fujitsu_dev\os\ports\GCC\RX600\chcore.c"
	"$(EXEDIR)\$(CH_DEBUG_COMPILER02_EXE)" -subcommand=<<
-mcpu=rx600
-mlittle-endian-data
-mint-register=0
-I "$(TC_INSTALL_DIR)\rx-elf\rx-elf\include"
-I "$(TC_INSTALL_DIR)\rx-elf\lib\gcc\rx-elf\4.5-GNURX_v10.03\include"
-I "C:\rtos\fujitsu_dev\os\kernel\include"
-I "..\ch\."
-I "..\board"
-I "..\ch"
-D DEBUG
-g
-g2
-o "..\ch\Debug\chcore.o"
"C:\rtos\fujitsu_dev\os\ports\GCC\RX600\chcore.c"
<<

!MESSAGE
!MESSAGE Executing GNU Assembler03 phase
!MESSAGE

$(CH_DEBUG_ASSEMBLER03_OUTFILESC0) : "C:\rtos\fujitsu_dev\os\ports\GCC\RX600\crt0.s"
	"$(EXEDIR)\$(CH_DEBUG_ASSEMBLER03_EXE)" -subcommand=<<
"C:\rtos\fujitsu_dev\os\ports\GCC\RX600\crt0.s"
--mlittle-endian-data
-include="..\ch"
-nodebug
-object="..\ch\Debug\crt0.o"
-nolist
-nologo
<<

!MESSAGE
!MESSAGE Executing GNU Linker04 phase
!MESSAGE

$(CH_DEBUG_LINKER04_OUTFILESC0) : $(CH_DEBUG_LINKER04_INFILESC0)
	"$(EXEDIR)\$(CH_DEBUG_LINKER04_EXE)" -subcommand=<<
noprelink
list "..\ch\Debug\ch.map"
nologo
"..\ch\Debug\chcond.o"
"..\ch\Debug\chcore.o"
"..\ch\Debug\chdebug.o"
"..\ch\Debug\chdynamic.o"
"..\ch\Debug\chevents.o"
"..\ch\Debug\chheap.o"
"..\ch\Debug\chlists.o"
"..\ch\Debug\chmboxes.o"
"..\ch\Debug\chmemcore.o"
"..\ch\Debug\chmempools.o"
"..\ch\Debug\chmsg.o"
"..\ch\Debug\chmtx.o"
"..\ch\Debug\chqueues.o"
"..\ch\Debug\chregistry.o"
"..\ch\Debug\chschd.o"
"..\ch\Debug\chsem.o"
"..\ch\Debug\chsys.o"
"..\ch\Debug\chthreads.o"
"..\ch\Debug\chvt.o"
"..\ch\Debug\crt0.o"
"..\ch\Debug\main.o"
-l "libgcc.a"
-l "libch.a"
-o "..\ch\Debug\ch.x"
-e _PowerON_Reset
end
"..\ch\Debug\ch.x"
output "..\ch\Debug\ch.x"
<<

