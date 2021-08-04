#include "types.h"
#include "device.h"
#include "sbi.h"
#include "reg.h"
#include "printf.h"

extern RegisterRoute_t RegisterAccess;

void fnTimerInit(){
    fnEnableTimerIntr();
}

void fnSetTimerInterval(uint64_t _val){
    register uint64_t eid asm("x17") = 0 ;
    register uint64_t arg1 asm("x16") = 0;
    register uint64_t arg0 asm("x10") = _val;
    

    __asm__ volatile ("ecall");
}

void fnEnableTimerIntr(){
    uint64_t enableTimerIntrBit = 1 << 5;

    uint64_t sieValue = 0;
    
    RegisterAccess.readSie(&sieValue);

    sieValue |= enableTimerIntrBit;
    RegisterAccess.writeSie(enableTimerIntrBit);

    uint64_t cycles = 0;

    RegisterAccess.readCcyle(&cycles);

    fnSetTimerInterval(cycles + TIMER_BASE);
}

// void _clearTick(){

// }

// void _addTick(){

// }

// uint64_t _getTick(){

// }

// uint64_t _getCyle(){

// }