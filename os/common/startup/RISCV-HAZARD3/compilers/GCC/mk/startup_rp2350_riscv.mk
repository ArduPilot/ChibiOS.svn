# List of the ChibiOS generic RP2350 RISC-V Hazard3 startup files.

STARTUPSRC =

STARTUPASM = $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/compilers/GCC/crt0_hazard3.S \
             $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/compilers/GCC/crt0_c1_hazard3.S \
             $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/compilers/GCC/vectors_hazard3.S \
             $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/devices/RP2350/rp2350_riscv_imagedef.S

STARTUPINC = $(CHIBIOS)/os/common/portability/GCC \
             $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/compilers/GCC \
             $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/devices/RP2350 \
             $(CHIBIOS)/os/common/ext/RISCV \
             $(CHIBIOS)/os/common/ext/RP/RP2350

STARTUPLD  = $(CHIBIOS)/os/common/startup/RISCV-HAZARD3/compilers/GCC/ld

# Shared variables
ALLXASMSRC += $(STARTUPASM)
ALLCSRC    += $(STARTUPSRC)
ALLINC     += $(STARTUPINC)
