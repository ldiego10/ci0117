#include <stdlib.h>
#include "Barrier.h"


/*
 *  pthread_barrier_init
 */
Barrier::Barrier( int limit ) {
    int resultado = 0;
    this->count = limit;
    this->barrier = (pthread_barrier_t *) calloc (1, sizeof(pthread_barrier_t));	
    this->attr = (pthread_barrierattr_t *) calloc (1, sizeof(pthread_barrierattr_t));	
    resultado = pthread_barrier_init(this->barrier, this->attr, this->count);
    if(resultado == -1){
    	exit(1);
    }
}


/*
 * pthread_barrier_destroy
 */
Barrier::~Barrier() {
    int resultado = 0;
    resultado = pthread_barrier_destroy( this->barrier );
    if( resultado == -1 ){
    	exit(2);
    }
    free( this->barrier );
}


/*
 * pthread_barrier_wait
 */
void Barrier::Wait() {
    int resultado = 0;
    resultado = pthread_barrier_wait( this->barrier );
    if( resultado == -1 ){
        exit(3);
    }
}

