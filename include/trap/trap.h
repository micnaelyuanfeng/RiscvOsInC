#ifndef _TRAP_H_
#define _TRAP_H_


enum InterruptType {
    UserSoft,
    SupervisorSoft,
    UserTimer,
    SupervisorTimer = 5,
    UserExternal,
    SupervisorExternal,
    InterruptUnknown,
};

enum ExceptionType {
    InstructionMisaligned,
    InstructionFault,
    IllegalInstruction,
    Breakpoint,
    LoadFault,
    StoreMisaligned,
    StoreFault,
    UserEnvCall,
    InstructionPageFault,
    LoadPageFault,
    StorePageFault,
    ExceptionUnknown,
};

enum TrapType{
    TrapException,
    TrapInterrupt,
    TrapUnknown,
};

enum InterruptMode{
    DirectMode = 0,
    CascadeMode = 1,
    IntrModeInvalid
};

enum InterruptContrl{
    DisableInterrupt = 0,
    EnableInterrupt = 1,
};

#define REG_CONTEXT_NUM 32

typedef struct Trapframe {
    uint64_t gpr[REG_CONTEXT_NUM];
    uint64_t sStatus;
    uint64_t sSepc;
    uint64_t sStval;
    uint64_t sScaues;
}__attribute__((packed, aligned(8))) Trapframe_t;


void fnDispatchInterrupt(Trapframe_t* _tf);
void fnDispatchSoftInterrupt(Trapframe_t* _tf);
void fnDispatchExtrInterrupt(Trapframe_t* _tf);

void fnTrapInit();
uint8_t fnTrapTypeParse(uint64_t _sscauseValue);

void fnInterruptTest();

#endif