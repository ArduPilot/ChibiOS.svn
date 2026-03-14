# List of the ChibiOS RISC-V Hazard3 port files.

# Dependencies.
include $(CHIBIOS)/os/common/portability/GCC/ccportab.mk
include $(CHIBIOS)/os/common/ports/RISCV-common/riscv-common.mk

PORTSRC = $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/chcore.c \
          $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/compilers/GCC/vectors_riscv.c

PORTASM = $(CHIBIOS)/os/common/ports/RISCV-HAZARD3/compilers/GCC/chcoreasm.S

PORTINC = $(CHIBIOS)/os/common/ports/RISCV-HAZARD3

# Shared variables
ALLXASMSRC += $(PORTASM)
ALLCSRC    += $(PORTSRC)
ALLINC     += $(PORTINC)
