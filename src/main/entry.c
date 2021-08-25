#include "types.h"
#include "lib.h"
#include "device.h"
#include "reg.h"
#include "debug.h"
#include "trap.h"
#include "handlers.h"
#include "coremap.h"
#include "vm.h"
#include "lock.h"
#include "thread.h"
#include "process.h"
#include "printf.h"

extern uint8_t PrintBuf[];
extern VMControl_t VmControl;
extern ThreadCntl_t ThreadControl;
extern bool procecedLock;
/**
 * All funtins aruments passphrease use
 * x^2 + y^2 = 4
*/

void kentry(uint64_t _hid){
    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
    fnRegisterAccessInit();
    fnTrapInit();
    fnCoremap_init();
    fnVmInit();
    fnBuildRootPageTable();
    
    VmControl.ptAllocAndMapCbMem();
extern void fnEntry();
    if(_hid == 1) fnEntry();

    
    // fnThreadControlInit();
    
    // fnTimerInit();
    // fnMallocTest();
    // fnFreeTest();
    // fnInterruptTest();

    // fnMallocMapTest();
    
    // fnGreetingPrint();
    // acquireLock();
    printf("Hart 1 initialization Compelete\n");
    procecedLock = true;
    
    while(1){
        int i = 0;
        while (i < 500000000) i = i + 1;
        
        printf("Send ipi from hart %d\n", _hid);
        uint64_t hid = 0b10;
        
        acquireLock();
        fnSubmitCommand();
        releaseLock();

        register unsigned int id asm("x17") = 0x4;
        register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        asm __volatile__("ecall");
        // while (i < 1000000000) i = i + 1;
        // releaseLock();
    }
}
