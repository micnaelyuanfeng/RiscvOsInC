#include "types.h"
#include "device.h"
#include "reg.h"
#include "lib.h"
#include "trap.h"
#include "coremap.h"
#include "vm.h"
#include "thread.h"
#include "bin.h"
#include "printf.h"
#include "hart.h"

extern HartInfo_t* pHart0;
extern HartInfo_t* pHart1;
extern uint64_t satp;

void fnThreadControlInit(){
    pHart0->ThreadControl.destroy = _destroy;
    pHart0->ThreadControl.exec = _exec;
    pHart0->ThreadControl.fork = _fork;
}

static void memcpy(uint8_t* dst, uint8_t* src, uint32_t size){
    for (int i = 0; i < size; i ++){
        *(dst + i) = *(src + i);
    }
}

void _fork(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;
    
    uint64_t stackPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t stackVa = P2V(stackPa);
    pHart0->VmControl.updatePageTable(stackVa, stackPa, PT_LEVEL - 1);

    uint64_t threadContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t threadContextVa = P2V(threadContextPa);
    pHart0->VmControl.updatePageTable(threadContextVa, threadContextPa, PT_LEVEL - 1);
    
    ThreadContextContent_t* pContextContent = (ThreadContextContent_t*)((uint8_t*)threadContextVa + _sizeof(Thread_t));

extern void __trap_exit();

    pContextContent->ra = (uint64_t)__trap_exit;
    pContextContent->tf.gpr[2] = stackVa + PAGE_SIZE;

    uint32_t codeSizeInPage = 0; 
    if (UCODE_SIZE > 0) codeSizeInPage = (UCODE_SIZE <= PAGE_SIZE) ? 1 : ((UCODE_SIZE / PAGE_SIZE) + 1);

    uint32_t dataSizeInPage = 0;
    if (UDATA_SIZE > 0) dataSizeInPage = (UDATA_SIZE <= PAGE_SIZE) ? 1 : ((UDATA_SIZE / PAGE_SIZE) + 1);

    blkInf.numOfPage = UCODE_SIZE_IN_PAGE;

    uint64_t binPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t binVa = (uint64_t)BIN_START_VA;
    uint64_t binKVa = P2V(binPa);

    printf("num of page is %d\n", blkInf.numOfPage);
    uint64_t binStartVa = binVa;
    uint64_t binStartKVa = binKVa;
    uint64_t binStartPa = binPa;

    for (int i = 0; i < blkInf.numOfPage ; i++){
        pHart0->VmControl.updatePageTable(binStartVa, binStartPa, PT_LEVEL - 1);
        pHart0->VmControl.updatePageTable(binStartKVa, binStartPa, PT_LEVEL - 1);

        binStartPa += PAGE_SIZE;
        binStartVa += PAGE_SIZE;
        binStartKVa += PAGE_SIZE;
    }

    if (codeSizeInPage > 0) memcpy((uint8_t*)binKVa, (uint8_t*)UCODE, UCODE_SIZE);
    if (dataSizeInPage > 0) memcpy((uint8_t*)(binKVa + UDATA_START_VA - UCODE_START_VA), (uint8_t*)UDATA, UDATA_SIZE);

extern void testFunc();
    pContextContent->tf.sSepc = (uint64_t)UCODE_ENTRY_ADDR;

    uint64_t sstatus = 0;
    pHart0->RegisterAccess.readSstatus(&sstatus);

    sstatus = sstatus | (1UL << 8);
    sstatus = sstatus | (1UL << 5);
    sstatus = sstatus & ~(1UL << 1);

    pContextContent->tf.sStatus = sstatus;

    uint8_t* ptr = (uint8_t*)(pContextContent->tf.gpr[2] - _sizeof(ThreadContextContent_t));

    Thread_t* pThread = (Thread_t*)threadContextVa;

    pThread->context = (uint64_t)ptr;
    pThread->stackVa = stackVa;

extern void __switchTo(uint64_t a, uint64_t b);

    uint64_t currentContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t currentContextVa = P2V(currentContextPa);
    pHart0->VmControl.updatePageTable(currentContextVa, currentContextPa, PT_LEVEL - 1);

    uint64_t thread2ContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t thread2ContextVa = P2V(thread2ContextPa);
    pHart0->VmControl.updatePageTable(thread2ContextVa, thread2ContextPa, PT_LEVEL - 1);

    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[10] = thread2ContextVa;
    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[11] = threadContextVa;
    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[12] = 0;

    pHart0->VmControl.ptClone(&pContextContent->satp);

    memcpy(ptr, (uint8_t*)pContextContent, _sizeof(ThreadContextContent_t));

    satp = pContextContent->satp;

    printf("~~~~~~~~ start logging ~~~~~~~~\n");

    __switchTo((uint64_t)&((Thread_t*)thread2ContextVa)->context, (uint64_t)&ptr);
}

void _exec(){

}

void _destroy(){

}

uint64_t _createContext(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;
    
    uint64_t stackPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t stackVa = P2V(stackPa);
    pHart0->VmControl.updatePageTable(stackVa, stackPa, PT_LEVEL - 1);

    uint64_t threadContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t threadContextVa = P2V(threadContextPa);
    pHart0->VmControl.updatePageTable(threadContextVa, threadContextPa, PT_LEVEL - 1);
    
    ThreadContextContent_t* pContextContent = (ThreadContextContent_t*)((uint8_t*)threadContextVa + _sizeof(Thread_t));

extern void __trap_exit();

    pContextContent->ra = (uint64_t)__trap_exit;
    pContextContent->tf.gpr[2] = stackVa + PAGE_SIZE;

    uint64_t binPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t binVa = (uint64_t)BIN_START_VA;
    uint64_t binKVa = P2V(binPa);

    pHart0->VmControl.updatePageTable(binVa, binPa, PT_LEVEL - 1);
    pHart0->VmControl.updatePageTable(binKVa, binPa, PT_LEVEL - 1);
  
    memcpy((uint8_t*)binKVa, (uint8_t*)UCODE, 120);

extern void testFunc();
    pContextContent->tf.sSepc = (uint64_t)binVa;

    uint64_t sstatus = 0;
    pHart0->RegisterAccess.readSstatus(&sstatus);

    sstatus = sstatus | (1UL << 8);
    sstatus = sstatus | (1UL << 5);
    sstatus = sstatus & ~(1UL << 1);

    pContextContent->tf.sStatus = sstatus;

    uint8_t* ptr = (uint8_t*)(pContextContent->tf.gpr[2] - _sizeof(ThreadContextContent_t));

    Thread_t* pThread = (Thread_t*)threadContextVa;

    pThread->context = (uint64_t)ptr;
    pThread->stackVa = stackVa;

extern void __switchTo(uint64_t a, uint64_t b);

    uint64_t currentContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t currentContextVa = P2V(currentContextPa);
    pHart0->VmControl.updatePageTable(currentContextVa, currentContextPa, PT_LEVEL - 1);

    uint64_t thread2ContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t thread2ContextVa = P2V(thread2ContextPa);
    pHart0->VmControl.updatePageTable(thread2ContextVa, thread2ContextPa, PT_LEVEL - 1);

    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[10] = thread2ContextVa;
    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[11] = threadContextVa;
    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[12] = 0;

    pHart0->VmControl.ptClone(&pContextContent->satp);

    memcpy(ptr, (uint8_t*)pContextContent, _sizeof(ThreadContextContent_t));

    __switchTo((uint64_t)&((Thread_t*)thread2ContextVa)->context, (uint64_t)&ptr);
}

uint64_t _createContextLegacy(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;
    
    uint64_t stackPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t stackVa = P2V(stackPa);
    pHart0->VmControl.updatePageTable(stackVa, stackPa, PT_LEVEL - 1);

    uint64_t threadContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t threadContextVa = P2V(threadContextPa);
    pHart0->VmControl.updatePageTable(threadContextVa, threadContextPa, PT_LEVEL - 1);
    
    ThreadContextContent_t* pContextContent = (ThreadContextContent_t*)((uint8_t*)threadContextVa + _sizeof(Thread_t));

extern void __trap_exit();

    pContextContent->ra = (uint64_t)__trap_exit;

    uint64_t satp = 0;
    pHart0->RegisterAccess.readStap(&satp);

    pContextContent->satp = satp;
    pContextContent->tf.gpr[2] = stackVa + PAGE_SIZE;

extern void testFunc();
    pContextContent->tf.sSepc = (uint64_t)testFunc;

    uint64_t sstatus = 0;
    pHart0->RegisterAccess.readSstatus(&sstatus);

    sstatus = sstatus | (1UL << 8);
    sstatus = sstatus | (1UL << 5);
    sstatus = sstatus & ~(1UL << 1);

    pContextContent->tf.sStatus = sstatus;

    uint8_t* ptr = (uint8_t*)(pContextContent->tf.gpr[2] - _sizeof(ThreadContextContent_t));

    memcpy(ptr, (uint8_t*)pContextContent, _sizeof(ThreadContextContent_t));

    Thread_t* pThread = (Thread_t*)threadContextVa;

    pThread->context = (uint64_t)ptr;
    pThread->stackVa = stackVa;

extern void __switchTo(uint64_t a, uint64_t b);

    uint64_t currentContextPa = pHart0->CoreMapControl.kmalloc(&blkInf);
    uint64_t currentContextVa = P2V(currentContextPa);
    pHart0->VmControl.updatePageTable(currentContextVa, currentContextPa, PT_LEVEL - 1);

    __switchTo((uint64_t)&currentContextVa, (uint64_t)&ptr);

}

void fnTestAppendArguments(uint64_t _fromThread, uint64_t _toThread, uint64_t _ptrArgs){
    Thread_t* pThread = (Thread_t*) _toThread;

    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[10] = _fromThread;
    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[11] = _toThread;
    ((ThreadContextContent_t*)(pThread->context))->tf.gpr[12] = _ptrArgs;
}

void testFunc(uint64_t _fromThread, uint64_t _currentThread){
    printf("Hello World from Thread Function\n");

extern void __switchTo(uint64_t a, uint64_t b);

    __switchTo((uint64_t)&((Thread_t*)_currentThread)->context, (uint64_t)&((Thread_t*)_fromThread)->context);

}