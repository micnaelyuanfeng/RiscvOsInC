#ifndef _THREAD_H_
#define _THREAD_H_

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
    
    __createContext createContext;
}ThreadCntl_t;

typedef struct ThreadContextContent{
    uint64_t ra;
    uint64_t satp;
    uint64_t s[12];
    Trapframe_t tf;
}ThreadContextContent_t;

typedef struct ThreadContext{
    uint64_t contextAddt;
}ThreadContext_t;

typedef struct Thread {
    uint64_t context;
    struct {
        uint64_t id : 5;
        uint64_t state : 2;
        uint64_t privillege : 3;
        uint64_t reserved : 22;
    }info;

    uint64_t ptVa;
    uint64_t heapVa;
    uint64_t stackVa;
    uint64_t ipiMemVa;
}Thread_t;

void _fork();
void _exec();
void _destroy();

uint64_t _createContext();

void fnThreadControlInit();

#endif