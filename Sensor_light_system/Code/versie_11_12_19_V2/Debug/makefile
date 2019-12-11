################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
versie_11_12_19_V2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
versie_11_12_19_V2.list \


# All Target
all: versie_11_12_19_V2.elf secondary-outputs

# Tool invocations
versie_11_12_19_V2.elf: $(OBJS) $(USER_OBJS) C:\Users\Jonas\Documents\STM32CubeIDE\versie_11_12_19_V2\STM32F030C8TX_FLASH.ld
	arm-none-eabi-gcc -o "versie_11_12_19_V2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\Jonas\Documents\STM32CubeIDE\versie_11_12_19_V2\STM32F030C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="versie_11_12_19_V2.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

versie_11_12_19_V2.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "versie_11_12_19_V2.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
