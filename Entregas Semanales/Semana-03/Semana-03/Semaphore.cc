/*
 *  C++ class to encapsulate Unix semaphore intrinsic structures and system calls
 *  Author: Programacion Concurrente (Francisco Arroyo)
 *  Version: 2020/Ago/08
 *
 * Ref.: https://en.wikipedia.org/wiki/Semaphore_(programming)
 *
 */

#include "Semaphore.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


Semaphore::Semaphore( int ValorInicial ) {
	int resultado;
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *_buf;
	}valor;
	this -> id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
	if(-1 == this->id){
		perror("Semaphore::Semaforo construccion del recurso");
		exit(2);
	}
	valor.val = ValorInicial;
	resultado = semctl(this->id, 0, SETVAL, valor);
	if(-1 == resultado){
		perror("Semaphore::Semaforo valor incial");
		exit(3);
	}
	this->creador = getpid();
}


Semaphore::~Semaphore() {
	int resultado;
	if(this->creador == getpid()){
		resultado = semctl(this->id, 0, IPC_RMID);
		if(1 == resultado){
			perror("Semaforo::~Semaforo");
			exit(4);
		}
		printf("Llamando el destructor\n");
	}
}

int Semaphore::Signal() {
   int resultado = -1;
   struct sembuf signal;
   signal.sem_num = 0;
   signal.sem_op = +1;
   signal.sem_flg = 0;
   resultado = semop (this -> id, &signal, 1);
   if(1 == resultado){
       perror("Semaphore::Signal");
       exit(5);
   }
   return resultado;

}

int Semaphore::Wait() {
   int resultado = -1;
   struct sembuf wait;
   wait.sem_num = 0;
   wait.sem_op = -1;
   wait.sem_flg = 0;
   resultado = semop (this -> id, &wait, 1);
   if(1 == resultado){
       perror("Semaphore::Wait");
       exit(6);
   }
   return resultado;

}


