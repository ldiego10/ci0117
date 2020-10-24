#include "Lock.h"


Lock::Lock() {
	omp_init_lock(&writelock);
}


/**
 * Destroys the lock
 */
Lock::~Lock() {
	omp_destroy_lock(&writelock);
}


/**
 * Acquires the lock
 *
 */
void Lock::Acquire() {
	omp_set_lock(&writelock);
} 

  
/**
 * Release the lock
 *
 */
void Lock::Release() {
	omp_unset_lock(&writelock);
}


