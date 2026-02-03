################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/kernal_src/user_os_kernal.c 

OBJS += \
./Src/kernal_src/user_os_kernal.o 

C_DEPS += \
./Src/kernal_src/user_os_kernal.d 


# Each subdirectory must supply rules for building sources it contributes
Src/kernal_src/%.o Src/kernal_src/%.su Src/kernal_src/%.cyclo: ../Src/kernal_src/%.c Src/kernal_src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407xx -c -I../Inc -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Inc/kernal_inc" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Inc/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Inc/chip_headers/CMSIS/Include" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Inc/user_app_inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-kernal_src

clean-Src-2f-kernal_src:
	-$(RM) ./Src/kernal_src/user_os_kernal.cyclo ./Src/kernal_src/user_os_kernal.d ./Src/kernal_src/user_os_kernal.o ./Src/kernal_src/user_os_kernal.su

.PHONY: clean-Src-2f-kernal_src

