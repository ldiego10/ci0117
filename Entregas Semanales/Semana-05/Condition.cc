
#include "Condition.h"
#include <stdio.h>
/*
 *  Creates a new condition variable
 *
 *  Uses an internal structure to make workers wait for resources
 *
**/
Condition::Condition() {

   this->workers = 0;
   this->internalWaitMechanism = new Lock();	// Could be any other mechanism

}


/**
 * Destroys our condition variable
**/
Condition::~Condition() {

   delete this->internalWaitMechanism;

}


/**
 *  Wait for the condition controlled by our variable
 *
**/
void Condition::Wait( Lock * affectedLock, int x ) {

   this->workers++;
   affectedLock -> Release();
   this->internalWaitMechanism ->Acquire();

} 

  
/**
 *  Notify one worker from the queue, if empty has no effect
 *
**/
void Condition::NotifyOne(int x) {

   if ( this->workers > 0 ) {
      	// One
   // To be completed by students
     
      this->workers--;
   }

}


/**
 *  Same method as notify one, declared for compatibility with many examples
 *
**/
void Condition::Signal(int x) {

   this->NotifyOne(x);
 this->internalWaitMechanism->Release();
}


/**
 *  Signal all workers from the queue, if empty has no effect
 *
**/
void Condition::NotifyAll() {

   while ( this->workers > 0 ) {
      this->workers--;
   // To be completed by students
   }

}

