################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User_App/user_app_src/user_led.c \
../User_App/user_app_src/user_uart.c 

OBJS += \
./User_App/user_app_src/user_led.o \
./User_App/user_app_src/user_uart.o 

C_DEPS += \
./User_App/user_app_src/user_led.d \
./User_App/user_app_src/user_uart.d 


# Each subdirectory must supply rules for building sources it contributes
User_App/user_app_src/%.o User_App/user_app_src/%.su User_App/user_app_src/%.cyclo: ../User_App/user_app_src/%.c User_App/user_app_src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407xx -c -I"C:/Users/ronyp/Desktop/GIT_PROJECTS/PROTO_PROJECTS/RTOS/FEATHER_RTOS/Feather_Kernal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ronyp/Desktop/GIT_PROJECTS/PROTO_PROJECTS/RTOS/FEATHER_RTOS/Feather_Kernal/chip_headers/CMSIS/Include" -I"C:/Users/ronyp/Desktop/GIT_PROJECTS/PROTO_PROJECTS/RTOS/FEATHER_RTOS/Feather_Kernal/kernal_inc" -I"C:/Users/ronyp/Desktop/GIT_PROJECTS/PROTO_PROJECTS/RTOS/FEATHER_RTOS/User_App/user_app_inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User_App-2f-user_app_src

clean-User_App-2f-user_app_src:
	-$(RM) ./User_App/user_app_src/user_led.cyclo ./User_App/user_app_src/user_led.d ./User_App/user_app_src/user_led.o ./User_App/user_app_src/user_led.su ./User_App/user_app_src/user_uart.cyclo ./User_App/user_app_src/user_uart.d ./User_App/user_app_src/user_uart.o ./User_App/user_app_src/user_uart.su

.PHONY: clean-User_App-2f-user_app_src

