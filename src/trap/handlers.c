#include "types.h"
#include "reg.h"
#include "device.h"
#include "trap.h"
#include "printf.h"
#include "handlers.h"

extern RegisterRoute_t RegisterAccess;
extern uint64_t cycle;

void _handlerEbp(void* _tf){
    ((Trapframe_t*)_tf)->sSepc += 4;
}

// void __handlerSysCall(void* _tf, ...){

// }

uint64_t counter = 0;

void _handlerSupervisorTimer(void* _tf){
    RegisterAccess.readCcyle(&cycle);

    if (counter == 500000){
        printf("Timer Interrupt\n");
        counter = 0;
    }
    counter += 1;

    fnSetTimerInterval();
}