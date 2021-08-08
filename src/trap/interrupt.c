#include "types.h"
#include "reg.h"
#include "device.h"
#include "trap.h"
#include "printf.h"
#include "handlers.h"


extern RegisterRoute_t RegisterAccess;
extern void __trap_enter();

_intrHandler TrapVecTbl[InterruptUnknown];
_intrHandler ExcpVecTbl[ExceptionUnknown];

void fnBuildIntrVetTbl(){
    ExcpVecTbl[Breakpoint] = _handlerEbp;
    TrapVecTbl[SupervisorTimer] = _handlerSupervisorTimer;
}

void fnTrapInit(){
    fnBuildIntrVetTbl();

    RegisterAccess.writeScratch(0);
    
    uint64_t value = (uint64_t) __trap_enter | (uint64_t)DirectMode;

    RegisterAccess.writeStvec(value);

    value = 0;
    RegisterAccess.readSstatus(&value);
    value |= (1 << 1);
    RegisterAccess.writeSstatus(value);

    value = 0;
    RegisterAccess.readSie(&value);
    value |= (1 << 1);
    RegisterAccess.writeSie(value);
}

void fnDispatchInterrupt(Trapframe_t* _tf){
    switch(fnTrapTypeParse(_tf->sScaues)){
        case TrapException:
        {
            fnDispatchSoftInterrupt(_tf);
            break;
        }
        case TrapInterrupt:
        {
            fnDispatchExtrInterrupt(_tf);
            break;
        }
        default:
        {
            break;
        }
    }
}

// void _tfDump(Trapframe_t* __tf){
//     if (__tf != _nullptr){
//         for(uint8_t i = 0; i < REG_CONTEXT_NUM; i++){
//             printf("Reg Value: 0x%x\n", __tf->gpr[i]);
//         }

//         printf("Reg Value: 0x%x\n", __tf->sScaues);
//         printf("Reg Value: 0x%x\n", __tf->sSepc);
//         printf("Reg Value: 0x%x\n", __tf->sStval);

//     }
// }

uint8_t fnTrapTypeParse(uint64_t _sscauseValue){
    uint64_t trapCode = _sscauseValue & (1UL << 63);

    return trapCode >> 63;
}

void fnDispatchSoftInterrupt(Trapframe_t* _tf){
    ExcpVecTbl[_tf->sScaues & 0xF]((void*)_tf);
}

void fnDispatchExtrInterrupt(Trapframe_t* _tf){
    TrapVecTbl[_tf->sScaues]((void*)_tf);
}

void fnInterruptTest(){
    printf("|=============================$!\n");
    printf("|====>    Interrupt Test Starts\n");
    __asm__ volatile(
        "ebreak"
    );

    printf("|====>    EBREAK Test Pass\n");

extern DeviceTimer_t TimerControl;
    while(TimerControl.tick < 2);
    printf("|====>    Timer Interrupt Test Pass\n");
    printf("|====>    Interrupt Test Ends\n");
    printf("|=============================$!\n");
}