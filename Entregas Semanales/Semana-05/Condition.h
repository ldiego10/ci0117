
#include "Lock.h"
#include "Semaforo.h"

class Condition {

   public:
      Condition();
      ~Condition();
      void Wait( Lock *, int );
      void NotifyOne(int);
      void NotifyAll();
      void Signal(int);

   private:
     int workers;
    Lock * internalWaitMechanism;

};

