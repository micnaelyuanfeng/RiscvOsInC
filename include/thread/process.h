#ifndef _PROCESS_H_
#define _PROCESS_H_

#define GLOBAL_MEM_VA_START 0xFFFFFFFFFF80200000
#define GLOBAL_MEM_VA_SIZE  0x1000

void fnSubmitCommand();
void fnReadCommand();

#endif