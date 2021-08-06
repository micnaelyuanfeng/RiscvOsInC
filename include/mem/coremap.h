#ifndef _COREMAP_H_
#define _COREMAP_H_

#ifndef QEMU_RUN
/*
*   Qemu load kernel image at 0x80200000 and grab physical memory size predefined by user
*   Avaiable physical memory equals to 0x80200000 + PHY_SZ - KEN_SZ + 1
*/

#else

uint64_t _DramStart = 0x0;
uint64_t _KernelStart = 0x0;

#endif

typedef void (*_kmalloc)(void* info, ...);
typedef void (*_kfree)(void* info, ...);
typedef void (*_coremapInit)();
typedef void (*_coremapDump)();

typedef struct CoreMapCntl {
    _kmalloc kmalloc;
    _kfree  kfree;
    _coremapDump coremapDump;
    _coremapInit coremapInit;

    uint64_t kernelStartAddr;
    uint64_t kernelEndAddr;
    uint64_t coremapStartAddr;
    uint64_t coremapCapacityInPageSize;
    uint64_t pageUsed;
}CoreMapCntl_t;

typedef struct CoreMemBlkInfo {
    uint64_t numOfPage : 20;
    uint64_t numOfByte : 20;
    uint64_t reserved : 24;
}CoreMemBlkInfo_t;

#define WrapUpMemInfo(n) (n) + 10

void fnCoremap_init();

void __kmalloc(void* info, ...);
void __kfree(void* info, ...);
void __coremapInit();
void __coremapDump();

#endif