#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "Semaforo.h"

/*
 *  sem_init
 */
Semaforo::Semaforo( int inicial ) {
   int resultado = 0;
   this->semId = (sem_t *) calloc (1, sizeof(sem_t));
   resultado = sem_init(this -> semId, 0, inicial);
   if( resultado == -1 ){
   	exit(0);
   }
}


/*
 *  sem_destroy
 */
Semaforo::~Semaforo() {
    int resultado = 0;
    resultado = sem_destroy( this->semId );
    if( resultado == -1 ){
    	exit(1);
    }
    free( this->semId );
}


/*
 *  sem_post
 */
int Semaforo::Signal() {
   int resultado = 0;
   resultado = sem_post( this->semId );
   if( resultado == -1 ){
   	exit(2);
   }
   return resultado;
}


/*
 *  sem_wait
 */
int Semaforo::Wait() {
   int resultado = 0;
   resultado = sem_wait( this->semId );
   if( resultado == -1 ){
   	exit(3);
   }
   return resultado;
}


/*
 *  sem_trywait
 */
int Semaforo::tryWait() {
   int resultado = 0;
   resultado = sem_trywait( this->semId);
   if( resultado == -1){
   	exit(4);
   }
   return resultado;

}


/*
 *  sem_timedwait
 */
int Semaforo::timedWait( long sec, long nsec ) {
   int resultado = 0;
   struct timespec lapso;

   lapso.tv_nsec = nsec;
   lapso.tv_sec = sec;
   resultado = sem_timedwait(this->semId, &lapso);
   if(resultado == -1){
   	exit(5);
   }

   return resultado;

}
