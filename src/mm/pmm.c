#include "types.h"
#include "reg.h"
#include "printf.h"
#include "coremap.h"

extern RegisterRoute_t RegisterAccess;

extern CoreMapCntl_t CoreMapControl;

void fnCoremap_init(){
    CoreMapControl.coremapDump = __coremapDump;
    CoreMapControl.coremapInit = __coremapInit;
    CoreMapControl.kfree = __kfree;
    CoreMapControl.kmalloc = __kmalloc;

    CoreMapControl.coremapInit();

    printf("addr is 0x%x\n", __KernelEndAddr);
}

void __coremapInit(){

}

void __kmalloc(){

}

void __kfree(){

}

void __coremapDump(){

}