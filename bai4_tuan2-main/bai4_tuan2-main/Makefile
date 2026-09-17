TARGET = bai4_tuan2

# Toolchain
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)ld
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

# Cấu hình kiến trúc chip STM32F103 (Cortex-M3)
CPU = -mcpu=cortex-m3 -mthumb

# Thư mục
SRCDIR = Src
INCDIR = Inc
BUILDDIR = build

# Khai báo nguồn file C và Startup
C_SOURCES = $(SRCDIR)/main.c
ASM_SOURCES = Startup/startup_stm32f103xb.s

# Gom nhóm file Object đầu ra vào thư mục build
OBJECTS = $(BUILDDIR)/main.o
OBJECTS += $(BUILDDIR)/startup_stm32f103xb.o

# Cờ biên dịch C
CFLAGS = $(CPU) -std=gnu11 -O0 -Wall -fdata-sections -ffunction-sections \
         -I$(INCDIR) -IDrivers/CMSIS/Include -IDrivers/CMSIS/Device/ST/STM32F1xx/Include

# Cờ liên kết (Linker)
LDFLAGS = $(CPU) -specs=nosys.specs -TSTM32F103C8Tx_FLASH.ld -Wl,-Map=$(BUILDDIR)/$(TARGET).map,--gc-sections -static

all: $(BUILDDIR)/$(TARGET).elf $(BUILDDIR)/$(TARGET).hex $(BUILDDIR)/$(TARGET).bin

# Quy luật dịch file C trong thư mục Src/
$(BUILDDIR)/main.o: $(SRCDIR)/main.c | $(BUILDDIR)
	$(CC) -c $(CFLAGS) $< -o $@

# Quy luật dịch file Assembly trong thư mục Startup/
$(BUILDDIR)/startup_stm32f103xb.o: Startup/startup_stm32f103xb.s | $(BUILDDIR)
	$(AS) $(CPU) $< -o $@

# Liên kết các file object thành file ELF
$(BUILDDIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

# Tạo file HEX
$(BUILDDIR)/%.hex: $(BUILDDIR)/%.elf
	$(CP) -O ihex $< $@

# Tạo file BIN để nạp
$(BUILDDIR)/%.bin: $(BUILDDIR)/%.elf
	$(CP) -O binary -S $< $@

# Tạo thư mục build nếu chưa có
$(BUILDDIR):
	mkdir -p $@

# Xóa các file build cũ
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
