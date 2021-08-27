#ifndef _HART_H_
#define _HART_H_

#include "coremap.h"
#include "vm.h"
#include "trap.h"
#include "thread.h"
#include "device.h"

#define NUM_OF_HART 8

typedef struct HartInfo{
    RegisterRoute_t RegisterAccess;
    CoreMapCntl_t CoreMapControl;
    DeviceTimer_t TimerControl;
    VMControl_t VmControl;
    ThreadCntl_t ThreadControl;
    DeviceRingBuf_t CmdRingMem;
    
}HartInfo_t;

#endif