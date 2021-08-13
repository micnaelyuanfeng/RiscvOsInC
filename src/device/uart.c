#include "types.h"
#include "lib.h"
#include "reg.h"
#include "device.h"
#include "printf.h"

extern uint8_t PrintBuf[];

void fnUartInit(){
    fnStdoutInit(PrintBuf, fnUartPutCharWrap);
    fnUartHwInit();
}

void fnUartHwInit(){
    uint8_t volatile* uartBaseAddr = (uint8_t volatile*)UART_BASE;
    uint8_t volatile* uartFCRAddr = (uint8_t volatile*)UART_FCR_ADDR;
    uint8_t volatile* uartIERAddr = (uint8_t volatile*)UART_IER_ADDR;
    uint8_t volatile* uartLCRAddr = (uint8_t volatile*)UART_LCR_ADDR;

    uint8_t regValue = (1 << 0) | (1 << 1);

    *uartLCRAddr = regValue;

    regValue = 1 << 0;

    *uartFCRAddr = regValue;
    *uartIERAddr = regValue;

    uint16_t divisor = BAUD_RATE_DIV;
    uint8_t divisor_low = LowByteMaskOut(divisor);
    uint8_t divisor_hi = HighByteMaskOut(divisor);

    uint8_t lcr = *uartLCRAddr;
    *uartLCRAddr = lcr | ( 1 << 7);
    *uartBaseAddr = divisor_low;
    *uartIERAddr = divisor_hi;

    *uartLCRAddr = lcr;
}

void fnUartPutChar(uint8_t __c){
    fnMmioWriteByte((uint64_t)UART_BASE, __c);
}

void fnUartPutCharWrap(void* __dummy, uint8_t __c){
    fnUartPutChar(__c);
    // fnConsolePucharSbi(__c);
}

uint8_t fnUartGetChar() {

}

void fnUartPrint(uint8_t* _str){
    for (uint8_t idx = 0; _str[idx] = '\0'; idx++){
        fnUartPutChar((uint8_t)_str[idx]);
    }
}

