# List of the ChibiOS OOP module.
OOPSRC = ${CHIBIOS}/os/common/oop/src/oop_base_object.c \
         ${CHIBIOS}/os/common/oop/src/oop_referenced_object.c
 
OOPINC = ${CHIBIOS}/os/common/oop/include

# Shared variables
ALLCSRC += $(OOPSRC)
ALLINC  += $(OOPINC)
