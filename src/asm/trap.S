.altmacro

.set REG_WIDTH, 8
.set CONTEXT_SZ, 36

.macro SAVE reg, stack_offset
    sd \reg, \stack_offset*REG_WIDTH(sp) 
.endm

.macro LOAD reg, stack_offset
    ld \reg, \stack_offset*REG_WIDTH(sp) 
.endm

    .section .text.trap
    .globl __trap_enter
    .align 16
__trap_enter:
    # sp <-> sscratch
    csrrw sp, sscratch, sp

    bnez sp, __user_level

__kernel_level:

    # if sscratch was zero, just use the old sp value (which was kernel stack)
    csrr sp, sscratch

__user_level:
    addi sp, sp, -CONTEXT_SZ*REG_WIDTH
    
    # x0 = 0 and no need to save
    # x2 => sp

    SAVE x1, 1
    SAVE x3, 3
    SAVE x4, 4
    SAVE x5, 5
    SAVE x6, 6
    SAVE x7, 7
    SAVE x8, 8
    SAVE x9, 9
    SAVE x10, 10
    SAVE x11, 11
    SAVE x12, 12
    SAVE x13, 13
    SAVE x14, 14
    SAVE x15, 15
    SAVE x16, 16
    SAVE x17, 17
    SAVE x18, 18
    SAVE x19, 19
    SAVE x20, 20
    SAVE x21, 21
    SAVE x22, 22
    SAVE x23, 23
    SAVE x24, 24
    SAVE x25, 25
    SAVE x26, 26
    SAVE x27, 27
    SAVE x28, 28
    SAVE x29, 29
    SAVE x30, 30
    SAVE x31, 31

    csrrw s0, sscratch, x0

    csrr s1, sstatus
    csrr s2, sepc
    csrr s3, stval
    csrr s4, scause

    SAVE s0, 2
    SAVE s1, 32
    SAVE s2, 33
    SAVE s3, 34
    SAVE s4, 35

    mv a0, sp
    jal fnDispatchInterrupt


    .section .text.trap
    .globl __trap_exit
    .align 16
__trap_exit:

    LOAD s1, 32

    LOAD s2, 33

    andi s0, s1, 1 << 8
    bnez s0, _ret_to_kernel
_ret_to_user:


    addi s0, sp, CONTEXT_SZ*REG_WIDTH
    csrw sscratch, s0

_ret_to_kernel:

    csrw sstatus, s1
    csrw sepc, s2

    LOAD x1, 1
    LOAD x3, 3
    LOAD x4, 4
    LOAD x5, 5
    LOAD x6, 6
    LOAD x7, 7
    LOAD x8, 8
    LOAD x9, 9
    LOAD x10, 10
    LOAD x11, 11
    LOAD x12, 12
    LOAD x13, 13
    LOAD x14, 14
    LOAD x15, 15
    LOAD x16, 16
    LOAD x17, 17
    LOAD x18, 18
    LOAD x19, 19
    LOAD x20, 20
    LOAD x21, 21
    LOAD x22, 22
    LOAD x23, 23
    LOAD x24, 24
    LOAD x25, 25
    LOAD x26, 26
    LOAD x27, 27
    LOAD x28, 28
    LOAD x29, 29
    LOAD x30, 30
    LOAD x31, 31

    LOAD x2, 2

    sret #pc = sepc