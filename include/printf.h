#ifndef __PRINTF_H_
#define __PRINTF_H_

#ifndef SBI_PRINT
/* SBI Print Definition Handles Starts */
void _tfpPrintf(const uint8_t *_fmt, ...);
void fnStdoutInit(void* __putP, void (*__putF)(void*, uint8_t));
void fnGreetingPrint();

#define BUF_SIZE 1024
#define printf _tfpPrintf

typedef void (*__putf) (void*, uint8_t);
/* SBI Print Definition Handles Ends */
#else 
    void dummy();
#endif

void fnConsolePucharSbi(uint8_t ch);

#endif
