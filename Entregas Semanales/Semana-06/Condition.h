#ifndef _COND_H
#define _COND_H

#include <pthread.h>
#include "Lock.h"
#include "Mutex.h"
class Condition {

   public:
      Condition();
      ~Condition();
      int Wait( Mutex * );
      int TimedWait( Mutex *, long, long );
      int Signal();
      int Broadcast();

   private:
      pthread_cond_t * vc;

};

#endif

