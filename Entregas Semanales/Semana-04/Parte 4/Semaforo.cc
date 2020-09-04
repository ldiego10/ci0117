
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "Semaforo.h"



Semaforo::Semaforo( int cantidad, int valorInicial ) {
   int status;
   union semun {
       int              val;
       struct semid_ds *buf;
       unsigned short  *array;
       struct seminfo  *__buf;
    }value;


   this->id = semget( IPC_PRIVATE, cantidad, 0600 | IPC_CREAT | IPC_EXCL );
   this->nsems = cantidad;

   value.val = valorInicial;	// Each semaphore will be initialized to this value
   for ( int i = 0; i < this->nsems; i++ ) {
       status = semctl( id, i, SETVAL, value );
       if ( -1 == status ) {
          perror( "Semaforo::Semaforo(int)" );
       }
   }

}



Semaforo::~Semaforo() {
	int resultado;
	resultado = semctl( id, 0, IPC_RMID, NULL );
   	if ( resultado == -1 ) {
      		perror( "Semaforo::~Semaforo" );
   	}
}

int Semaforo::Signal( int cual ) {
  	int resultado = -1;
   	struct sembuf semaforos[this->nsems];

   	for ( int i = 0; i < this->nsems; i++ ) {
      		semaforos[i].sem_num = i;
      		semaforos[i].sem_op  = 1;
      		semaforos[i].sem_flg = 0;
   	}
   	resultado = semop( this->id, semaforos, nsems );
   	if ( resultado == -1 ) {
      		perror( "Semaforo::Semaforo(int)" );
   	}
   	return resultado;
} 

int Semaforo::Wait( int cual ) {
   	int resultado = -1;
   	struct sembuf semaforos[ this->nsems ];

   	for ( int i = 0; i < this->nsems; i++ ) {
      		semaforos[i].sem_num = i;
      		semaforos[i].sem_op  = -1;
      		semaforos[i].sem_flg = 0;
   	}
   	resultado = semop( this->id, semaforos, nsems );
   	if ( resultado == -1 ) {
      		perror( "Semaforo::Semaforo(int)" );
   	}
   	return resultado;
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
void Semaforo::SP( int first, int second ) {
   int resultado;
   struct sembuf P[ 2 ];

   P[ 0 ].sem_num = first;
   P[ 0 ].sem_op  = -1;
   P[ 0 ].sem_flg = 0;

   P[ 1 ].sem_num = second;
   P[ 1 ].sem_op  = -1;
   P[ 1 ].sem_flg = 0;

   resultado = semop( this->id, P, 2 );
   if ( resultado == -1 ) {
      perror( "Semaforo::SP(int, int)" );
   }
}


/*
*
*/
void Semaforo::SV( int first, int second ) {
   int resultado;
   struct sembuf V[ 2 ];

   V[ 0 ].sem_num = first;
   V[ 0 ].sem_op  = 1;
   V[ 0 ].sem_flg = 0;

   V[ 1 ].sem_num = second;
   V[ 1 ].sem_op  = 1;
   V[ 1 ].sem_flg = 0;

   resultado = semop( this->id, V, 2 );
   if ( resultado == -1 ) {
      perror( "Semaforo::SV(int, int)" );
   }
}
