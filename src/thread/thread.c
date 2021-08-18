#include "types.h"
#include "device.h"
#include "reg.h"
#include "lib.h"
#include "trap.h"
#include "coremap.h"
#include "vm.h"
#include "thread.h"
#include "printf.h"

extern ThreadCntl_t ThreadControl;
extern CoreMapCntl_t CoreMapControl;
extern VMControl_t VmControl;
extern RegisterRoute_t RegisterAccess;

void fnThreadControlInit()
{
    ThreadControl.createContext = _createContext;
    ThreadControl.destroy = _destroy;
    ThreadControl.exec = _exec;
    ThreadControl.fork = _fork;
}

void _fork(){

}

void _exec(){

}

void _destroy(){

}

static void memcpy(uint8_t* dst, uint8_t* src, uint32_t size){
    for (int i = 0; i < size; i ++){
        *(dst + i) = *(src + i);
    }
}

uint64_t _createContext(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;
    
    uint64_t stackPa = CoreMapControl.kmalloc(&blkInf);
    uint64_t stackVa = P2V(stackPa);
    VmControl.updatePageTable(stackVa, stackPa, PT_LEVEL - 1);

    uint64_t threadContextPa = CoreMapControl.kmalloc(&blkInf);
    uint64_t threadContextVa = P2V(threadContextPa);
    VmControl.updatePageTable(threadContextVa, threadContextPa, PT_LEVEL - 1);
    
    ThreadContextContent_t* pContextContent = (ThreadContextContent_t*)((uint8_t*)threadContextVa + _sizeof(Thread_t));

extern void __trap_exit();

    pContextContent->ra = (uint64_t)__trap_exit;
    pContextContent->tf.gpr[2] = stackVa + PAGE_SIZE;

extern void testFunc();
    pContextContent->tf.sSepc = (uint64_t)testFunc;

    uint64_t sstatus = 0;
    RegisterAccess.readSstatus(&sstatus);

    sstatus = sstatus | (1UL << 8);
    sstatus = sstatus | (1UL << 5);
    sstatus = sstatus & ~(1UL << 1);

    pContextContent->tf.sStatus = sstatus;

    uint8_t* ptr = (uint8_t*)(stackVa - _sizeof(ThreadContextContent_t));

    memcpy(ptr, (uint8_t*)pContextContent, _sizeof(ThreadContextContent_t));

    Thread_t* pThread = (Thread_t*)threadContextVa;

    pThread->context = (uint64_t)ptr;
    pThread->stackVa = stackVa;
  
extern void __switchTo(uint64_t a, uint64_t b);

    uint64_t currentContextPa = CoreMapControl.kmalloc(&blkInf);
    uint64_t currentContextVa = P2V(currentContextPa);
    VmControl.updatePageTable(currentContextVa, currentContextPa, PT_LEVEL - 1);
   
    VmControl.ptClone(&pContextContent->satp);

    __switchTo((uint64_t)&currentContextVa, (uint64_t)&ptr);
}



uint64_t _createContextLegacy(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;
    
    uint64_t stackPa = CoreMapControl.kmalloc(&blkInf);
    uint64_t stackVa = P2V(stackPa);
    VmControl.updatePageTable(stackVa, stackPa, PT_LEVEL - 1);

    uint64_t threadContextPa = CoreMapControl.kmalloc(&blkInf);
    uint64_t threadContextVa = P2V(threadContextPa);
    VmControl.updatePageTable(threadContextVa, threadContextPa, PT_LEVEL - 1);
    
    ThreadContextContent_t* pContextContent = (ThreadContextContent_t*)((uint8_t*)threadContextVa + _sizeof(Thread_t));

extern void __trap_exit();

    pContextContent->ra = (uint64_t)__trap_exit;

    uint64_t satp = 0;
    RegisterAccess.readStap(&satp);

    pContextContent->satp = satp;
    pContextContent->tf.gpr[2] = stackVa + PAGE_SIZE;

extern void testFunc();
    pContextContent->tf.sSepc = (uint64_t)testFunc;

    uint64_t sstatus = 0;
    RegisterAccess.readSstatus(&sstatus);

    sstatus = sstatus | (1UL << 8);
    sstatus = sstatus | (1UL << 5);
    sstatus = sstatus & ~(1UL << 1);

    pContextContent->tf.sStatus = sstatus;

    uint8_t* ptr = (uint8_t*)(stackVa - _sizeof(ThreadContextContent_t));

    memcpy(ptr, (uint8_t*)pContextContent, _sizeof(ThreadContextContent_t));

    Thread_t* pThread = (Thread_t*)threadContextVa;

    pThread->context = (uint64_t)ptr;
    pThread->stackVa = stackVa;

extern void __switchTo(uint64_t a, uint64_t b);

    uint64_t currentContextPa = CoreMapControl.kmalloc(&blkInf);
    uint64_t currentContextVa = P2V(currentContextPa);
    VmControl.updatePageTable(currentContextVa, currentContextPa, PT_LEVEL - 1);

    __switchTo((uint64_t)&currentContextVa, (uint64_t)&ptr);

}

void testFunc(){
    printf("Hello World\n");
    while(1);
}