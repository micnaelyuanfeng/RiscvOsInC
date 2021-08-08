#include "types.h"
#include "reg.h"
#include "printf.h"
#include "coremap.h"
#include "vm.h"

extern RegisterRoute_t RegisterAccess;
extern CoreMapCntl_t CoreMapControl;

void fnCoremap_init(){
    CoreMapControl.coremapDump = __coremapDump;
    CoreMapControl.coremapInit = __coremapInit;
    CoreMapControl.kfree = __kfree;
    CoreMapControl.kmalloc = __kmalloc;

    CoreMapControl.coremapInit();
    printf("|=============================$!\n");
    printf("|====>    Physical Memory Info\n");
    printf("|====>      Kernel Start Addr is 0x%x\n", CoreMapControl.kernelStartAddr);
    printf("|====>      Kernel End Addr is 0x%x\n", CoreMapControl.kernelEndAddr);
    printf("|====>      Coremap Start Addr is 0x%x\n", CoreMapControl.coremapStartAddr);
    printf("|====>      Coremap Capacity is %d\n", CoreMapControl.coremapCapacityInPageSize);
    printf("|=============================$!\n");
}

void __coremapInit(){
    extern void __KernelStartAddr();
    extern void __KernelEndAddr();

    CoreMapControl.kernelStartAddr = (uint64_t)__KernelStartAddr;
    CoreMapControl.kernelEndAddr = (uint64_t)__KernelEndAddr;
    CoreMapControl.coremapStartAddr = (uint64_t)__KernelEndAddr + PAGE_SIZE;
    CoreMapControl.coremapCapacityInPageSize = (uint64_t) (256 << 20) / PAGE_SIZE - 1;
    CoreMapControl.pageUsed = 0;
}

uint64_t __kmalloc(void* info, ...){
    uint64_t memAddr = 0;

    if (CoreMapControl.pageUsed >= CoreMapControl.coremapCapacityInPageSize){
        __asm__ volatile (
            "ebreak" // trigger an exception
        );
    }else{
        CoreMemBlkInfo_t* pInfo = (CoreMemBlkInfo_t*)info;

        memAddr = CoreMapControl.coremapStartAddr + (CoreMapControl.pageUsed << 12);
    
        CoreMapControl.pageUsed += pInfo->numOfPage;
    }

    return memAddr;
}

void __kfree(void* info, ...){
    if(CoreMapControl.pageUsed == 0){
        __asm__ volatile (
            "ebreak" // trigger an exception
        );
    }else{
        CoreMemBlkInfo_t* pInfo = (CoreMemBlkInfo_t*)info;

        if(pInfo->numOfPage > CoreMapControl.pageUsed){
            __asm__ volatile (
                "ebreak"
            );
        }else{
            CoreMapControl.pageUsed -= pInfo->numOfPage;
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
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.kmalloc(&blkInfo));
    blkInfo.numOfPage++;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.kmalloc(&blkInfo));
    blkInfo.numOfPage++;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.kmalloc(&blkInfo));
    blkInfo.numOfPage++;
    printf("|====>      Malloc %d page(s), address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.kmalloc(&blkInfo));
    printf("|====>    Malloc Test Ends\n");
}

void fnFreeTest(){
    printf("|=============================$!\n");
    printf("|====>    Free Test Starts\n");
    CoreMemBlkInfo_t blkInfo;

    blkInfo.numOfPage = 1;
    CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.coremapStartAddr + (CoreMapControl.pageUsed << 12));
    blkInfo.numOfPage++;
    CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.coremapStartAddr + (CoreMapControl.pageUsed << 12));
    blkInfo.numOfPage++;
    CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.coremapStartAddr + (CoreMapControl.pageUsed << 12));
    blkInfo.numOfPage++;
    CoreMapControl.kfree(&blkInfo);
    printf("|====>      Free %d page(s), mem physical address is 0x%x\n", blkInfo.numOfPage, CoreMapControl.coremapStartAddr + (CoreMapControl.pageUsed << 12));
    printf("|====>    Free Test Starts\n");
    printf("|=============================$!\n");
}