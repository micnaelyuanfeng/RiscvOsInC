
#include "types.h"
#include "device.h"
#include "printf.h"

extern uint64_t _lockMem; 

bool __acquireLock(){
    // printf("0x%x\n", ConsoleLock);

    register unsigned int t0 asm("t0") = 0x1;
    register unsigned long long a0 asm("a0") = (uint64_t)&ConsoleLock;

    __asm__ volatile(
        "amoswap.w.aq t0, t0, (a0)\n \t");

    return (t0 == 1);
}

void __getLock(){
    while (__acquireLock());
}

void __releaseLock(){
    
    register unsigned long long a0 asm("a0") = (uint64_t)&ConsoleLock;
    __asm__ volatile(
        "amoswap.w.rl x0, x0, (a0)\n \t"
        ::"r"((uint64_t)&ConsoleLock));
}



// // #include "profile.h"
// struct TestProcessMem{
//     uint64_t wptr;
//     uint64_t doorbell;
//     struct PROCESS_CONTEXT process_ctx;
//     struct GANG_INFO gang_ctx[2];
//     struct STR_MEC_COMPUTE_512DW_MQD mqd;
//     // uint64_t mqd_flags[10];
//     uint64_t process_va_start;
//     uint64_t process_va_end;
//     uint64_t process_quantum;
// };

// struct TestProcessInfo{
//     struct TestProcessMem mem;
//     uint32_t process_id;
// };

// struct TestProcessInfo process1  __attribute__((section (".uq_info_sect")));
// struct TestProcessInfo process2  __attribute__((section (".uq_info_sect")));
// struct TestProcessInfo process3  __attribute__((section (".uq_info_sect")));
// // struct TestProcessInfo process4  __attribute__((section (".uq_info_sect")));

// void create_process_info(){
//     process1.process_id = 1;
//     process2.process_id = 2;
//     process3.process_id = 3;

//     process1.mem.process_va_start = 0xfffffffff0000000;
//     process1.mem.process_va_end =  0xffffffffffffffff;
//     process1.mem.process_quantum = 10;
//     process2.mem.process_va_start = 0xfffffffff0000000;
//     process2.mem.process_va_end =  0xffffffffffffffff;
//     process2.mem.process_quantum = 10;
//     process3.mem.process_va_start = 0xfffffffff0000000;
//     process3.mem.process_va_end =  0xffffffffffffffff;
//     process3.mem.process_quantum = 10;
// }


// struct RoQueue roq_mem __attribute__ ((section (".ipi_sect")));
// extern uint64_t lock_mem;
// bool notify_queue_data = false;

// // void sendIpiNotification(uint8_t hart_id){
// //     printf("Send ipi from hart hart_id\n", hart_id);
// //     // uint64_t hid = 0b10;
// //     register unsigned int id asm("x17") = 0x4;
// //     register unsigned int hart_mask asm("x10") = (uint64_t)&hart_id;
// //     asm __volatile__("ecall");
// // }

// void submit(uint32_t *data, size_t count){
//     // get_lock((uint64_t)&lock_mem);
//     for(int i = 0; i < API_FRAME_SIZE_IN_DWORDS; i++){
//         *(roq_mem.roq + i + roq_mem.wptr * API_FRAME_SIZE_IN_DWORDS) = *(data + i);
//         // printf("submit data dword : = 0x%x\n", *(data + i));
//     }
//     // release_lock((uint64_t)&lock_mem);
// }


// void submit_frame(uint32_t *data){
//     submit(data, API_FRAME_SIZE_IN_DWORDS);
// }

// void init_roq(){
//     roq_mem.roq = (uint32_t*)ROQ_VA;
//     roq_mem.roq_size = (uint32_t)ROQ_SZ;
//     roq_mem.api_completion_value = 0;
//     roq_mem.buffer_counter = 0;
// }

// void ipi_process_mem_test(){
//     process1.mem.process_ctx.process_vm_cntl = 7;
// }

// int main(){
//     init_roq();
    
//     // printf("******************\n");
//     // printf("Hello from Hart 0\n");

//     for(int i = 0; i < 500000000; i++) {
//         ;
//     }
    
//     get_lock((uint64_t)&lock_mem);
//     set_hw_resources();
//     // roq_mem.wptr++;
//     // ipi_process_mem_test();
//     sendIpiNotification(0b10);
//     release_lock((uint64_t)&lock_mem);
//     // create_process_info();
//     for(int i = 0; i < 1000000000; i++) {
//         ;
//     }
    
//     get_lock((uint64_t)&lock_mem);
//     roq_mem.wptr++;
//     add_queue(&process1, 0);
//     // // roq_mem.wptr++;
//     // // ipi_process_mem_test();
//     sendIpiNotification(0b10);
//     release_lock((uint64_t)&lock_mem);

//     for(int i = 0; i < 500000000; i++) {
//         ;
//     }
    
//     get_lock((uint64_t)&lock_mem);
//     roq_mem.wptr++;
//     add_queue(&process2, 0);
//     sendIpiNotification(0b10);
//     release_lock((uint64_t)&lock_mem);

//     for(int i = 0; i < 500000000; i++) {
//         ;
//     }
    
//     get_lock((uint64_t)&lock_mem);
//     roq_mem.wptr++;
//     add_queue(&process1, 1);
//     sendIpiNotification(0b10);
//     release_lock((uint64_t)&lock_mem);

//     while(1);
// }