/**
 * Problema del comedor estudiantil
 * 
 * Author: Programacion Concurrente (Francisco Arroyo)
 * Version: 2020/Oct/02
 *
 * Primer examen parcial
 * Grupo-2
 *
 * Suposicion:
 * Cada estudiante puede esperar lo que sea necesario
 * Aunque un estudiante se el primero en compraralmuerzo igual el junto a otro pueden ser los ultimos en irse.
**/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "Monitor.h"

Mutex * mutex;
Monitor * monitor;
int estudiantesSentados;

struct Datos{
	int totales = 0;
	int espera = 0;
};

void esperaFin(int cual, struct Datos * d){
       
   	sleep(3);
   	if(d->espera == 0){
      		d->espera++; 
      		printf("El estudiante %d espera a su companero \n", cual);
      		monitor->Wait(mutex);
  	}else{
      		printf("El estudiante %d termina\n",cual);
      		monitor->NotifyOne();
   	}
}


int ComprarAlmuerzo( int cual ) {
   	mutex->Lock();
   	int espera;
        printf("El estudiante %d compra\n", cual);
   	espera = random() & 0x3;
   	mutex->Unlock();
   	sleep( espera );
   	return espera; 
}

int Almorzar(int cual){
	mutex->Lock();
   	int espera;
   	printf("El estudiante %d almuerza\n", cual);
   	espera = random() & 0x3;
   	mutex->Unlock();
   	sleep( espera );
   	return espera;
}

int Salir(int cual, struct Datos * d){
int espera = 0;
	mutex->Lock();
	printf("Totales: %d\n", d->totales);
   	if(d->totales <= 2){
   		d->totales--;
      		esperaFin(cual, d);
   	}
  	d->totales--;
   	
   	printf("El estudiante %d se va\n", cual);
   	mutex->Unlock();
   	return espera;

}


int Estudiante( int cual, struct Datos * d, long w ) {
   	srand( getpid() );
   	sleep(1);
        printf( "Se produjo un estudiante %d\n", cual );
   	d->totales = w;
   	ComprarAlmuerzo(cual);
   	Almorzar(cual);
   	Salir(cual, d);
   	exit( 0 );
}


int main( int argc, char ** argv ) {
   	long workers;
   	int worker, pid, memId;
  	mutex = new Mutex();
  	monitor = new Monitor();
   	workers = 10;  
   	if ( argc > 1 ) {
      		workers = atol( argv[ 1 ] );
   	}
   	struct Datos * datos = new Datos();
   	datos->totales = workers;
   	
   	memId = shmget( IPC_PRIVATE, sizeof( Datos), 0600 | IPC_CREAT );
   	datos = (struct  Datos *) shmat( memId, NULL, 0 );
   	
   	for ( worker = 0; worker < workers; worker++ ) {
      		pid = fork();
      		if ( ! pid ) {
         		Estudiante( worker, datos, workers);
      		}
   	}

	for ( worker = 0; worker < workers; worker++ ) {
              int status;
	      pid_t pid = wait( &status );
	}
   	free(mutex);
   	shmdt( datos );
   	shmctl( memId, IPC_RMID, NULL );
}
