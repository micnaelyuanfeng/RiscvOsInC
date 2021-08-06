#include "types.h"
#include "sbi.h"
#include "reg.h"

extern RegisterRoute_t RegisterAccess;

void fnRegisterAccessInit(){
    RegisterAccess.readSstatus = __readSstatus;
    RegisterAccess.readStap = __readSatp;
    RegisterAccess.readSscratch = __readSscratch;
    RegisterAccess.readSie = __readSie;
    RegisterAccess.readCcyle = __readCcycle;

    RegisterAccess.setCcycle = __setCcycle;
    
    RegisterAccess.writeScratch = __writeSscratch;
    RegisterAccess.writeSie = __writeSie;
    RegisterAccess.writeStvec = __writeStvec;
    RegisterAccess.writeSstatus = __writeSstatus;

}

void __readSstatus(uint64_t* volatile retValue){
    __asm__ volatile (
        "csrr %0, sstatus"
        : "=r"(*retValue)
        :
        :"memory"
    );
}

void __readSatp(uint64_t* volatile retValue){
    __asm__ volatile (
        "csrr %0, satp"
        : "=r"(*retValue)
        :
        :"memory"
    );
}

void __flushTlb(uint64_t* volatile retValue){
    // __asm__ volatile (
    //     "csrr $0, sstatus"
    //     : "=r"(*retValue)
    // );
}

void __readCcycle(uint64_t* volatile retvalue){
    __asm__ volatile (
        // "csrrs %0, cycle, x0"
        "csrr %0, 0xc01"
            : "=r"(*retvalue)
            :
            :"memory"
    );
}

void __setCcycle(uint64_t volatile value){
    register uint64_t sbiId __asm__("x17") = __SBI_REQ_SET_TIMER;
    register uint64_t tid __asm__("x11") = value;
    
    __asm__ volatile (
        "ecall"
    );
}

void __readSscratch(uint64_t* volatile retValue){
    __asm__ volatile (
        "csrr %0, sscratch"
        : "=r"(*retValue)
        :
        :"memory"
    );
}

void __readStvec(uint64_t* volatile retValue){
    __asm__ volatile (
        "csrr %0, stvec"
        : "=r"(*retValue)
        :
        :"memory"
    );
}

void __readSie(uint64_t* volatile retValue){
    __asm__ volatile (
        "csrr %0, sie"
        : "=r"(*retValue)
        :
        :"memory"
    );
}

void __writeSstatus(uint64_t value){
    __asm__ volatile (
        "csrw sstatus, %0"
        :
        : "r"(value)
        :"memory"
    );
}

void __writeSscratch(uint64_t value){
    __asm__ volatile (
        "csrw sscratch, %0"
        :
        : "r"(value)
        : "memory"
    );
}

void __writeStvec(uint64_t value){
    __asm__ volatile (
        "csrw stvec, %0"
        :
        : "r"(value)
        : "memory"
    );
}

void __writeSie(uint64_t value){
    __asm__ volatile (
        "csrw sie, %0"
        :
        : "r"(value)
        : "memory"
    );
}

void fnMmioReadByte(uint64_t _addr, uint8_t* _retVal){
    register uint64_t __addr __asm__("t0")= _addr;

    __asm__ volatile (
        "lb t1, 0(t0)"
        : "=r"(*_retVal)
    );
}

void fnMmioWriteByte(uint64_t _addr, uint8_t _value){
    register uint64_t __addr __asm__("t0") = _addr;
    register uint8_t __value __asm__("t1") = _value;

    __asm__ volatile (
        "sb t1, 0(t0)"
    );
}

void __mmio_read_half_word(uint64_t _addr, uint16_t* _retVal){
    __asm__ volatile (
        ""
    );
}

void __mmio_write_half_word(uint64_t _addr, uint16_t* _value){
    __asm__ volatile (
        ""
    );
}

void __mmio_read_word(uint64_t _addr, uint32_t* _retVal){
    __asm__ volatile (
        ""
    );
}

void __mmio_write_word(uint64_t _addr, uint32_t _value){
    __asm__ volatile (
        ""
    );
}

void __mmio_read_double_word(uint64_t _addr, uint64_t* _retVal){
    __asm__ volatile (
        ""
    );
}

void __mmio_write_double_word(uint64_t _addr, uint64_t _value){
    __asm__ volatile (
        ""
    );
}
