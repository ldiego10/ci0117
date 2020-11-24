#include <sys/types.h>
#include "sys/ipc.h" 
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
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

   value.val = valorInicial;	
   for ( int i = 0; i < this->nsems; i++ ) {
       status = semctl( id, i, SETVAL, value );
       if ( -1 == status ) {
          perror( "Semaforo::Semaforo(int)" );
       }
   }


}


Semaforo::~Semaforo() {
    int resultado;
    resultado=semctl(id,0,IPC_RMID);
    if(resultado==-1){
        perror("Semaforo::~Semaforo");
        exit(0);
    } 
}

int Semaforo::Signal( int cual ) {
   int resultado = -1;
   struct sembuf signal;
   signal.sem_num = 0;
   signal.sem_op = +1;
   signal.sem_flg = 0;
   resultado = semop (this -> id, &signal, 1);
   if(1 == resultado){
       perror("Semaforo::Signal");
       exit(5);
   }
   return resultado;

}

int Semaforo::Wait( int cual ) {
   int resultado = -1;
   struct sembuf wait;
   wait.sem_num = 0;
   wait.sem_op = -1;
   wait.sem_flg = 0;
   resultado = semop (this -> id, &wait, 1);
   if(1 == resultado){
       perror("Semaforo::Wait");
       exit(6);
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
void Semaforo::SP( int primero, int segundo ) {
   int resultado;
   struct sembuf P[ 2 ];

   P[ 0 ].sem_num = primero;
   P[ 0 ].sem_op  = -1;
   P[ 0 ].sem_flg = 0;

   P[ 1 ].sem_num = segundo;
   P[ 1 ].sem_op  = -1;
   P[ 1 ].sem_flg = 0;

   resultado= semop( this->id,P,2);
   if(resultado==-1){
        perror("Semaforo::SP(int, int)");
        exit(7);
    } 
}


/*
 *
 */
void Semaforo::SV( int primero, int segundo ) {
   int resultado;
   struct sembuf V[ 2 ];

   V[ 0 ].sem_num = primero;
   V[ 0 ].sem_op  = 1;
   V[ 0 ].sem_flg = 0;

   V[ 1 ].sem_num = segundo;
   V[ 1 ].sem_op  = 1;
   V[ 1 ].sem_flg = 0;

   resultado = semop( this->id, V, 2 );
   if ( resultado == -1 ) {
      perror( "Semaforo::SV(int, int)" );
   }
}
