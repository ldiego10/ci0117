#ifndef _SEMAFORO_H
#define _SEMAFORO_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <iostream>


using namespace std;

class Semaforo {
   public:
      Semaforo( int ValorInicial = 1 );
      ~Semaforo();
      int Signal();	
      int Wait();
      void Signal(int x, int y, int z, int idT);
      void Wait(int x, int y, int z, int idT);
    private:

      int id;	
      int creador;	
};
#endif
