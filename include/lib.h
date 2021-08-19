#ifndef _LIB_H_
#define _LIB_H_

#define _sizeof(type) ({ \
        type var;   \
        ((char*)(&var + 1) - (char*)(&var)); \
    })

#define _va_list  \
    (void*)

typedef struct BoolClosure {
    bool (*__fn)(void*, ...);
    uint32_t nargs;
}BoolClosure_t;

typedef struct VoidClosure{
    void (*__fn)(void*, ...);
    uint32_t nargs;
}VoidColosure_t;

#define BUILD_BOOLCLOSURE(_fn, num) ({\
        BoolClosure_t c;\
        c.__fn = (_fn);\
        c.nargs = (num);\
        &c;  \
    })

#define LowByteMaskOut(n)  ({ \
    uint8_t __v = (n) & 0xFF; \
    __v;    \
})

#define HighByteMaskOut(n)  ({\
    uint8_t __v = ((n) >> 8) & 0xFF; \
    __v;    \
})

uint32_t __umuldi3(uint32_t a, uint32_t b);
int32_t __muldi3(int32_t a, int32_t b);
uint32_t __udivdi3(uint32_t a, uint32_t b);
uint32_t __umoddi3(uint32_t a, uint32_t b);

// bool __acquirelock();
// void __releaselock();

#endif