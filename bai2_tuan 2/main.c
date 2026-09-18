#include "stm32f10x.h"

// Khai báo các biến đếm tần số (sử dụng volatile vì thay đổi trong Interrupt)
volatile unsigned int cnt_01hz = 0;
volatile unsigned int cnt_1hz  = 0;
volatile unsigned int cnt_10hz = 0;

// Trình xử lý ngắt SysTick (xảy ra mỗi 1ms = 1000Hz)
void SysTick_Handler(void) {
    cnt_01hz++;
    cnt_1hz++;
    cnt_10hz++;

    // Tần số 0.1Hz -> Chu kỳ 10s -> Đảo trạng thái mỗi 5s (5000ms)
    if (cnt_01hz >= 5000) {
        GPIOA->ODR ^= (1 << 0);      // PA0 - LED 1 (0.1Hz)
        cnt_01hz = 0;
    }

    // Tần số 1Hz -> Chu kỳ 1s -> Đảo trạng thái mỗi 0.5s (500ms)
    if (cnt_1hz >= 500) {
        GPIOA->ODR ^= (1 << 1);      // PA1 - LED 2 (1Hz)
        cnt_1hz = 0;
    }

    // Tần số 10Hz -> Chu kỳ 0.1s -> Đảo trạng thái mỗi 0.05s (50ms)
    if (cnt_10hz >= 50) {
        GPIOA->ODR ^= (1 << 2);      // PA2 - LED 3 (10Hz)
        cnt_10hz = 0;
    }
}

int main(void) {
    // 1. Bật clock cho GPIOA (Bit 2 của thanh ghi APB2ENR)
    RCC->APB2ENR |= (1 << 2);

    // 2. Cấu hình PA0, PA1, PA2 làm Output General Purpose Push-Pull (tốc độ 50MHz)
    GPIOA->CRL &= ~(0xFFF);          // Xóa cấu hình cũ của PA0, PA1, PA2
    GPIOA->CRL |=  (0x333);          // Thiết lập Output 50MHz Push-Pull (0x3)

    // 3. Cấu hình SysTick tạo ngắt mỗi 1ms (Giả định chạy xung nội HSI = 8MHz)
    // Giá trị nạp = (8.000.000 Hz / 1000 Hz) - 1 = 7999
    STK_LOAD = 8000 - 1;
    STK_VAL  = 0;

    /* 
     * STK_CTRL:
     * Bit 0 (ENABLE)    = 1 : Bật SysTick timer
     * Bit 1 (TICKINT)   = 1 : Bật ngắt ngắt SysTick
     * Bit 2 (CLKSOURCE) = 1 : Chọn nguồn xung AHB (8MHz)
     */
    STK_CTRL = (1 << 0) | (1 << 1) | (1 << 2);

    // 4. Bật ngắt toàn cục (Global Interrupt Enable)
    __asm volatile ("cpsie i");

    while (1) {
        // Vòng lặp chính để trống, mọi việc xử lý nằm trong SysTick_Handler
    }
}
