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

    printf("Kernel Start Addr is 0x%x\n", CoreMapControl.kernelStartAddr);
    printf("Kernel End Addr is 0x%x\n", CoreMapControl.kernelEndAddr);
    printf("Coremap Start Addr is 0x%x\n", CoreMapControl.coremapStartAddr);
    printf("Coremap Capacity is %d\n", CoreMapControl.coremapCapacityInPageSize);
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

void __kmalloc(void* info, ...){
    if (CoreMapControl.pageUsed >= CoreMapControl.coremapCapacityInPageSize){
        __asm__ volatile (
            "ebreak" // trigger an exception
        );
    }else{
        
    }
}

void __kfree(void* info, ...){

}

void __coremapDump(){

}

void __freelistMgnt(){

}