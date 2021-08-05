#ifndef _DEVICE_H_
#define _DEVICE_H_

/*
*   UART
*/
#define UART_BASE 0x10000000
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

void fnTimerInit();
void fnEnableTimerIntr();
void fnSetTimerInterval();
void fnClearTick();
void fnAddTick();

uint64_t fnGetTick();
uint64_t fnGetCyle();

#endif