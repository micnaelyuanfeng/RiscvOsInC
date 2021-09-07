#include "types.h"
#include "reg.h"
#include "device.h"
#include "hart.h"
#include "ringbuffer.h"
#include "lib.h"
#include "printf.h"

extern HartInfo_t* pHart0;

void fnRbInit(){
    pHart0->pRingBufCrtl = (RingBufferControl_t*)pCommandQueueMem;
    pHart0->pRingBufCrtl->rptr = 6;
    pHart0->pRingBufCrtl->wptr = 0;
    pHart0->pRingBufCrtl->isFull = false;
    pHart0->pRingBufCrtl->size = (RB_SZ - 256) / CMD_SZ;
    pHart0->pRingBufCrtl->pQueueMemStar = (uint64_t*)((uint64_t)pCommandQueueMem + 256);
}

bool fnIsRbFull(){
    return pHart0->pRingBufCrtl->isFull; 
}

bool fnIsRbEmpty(){
    return (pHart0->pRingBufCrtl->wptr == pHart0->pRingBufCrtl->rptr) && pHart0->pRingBufCrtl->isFull;
}

bool fnRbSubmit(){
    if(fnIsRbFull()){
        printf("Full\n");
        return false;
    }

    uint8_t* cur = (uint64_t)pHart0->pRingBufCrtl->pQueueMemStar + pHart0->pRingBufCrtl->wptr * CMD_SZ;
    
    for(uint32_t i = 0; i < 512; i++){
        *(cur + i) = 0xB;
    }
    
    pHart0->pRingBufCrtl->wptr = (pHart0->pRingBufCrtl->wptr + 1) % pHart0->pRingBufCrtl->size;

    printf("wptr is %d\n", pHart0->pRingBufCrtl->wptr);

    if (pHart0->pRingBufCrtl->wptr == pHart0->pRingBufCrtl->rptr) pHart0->pRingBufCrtl->isFull = true;

    return true;
}
