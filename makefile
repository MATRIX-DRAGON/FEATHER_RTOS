# STM32F407 Linux Makefile for FEATHER_RTOS

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS  = -mcpu=cortex-m4 -mthumb -Wall -O0 -g -ffunction-sections -fdata-sections -DSTM32F407xx
LDFLAGS = -TSTM32F407VGTX_FLASH.ld -Wl,--gc-sections

# Include paths
INCLUDES = -IInc \
           -IFeather_Kernal/kernal_inc \
           -IFeather_Kernal/chip_headers/CMSIS/Include \
           -IFeather_Kernal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include \
           -IUser_App/user_app_inc

# Source files
SRC = Src/*.c \
      User_App/user_app_src/*.c \
      Feather_Kernal/kernal_src/*.c

STARTUP = Startup/startup_stm32f407vgtx.s

# Output
BUILD_DIR = Debug
ELF       = $(BUILD_DIR)/FEATHER_RTOS.elf
BIN       = $(BUILD_DIR)/FEATHER_RTOS.bin

# Default target
all: $(ELF) $(BIN)

# Build ELF
$(ELF): $(SRC) $(STARTUP)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(STARTUP) $(SRC) $(LDFLAGS) -o $@

# Build BIN
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

# Flash target
flash: $(BIN)
	st-flash write $(BIN) 0x08000000

# Clean build files
clean:
	rm -rf $(BUILD_DIR)/*.o $(ELF) $(BIN)

.PHONY: all clean flash
