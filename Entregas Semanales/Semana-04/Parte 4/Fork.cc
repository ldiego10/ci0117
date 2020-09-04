
#include "Lock.h"

/*
 *  Creates a lock, using a semaphore
 */
Lock::Lock() {

   this->lock = new Semaphore( 1 );

}


/**
 * Destroys the lock
 */
Lock::~Lock() {

   delete this->lock;

}


/**
 * Acquires the lock
 *
 */
void Lock::Acquire() {

   this->lock->Wait();

} 

  
/**
 * Release the lock
 *
 */
void Lock::Release() {

   this->lock->Signal();

}

