#ifndef _COREMAP_H_
#define _COREMAP_H_

#ifndef QEMU_RUN
/*
*   Qemu load kernel image at 0x80200000 and grab physical memory size predefined by user
*   Avaiable physical memory equals to 0x80200000 + PHY_SZ - KEN_SZ + 1
*/

extern void __KernelEndAddr();

#else

uint64_t _DramStart = 0x0;
uint64_t _KernelStart = 0x0;

#endif

typedef void (*_kmalloc)();
typedef void (*_kfree)();
typedef void (*_coremapInit)();
typedef void (*_coremapDump)();

typedef struct CoreMapCntl {
    _kmalloc kmalloc;
    _kfree  kfree;
    _coremapDump coremapDump;
    _coremapInit coremapInit;
}CoreMapCntl_t;

void fnCoremap_init();

void __kmalloc();
void __kfree();
void __coremapInit();
void __coremapDump();

#endif