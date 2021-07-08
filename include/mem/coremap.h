#ifndef _COREMAP_H_
#define _COREMAP_H_

uint64_t _CoreMapStart = 0;
uint64_t _DramEnd = 0;

#ifdef QEMU_RUN
/*
*   Qemu load kernel image at 0x80200000 and grab physical memory size predefined by user
*   Avaiable physical memory equals to 0x80200000 + PHY_SZ - KEN_SZ + 1
*/
uint64_t _DramStart = 0x80000000;
uint64_t _KernStart = 0x80200000;

#else

uint64_t _DramStart = 0x0;
uint64_t _KernStart = 0x0;

#endif

void _coremap_init();
void _kmalloc();
void _kfree();

#endif