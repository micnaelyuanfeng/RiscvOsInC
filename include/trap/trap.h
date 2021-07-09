#ifndef _TRAP_H_
#define _TRAP_H_

enum INT_VECT_TBL {
    
};

typedef struct Trapframe {
    
}_trapframe_t;

typedef struct TrapCtrl {
    void (*pDispatch)(_trapframe_t tf);
}_trapctrl_t;

void dispatch_interrupt(_trapframe_t tf));
void dispatch_soft_interrupt();
void dispatch_ext_interrupt();

void trap_init();

#endif