#include "types.h"
#include "reg.h"
#include "lock.h"
#include "device.h"
#include "vm.h"
#include "process.h"
#include "hart.h"
#include "printf.h"

extern HartInfo_t HartInstance[];
extern HartInfo_t* pHart1;
extern HartInfo_t* pHart0;
extern HartInfo_t* pHart0Daemon;
extern uint64_t satp;
extern bool procecedLock;

uint64_t newPtSatp __attribute__((section (".extdata")));
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

void fnDbgPrint() __attribute__((section (".extcode")));
void fnDbgPrint(){
    register uint64_t eid __asm__("x17") = 1;
    register uint64_t __ch __asm__("x10") = 80; 
    __asm__ volatile (
        "ecall"
    );
}

static void memcpy(uint8_t* dst, uint8_t* src, uint32_t sizeInBytes)__attribute__((section (".extcode")));
void memcpy(uint8_t* dst, uint8_t* src, uint32_t sizeInBytes){
    for (uint32_t i = 0; i < sizeInBytes; i++){
        *(dst + i) = *(src + i);
    }
}

extern uint8_t PrintBuf[];

void fnEntry() __attribute__((section (".extcode")));
void fnEntry(){
    while (!procecedLock);

    uint64_t cycle = 0;

    pHart0Daemon->RegisterAccess.readCcyle(&cycle);
    pHart1->RegisterAccess.readCcyle(&cycle);

    pHart0Daemon->ThreadControl.fork();
    
    printf("satp is 0x%x%x\n", satp >> 32, satp);
    

    // fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    // fnUartHwInit();
    // printf("Value: %x%x\n", newPtSatp >> 32, newPtSatp);
    // fnBuildPtForOtherThread(0b10); //bug4 pt updated, but empty physical memory

    __asm__ volatile (
        "csrw satp, %0"
        :
        : "r"(satp)
        :"memory"
    );

    __asm__ volatile (
        "sfence.vma"
    );

    // fnMapGlobalMemInit();
    // fnBuildPtForOtherThread(0b10); //Bug1 range is not correct for the other hart  Bug2 Bug3
    fnDbgPrint();
    // printf("Hart 2 Start Executing\n");


    
    
        // acquireLock();
        // printf("%d ", _hid);
        // printf("Enter wfi\n");
        // wfi();
        // printf("Wake Up\n");
    
        // printf("Send ipi from hart %d\n", _hid);
        // uint64_t hid = 0b01;
        // register unsigned int id asm("x17") = 0x4;
        // register unsigned int hart_mask asm("x10") = (uint64_t)&hid;
        // asm __volatile__("ecall");
        // while (i < 1000000000) i = i + 1;
        // acquireLock();
        // fnReadCommand();
        // releaseLock();
    while(1){
        for(int i = 0 ; i < 100; i++){
            ringBuffer[i] = 0xDEADBEEF;
        }
    }
}

void fnSubmitCommand(){
    uint64_t* pCmdBuffer = (uint64_t*)pCommandQueueMem;

    for(int i = 0; i < 50; i++){
        pCmdBuffer[i] = 0xDEADBEEF;
    }
}

void fnReadCommand(){
    uint64_t* pCmdBuffer = (uint64_t*)pCommandQueueMem;

    for(int i = 0; i < 512; i++){
        printf("0x%x ", pCmdBuffer[i]);
    }
}