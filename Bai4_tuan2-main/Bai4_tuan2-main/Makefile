# Tên các công cụ biên dịch (Cross-compiler cho ARM Cortex-M)
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Tên file đầu ra
TARGET = firmware

# Cờ biên dịch cho Cortex-M3
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall -ffreestanding
LDFLAGS = -T stm32f103.ld -nostdlib -Wl,-Map=$(TARGET.map)

# Danh sách các file mã nguồn
C_SOURCES = main.c
ASM_SOURCES = startup.s

# Danh sách các file đối tượng (object files)
OBJECTS = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.s=.o)

all: $(TARGET).elf $(TARGET).hex $(TARGET).bin size

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

size: $(TARGET).elf
	$(SIZE) $<

clean:
	rm -rf *.o *.elf *.hex *.bin *.map

.PHONY: all clean size
