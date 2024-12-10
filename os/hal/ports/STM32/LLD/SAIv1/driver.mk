ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_SAI TRUE,$(HALCONF)),)
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/STM32/LLD/SAIv1/hal_sai_lld.c
endif
else
PLATFORMSRC += $(CHIBIOS)/os/hal/ports/STM32/LLD/SAIv1/hal_sai_lld.c
endif

PLATFORMINC += $(CHIBIOS)/os/hal/ports/STM32/LLD/SAIv1