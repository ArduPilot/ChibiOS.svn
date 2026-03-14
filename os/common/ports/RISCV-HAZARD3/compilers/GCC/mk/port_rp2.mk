# List of the ChibiOS/RT RISC-V Hazard3 RP2 SMP port files.

# Dependencies.
include $(CHIBIOS)/os/common/portability/GCC/ccportab.mk
include $(CHIBIOS)/os/common/ports/RISCV-common/riscv-common.mk

PORTSRC = $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/chcore.c \
          $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/compilers/GCC/vectors_riscv.c \
          $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/smp/rp2/chcoresmp.c

PORTASM = $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/compilers/GCC/chcoreasm.S

PORTINC = $(CHIBIOS)/os/common/ports/RISCV-HAZARD3 \
          $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/smp/rp2

# Shared variables
ALLXASMSRC += $(PORTASM)
ALLCSRC    += $(PORTSRC)
ALLINC     += $(PORTINC)
