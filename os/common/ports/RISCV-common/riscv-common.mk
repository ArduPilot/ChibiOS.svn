# RISCV-common subsystem build.

# Required files.
ifndef RISCVCOMMONSRC
  RISCVCOMMONSRC =
  ALLCSRC += $(RISCVCOMMONSRC)
endif

# Required include directories
ifndef RISCVCOMMONINC
  RISCVCOMMONINC = ${CHIBIOS}/os/common/ports/RISCV-common/include
  ALLINC += $(RISCVCOMMONINC)
endif
