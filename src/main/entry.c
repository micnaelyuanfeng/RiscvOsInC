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
#include "hart.h"

extern uint8_t PrintBuf[];
extern bool procecedLock;

extern HartInfo_t HartInstance[];
extern HartInfo_t* pHart0;

static void memcpy(uint8_t* dst, uint8_t* src, uint32_t sizeInBytes){
    for (uint32_t i = 0; i < sizeInBytes; i++){
        *(dst + i) = *(src + i);
    }
}


void kentry(uint64_t _hid){

extern void fnEntry();
    if(_hid == 1) fnEntry();

    pHart0 = &HartInstance[_hid];

    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
    fnRegisterAccessInit();
    fnTrapInit(); 
    fnCoremap_init();
    fnMallocTest();
    fnFreeTest();

    fnVmInit(_hid);
    fnBuildRootPageTable();
    fnMalloMapUtilitiesMem();
    fnMallocMapTest();
    fnThreadControlInit();
    fnTimerInit(_hid);
    fnInterruptTest();
    
    memcpy((uint8_t*)pHartInstance, (uint8_t*)HartInstance, _sizeof(HartInfo_t) * NUM_OF_HART);

    pHart0 = &((HartInfo_t*)pHartInstance)[_hid];

    uint64_t cycle = 0;

    pHart0->RegisterAccess.readCcyle(&cycle);

    // printf("cycle is %x\n", cycle);

    // printf("Root Page Table is 0x%x%x\n", pHart0->VmControl.ptVa >> 32, pHart0->VmControl.ptVa);
    // printf("Root Page Tabke is 0x%x%x\n", pHart0->VmControl.ptPa >> 32, pHart0->VmControl.ptPa);


    fnGreetingPrint();
    
    // printf("Hart 1 initialization Compelete\n");

    procecedLock = true;

extern void fnSubmitCommand();    
    while(1){
        // int i = 0;
        // while (i < 500000000) i = i + 1;
        
        // printf("Send ipi from hart %d\n", _hid);
        // uint64_t hid = 0b10;
        
        // acquireLock();
        // fnSubmitCommand();
        // releaseLock();

        // register unsigned int id asm("x17") = 0x4;
        // register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        // asm __volatile__("ecall");
        // while (i < 1000000000) i = i + 1;
        // releaseLock();
    }
}
