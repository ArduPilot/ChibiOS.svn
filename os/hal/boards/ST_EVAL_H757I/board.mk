# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_EVAL_H757I/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_EVAL_H757I

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
