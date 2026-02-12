################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Feather_Kernal/kernal_src/user_os_kernal.c 

OBJS += \
./Feather_Kernal/kernal_src/user_os_kernal.o 

C_DEPS += \
./Feather_Kernal/kernal_src/user_os_kernal.d 


# Each subdirectory must supply rules for building sources it contributes
Feather_Kernal/kernal_src/%.o Feather_Kernal/kernal_src/%.su Feather_Kernal/kernal_src/%.cyclo: ../Feather_Kernal/kernal_src/%.c Feather_Kernal/kernal_src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407xx -c -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Feather_Kernal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Feather_Kernal/chip_headers/CMSIS/Include" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/Feather_Kernal/kernal_inc" -I"C:/Users/ronyp/Desktop/PROJERCS/RPC_RTOS/COD_WS/FEATHER_RTOS/User_App/user_app_inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Feather_Kernal-2f-kernal_src

clean-Feather_Kernal-2f-kernal_src:
	-$(RM) ./Feather_Kernal/kernal_src/user_os_kernal.cyclo ./Feather_Kernal/kernal_src/user_os_kernal.d ./Feather_Kernal/kernal_src/user_os_kernal.o ./Feather_Kernal/kernal_src/user_os_kernal.su

.PHONY: clean-Feather_Kernal-2f-kernal_src

