#include "types.h"
#include "reg.h"
#include "device.h"
#include "trap.h"
#include "printf.h"
#include "handlers.h"

extern RegisterRoute_t RegisterAccess;

void _handlerEbp(void* _tf){
    ((Trapframe_t*)_tf)->sSepc += 4;
}

// void __handlerSysCall(void* _tf, ...){

// }

uint64_t counter = 0;

void _handlerSupervisorTimer(void* _tf, ...){
    uint64_t value = 0;
    
    RegisterAccess.readCcyle(&value);
    

    if (counter == 100){
        printf("Timer Interrupt %x\n", value);
        counter = 0;
    }
    counter += 1;
    
    // _setTimerInterval(value + TIMER_BASE);
}