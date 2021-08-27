#include "types.h"
#include "device.h"
#include "sbi.h"
#include "reg.h"
#include "printf.h"
#include "hart.h"

// extern RegisterRoute_t RegisterAccess;
// extern DeviceTimer_t TimerControl;
extern HartInfo_t* pHart0;

void fnTimerInit(){
    pHart0->TimerControl._enableTimerIntr = fnEnableTimerIntr;
    pHart0->TimerControl._addTick = fnAddTick;
    pHart0->TimerControl._clearTick = fnClearTick;
    pHart0->TimerControl.tick = 0;

    pHart0->TimerControl._enableTimerIntr();
}

void fnSetTimerInterval(){

    register uint64_t eid asm("x17") = 0 ;
    register uint64_t arg0 asm("x10") = pHart0->TimerControl.cycle + TIMER_BASE;
    register uint64_t arg1 asm("x11") = 0;
    register uint64_t arg2 asm("x12") = 0;

    __asm__ volatile (
        "ecall"  
    );
}

void fnEnableTimerIntr(){
    uint64_t enableTimerIntrBit = 1 << 5;

    uint64_t sieValue = 0;
    
    pHart0->RegisterAccess.readSie(&sieValue);

    sieValue |= enableTimerIntrBit;
    pHart0->RegisterAccess.writeSie(sieValue);

    pHart0->RegisterAccess.readCcyle(&pHart0->TimerControl.cycle);

    fnSetTimerInterval();
}

void fnAddTick(){

}

void fnClearTick(){

}
