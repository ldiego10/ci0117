#ifndef _LOCK_H
#define _LOCK_H
#include "Mutex.h"

class Lock {
   public:
      Lock();
      ~Lock();
      void Acquire();
      void Release();

   private:
      Mutex * mutex;

};

#endif
