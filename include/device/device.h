#ifndef _DEVICE_H_
#define _DEVICE_H_

/*
*   UART
*/
#define UART_BASE 0xFFFFFFFF10000000
#define UART_LCR_ADDR UART_BASE + 0x3
#define UART_FCR_ADDR UART_BASE + 0x2
#define UART_IER_ADDR UART_BASE + 0x1

#define BAUD_RATE_DIV   592

typedef void (*__write)();
typedef void (*__read)();
typedef void (*__hwInit)();

typedef struct DeviceUart {
    uint64_t   _mmioAddr;

    __hwInit   _hwInit;
    __write    _write;
    __read     _read;
}DeviceUart_t;

void fnUartHwInit();
void fnUartPutChar(uint8_t __c);
void fnUartPutCharWrap(void* __dummy, uint8_t __C);
void fnUartPrint(uint8_t* _str);

uint8_t fnUartGetChar();

/*
*   TIMER
*/
#define TIMER_BASE  100000

typedef void (*__enableTimerIntr)();
typedef void (*__clearTick)();
typedef void (*__addTick)();

typedef struct DeviceTimer {
    uint64_t cycle;
    uint64_t tick;

    __enableTimerIntr _enableTimerIntr;
    __clearTick _clearTick;
    __addTick _addTick;
}DeviceTimer_t;

void fnTimerInit();
void fnEnableTimerIntr();
void fnClearTick();
void fnAddTick();
void fnSetTimerInterval();


typedef void (*_write)();
typedef void (*_read)();
/**
 * Ring Buffer
*/

extern void __CommandQueueMemStart();
extern void __LockMemStart();
extern void __PrinfBuffStart();
extern void __HartInfoArray();

extern uint64_t __consoleLock;
extern uint64_t __queueMemLock;

#define pCommandQueueMem __CommandQueueMemStart
#define pLockMemStart __LockMemStart
#define ConsoleLock __consoleLock
#define QueueMemLock __queueMemLock
#define pHartInstance __HartInfoArray
#define pPrinfBuf __PrinfBuffStart
typedef struct DeviceRingBuf {
    uint64_t cbStartVa;
    uint64_t cbStartPa;
    uint64_t sizeInBytes;
    bool isCbFull;

    _write write;
    _read read;
}DeviceRingBuf_t;

void fnWriteRb();
void fnReadRb();

#endif