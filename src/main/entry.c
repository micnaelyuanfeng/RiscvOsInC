#include "types.h"
#include "lib.h"
#include "device.h"
#include "reg.h"
#include "debug.h"
#include "trap.h"
#include "handlers.h"
#include "printf.h"

extern uint8_t PrintBuf[];

void kentry(){
    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
    fnRegisterAccessInit();
    fnTrapInit();
    fnTimerInit();
    // fnGreetingPrint();

    while(1);
}
