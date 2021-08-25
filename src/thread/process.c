#include "types.h"
#include "lock.h"
#include "device.h"
#include "process.h"
#include "printf.h"

extern bool procecedLock;

void fnMapGlobalMemInit(){

}

void fnMapGlobalMemWrite(){

}

void fnMapGlobalMemRead(){

}


void fnLockMemoryWrite(){

}

void fnLockMemoryRead(){

}

void fnEntry(){
    while (!procecedLock);

    printf("Hart 2 Start Executing\n");

    while(1){
        // acquireLock();
        // printf("%d ", _hid);
        // printf("Enter wfi\n");
        wfi();
        // printf("Wake Up\n");
        int i = 0;
        // printf("Send ipi from hart %d\n", _hid);
        // uint64_t hid = 0b01;
        // register unsigned int id asm("x17") = 0x4;
        // register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        // asm __volatile__("ecall");
        // while (i < 1000000000) i = i + 1;
        acquireLock();
        fnReadCommand();
        releaseLock();
    } 
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