#include "Semaforo.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#define N       100


int H( int, struct Agua * a );
int O( int, struct Agua * a );

Semaforo *sO;	
Semaforo *sH;	

struct Agua {
        int cO = 0;
        int cH = 0;
};


int id = 0;



int main(){
        int i = 0;
        int r;

        id = shmget( 0xABCDEF, sizeof( Agua ), 0600 | IPC_CREAT );
        if ( -1 == id ) {
           perror( "main" );
           exit( 0 );
        }
	struct Agua * agua;
        agua = (struct Agua * ) shmat( id, NULL, 0 );
        sH = new Semaforo(0);
	sO = new Semaforo(0);
	
        srand( time( NULL ) );

        for(i=0; i<N; i++) {
		int r = rand();
			if ( ! fork()) {  
				usleep(1000);     
             			if ( r % 2 ) {
                			printf( "Se toma un atomo de oxigeno [%d]\n", i );
                			O( i, agua );
             			}else{
                			printf( "Se toma un atomo de hidrogeno [%d]\n", i );
                			H( i, agua );
             			}
          		}
          		usleep(1000);

        }

        for (i=0; i<N; i++) {
      	   wait(&r);
        }
        
        shmdt( (const void *) agua );
        shmctl( id, IPC_RMID, NULL );
}      



int O( int i, struct Agua * a ){
	if ( a->cH > 1 ) {
	   a->cH -= 2;
	   sH->Wait();
	   sH->Wait();
	  // MakeWater();
	  printf( "Molecula de agua creada [%d] \n", i );
	} else {
	   a->cO++;
	   sO->Signal();
	}
        exit( 0 );
        return 0;
}

int H( int i, struct Agua * a ){
	if ( ( a->cH > 0) && (a->cO > 0) ) {
	   a->cH --;
	   a->cO --;
	   sH->Wait();
	   sO->Wait();
	   //MakeWater
	   printf( "Molecula de agua creada [%d] \n", i );
	} else {
	   a->cH++;
	   sH->Signal();
	}
	exit( 0 );
	return 0;
}
