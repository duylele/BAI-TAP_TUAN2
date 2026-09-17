.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global	g_pfnVectors
.global	Default_Handler

/* start address for the initialization values of the .data section. defined in linker script */
.word	_sidata
/* start address for the .data section. defined in linker script */
.word	_sdata
/* end address for the .data section. defined in linker script */
.word	_edata
/* start address for the .bss section. defined in linker script */
.word	_sbss
/* end address for the .bss section. defined in linker script */
.word	_ebss

.section	.text.Reset_Handler
.weak	Reset_Handler
.type	Reset_Handler, %function
Reset_Handler:
  /* Set stack pointer */
  ldr   r0, =_estack
  mov   sp, r0

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sidata
  ldr r1, =_sdata
  ldr r2, =_edata
  movs r3, #0
  b	LoopCopyDataInit

CopyDataInit:
  ldr r4, [r0, r3]
  str r4, [r1, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r1, r3
  cmp r4, r2
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

  /* Call system initialization file */
  bl SystemInit
  /* Call the application's entry point */
  bl main
  bx lr
.size	Reset_Handler, .-Reset_Handler

/* Default interrupt handler */
.section	.text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b	Infinite_Loop
.size	Default_Handler, .-Default_Handler

/* Vector Table */
.section	.isr_vector,"a",%progbits
.type	g_pfnVectors, %object
.size	g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word	_estack
  .word	Reset_Handler
  .word	NMI_Handler
  .word	HardFault_Handler
  .word	MemManage_Handler
  .word	BusFault_Handler
  .word	UsageFault_Handler
  .word	0
  .word	0
  .word	0
  .word	0
  .word	SVC_Handler
  .word	DebugMon_Handler
  .word	0
  .word	PendSV_Handler
  .word	SysTick_Handler
  
  /* External Interrupts */
  .word	WWDG_IRQHandler
  .word	PVD_IRQHandler
  .word	TAMPER_IRQHandler
  .word	RTC_IRQHandler
  .word	FLASH_IRQHandler
  .word	RCC_IRQHandler
  .word	EXTI0_IRQHandler
  .word	EXTI1_IRQHandler
  .word	EXTI2_IRQHandler
  .word	EXTI3_IRQHandler
  .word	EXTI4_IRQHandler
  .word	DMA1_Channel1_IRQHandler
  .word	DMA1_Channel2_IRQHandler
  .word	DMA1_Channel3_IRQHandler
  .word	DMA1_Channel4_IRQHandler
  .word	DMA1_Channel5_IRQHandler
  .word	DMA1_Channel6_IRQHandler
  .word	DMA1_Channel7_IRQHandler
  .word	ADC1_2_IRQHandler
  .word	USB_HP_CAN1_TX_IRQHandler
  .word	USB_LP_CAN1_RX0_IRQHandler
  .word	CAN1_RX1_IRQHandler
  .word	CAN1_SCE_IRQHandler
  .word	EXTI5_9_IRQHandler
  .word	TIM1_BRK_IRQHandler
  .word	TIM1_UP_IRQHandler
  .word	TIM1_TRG_COM_IRQHandler
  .word	TIM1_CC_IRQHandler
  .word	TIM2_IRQHandler
  .word	TIM3_IRQHandler
  .word	TIM4_IRQHandler
  /* (Các ngắt khác được rút gọn để mặc định về Default_Handler) */

/* Weak aliases for interrupts */
.weak	NMI_Handler
.thumb_set NMI_Handler,Default_Handler

.weak	HardFault_Handler
.thumb_set HardFault_Handler,Default_Handler

.weak	MemManage_Handler
.thumb_set MemManage_Handler,Default_Handler

.weak	BusFault_Handler
.thumb_set BusFault_Handler,Default_Handler

.weak	UsageFault_Handler
.thumb_set UsageFault_Handler,Default_Handler

.weak	SVC_Handler
.thumb_set SVC_Handler,Default_Handler

.weak	DebugMon_Handler
.thumb_set DebugMon_Handler,Default_Handler

.weak	PendSV_Handler
.thumb_set PendSV_Handler,Default_Handler

.weak	SysTick_Handler
.thumb_set SysTick_Handler,Default_Handler

.weak	TIM2_IRQHandler
.thumb_set TIM2_IRQHandler,Default_Handler
