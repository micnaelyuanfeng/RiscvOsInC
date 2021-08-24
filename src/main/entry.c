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
    
extern void kentry2();
    if(_hid == 1) kentry2(_hid);

    fnCoremap_init();
    fnVmInit();
    fnBuildRootPageTable();
    fnThreadControlInit();
    fnTrapInit();
    // fnTimerInit();
    fnMallocTest();
    fnFreeTest();
    // fnInterruptTest();

    fnMallocMapTest();
    
    fnGreetingPrint();

    printf("Hart 1 initialization Compelete\n");

    procecedLock = true;
    
    while(1){
        // acquireLock();
        // printf("Get Lock %d\n", _hid);
        // int i = 0;
        // while (i < 1000000000) i = i + 1;
        printf("Enter wfi\n");
        wfi();
        printf("Wake Up\n");
        uint64_t hid = 0b10;
        register unsigned int id asm("x17") = 0x4;
        register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        asm __volatile__("ecall");
        // releaseLock();
    }
}

void kentry2(uint64_t _hid){
    while (!procecedLock);

    printf("Hart 2 Start Executing\n");

    while(1){
        // acquireLock();
        // printf("Get Lock %d\n", _hid);
        int i = 0;
        printf("Send ipi from hart %d\n", _hid);
        uint64_t hid = 0b01;
        register unsigned int id asm("x17") = 0x4;
        register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        asm __volatile__("ecall");
        while (i < 1000000000) i = i + 1;
        // releaseLock();
    } 
}


