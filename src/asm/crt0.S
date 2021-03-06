/*
    M-Mode
    S-Mode
    RISCV enter M mode when powering on
    OpenSBI loads cr0 and program hw to enter S Mode
*/
    .section .text.init
    .globl _start
_start:
    call _clear_bss

    lui t0, %hi(_root_page_table)
    li t1, 0xffffffff00000000
    sub t0, t0, t1
    srli t0, t0, 12

    li t1, 0x8
    slli t1, t1, 60
    or t0, t0, t1

    csrw satp, t0
    sfence.vma

    bnez a0, 2f

    lui sp, %hi(_main_stack_top)
    addi sp, sp, %lo(_main_stack_top)
    # la sp, _main_stack_top

loop:
    lui t0, %hi(kentry)
    addi t0, t0, %lo(kentry)
    jr t0
    # jal kentry

2:
    wfi

    j 2b

_clear_bss:
    la a2, _bss_start
    la a1, _bss_end
2:
    sw zero, (a2)
    addi a2, a2, 4
    bltu a1, a2, 2b
    ret

    .align 12
    .section .bss.stack
    .globl _main_stack
_main_stack:
    .space 4096 * 40
    .globl _main_stack_top
_main_stack_top:

    .align 12
    .section .data
_root_page_table:
    .quad (0x00000 << 10) | 0xcf
    .quad 0
    .quad (0x80000 << 10) | 0xcf
    .zero 505 * 8
    .quad (0x00000 << 10) | 0xcf
    .quad 0
    .quad (0x80000 << 10) | 0xcf
    .quad 0