#include "omp.h"

class Semaforo{
	public:
		Semaforo();
		Semaforo(int);
		~Semaforo();
		void Wait();
		void Signal();
		int getSemaforos();
	
	private:
		int semaforos;
		omp_lock_t semaforo;		

};
