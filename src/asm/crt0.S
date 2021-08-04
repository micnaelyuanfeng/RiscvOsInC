/*
    M-Mode
    S-Mode
    RISCV enter M mode when powering on
    OpenSBI loads cr0 and program hw to enter S Mode
*/

#include "define.inc"

    .section .text.init
    .globl _start
_start:
    bnez a0, 2f

    la sp, _main_stack_top

loop:
    jal kentry

2:
    wfi

    j 2b

    .align 16
    .section .bss.stack
    .globl _main_stack
_main_stack:
    .space 4096 * 10
    .globl _main_stack_top
_main_stack_top:
