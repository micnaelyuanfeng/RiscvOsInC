.equ REG_WIDTH, 8 #register width
.equ THREAD_CTX_SIZE_IN_QWORD, 14

.macro SAVE reg, addr
    sd \reg, \addr*REG_WIDTH(sp) 
.endm

.macro LOAD reg, addr
    ld \reg, \addr*REG_WIDTH(sp) 
.endm

    .section .text
    .global __switchTo
__switchTo:

    addi sp, sp, -THREAD_CTX_SIZE_IN_QWORD*REG_WIDTH
    sd sp, 0(a0)

    SAVE ra, 0
    SAVE s0, 2
    SAVE s1, 3
    SAVE s2, 4
    SAVE s3, 5
    SAVE s4, 6
    SAVE s5, 7
    SAVE s6, 8
    SAVE s7, 9
    SAVE s8, 10
    SAVE s9, 11
    SAVE s10, 12
    SAVE s11, 13

    csrr s11, satp

    SAVE s11, 1

    ld sp, 0(a1)

    # LOAD s11, 1

    csrw satp, s11
    sfence.vma

    LOAD ra, 0
    LOAD s0, 2
    LOAD s1, 3
    LOAD s2, 4
    LOAD s3, 5
    LOAD s4, 6
    LOAD s5, 7
    LOAD s6, 8
    LOAD s7, 9
    LOAD s8, 10
    LOAD s9, 11
    LOAD s10, 12
    LOAD s11, 13

    addi sp, sp, THREAD_CTX_SIZE_IN_QWORD*REG_WIDTH

    sd zero, 0(a1)

    ret # pc = ra



