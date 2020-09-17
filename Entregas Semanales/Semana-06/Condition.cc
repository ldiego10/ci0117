#include <stdlib.h>
#include "Condition.h"

/*
 * pthread_cond_init
 */
Condition::Condition() {
   int resultado = 0;
   pthread_condattr_t cattr;
   pthread_condattr_init(&cattr);
   this->vc = (pthread_cond_t *) calloc (1, sizeof(pthread_cond_t)); 
   resultado = pthread_cond_init(this->vc, &cattr);
   
   if (resultado != 0){
   	exit(1);
   }
}


/*
 * pthread_cond_destroy
 */
Condition::~Condition() {
int resultado = 0;
   resultado = pthread_cond_destroy( this->vc );
   free(this->vc);
   if (resultado != 0){
   	exit(2);
   }
}


/*
 * pthread_cond_wait
 */
int Condition::Wait( Mutex * mutex ) {
   int resultado = 0;
   resultado = pthread_cond_wait( this->vc, mutex->getMutex());
   
   if (resultado != 0){
   	exit(3);
   }
   return -1;
}


/*
 * pthread_cond_timedwait
 */
int Condition::TimedWait( Mutex * mutex, long nsec, long sec ) {
   int resultado = 0;
   struct timespec lapso;
   lapso.tv_sec = sec;
   lapso.tv_nsec = nsec;
   resultado = pthread_cond_timedwait(this->vc, mutex->getMutex(), &lapso);
   if(resultado == -1){
   	exit(4);
   }
   return -1;
}


/*
 * pthread_cond_signal
 */
int Condition::Signal() {
   int resultado = 0;
   resultado = pthread_cond_signal( this->vc );
   
   if (resultado != 0){
   	exit(4);
   }
   return -1;
}


/*
 * pthread_cond_broadcast
 */
int Condition::Broadcast() {
   int resultado = 0;
   resultado = pthread_cond_broadcast(this->vc);
   if(resultado == -1){
   	exit(5);
   }
   return -1;
}

