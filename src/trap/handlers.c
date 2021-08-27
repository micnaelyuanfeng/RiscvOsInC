#include "types.h"
#include "reg.h"
// #include "device.h"
// #include "trap.h"
#include "printf.h"
#include "handlers.h"
#include "hart.h"

// extern RegisterRoute_t RegisterAccess;
// extern DeviceTimer_t TimerControl;

extern HartInfo_t* pHart0;

static inline void _clearSuperVisorSoftwareIntr(){
    uint64_t sip;

    pHart0->RegisterAccess.readSip(&sip);
    // rs64RegReadSip(&sip);
    sip &= ~(1UL << 1UL);//clear ssip
    // rs64RegWriteSip(sip);
    pHart0->RegisterAccess.writeSip(sip);
}

void _handlerEbp(void* _tf, ...){
    ((Trapframe_t*)_tf)->sSepc += 2;
}

void _handlerSupervisorTimer(void* _tf, ...){
    pHart0->RegisterAccess.readCcyle(&pHart0->TimerControl.cycle);
 
    if (pHart0->TimerControl.tick == 100) pHart0->TimerControl.tick = 0;
  
    pHart0->TimerControl.tick += 1;
    
    fnSetTimerInterval();
}

void _handlerSupervisorSoftInt(void* _tf, ...){
    _clearSuperVisorSoftwareIntr();
    printf("Receive Software Interrupt, and clear\n");
}
