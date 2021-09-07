#ifndef _RINGBUFFER_
#define _RINGBUFFER_

#define RB_SZ 0x1000
#define CMD_SZ 512
#define RB_SZ_IN_CMD (RB_SZ / CMD_SZ)

typedef struct RingBufferControl{
    bool isFull;
    uint64_t* pQueueMemStar;
    uint32_t  wptr;
    uint32_t  rptr;
    uint32_t  size; 
} RingBufferControl_t;

void fnRbInit();
bool fnRbSubmit();
bool fnIsRbFull();

#endif