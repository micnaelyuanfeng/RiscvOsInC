#include "types.h"
#include "reg.h"
#include "device.h"
#include "trap.h"
#include "printf.h"
#include "handlers.h"

extern RegisterRoute_t RegisterAccess;
extern DeviceTimer_t TimerControl;

void _handlerEbp(void* _tf, ...){
    ((Trapframe_t*)_tf)->sSepc += 4;
}

void _handlerSupervisorTimer(void* _tf, ...){
    RegisterAccess.readCcyle(&TimerControl.cycle);
 
    if (TimerControl.tick == 100) TimerControl.tick = 0;
  
    TimerControl.tick += 1;
    
    fnSetTimerInterval();
}