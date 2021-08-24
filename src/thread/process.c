#include "types.h"
#include "device.h"
#include "process.h"
#include "printf.h"

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
    while(1);
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