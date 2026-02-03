################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/user_app/user_app_src/user_led.c \
../Src/user_app/user_app_src/user_uart.c 

OBJS += \
./Src/user_app/user_app_src/user_led.o \
./Src/user_app/user_app_src/user_uart.o 

C_DEPS += \
./Src/user_app/user_app_src/user_led.d \
./Src/user_app/user_app_src/user_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/user_app/user_app_src/%.o Src/user_app/user_app_src/%.su Src/user_app/user_app_src/%.cyclo: ../Src/user_app/user_app_src/%.c Src/user_app/user_app_src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407xx -c -I../Inc -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Src/kernal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Src/kernal/chip_headers/CMSIS/Include" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Src/kernal/kernal_inc" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Src/user_app/user_app_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-user_app-2f-user_app_src

clean-Src-2f-user_app-2f-user_app_src:
	-$(RM) ./Src/user_app/user_app_src/user_led.cyclo ./Src/user_app/user_app_src/user_led.d ./Src/user_app/user_app_src/user_led.o ./Src/user_app/user_app_src/user_led.su ./Src/user_app/user_app_src/user_uart.cyclo ./Src/user_app/user_app_src/user_uart.d ./Src/user_app/user_app_src/user_uart.o ./Src/user_app/user_app_src/user_uart.su

.PHONY: clean-Src-2f-user_app-2f-user_app_src

