#include "types.h"
#include "sbi.h"
#include "device.h"
#include <stdarg.h>
#include "printf.h"

static __putf __stdoutF;
static void* __stdoutP;

extern uint8_t PrintBuf;

void fnConsolePucharSbi(uint8_t _ch){
    register uint64_t eid __asm__("x17") = __SBI_REQ_CONSOLE_PUTCHAR;
    register uint64_t __ch __asm__("x10") = _ch; 
    __asm__ volatile (
        "ecall"
    );
}


static void ui2a(unsigned int num, unsigned int base, int uc,char * bf){
    int n=0;
    unsigned int d=1;
    while (num/d >= base)
        d*=base;
    while (d!=0) {
        int dgt = num / d;
        num%= d;
        d/=base;
        if (n || dgt>0 || d==0) {
            *bf++ = dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10);
            ++n;
            }
        }
    *bf=0;
}

static void i2a (int num, char * bf){
    if (num<0) {
        num=-num;
        *bf++ = '-';
    }
    
    ui2a(num,10,0,bf);
}

static int a2d(char ch){
    if (ch>='0' && ch<='9')
        return ch-'0';
    else if (ch>='a' && ch<='f')
        return ch-'a'+10;
    else if (ch>='A' && ch<='F')
        return ch-'A'+10;
    else return -1;
}

static char a2i(char ch, char** src,int base,int* nump){
    char* p= *src;
    int num=0;
    int digit;

    while ((digit=a2d(ch))>=0) {
        if (digit>base) break;
        num=num*base+digit;
        ch=*p++;
    }
    
    *src=p;
    *nump=num;
    return ch;
}

static void putchw(void* putp, __putf putf,int n, char z, char* bf){
    char fc=z? '0' : ' ';
    char ch;
    char* p=bf;
    while (*p++ && n > 0)
        n--;
    while (n-- > 0)
        putf(putp,fc);
    while ((ch= *bf++))
        putf(putp,ch);
    }

void _tfpFormat(void * putp, __putf putf, char* fmt, va_list va){
    char bf[12];

    char ch;


    while ((ch=*(fmt++))) {
        if (ch!='%')
            putf(putp,ch);
        else {
            char lz=0;
            int w=0;
            ch=*(fmt++);
            if (ch=='0') {
                ch=*(fmt++);
                lz=1;
                }
            if (ch>='0' && ch<='9') {
                ch=a2i(ch,&fmt,10,&w);
                }
            switch (ch) {
                case 0:
                    goto abort;
                case 'u' : {
                    ui2a(va_arg(va, unsigned int),10,0,bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                    }
                case 'd' :  {
                    i2a(va_arg(va, int),bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                    }
                case 'x': case 'X' :
                    ui2a(va_arg(va, unsigned int),16,(ch=='X'),bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                case 'c' :
                    putf(putp,(char)(va_arg(va, int)));
                    break;
                case 's' :
                    putchw(putp,putf,w,0,va_arg(va, char*));
                    break;
                case '%' :
                    putf(putp,ch);
                default:
                    break;
                }
            }
        }
    abort:;
}



void _tfpPrintf(const uint8_t* _fmt, ...){
    va_list va;
    va_start(va, _fmt);
    _tfpFormat(__stdoutP, __stdoutF, _fmt, va);
    va_end(va);
}

void fnStdoutInit(void* __putP, void (*__putF)(void*, uint8_t)){
    __stdoutF = __putF;
    __stdoutP == __putP;
}

void fnGreetingPrint(){
    printf("\n\n");
    printf("|=============================$!\n");
    printf("|====>     Profiler Kernel V1.01 \n");
    printf("|====>     nullptr()\n");
    printf("|====>     Hello World        \n");
}
