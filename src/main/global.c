#include "types.h"
#include "reg.h"
#include "device.h"
#include "coremap.h"
#include "vm.h"
#include "trap.h"
#include "thread.h"
#include "printf.h"

uint8_t PrintBuf[BUF_SIZE];
RegisterRoute_t RegisterAccess = {0};
CoreMapCntl_t CoreMapControl = {0};
DeviceTimer_t TimerControl = {0};
VMControl_t VmControl = {0};
ThreadCntl_t ThreadControl = {0};
DeviceRingBuf_t CmdRingMem = {0};

bool procecedLock = false;

uint64_t _lockMem = 0; 