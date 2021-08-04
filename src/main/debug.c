#include "types.h"
#include "debug.h"
#include "sbi.h"

void putc(uint8_t _c){
    register unsigned int a asm("a6") = 0;
    register unsigned int sbiReqId asm("a7") = 1;
    
    register uint8_t str asm("a0") = _c;

    __asm__ volatile("ecall");
}