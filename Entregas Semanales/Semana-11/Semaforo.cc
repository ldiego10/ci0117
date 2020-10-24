#include "Semaforo.h"

Semaforo::Semaforo(int semaforos){
	this->semaforos = semaforos;
	omp_init_lock(&this->semaforo);
	if(this->semaforos <= 0){
		this->semaforos = 0;
		omp_set_lock(&this->semaforo);
	}
}

Semaforo::~Semaforo(){
	omp_destroy_lock(&this->semaforo);
}

void Semaforo::Wait(){
	#pragma omp critical
	{
	if(this->semaforos > 0 || this->semaforos < 0){
		this->semaforos--;
	}
	}
	omp_set_lock(&this->semaforo);
}

void Semaforo::Signal(){
	if(this->semaforos == 0){
		omp_unset_lock(&this->semaforo);
	}
	#pragma omp critical
	{
		this->semaforos++;
	}
	
	
}

int Semaforo::getSemaforos(){
	return this->semaforos;
}	


