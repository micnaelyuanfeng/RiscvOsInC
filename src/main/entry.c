#include "types.h"
#include "lib.h"
#include "device.h"
#include "reg.h"
#include "debug.h"
#include "trap.h"
#include "handlers.h"
#include "coremap.h"
#include "vm.h"
#include "thread.h"
#include "printf.h"

extern uint8_t PrintBuf[];
extern VMControl_t VmControl;
extern ThreadCntl_t ThreadControl;
extern bool sharelock;
/**
 * All funtins aruments passphrease use
 * x^2 + y^2 = 4
*/

void kentry(uint64_t _hid){
    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
    fnRegisterAccessInit();
extern void kentry2();
    if(_hid == 1) kentry2(_hid);
    // fnCoremap_init();
    // fnVmInit();
    // fnBuildRootPageTable();

    // fnTrapInit();
    // fnThreadControlInit();

    // fnTimerInit();
    // fnMallocTest();
    // fnFreeTest();
    // fnInterruptTest();

    // fnMallocMapTest();
    
    // fnGreetingPrint();
    
    while(1)printf("%d ", _hid);
}

void kentry2(uint64_t _hid){
    while(!sharelock) printf("%d ", _hid);
}


