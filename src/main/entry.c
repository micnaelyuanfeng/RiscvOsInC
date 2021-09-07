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
#include "ringbuffer.h"
#include "printf.h"
#include "hart.h"

extern uint8_t PrintBuf[];
extern bool procecedLock;

extern HartInfo_t HartInstance[];
extern HartInfo_t* pHart0;
extern HartInfo_t* pHart1;
extern HartInfo_t* pHart0Daemon;

static void memcpy(uint8_t* dst, uint8_t* src, uint32_t sizeInBytes){
    for (uint32_t i = 0; i < sizeInBytes; i++){
        *(dst + i) = *(src + i);
    }
}


void kentry(uint64_t _hid){

extern void fnEntry();
    if(_hid == 1) fnEntry();
    
    pHart0 = &HartInstance[_hid];
    pHart0Daemon = pHart0;

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
    // fnTimerInit(_hid);
    // fnInterruptTest();
    // pHart0->VmControl.ptAllocAndMapCbMem();

    // memcpy((uint8_t*)pHartInstance, (uint8_t*)HartInstance, _sizeof(HartInfo_t));

    // memcpy((uint8_t*)&((HartInfo_t*)pHartInstance)[1], (uint8_t*)HartInstance, _sizeof(HartInfo_t));

    memcpy((uint8_t*)&HartInstance[1], (uint8_t*)HartInstance, _sizeof(HartInfo_t));
    
    pHart1 = &HartInstance[1];

    fnRbInit();

    fnGreetingPrint();
    
    // printf("Hart 1 initialization Compelete\n");
    
    procecedLock = true;

    int i = 0;
    while ( i < 100000000){
        i = i + 1;
    }

    // register unsigned int id asm("x17") = 0x4;
    // register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
    // asm __volatile__("ecall");

extern void fnSubmitCommand();    
    while(1){
        int i = 0;
        // while (i < 500000000) i = i + 1;
        
        // printf("Send ipi from hart %d\n", _hid);
        uint64_t hid = 0b10;
        acquireCbLock();
        // fnSubmitCommand();
        
        // if(!fnRbSubmit()) printf("submit failed\n");
        // // releaseLock();
        register unsigned int id asm("x17") = 0x4;
        register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        asm __volatile__("ecall");
        while (i < 100000000) i = i + 1;
        // releaseLock();
        releaseCbLock();
    }
}
