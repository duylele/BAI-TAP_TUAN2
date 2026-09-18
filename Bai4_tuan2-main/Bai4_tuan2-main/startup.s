.syntax unified
.cpu cortex-m3
.thumb

.global Reset_Handler
.global _estack

.section .isr_vector,"a",%progbits

.word _estack
.word Reset_Handler

.section .text.Reset_Handler
.thumb_func

Reset_Handler:

    bl main

Loop:
    b Loop

