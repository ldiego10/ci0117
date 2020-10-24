#ifndef _CONDITION_H
#define _CONDITION_H
#include <stdio.h>
#include <stdlib.h>
#include "Lock.h"

class Condition{
	public:
		Condition();
		~Condition();
		void Signal();
		void Wait(Lock*);
		
	private:
		Lock *lock;
		int contador;
};
#endif
