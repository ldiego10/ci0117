
#ifndef MONITOR_H
#define MONITOR_H
#include "Semaforo.h"
#include <cstdlib>

class Monitor {
	public:
		Monitor(int);
		~Monitor();
		void Signal(int, int);
		void Wait(int, int);
	
	private:
		Semaforo *semaforo;
};
#endif
