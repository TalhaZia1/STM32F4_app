TARGET = STM32F4_APP
DEBUG = 1
OPT = -Og
BUILD_DIR = build
FREERTOS_PATH = FreeRTOS-Kernel
APP_PATH = Core/Src
HAL_LIB_PATH = Drivers/STM32F4xx_HAL_Driver/Src

######################################
# source
######################################
# C sources
C_SOURCES =  \
	$(APP_PATH)/main.c \
	$(APP_PATH)/stm32f4xx_it.c \
	$(APP_PATH)/stm32f4xx_hal_msp.c \
	$(APP_PATH)/system_stm32f4xx.c \
	$(APP_PATH)/uart_cfg.c \
	$(APP_PATH)/clock_cfg.c \
	$(APP_PATH)/gpio_cfg.c \
	$(APP_PATH)/timer_cfg.c \
	$(APP_PATH)/low_power_cfg.c \
	$(APP_PATH)/bkup_SRAM_cfg.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_tim.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_tim_ex.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_rcc.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_rcc_ex.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_flash.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_flash_ex.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_flash_ramfunc.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_gpio.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_dma_ex.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_dma.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_pwr.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_pwr_ex.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_cortex.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_exti.c \
	$(HAL_LIB_PATH)/stm32f4xx_hal_uart.c 

# FreeRTOS source files
FREERTOS_SRC_FILES =  \
    $(FREERTOS_PATH)/portable/Common/mpu_wrappers.c \
    $(FREERTOS_PATH)/portable/GCC/ARM_CM4F/port.c \
    $(FREERTOS_PATH)/portable/MemMang/heap_4.c \
	$(FREERTOS_PATH)/event_groups.c \
	$(FREERTOS_PATH)/list.c \
	$(FREERTOS_PATH)/queue.c \
	$(FREERTOS_PATH)/stream_buffer.c \
	$(FREERTOS_PATH)/tasks.c \
	$(FREERTOS_PATH)/timers.c 

# Add FreeRTOS source files to the list of sources
C_SOURCES += $(FREERTOS_SRC_FILES)

# ASM sources
ASM_SOURCES =  \
startup_stm32f446xx.s

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F446xx

# Compiler flags and options for FreeRTOS
FREERTOS_CFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -Wextra -std=gnu11

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
	-ICore/Inc \
	-IDrivers/STM32F4xx_HAL_Driver/Inc \
	-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
	-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
	-IDrivers/CMSIS/Include 

# FreeRTOS include files
FREERTOS_INC_FILES =  \
    -I$(FREERTOS_PATH)/include \
    -I$(FREERTOS_PATH)/portable/GCC/ARM_CM4F

# Add FreeRTOS include directories to the list of include directories
C_INCLUDES += $(FREERTOS_INC_FILES)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(FREERTOS_CFLAGS) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F446RETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***