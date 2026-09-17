# Bài tập Tuần 04: Lập trình PWM STM32F103 (Bare-metal)

Dự án cấu hình và điều khiển PWM sử dụng vi điều khiển STM32F103C8T6 (Cortex-M3) với toolchain dòng lệnh (`arm-none-eabi-gcc` và `make`) không sử dụng thư viện HAL nặng.

## Cấu trúc dự án
- `Src/main.c`: Mã nguồn chính cấu hình Timer 2 (TIM2) phát xung PWM 4 kênh (duty cycle 10%, 30%, 50%, 70%).
- `Startup/`: File khởi động viết bằng hợp ngữ (`startup_stm32f103xb.s`).
- `Inc/`: Thư mục chứa các file header.
- `Drivers/`: Thư mục CMSIS.
- `Makefile`: Tệp cấu hình tự động hóa quá trình biên dịch.

## Biên dịch dự án
Để biên dịch mã nguồn và tạo các file firmware (`.bin`, `.hex`, `.elf`) trong thư mục `build/`, bạn chạy lệnh:

```bash
make clean
make
