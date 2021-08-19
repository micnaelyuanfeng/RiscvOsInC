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

#endif