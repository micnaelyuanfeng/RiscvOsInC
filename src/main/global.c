#include "types.h"
#include "reg.h"
#include "device.h"
#include "coremap.h"
#include "vm.h"
#include "trap.h"
#include "thread.h"
#include "printf.h"
#include "hart.h"

uint8_t* PrintBuf = (uint8_t*) pPrinfBuf;
uint64_t satp;
// RegisterRoute_t RegisterAccess = {0};
// CoreMapCntl_t CoreMapControl = {0};
// DeviceTimer_t TimerControl = {0};
// VMControl_t VmControl = {0};
// ThreadCntl_t ThreadControl = {0};
// DeviceRingBuf_t CmdRingMem = {0};

HartInfo_t HartInstance[NUM_OF_HART] = {0};

bool procecedLock = false;

HartInfo_t* pHart0;
HartInfo_t* pHart1;
HartInfo_t* pHart2;
HartInfo_t* pHart3;
HartInfo_t* pHart4;
HartInfo_t* pHart5;
HartInfo_t* pHart6;
HartInfo_t* pHart7;
HartInfo_t* pHart0Daemon;
 