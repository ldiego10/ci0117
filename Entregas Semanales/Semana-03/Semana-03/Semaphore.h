/*
 *  C++ class to encapsulate Unix semaphore intrinsic structures and system calls
 *  Author: Programacion Concurrente (Francisco Arroyo)
 *  Version: 2020/Ago/08
 *
 * Ref.: https://en.wikipedia.org/wiki/Semaphore_(programming)
 *
 */

class Semaphore {
   public:
      Semaphore( int ValorInicial = 0 );
      ~Semaphore();
      int Signal();	// Puede llamarse V
      int Wait();	// Puede llamarse P
   private:
      int creador;
      int id;		// Identificador del semaforo
};
