#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/shm.h>
#include <wait.h>
#include "Buzon.h"
#include "Mutex.h"

struct Papa{
	int valorActual = 0;
	int vivo = 0;
	int ID = 0;
};

struct totales{
	int IdActual = 0;
	int verifica = 0;
	int total = 0;
};


int N = 10;
int id = 0;
Mutex *mutex;

int verificarGana(struct totales *l){
	if(l->total == N-1){
		l->verifica = 1;
	}else{
		l->verifica = 0;
	}
	return l->verifica;
}

int cambiarPapa(int valorP){
	 if ( valorP & 1 ) {		
           valorP = valorP * 3 + 1;
        } else {
            valorP = valorP/2;			
        }
   	return valorP;
}

int juegoPapa(struct Papa *p, struct totales *t, Buzon *b){
	mutex->Unlock();
	while(N > 0){
		while(p->ID != t->IdActual){
			mutex->Lock();
			if(t->verifica == 1){
				if(p->vivo == 1){
					fprintf(stderr, "Gano el jugador %d\n", p->ID);
					b->Enviar(-1, 2020);
					mutex->Unlock();
					_exit(0);
				}else{
					mutex->Unlock();
					_exit(0);
				}
			}
			if(t->IdActual == 0){
				t->IdActual = N;
			}
			mutex->Unlock();
		}
		b->Recibir(b->pa.valor, 2020);
		p->valorActual = b->pa.valor;
		if(p->vivo == 1){
			fprintf(stderr, "El jugador %d tiene la papa con valor %d\n",p->ID, p->valorActual);
			p->valorActual = cambiarPapa(p->valorActual);
			if(p->valorActual == 1){
				fprintf(stderr, "Perdio el jugador %d con papa en valor %d\n\n", p->ID, p->valorActual);
				p->vivo = 0;
				t->total++;
				p->valorActual = rand() % 100 + 2;
				b->pa.valor = p->valorActual;
				b->Enviar(b->pa.valor, 2020);
				t->verifica = verificarGana(t);
				t->IdActual = (p->ID + 1) % N;
			}else{
				b->pa.valor = p->valorActual;
				b->Enviar(b->pa.valor, 2020);
				t->IdActual = (p->ID + 1) % N;
			}
		}else{
			fprintf(stderr, "El jugador pasivo %d recibio la papa con valor %d\n",p->ID, p->valorActual);
			b->pa.valor = p->valorActual;
			b->Enviar(b->pa.valor, 2020);
			t->IdActual = (p->ID + 1) % N;
		}
	}
	return 0;
}

int main(int argc, char ** argv){
	int r;
	mutex = new Mutex();
	id = shmget( IPC_PRIVATE, sizeof(totales), 0600|IPC_CREAT);
	if ( -1 == id ) {
           perror( "main" );
           exit( 0 );
        }
        int inicial = 0;
        struct totales *compartido;
        compartido = (struct totales *) shmat(id, NULL, 0);
        
    
	srand(time(NULL));
        
        Buzon *buzon = new Buzon(rand());
        
        if ( argc > 1 ) {
      		N = atoi( argv[ 1 ] );
   	}
   	if ( N <= 0 ) {
     		N = 10;
   	}
   	
   	if ( argc > 1 ) {
      		inicial = atoi( argv[ 2 ] );
   	}
   	if ( inicial <= 0 ) {
     		inicial = rand() % 100 + 1;
   	}
   	
   	buzon->Enviar(inicial, 2020);
   	compartido -> IdActual = rand() % N + 1;
   	int x = 0;
   	
   	for(x = 1; x <= N; x++){
   	fflush(stdout);
   		r = rand();
   		if(!fork()){
   			mutex->Lock();
   			struct Papa persona;
   			persona.ID = x;
   			persona.vivo = 1;
   			juegoPapa(&persona, compartido, buzon);
   		}
   	
   	}
   	for (x=0; x<N; x++) {
      	   wait(&r);
        }
        shmdt( (const void *) compartido );
        shmctl( id, IPC_RMID, NULL );
   	delete(buzon);
   	delete(mutex);
        exit(1);	
}
