.syntax unified
.cpu cortex-m3
.thumb

/* Bảng Vector Ngắt (Interrupt Vector Table) */
.section .isr_vector, "a", %progbits
.type g_pfnVectors, %object

g_pfnVectors:
    .word 0x20005000            /* 1. Stack Pointer ban đầu (RAM 20KB) */
    .word Reset_Handler         /* 2. Reset Handler */
    .word Default_Handler       /* 3. NMI Handler */
    .word Default_Handler       /* 4. Hard Fault Handler */
    .word Default_Handler       /* 5. MPU Fault Handler */
    .word Default_Handler       /* 6. Bus Fault Handler */
    .word Default_Handler       /* 7. Usage Fault Handler */
    .word 0                     /* 8. Reserved */
    .word 0                     /* 9. Reserved */
    .word 0                     /* 10. Reserved */
    .word 0                     /* 11. Reserved */
    .word Default_Handler       /* 12. SVCall Handler */
    .word Default_Handler       /* 13. Debug Monitor Handler */
    .word 0                     /* 14. Reserved */
    .word Default_Handler       /* 15. PendSV Handler */
    .word SysTick_Handler       /* 16. SysTick Handler */

/* Đoạn mã xử lý Reset */
.section .text
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Cấu hình lại Stack Pointer từ bảng Vector */
    ldr r0, =0x20005000
    mov sp, r0

    /* Gọi hàm main */
    bl main

Loop_Forever:
    b Loop_Forever

/* Xử lý ngắt mặc định */
.global Default_Handler
.type Default_Handler, %function
Default_Handler:
    b Default_Handler

/* Khai báo Weak cho SysTick_Handler */
.weak SysTick_Handler
.global SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler
