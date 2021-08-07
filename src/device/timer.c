#include "types.h"
#include "device.h"
#include "sbi.h"
#include "reg.h"
#include "printf.h"

extern RegisterRoute_t RegisterAccess;
extern DeviceTimer_t TimerControl;

void fnTimerInit(){
    TimerControl._enableTimerIntr = fnEnableTimerIntr;
    TimerControl._addTick = fnAddTick;
    TimerControl._clearTick = fnClearTick;
    TimerControl.tick = 0;

    TimerControl._enableTimerIntr();
}

void fnSetTimerInterval(){

    register uint64_t eid asm("x17") = 0 ;
    register uint64_t arg0 asm("x10") = TimerControl.cycle + TIMER_BASE;
    register uint64_t arg1 asm("x11") = 0;
    register uint64_t arg2 asm("x12") = 0;

    __asm__ volatile (
        "ecall"  
    );
}

void fnEnableTimerIntr(){
    uint64_t enableTimerIntrBit = 1 << 5;

    uint64_t sieValue = 0;
    
    RegisterAccess.readSie(&sieValue);

    sieValue |= enableTimerIntrBit;
    RegisterAccess.writeSie(sieValue);

    RegisterAccess.readCcyle(&TimerControl.cycle);

    fnSetTimerInterval();
}

void fnAddTick(){

}

void fnClearTick(){

}
