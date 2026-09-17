# Bài tập 04: Cấu hình PWM 4 Kênh trên STM32F103 (Bare-Metal)
Dự án lập trình nhúng Bare-Metal không sử dụng thư viện HAL/SPL cho vi điều khiển STM32F103 (Cortex-M3), điều khiển 4 channel xuất tín hiệu PWM từ Timer 3.
## 📌 Yêu cầu đề bài
* Cấu hình 4 chân của 1 bộ Timer ở chế độ PWM tương ứng.
* Cấu hình Timer hoạt động với chu kỳ **1kHz**.
* Duty (độ rộng xung) của 4 LED lần lượt ở các mức:
  * **Kênh 1 (Channel 1):** 10%
  * **Kênh 2 (Channel 2):** 30%
  * **Kênh 3 (Channel 3):** 50%
  * **Kênh 4 (Channel 4):** 70%
## ⚙️ Cấu hình Phần cứng & Ngoại vi
### 1. Phân bố chân (Pinout)
* **TIM3_CH1:** PA6
* **TIM3_CH2:** PA7
* **TIM3_CH3:** PB0
* **TIM3_CH4:** PB1
### 2. Thông số Timer 3 (TIM3)
Với tần số cấp cho TIM3 mặc định là **8 MHz**:
* **Prescaler (`TIM3_PSC`):** `7` (Tần số đếm = 8 MHz / (7 + 1) = 1 MHz)
* **Auto-reload (`TIM3_ARR`):** `999` (Tần số PWM = 1 MHz / (999 + 1) = **1 kHz**)
* **Compare Registers (`CCR`):**
  * `TIM3_CCR1` = 100 (Duty = 100/1000 = **10%**)
  * `TIM3_CCR2` = 300 (Duty = 300/1000 = **30%**)
  * `TIM3_CCR3` = 500 (Duty = 500/1000 = **50%**)
  * `TIM3_CCR4` = 700 (Duty = 700/1000 = **70%**)
## 📁 Cấu trúc thư mục
```text
Bai4_tuan2/
├── main.c                  # Mã nguồn chương trình chính & khởi tạo PWM
├── startup.s               # File Startup chứa Vector Table & Reset Handler
├── stm32f103.ld            # Linker Script quản lý phân bổ bộ nhớ FLASH & RAM
├── Makefile                # File cấu hình biên dịch bằng arm-none-eabi-gcc
└── README.md               # Tài liệu hướng dẫn dự án
