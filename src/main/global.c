#include "types.h"
#include "reg.h"
#include "device.h"
#include "coremap.h"
#include "printf.h"

uint8_t PrintBuf[BUF_SIZE];
RegisterRoute_t RegisterAccess = {0};
CoreMapCntl_t CoreMapControl = {0};
DeviceTimer_t TimerControl = {0};

uint64_t DramStart = 0x80000000;
uint64_t KernelStart = 0x80200000;