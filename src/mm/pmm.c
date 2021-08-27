#include "types.h"
#include "reg.h"
#include "printf.h"
#include "coremap.h"
#include "vm.h"
#include "hart.h"

// extern RegisterRoute_t RegisterAccess;
// extern CoreMapCntl_t CoreMapControl;

extern HartInfo_t* pHart0;

void fnCoremap_init(){
    pHart0->CoreMapControl.coremapDump = __coremapDump;
    pHart0->CoreMapControl.coremapInit = __coremapInit;
    pHart0->CoreMapControl.kfree = __kfree;
    pHart0->CoreMapControl.kmalloc = __kmalloc;

    pHart0->CoreMapControl.coremapInit();
    // printf("|=============================$!\n");
    // printf("|====>    Physical Memory Info\n");
    // printf("|====>      Kernel Start Addr is 0x%x\n", CoreMapControl.kernelStartAddr);
    // printf("|====>      Kernel End Addr is 0x%x\n", CoreMapControl.kernelEndAddr);
    // printf("|====>      Coremap Start Addr is 0x%x\n", CoreMapControl.coremapStartAddr);
    // printf("|====>      Coremap Capacity is %d\n", CoreMapControl.coremapCapacityInPageSize);
    // printf("|=============================$!\n");
}

void __coremapInit(){
    extern void __KernelStartAddr();
    extern void __KernelEndAddr();

    pHart0->CoreMapControl.kernelStartAddr = (uint64_t)__KernelStartAddr;
    pHart0->CoreMapControl.kernelEndAddr = (uint64_t)__KernelEndAddr;
    pHart0->CoreMapControl.coremapStartAddr = ((uint64_t)__KernelEndAddr + PAGE_SIZE) & 0x00000000FFFFFFFF;
    pHart0->CoreMapControl.coremapCapacityInPageSize = (uint64_t) (256 << 20) / PAGE_SIZE - 1;
    pHart0->CoreMapControl.pageUsed = 0;
}

uint64_t __kmalloc(void* info, ...){
    uint64_t memAddr = 0;

    if (pHart0->CoreMapControl.pageUsed >= pHart0->CoreMapControl.coremapCapacityInPageSize){
        __asm__ volatile (
            "ebreak" // trigger an exception
        );
    }else{
        CoreMemBlkInfo_t* pInfo = (CoreMemBlkInfo_t*)info;

        memAddr = pHart0->CoreMapControl.coremapStartAddr + (pHart0->CoreMapControl.pageUsed << 12);
    
        pHart0->CoreMapControl.pageUsed += pInfo->numOfPage;
    }

    return memAddr;
}

void __kfree(void* info, ...){
    if(pHart0->CoreMapControl.pageUsed == 0){
        __asm__ volatile (
            "ebreak" // trigger an exception
        );
    }else{
        CoreMemBlkInfo_t* pInfo = (CoreMemBlkInfo_t*)info;

        if(pInfo->numOfPage > pHart0->CoreMapControl.pageUsed){
            __asm__ volatile (
                "ebreak"
            );
        }else{
            pHart0->CoreMapControl.pageUsed -= pInfo->numOfPage;
        }
    }
}

void __coremapDump(){

}

void __freelistMgnt(){

}

void fnMallocTest(){
    printf("|=============================$!\n");
    printf("|====>    Malloc Test Starts\n");
    CoreMemBlkInfo_t blkInfo;

    blkInfo.numOfPage = 1;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.kmalloc(&blkInfo));
    blkInfo.numOfPage++;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.kmalloc(&blkInfo));
    blkInfo.numOfPage++;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.kmalloc(&blkInfo));
    blkInfo.numOfPage++;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.kmalloc(&blkInfo));
    printf("|====>    Malloc Test Ends\n");
}

void fnFreeTest(){
    printf("|=============================$!\n");
    printf("|====>    Free Test Starts\n");
    CoreMemBlkInfo_t blkInfo;

    blkInfo.numOfPage = 1;
    pHart0->CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.coremapStartAddr + (pHart0->CoreMapControl.pageUsed << 12));
    blkInfo.numOfPage++;
    pHart0->CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.coremapStartAddr + (pHart0->CoreMapControl.pageUsed << 12));
    blkInfo.numOfPage++;
    pHart0->CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.coremapStartAddr + (pHart0->CoreMapControl.pageUsed << 12));
    blkInfo.numOfPage++;
    pHart0->CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, pHart0->CoreMapControl.coremapStartAddr + (pHart0->CoreMapControl.pageUsed << 12));
    printf("|====>    Free Test Starts\n");
    printf("|=============================$!\n");
}