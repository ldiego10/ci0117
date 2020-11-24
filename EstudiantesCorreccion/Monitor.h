#ifndef _MONITOR_H
#define _MONITOR_H
#include "Mutex.h"
#include <cstdlib>



class Monitor {

   public:
      Monitor();
      Monitor(int);
      ~Monitor();
      void Wait( Mutex * );
      void Wait(int, int);
      void NotifyOne();
      void Signal();
      void Signal(int, int);

   private:
     int workers;
     Mutex* internalWaitMechanism;
     Semaforo *semaforo;

};
#endif

