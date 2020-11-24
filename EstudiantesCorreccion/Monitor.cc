
#include <stdio.h> 
#include "Monitor.h"

Monitor::Monitor(){

   this->workers = 0;
    internalWaitMechanism=new Mutex();
}


Monitor::Monitor(int workers) {
   semaforo = new Semaforo(workers, 1);
   
}

Monitor::~Monitor() {
	free(semaforo);
	delete this->internalWaitMechanism;
   
}



void Monitor::Wait( Mutex * affectedLock ) {

   	this->workers++;
   	affectedLock->Unlock();
   	internalWaitMechanism->Lock();
	affectedLock->Lock();
} 


void Monitor::Wait(int cual1, int cual2){
	semaforo->SP(cual1, cual2);
}

  

void Monitor::NotifyOne() {
   if ( this->workers > 0 ) {	
       internalWaitMechanism->Unlock();
       this->workers--;
   }

}



void Monitor::Signal() {

   this->NotifyOne();

}

void Monitor::Signal(int cual1, int cual2){
	semaforo->SV(cual1, cual2);
}

