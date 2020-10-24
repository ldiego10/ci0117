#ifndef _LOCK_H
#define _LOCK_H
#include <omp.h>

class Lock {
   public:
      Lock();
      ~Lock();
      void Acquire();
      void Release();

   private:
      omp_lock_t writelock;

};

#endif
