#include <stdlib.h>
#include <pthread.h>

#include "Mutex.h"


/**
 *
 *  pthread_mutex_init()
 *
**/
Mutex::Mutex() {
   int resultado = 0; 
   this->mutex = (pthread_mutex_t *) calloc (1, sizeof(pthread_mutex_t));
   resultado = pthread_mutex_init( this->mutex, NULL);
   if (resultado != 0){
   	exit(1);
   }
}


/**
 *
 * pthread_mutex_destroy()
 *
**/
Mutex::~Mutex() {
   int resultado = 0;
   resultado = pthread_mutex_destroy( this->mutex );
   free(this->mutex);
   if (resultado != 0){
   	exit(2);
   }
}


/**
 *
 * pthread_mutex_lock()
 *
**/
int Mutex::Lock() {
   int resultado = 0;
   resultado = pthread_mutex_lock( this->mutex);
  
   if (resultado != 0){
   	exit(3);
   }
   return resultado;
}


/**
 *  pthread_mutex_trylock()
**/
int Mutex::TryLock() {
   int resultado = 0;
   resultado = pthread_mutex_trylock( this-> mutex);
   return resultado;

}

/**
 *  pthread_mutex_unlock()
**/
int Mutex::Unlock() {
   int resultado = 0;
   resultado = pthread_mutex_unlock( this -> mutex);
   return resultado;
   if (resultado != 0){
   	exit(4);
   }

}


/**
 * 
**/
pthread_mutex_t * Mutex::getMutex() {

   return this->mutex;

}

