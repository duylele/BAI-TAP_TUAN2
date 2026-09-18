# Compiler toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Target file name
TARGET  = bai5

# C sources and Include paths
C_SOURCES = main.c
ASM_SOURCES = startup_stm32f10x_md.s

CFLAGS  = -mcpu=cortex-m3 -mthumb -O0 -Wall -g -I. -ICMSIS -DSTM32F10X_MD
LDFLAGS = -mcpu=cortex-m3 -mthumb --specs=nano.specs --specs=nosys.specs -T stm32_flash.ld -Wl,-Map=$(TARGET).map,--gc-sections

all: $(TARGET).bin

$(TARGET).elf: $(C_SOURCES) $(ASM_SOURCES)
	$(CC) $(CFLAGS) $(C_SOURCES) $(ASM_SOURCES) $(LDFLAGS) -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(TARGET).elf $(TARGET).bin $(TARGET).hex $(TARGET).map

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x8000000

.PHONY: all clean flash
