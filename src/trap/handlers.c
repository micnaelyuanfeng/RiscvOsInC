#include "types.h"
#include "reg.h"
#include "device.h"
#include "trap.h"
#include "printf.h"
#include "handlers.h"

extern RegisterRoute_t RegisterAccess;
extern DeviceTimer_t TimerControl;

static inline void _clearSuperVisorSoftwareIntr(){
    uint64_t sip;

    RegisterAccess.readSip(&sip);
    // rs64RegReadSip(&sip);
    sip &= ~(1UL << 1UL);//clear ssip
    // rs64RegWriteSip(sip);
    RegisterAccess.writeSip(sip);
}

void _handlerEbp(void* _tf, ...){
    ((Trapframe_t*)_tf)->sSepc += 2;
}

void _handlerSupervisorTimer(void* _tf, ...){
    RegisterAccess.readCcyle(&TimerControl.cycle);
 
    if (TimerControl.tick == 100) TimerControl.tick = 0;
  
    TimerControl.tick += 1;
    
    fnSetTimerInterval();
}

void _handlerSupervisorSoftInt(void* _tf, ...){
    _clearSuperVisorSoftwareIntr();
    printf("Receive Software Interrupt, and clear\n");
}
