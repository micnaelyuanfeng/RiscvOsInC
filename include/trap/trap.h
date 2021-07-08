#ifndef _TRAP_H_
#define _TRAP_H_

enum INT_VECT_TBL {
    
};

typedef struct Trapframe {
    
}_trapframe_t;

void dispatch_interrupt();
void dispatch_soft_interrupt();
void dispatch_ext_interrupt();

#endif