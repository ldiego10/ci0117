#include "Condition.h"

Condition::Condition(){
	this->contador = 0;
	this->lock= new Lock();
}

Condition::~Condition(){
	delete this->lock;
}

void Condition::Signal(){
	if(0 < this->contador){
		this->contador--;
		lock->Release();
	}
}

void Condition::Wait(Lock * lockP){
	this->contador++;
	lockP->Release();
	lock->Acquire();
	lockP->Acquire();
}
