#include "types.h"
#include "device.h"
#include "trap.h"
#include "thread.h"
#include "printf.h"

extern ThreadCntl_t ThreadControl;

void fnThreadControlInit()
{
    ThreadControl.createContext = _createContext;
    
    ThreadControl.destroy = _destroy;
    ThreadControl.exec = _exec;
    ThreadControl.fork = _fork;
}

