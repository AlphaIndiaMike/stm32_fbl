################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FBL/Src/fbl.c 

OBJS += \
./FBL/Src/fbl.o 

C_DEPS += \
./FBL/Src/fbl.d 


# Each subdirectory must supply rules for building sources it contributes
FBL/Src/%.o FBL/Src/%.su FBL/Src/%.cyclo: ../FBL/Src/%.c FBL/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"/Users/alex/Desktop/AIM/05_Hobby/01_Projects/18_STM32F7_FBL/offline/FBL/Inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FBL-2f-Src

clean-FBL-2f-Src:
	-$(RM) ./FBL/Src/fbl.cyclo ./FBL/Src/fbl.d ./FBL/Src/fbl.o ./FBL/Src/fbl.su

.PHONY: clean-FBL-2f-Src

