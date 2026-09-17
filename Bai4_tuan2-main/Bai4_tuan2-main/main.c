#include <stdint.h>

#define RCC_BASE        0x40021000UL
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x1C))

#define GPIOA_BASE      0x40010800UL
#define GPIOA_CRL       (*(volatile uint32_t *)(GPIOA_BASE + 0x00))

#define GPIOB_BASE      0x40010C00UL
#define GPIOB_CRL       (*(volatile uint32_t *)(GPIOB_BASE + 0x00))

#define TIM3_BASE       0x40000400UL

#define TIM3_CR1        (*(volatile uint32_t *)(TIM3_BASE + 0x00))
#define TIM3_EGR        (*(volatile uint32_t *)(TIM3_BASE + 0x14))
#define TIM3_CCMR1      (*(volatile uint32_t *)(TIM3_BASE + 0x18))
#define TIM3_CCMR2      (*(volatile uint32_t *)(TIM3_BASE + 0x1C))
#define TIM3_CCER       (*(volatile uint32_t *)(TIM3_BASE + 0x20))
#define TIM3_PSC        (*(volatile uint32_t *)(TIM3_BASE + 0x28))
#define TIM3_ARR        (*(volatile uint32_t *)(TIM3_BASE + 0x2C))
#define TIM3_CCR1       (*(volatile uint32_t *)(TIM3_BASE + 0x34))
#define TIM3_CCR2       (*(volatile uint32_t *)(TIM3_BASE + 0x38))
#define TIM3_CCR3       (*(volatile uint32_t *)(TIM3_BASE + 0x3C))
#define TIM3_CCR4       (*(volatile uint32_t *)(TIM3_BASE + 0x40))

void PWM_init(void){

	RCC_APB2ENR |= (1<<2) ;   // dich trai 2 bit de bat clock GPIOA
  	RCC_APB2ENR |= (1<<3) ;   // dich trai 3 bit de bat clock GPIOB
	RCC_APB1ENR |= (1<<1) ;   // bat Clock TIM3

	// cau hinh chan PA6
	GPIOA_CRL &= ~(0xF << 24);
	GPIOA_CRL |= (0xB << 24);
	
	// cau hinh chan PA7
	GPIOA_CRL &= ~(0xF << 28);
	GPIOA_CRL |= (0xB << 28);
	
	// cau hinh chan PB0
	GPIOB_CRL &= ~(0xF << 00);
	GPIOB_CRL |= (0xB << 00);
	
	// cau hinh chan PB1
	GPIOB_CRL &= ~(0xF << 4);
	GPIOB_CRL |= (0xB << 4); 
	
	// cau hinh bo dem
	TIM3_PSC = 7;

	// Cau hinh chu ki ARR
	TIM3_ARR = 999;

	// Cau hinh duty
	TIM3_CCR1 = 100;
	TIM3_CCR2 = 300;
	TIM3_CCR3 = 500;
	TIM3_CCR4 = 700;
 	
	// cau hinh PWM mode 1 CH1
	TIM3_CCR1 &= ~(0xF << 4);
	TIM3_CCR1 |= (6 << 4);
	TIM3_CCR1 |= (1 << 3);
	
	// cau hinh PWM mode 1 CH2
	TIM3_CCR1 &= ~(0xF << 12);
	TIM3_CCR1 |= (6 << 12);
	TIM3_CCR1 |= (1 << 11);

	// cau hinh PWM mode 1 CH3
	TIM3_CCR2 &= ~(0xF << 4);
	TIM3_CCR2 |= (6 << 4);
	TIM3_CCR2 |= (1 << 3);

	// cau hinh PWM MOde 1 CH4
	TIM3_CCR2 &= ~(0xF << 12);
	TIM3_CCR2 |= (6 << 12);
	TIM3_CCR2 |= (1 << 11);

	// bat 4 kenh PWM
	TIM3_CCER |= (1 << 0);
	TIM3_CCER |= (1 << 4);
	TIM3_CCER |= (1 << 8);
	TIM3_CCER |= (1 << 12);

	// update timer 
	TIM3_EGR |= (1 << 0);
	TIM3_CR1 |= (1 << 7);
	TIM3_CR1 |= (1 << 0); 
}
int main(void){
	PWM_init();
	while(1){
	}
}
