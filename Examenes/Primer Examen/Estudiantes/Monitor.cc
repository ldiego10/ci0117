#include <stdio.h>

#include "Monitor.h"

Monitor::Monitor(int workers) {
   semaforo = new Semaforo(workers, 1);
   
}

Monitor::~Monitor(){
	free(semaforo);
}

void Monitor::Wait(int cual1, int cual2){
	semaforo->SP(cual1, cual2);
}

void Monitor::Signal(int cual1, int cual2){
	semaforo->SV(cual1, cual2);
}
