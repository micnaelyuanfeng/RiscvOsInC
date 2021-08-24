#ifndef __HANDLERS_H_
#define __HANDLERS_H_

#define TRAP_SUPPORTED_NUM  InterruptUnknown + ExceptionUnknown
#define TRAP_NUM_OFFSET 7
typedef void (*_intrHandler)(void* _tf, ...);



void _handlerSupervisorTimer(void* _tf, ...);
void _handlerEbp(void* _tf, ...);
void _handlerSysCall(void* _tf, ...);
void _handlerSupervisorSoftInt(void* _tf, ...);

#endif