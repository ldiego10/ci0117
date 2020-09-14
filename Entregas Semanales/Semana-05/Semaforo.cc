#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "Semaforo.h"


Semaforo::Semaforo( int cantidad, int valorInicial ) {
   int status;
   union semun {
      int              val;
      struct semid_ds *buf;
      unsigned short  *array;
      struct seminfo  *__buf;
   } value;

   this->id = semget( IPC_PRIVATE, cantidad, 0600 | IPC_CREAT | IPC_EXCL );
   this->nsems = cantidad;

   value.val = valorInicial;	// Each semaphore will be initialized to this value
   for ( int i = 0; i < this->nsems; i++ ) {
       status = semctl( id, i, SETVAL, value );
       if ( -1 == status ) {
          perror( "Semaphore::Semaphore(int)" );
       }
   }

}


Semaforo::~Semaforo() {
}

int Semaforo::Signal( int cual ) {
    int resultado;
   struct sembuf datos;
   datos.sem_num = cual;
   datos.sem_op = 1;
   datos.sem_flg = 0;

  resultado = semop(this->id, &datos, 1);
  if(-1 == resultado)
  {
    perror("Semaforo Signal");
    exit(4);
  }

  return 0;

}

int Semaforo::Wait( int cual ) {
    int resultado;
    struct sembuf dato;
    dato.sem_num = cual;
    dato.sem_op = -1;
    dato.sem_flg = 0;

    resultado = semop(this->id, &dato, 1);
    if(-1 == resultado)
    {
        perror("Semaforo Wait");
        exit(5);
    } 

 return 0;

}

/*
 * Do a Wait operation on two semaphores, will try to substract one to each semaphore
 * This operation must be atomic, not allowed to block one semaphore
 * and try to block the other
 * The block operation must occur on both semaphores atomically
 * It will try to get the lock on two semaphores from the group,
 * especified by parameters
 *
 */
void Semaforo::SP( int primero, int segundo ) {
   int resultado;
   struct sembuf P[ 2 ];

   P[ 0 ].sem_num = primero;
   P[ 0 ].sem_op  = -1;
   P[ 0 ].sem_flg = 0;

   P[ 1 ].sem_num = segundo;
   P[ 1 ].sem_op  = -1;
   P[ 1 ].sem_flg = 0;

   // resultado = semop( ... );

}


/*
 *
 */
void Semaforo::SV( int primero, int segundo ) {
}
