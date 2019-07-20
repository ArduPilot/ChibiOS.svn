# List of the ChibiOS ARMv7-M sandbox host files.
SBHOSTSRC = $(CHIBIOS)/os/sb/host/sbhost.c \
			$(CHIBIOS)/os/sb/host/sbapi.c
          
SBHOSTASM =

SBHOSTINC = $(CHIBIOS)/os/sb/host

# Shared variables
ALLXASMSRC += $(SBHOSTASM)
ALLCSRC    += $(SBHOSTSRC)
ALLINC     += $(SBHOSTINC)
