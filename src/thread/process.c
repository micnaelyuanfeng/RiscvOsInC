#include "types.h"
#include "reg.h"
#include "lock.h"
#include "device.h"
#include "vm.h"
#include "process.h"
#include "bin.h"
#include "printf.h"

extern bool procecedLock;

uint64_t ringBuffer[100] __attribute__((section (".extdata")));

void fnMapGlobalMemInit() __attribute__((section (".extcode")));
void fnMapGlobalMemInit(){

}

void fnMapGlobalMemWrite() __attribute__((section (".extcode")));
void fnMapGlobalMemWrite(){

}

void fnMapGlobalMemRead() __attribute__((section (".extcode")));
void fnMapGlobalMemRead(){

}

void fnBuildCommand() __attribute__((section (".extcode")));
void fnBuildCommand(){

}

void fnLockMemoryWrite() __attribute__((section (".extcode")));
void fnLockMemoryWrite(){

}

void fnLockMemoryRead() __attribute__((section (".extcode")));
void fnLockMemoryRead(){

}

extern uint8_t PrintBuf[];

void fnEntry() __attribute__((section (".extcode")));
void fnEntry(){
    while (!procecedLock);

    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();

    printf("Hart 2 Start Executing\n");


    // fnBuildPtForOtherThread(0b10);
    
        // acquireLock();
        // printf("%d ", _hid);
        // printf("Enter wfi\n");
        // wfi();
        // printf("Wake Up\n");
    for(int i = 0 ; i < 100; i++){
        ringBuffer[i] = 0xDEADBEEF;
    }
        // printf("Send ipi from hart %d\n", _hid);
        // uint64_t hid = 0b01;
        // register unsigned int id asm("x17") = 0x4;
        // register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        // asm __volatile__("ecall");
        // while (i < 1000000000) i = i + 1;
        // acquireLock();
        // fnReadCommand();
        // releaseLock();
    
}

void fnSubmitCommand(){
    uint64_t* pCmdBuffer = (uint64_t*)pCommandQueueMem;

    for(int i = 0; i < 512; i++){
        pCmdBuffer[i] = 0xBEEFBEEF;
    }
}

void fnReadCommand(){
    uint64_t* pCmdBuffer = (uint64_t*)pCommandQueueMem;

    for(int i = 0; i < 512; i++){
        printf("0x%x ", pCmdBuffer[i]);
    }
}