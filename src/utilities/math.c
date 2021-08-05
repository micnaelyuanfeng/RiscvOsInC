#include "types.h"
#include "lib.h"

uint32_t __umuldi3(uint32_t a, uint32_t b){
    uint32_t res = 0;
    while (b){
        if (b & 1) res += a;
        a = a + a;
        b >>= 1;
    }

    return res;
}

int32_t __muldi3(int32_t a, int32_t b)
{
    bool r = false;
    
    if (a < 0){
        a = -a;
        r = !r;
    }
    
    if (b < 0){
        b = -b;
        r = !r;
    }

    int32_t rr = (uint32_t)__umuldi3((uint32_t)a, (uint32_t)b);
    if (r)rr=-rr;

    return rr;
}

uint32_t __udivdi3(uint32_t a, uint32_t b){
    uint32_t res = 0;

    //find highest power of 2 of b <= a
    uint64_t x = b;
    uint32_t count = 1;

    while ((x << 1) <= a){
        x <<= 1;
        count <<= 1;
    }

    //repeatedly subtract from a
    while (a >= b){
        if (a >= x){
            a -= x;
            res += count;
        }
        count >>= 1;
        x >>= 1;
    }

    return res;
}

uint32_t __umoddi3(uint32_t a, uint32_t b){
    return a - __umuldi3(__udivdi3(a, b), b);
}
