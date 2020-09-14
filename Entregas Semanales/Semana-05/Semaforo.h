#ifndef _SEMAFORO_H
#define _SEMAFORO_H
class Semaforo {
   public:
      Semaforo( int, int = 0 );
      ~Semaforo();
      int Signal( int = 0 );
      int Wait( int = 0 );
      void SP( int, int );
      void SV( int, int );

   private:
      int id;		// Identificador del semaforo
      int nsems;	// Cantidad de semaforos en el arreglo
};
#endif

