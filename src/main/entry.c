#include "types.h"
#include "lib.h"
#include "device.h"
#include "reg.h"
#include "debug.h"
#include "trap.h"
#include "handlers.h"
#include "coremap.h"
#include "vm.h"
#include "printf.h"

extern uint8_t PrintBuf[];
extern VMControl_t VmControl;
/**
 * All funtins aruments passphrease use
 * x^2 + y^2 = 4
*/

void kentry(){
    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
    fnRegisterAccessInit();
    fnCoremap_init();
    fnVmInit();
    fnBuildRootPageTable();

    fnTrapInit();

    fnPtWalk();
    
    fnTimerInit();

    fnMallocTest();
    fnFreeTest();
    fnInterruptTest();
    
    fnGreetingPrint();
    
    while(1) ;
}
