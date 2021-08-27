#include "types.h"
#include "sbi.h"
#include "reg.h"
#include "hart.h"

// extern RegisterRoute_t RegisterAccess;
extern HartInfo_t* pHart0;

void fnRegisterAccessInit(){
    pHart0->RegisterAccess.readSstatus = __readSstatus;
    pHart0->RegisterAccess.readStap = __readSatp;
    pHart0->RegisterAccess.readSscratch = __readSscratch;
    pHart0->RegisterAccess.readSie = __readSie;
    pHart0->RegisterAccess.readCcyle = __readCcycle;

    pHart0->RegisterAccess.setCcycle = __setCcycle;
    
    pHart0->RegisterAccess.writeScratch = __writeSscratch;
    pHart0->RegisterAccess.writeSie = __writeSie;
    pHart0->RegisterAccess.writeStvec = __writeStvec;
    pHart0->RegisterAccess.writeSstatus = __writeSstatus;

    pHart0->RegisterAccess.writeSatp = __writeSatp;
    pHart0->RegisterAccess.flushTlb  = __flushTlb;

    pHart0->RegisterAccess.readSip = __readSip;
    pHart0->RegisterAccess.writeSip = __writeSip;
}

void __readSip(uint64_t* volatile retValue){
    __asm__ volatile (
        "csrr %0, sip"
        : "=r"(*retValue)
        :
        :"memory"
    );
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
    __asm__ volatile (
        "sfence.vma"
    );
}

void __readCcycle(uint64_t* volatile retvalue){
    __asm__ volatile (
        // "csrrs %0, cycle, x0"
        "rdtime %0"
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

void __writeSatp(uint64_t value){
    __asm__ volatile (
        "csrw satp, %0"
        :
        : "r"(value)
        :"memory"
    );
}

void __writeSip(uint64_t value){
    __asm__ volatile (
        "csrw sip, %0"
        :
        : "r"(value)
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
