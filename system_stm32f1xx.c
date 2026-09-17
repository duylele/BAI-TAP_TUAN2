#include "stm32f1xx.h"

uint32_t SystemCoreClock = 72000000;
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

void SystemInit (void) {
    RCC->CR |= (uint32_t)0x00000001;
    RCC->CFGR &= (uint32_t)0xF8FF0000;
    RCC->CR &= (uint32_t)0xFEF6FFFF;
    RCC->CR &= (uint32_t)0xFFFBFFFF;
    RCC->CFGR &= (uint32_t)0xFF80FFFF;
    RCC->CIR = 0x009F0000;
}
