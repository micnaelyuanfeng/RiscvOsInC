#ifndef _LOCK_H_
#define _LOCK_H_

void __getLock();
void __releaseLock();

#define acquireLock(...) __getLock()
#define releaseLock(...) __releaseLock()
#endif
