#include "types.h"
#include "device.h"
#include "trap.h"
#include "vm.h"
#include "thread.h"
#include "printf.h"

extern ThreadCntl_t ThreadControl;
extern VMControl_t VmControl;

void fnThreadControlInit()
{
    ThreadControl.createContext = _createContext;
    ThreadControl.destroy = _destroy;
    ThreadControl.exec = _exec;
    ThreadControl.fork = _fork;
}

void _fork(){

}

void _exec(){

}

void _destroy(){

}

uint64_t _createContext(){
    VmControl.
}