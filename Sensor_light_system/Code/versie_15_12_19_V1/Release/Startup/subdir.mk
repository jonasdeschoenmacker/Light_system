################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f030c8tx.s 

OBJS += \
./Startup/startup_stm32f030c8tx.o 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -c -I../ -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

