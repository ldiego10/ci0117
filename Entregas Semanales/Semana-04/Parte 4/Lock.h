
#ifndef _LOCK_H
#define _LOCK_H
#include "Semaforo.h"

class Lock {
   public:
      Lock();
      ~Lock();
      void Acquire();
      void Release();

   private:
      Semaforo * lock;

};

#endif
