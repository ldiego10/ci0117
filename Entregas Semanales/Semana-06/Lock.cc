#include "Lock.h"

/*
 *  Creates a lock, using a mutex
 */
Lock::Lock() {
	this->mutex = new Mutex();
}


/**
 * Destroys the lock
 */
Lock::~Lock() {
	delete this->mutex;
}


/**
 * Acquires the lock
 *
 */
void Lock::Acquire() {
	this->mutex->Lock();
} 

  
/**
 * Release the lock
 *
 */
void Lock::Release() {
	this->mutex->Unlock();
}


