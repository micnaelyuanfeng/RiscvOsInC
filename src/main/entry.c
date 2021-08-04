#include "types.h"
#include "lib.h"
#include "device.h"
#include "reg.h"
#include "debug.h"
#include "trap.h"
#include "handlers.h"
#include "printf.h"

extern uint8_t PrintBuf[];
extern RegisterRoute_t RegisterAccess;

void kentry(){
    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
    fnRegisterAccessInit();
    fnTrapInit();
    fnTimerInit();
    fnGreetingPrint();
    
    // asm("ebreak");
   
    while(1);
}
