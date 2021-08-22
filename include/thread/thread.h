#ifndef _THREAD_H_
#define _THREAD_H_

#define THREAD_STACK_SIZE_IN_PAGE   20
#define THREAD_CONTEXT_SIZE_IN_PAGE 1

enum ThreadStatus{
    ThreadSleep = 0,
    ThreadRunning = 1,
};

typedef void (*__fork)();
typedef void (*__exec)();
typedef void (*__destroy)();

typedef uint64_t (*__createContext)();

typedef struct ThreadCntl {
    __fork fork;
    __exec exec;
    __destroy destroy;
}ThreadCntl_t;

typedef struct ThreadContextContent{
    uint64_t ra;
    uint64_t satp;
    uint64_t s[12];
    Trapframe_t tf;
}__attribute__((packed, aligned(8))) ThreadContextContent_t;

typedef struct ThreadContext{
    uint64_t contextAddt;
}__attribute__((packed, aligned(8))) ThreadContext_t;

typedef struct Thread {
    uint64_t context;
    struct {
        uint64_t id : 3;
        uint64_t state : 2;
        uint64_t privillege : 3;
        uint64_t reserved : 56;
    }info;

    uint64_t ptVa;
    uint64_t heapVa;
    uint64_t stackVa;
    uint64_t ipiMemVa;
}__attribute__((packed, aligned(8))) Thread_t;

void _fork();
void _exec();
void _destroy();

uint64_t _createContext();

void fnThreadControlInit();

#endif