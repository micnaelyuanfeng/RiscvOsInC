#ifndef _REG_H_
#define _REG_H_

typedef void (*_readSstatus)();
typedef void (*_writeSstatus)();
typedef void (*_readStap)();
typedef void (*_writeSatp)();
typedef void (*_flushTlb)();
typedef void (*_readSscratch)();
typedef void (*_writeSscratch)();
typedef void (*_readStvec)();
typedef void (*_writeStvec)();
typedef void (*_writeSatp)();
typedef void (*_readSie)();
typedef void (*_writeSie)();
typedef void (*_readCcyle)();
typedef void (*_setCcycle)();
typedef void (*_readSip)();
typedef void (*_writeSip)();

void __readSstatus(uint64_t* volatile retValue);
void __readSatp(uint64_t* volatile retValue);
void __flushTlb();
void __readSscratch(uint64_t* volatile retValue);
void __readStvec(uint64_t* volatile retValue);
void __readSie(uint64_t* volatile retValue);
void __readCcycle(uint64_t* retValue);
void __writeSatp(uint64_t volatile value);
void __writeSscratch(uint64_t volatile value);
void __writeStvec(uint64_t volatile value);
void __writeSie(uint64_t volatile value);
void __writeSstatus(uint64_t volatile value);

void __setCcycle(uint64_t volatile value);
void __readSip(uint64_t* volatile retValue);
void __writeSip(uint64_t volatile value);


typedef struct RegisterRoute{
    _readSstatus   readSstatus;
    _readStap      readStap;
    _readSscratch  readSscratch;
    _readStvec     reasStevc;
    _readSie       readSie;
    _readCcyle     readCcyle;
    _setCcycle     setCcycle;
    _writeSscratch writeScratch;
    _writeStvec    writeStvec;
    _writeSie      writeSie;
    _writeSstatus  writeSstatus;
    _writeSatp     writeSatp;
    _flushTlb      flushTlb;
    _readSip       readSip;
    _writeSip      writeSip;
}RegisterRoute_t;

void fnRegisterAccessInit();

void fnMmioReadByte(uint64_t _addr, uint8_t* _retVal);
void fnMmioWriteByte(uint64_t _addr, uint8_t _value);


#endif