/* Định nghĩa trực tiếp địa chỉ thanh ghi cho STM32F103 để không cần file header ngoài */
#define PERIPH_BASE     (0x40000000UL)
#define APB1PERIPH_BASE (PERIPH_BASE)
#define AHBPERIPH_BASE  (PERIPH_BASE + 0x00020000UL)
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)

#define RCC_BASE        (AHBPERIPH_BASE + 0x00001000UL)
#define GPIOA_BASE      (APB2PERIPH_BASE + 0x00080000UL)
#define TIM2_BASE       (APB1PERIPH_BASE + 0x00000000UL)

typedef struct {
    volatile unsigned int CR;
    volatile unsigned int CFGR;
    volatile unsigned int CIR;
    volatile unsigned int APB2RSTR;
    volatile unsigned int APB1RSTR;
    volatile unsigned int AHBENR;
    volatile unsigned int APB2ENR;
    volatile unsigned int APB1ENR;
} RCC_TypeDef;

typedef struct {
    volatile unsigned int CRL;
    volatile unsigned int CRH;
    volatile unsigned int IDR;
    volatile unsigned int ODR;
    volatile unsigned int BSRR;
    volatile unsigned int BRR;
    volatile unsigned int LCKR;
} GPIO_TypeDef;

typedef struct {
    volatile unsigned int CR1;
    volatile unsigned int CR2;
    volatile unsigned int SMCR;
    volatile unsigned int DIER;
    volatile unsigned int SR;
    volatile unsigned int EGR;
    volatile unsigned int CCMR1;
    volatile unsigned int CCMR2;
    volatile unsigned int CCER;
    volatile unsigned int CNT;
    volatile unsigned int PSC;
    volatile unsigned int ARR;
    volatile unsigned int RCR;
    volatile unsigned int CCR1;
    volatile unsigned int CCR2;
    volatile unsigned int CCR3;
    volatile unsigned int CCR4;
} TIM_TypeDef;

#define RCC   ((RCC_TypeDef *) RCC_BASE)
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define TIM2  ((TIM_TypeDef *) TIM2_BASE)

void TIM2_PWM_Init(void) {
    // 1. Bật xung clock cho GPIOA (bit 2) và TIM2 (bit 0 trong APB1ENR)
    RCC->APB2ENR |= (1 << 2);
    RCC->APB1ENR |= (1 << 0);

    // 2. Cấu hình chân GPIOA (PA0, PA1, PA2, PA3) làm Alternate Function Push-Pull (50MHz)
    GPIOA->CRL &= 0xFFFF0000;
    GPIOA->CRL |= 0x0000BBBB; 

    // 3. Cấu hình tần số Timer 1kHz
    TIM2->PSC = 72 - 1;   // 72MHz / 72 = 1MHz (1us/tick)
    TIM2->ARR = 1000 - 1; // 1000us = 1ms -> 1kHz

    // 4. Cấu hình chế độ PWM Mode 1 cho 4 kênh (CCMR1, CCMR2)
    TIM2->CCMR1 |= (6 << 4) | (1 << 3);   // Channel 1
    TIM2->CCMR1 |= (6 << 12) | (1 << 11); // Channel 2
    TIM2->CCMR2 |= (6 << 4) | (1 << 3);   // Channel 3
    TIM2->CCMR2 |= (6 << 12) | (1 << 11); // Channel 4

    // 5. Bật Output Enable cho 4 kênh (CC1E, CC2E, CC3E, CC4E)
    TIM2->CCER |= (1 << 0) | (1 << 4) | (1 << 8) | (1 << 12);

    // 6. Cài đặt Duty Cycle theo yêu cầu bài 4
    TIM2->CCR1 = 100; // 10%
    TIM2->CCR2 = 300; // 30%
    TIM2->CCR3 = 500; // 50%
    TIM2->CCR4 = 700; // 70%

    // 7. Bật Timer 2 (CEN = 1)
    TIM2->CR1 |= (1 << 0);
}
// Định nghĩa hàm SystemInit để file startup gọi tới trước khi vào main
void SystemInit(void) {
    // Có thể để trống hoặc cấu hình xung nhịp hệ thống tại đây nếu cần
}
int main(void) {
    TIM2_PWM_Init();
    while (1) {
    }
}
