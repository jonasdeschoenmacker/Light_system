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
STM32F030_test1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F030_test1.list \


# All Target
all: STM32F030_test1.elf secondary-outputs

# Tool invocations
STM32F030_test1.elf: $(OBJS) $(USER_OBJS) C:\Users\Jonas\Documents\school\KULeuven\jaar1\semester1\Elektronische\ tech\ Labo\Light_system\Sensor_light_system\Code\STM32F030_test1\STM32F030C8TX_FLASH.ld
	arm-none-eabi-gcc -o "STM32F030_test1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\Jonas\Documents\school\KULeuven\jaar1\semester1\Elektronische tech Labo\Light_system\Sensor_light_system\Code\STM32F030_test1\STM32F030C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F030_test1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F030_test1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F030_test1.list"
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
