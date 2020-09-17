#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

class Mutex {
public:
   Mutex();
   ~Mutex();
   int Lock();
   int TryLock();
   int Unlock();
   pthread_mutex_t * getMutex();

private:
   pthread_mutex_t * mutex;

};
#endif
