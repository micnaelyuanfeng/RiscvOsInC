#include "types.h"
#include "device.h"
#include "sbi.h"
#include "reg.h"
#include "printf.h"

extern RegisterRoute_t RegisterAccess;

uint64_t cycle;

void fnTimerInit(){
    fnEnableTimerIntr();
}

void fnSetTimerInterval(){

    RegisterAccess.readCcyle(&cycle);

    register uint64_t eid asm("x17") = __SBI_REQ_SET_TIMER ;
    register uint64_t arg0 asm("x10") = cycle + TIMER_BASE;
    register uint64_t arg1 asm("x11") = 0;
    register uint64_t arg2 asm("x12") = 0;

    __asm__ volatile (
        "ecall"  
    );
}

void fnEnableTimerIntr(){
    uint64_t enableTimerIntrBit = 0xFF;

    uint64_t sieValue = 0;
    
    RegisterAccess.readSie(&sieValue);

    sieValue |= enableTimerIntrBit;
    RegisterAccess.writeSie(sieValue);

    fnSetTimerInterval();
}

// void _clearTick(){

// }

// void _addTick(){

// }

// uint64_t _getTick(){

// }

// uint64_t _getCyle(){

// }