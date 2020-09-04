#include "Semaforo.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define KEY 0xA12345

Semaforo::Semaforo(int valorInicial){//CONSTRUCTOR

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
	valor.val = valorInicial;
	resultado = semctl(this->id, 0, SETVAL, valor);
	if(-1 == resultado){
		perror("Semaphore::Semaforo valor incial");
		exit(3);
	}
	this->creador = getpid();
}

Semaforo::~Semaforo(){//DESTRUCTOR.
	int resultado;
	if(this->creador == getpid()){
		resultado = semctl(this->id, 0, IPC_RMID);
		if(1 == resultado){
			perror("Semaforo::~Semaforo");
			exit(4);
		}
	}
}

int Semaforo::Signal() {
   int resultado = -1;
   struct sembuf signal;
   signal.sem_num = 0;
   signal.sem_op = +1;
   signal.sem_flg = 0;
   resultado = semop (this -> id, &signal, 1);
   if(1 == resultado){
       perror("Semaforo::Signal");
       exit(5);
   }
   return resultado;

}

int Semaforo::Wait() {
   int resultado = -1;
   struct sembuf wait;
   wait.sem_num = 0;
   wait.sem_op = -1;
   wait.sem_flg = 0;
   resultado = semop (this -> id, &wait, 1);
   if(1 == resultado){
       perror("Semaforo::Wait");
       exit(6);
   }
   return resultado;

}

void Semaforo::Signal(int x, int y, int z, int idT){
   int resultado = -1;
   struct sembuf signal;
   signal.sem_num = x;
   signal.sem_op = y;
   signal.sem_flg = z;
   resultado = semop (idT, &signal, 1);
   if(1 == resultado){
       perror("Semaforo::Signal");
       exit(7);
   }
}

void Semaforo::Wait(int x, int y, int z, int idT){
   int resultado = -1;
   struct sembuf wait;
   wait.sem_num = x;
   wait.sem_op = y;
   wait.sem_flg = z;
   resultado = semop (idT, &wait, 1);
   if(1 == resultado){
       perror("Semaforo::Wait");
       exit(8);
   }
}
