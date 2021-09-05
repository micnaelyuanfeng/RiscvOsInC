#ifndef _LOCK_H_
#define _LOCK_H_

void __getLock();
void __releaseLock();
void __getCbLock();
void __releaseCbLock();

#define acquireLock(...) __getLock()
#define releaseLock(...) __releaseLock()
#define acquireCbLock(...) __getCbLock()
#define releaseCbLock(...) __releaseCbLock()

#define wfi(...) ({ \
    __asm__ volatile ("wfi");   \
})

#endif
