#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <sys/wait.h>
#include <curses.h>
#include "Semaforo.h"
#include "Mutex.h"

int subir(int i, struct Compartido *d);
int verificarCuerda(int z);
int bajar(int i, struct Compartido *e);
int monos(int i, int dir, struct Compartido * c);

Semaforo *izq;
Semaforo *der;
Mutex *mutex;

struct Compartido{
	int limite = 0;
	int izqE = 0;
	int derE = 0;
	int confirma = 0;
	int direccion = 0;
	int direccion2 = 0;
	int entra1 =0;
	int entra2 = 0;
	int resistencia = 0;
};

int id = 0;
int N;

int subir(int x, struct Compartido *d){
	if(d-> direccion == 1){
	fprintf(stderr, "Se subio el mono %d de derecha\n", x);
	d->direccion2 = 1;
	}else{
	fprintf(stderr, "Se subio el mono %d de izquierda\n", x);
	d->direccion2 = 0;
	}
	
	return 0;
}


int verificarCuerda(int z){
	if (z == 3 ){
		fprintf(stderr, "Se rompio la cuerda por exceso de monos.\n");
		kill(0, SIGKILL);
	}
	return 0;
}

int bajar(int x, struct Compartido *e){

	if(e->direccion2 == 1){
	fprintf(stderr, "Se bajo el mono %d de derecha\n", x);
	}else{
	fprintf(stderr, "Se bajo el mono %d de izquierda\n", x);
	}
	
	return 0;
}

int monos(int i, int dir,  struct Compartido * c){
	if(dir == 0){
		if(c->direccion == 1 && c->derE > 0){
		mutex->Lock();
		c->entra2++;
		mutex->Unlock();
			izq->Wait();
		}
		
		mutex->Lock();
		subir(i, c);
		c->resistencia++;
		c->izqE--;
		c->limite++;
		mutex->Unlock();
		verificarCuerda(c->resistencia);
		
		
		mutex->Lock();
		bajar(i, c);
		c->resistencia--;
		mutex->Unlock();
		
		mutex->Lock();
		if((c->limite == 5 || c->izqE == 0) ){
			c->limite = 0;
			for(int x =0 ; x <c-> entra1; x++){
			der->Signal();
			}
			c->direccion = 1;
			c->entra1 = 0;
		}
		mutex->Unlock();
	}else{
		if(c->direccion == 0 && c->izqE > 0){
		mutex->Lock();
		c->entra1++;
		mutex->Unlock();
			der->Wait();
		}
		
		
		
		mutex->Lock();
		subir(i, c);
		c->resistencia++;
		c->derE--;
		c->limite++;
		mutex->Unlock();
			
		verificarCuerda(c->resistencia);
		
		mutex->Lock();
		bajar(i, c);
		c->resistencia--;
		mutex->Unlock();
		mutex->Lock();
		if((c->limite == 5 || c->derE == 0) ){
			c->limite = 0;
			for(int y =0 ; y <c-> entra2; y++){
			izq->Signal();
			}
			c->direccion = 0;
			c->entra2 = 0;
		}
		
		mutex->Unlock();
	}
	_exit(0);
	return 0;
}

int main(int argc, char **argv){
	
        mutex = new Mutex();
	int i = 0;
	int r;
	if ( argc > 1 ) {
    
      		N = atoi( argv[ 1 ] );
   	}else{
   		N = 10;
   		printf("Se va a ejecutar con 10 monos por no ingresar un dato para el total de monos.\n");
   	}
	
	id = shmget( IPC_PRIVATE, sizeof(Compartido), 0600|IPC_CREAT);
	if ( -1 == id ) {
           perror( "main" );
           exit( 0 );
        }
        struct Compartido *barranco;
        barranco = (struct Compartido *) shmat(id, NULL, 0);
        izq = new Semaforo(0);
        der = new Semaforo(0);
        srand(time(NULL));
        
        for(i = 0; i < N; i++){
        	 r = rand();
        		if(!fork()){
        			srandom( getpid() );
        			if(random() & 0x1 > 0){
        			mutex->Lock();
        				barranco -> izqE++;
        				mutex->Unlock();
        				monos(i, 0, barranco);
        			}else{
        			mutex->Lock();
        				barranco -> derE++;
        				mutex->Unlock();
        				monos(i, 1, barranco);
        			}
        		
        		}
        }
        for (i=0; i<N; i++) {
      	   wait(&r);
        }
        shmdt( (const void *) barranco );
        shmctl( id, IPC_RMID, NULL );
        return 0;

}
