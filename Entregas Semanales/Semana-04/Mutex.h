#ifndef _MUTEX_H
#define _MUTE_HX
#include "Semaforo.h"

class Mutex {
   public:
      Mutex();
      ~Mutex();
      void Lock();
      void Unlock();

   private:
      Semaforo * mutex;

};

#endif

