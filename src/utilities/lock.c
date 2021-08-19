

void __acquireLock(){
    __asm__ volatile(
        "nop"
    );
}

void __releaseLock(){
    __asm__ volatile(
        "nop"
    );
}