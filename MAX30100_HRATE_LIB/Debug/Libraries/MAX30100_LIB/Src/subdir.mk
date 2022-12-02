################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/MAX30100_LIB/Src/MAX30100.c \
../Libraries/MAX30100_LIB/Src/MAX30100_BeatDetector.c \
../Libraries/MAX30100_LIB/Src/MAX30100_Filters.c \
../Libraries/MAX30100_LIB/Src/MAX30100_PulseOximeter.c \
../Libraries/MAX30100_LIB/Src/MAX30100_SpO2Calculator.c \
../Libraries/MAX30100_LIB/Src/ring_buffer.c 

OBJS += \
./Libraries/MAX30100_LIB/Src/MAX30100.o \
./Libraries/MAX30100_LIB/Src/MAX30100_BeatDetector.o \
./Libraries/MAX30100_LIB/Src/MAX30100_Filters.o \
./Libraries/MAX30100_LIB/Src/MAX30100_PulseOximeter.o \
./Libraries/MAX30100_LIB/Src/MAX30100_SpO2Calculator.o \
./Libraries/MAX30100_LIB/Src/ring_buffer.o 

C_DEPS += \
./Libraries/MAX30100_LIB/Src/MAX30100.d \
./Libraries/MAX30100_LIB/Src/MAX30100_BeatDetector.d \
./Libraries/MAX30100_LIB/Src/MAX30100_Filters.d \
./Libraries/MAX30100_LIB/Src/MAX30100_PulseOximeter.d \
./Libraries/MAX30100_LIB/Src/MAX30100_SpO2Calculator.d \
./Libraries/MAX30100_LIB/Src/ring_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/MAX30100_LIB/Src/%.o Libraries/MAX30100_LIB/Src/%.su: ../Libraries/MAX30100_LIB/Src/%.c Libraries/MAX30100_LIB/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -c -I../Core/Inc -I"E:/STM codes/STM32F070 SPACE/MAX30100_HRATE_LIB/Libraries/BML_DRIVERS/Inc" -I"E:/STM codes/STM32F070 SPACE/MAX30100_HRATE_LIB/Libraries/MAX30100_LIB/Inc" -I"E:/STM codes/STM32F070 SPACE/MAX30100_HRATE_LIB/Libraries/MLX90614_LIB/Inc" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-MAX30100_LIB-2f-Src

clean-Libraries-2f-MAX30100_LIB-2f-Src:
	-$(RM) ./Libraries/MAX30100_LIB/Src/MAX30100.d ./Libraries/MAX30100_LIB/Src/MAX30100.o ./Libraries/MAX30100_LIB/Src/MAX30100.su ./Libraries/MAX30100_LIB/Src/MAX30100_BeatDetector.d ./Libraries/MAX30100_LIB/Src/MAX30100_BeatDetector.o ./Libraries/MAX30100_LIB/Src/MAX30100_BeatDetector.su ./Libraries/MAX30100_LIB/Src/MAX30100_Filters.d ./Libraries/MAX30100_LIB/Src/MAX30100_Filters.o ./Libraries/MAX30100_LIB/Src/MAX30100_Filters.su ./Libraries/MAX30100_LIB/Src/MAX30100_PulseOximeter.d ./Libraries/MAX30100_LIB/Src/MAX30100_PulseOximeter.o ./Libraries/MAX30100_LIB/Src/MAX30100_PulseOximeter.su ./Libraries/MAX30100_LIB/Src/MAX30100_SpO2Calculator.d ./Libraries/MAX30100_LIB/Src/MAX30100_SpO2Calculator.o ./Libraries/MAX30100_LIB/Src/MAX30100_SpO2Calculator.su ./Libraries/MAX30100_LIB/Src/ring_buffer.d ./Libraries/MAX30100_LIB/Src/ring_buffer.o ./Libraries/MAX30100_LIB/Src/ring_buffer.su

.PHONY: clean-Libraries-2f-MAX30100_LIB-2f-Src

