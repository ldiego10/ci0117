#include "Buzon.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <sys/msg.h>

#define N       100


int H( int, Buzon b );
int O( int, Buzon b );


struct Agua {
        int cO = 0;
        int cH = 0;
};


int id = 0;



int main(){
        int i = 0;
        int r;
	Buzon m;
        id = shmget( 0xABCDEF, sizeof( Agua ), 0600 | IPC_CREAT );
        if ( -1 == id ) {
           perror( "main" );
           exit( 0 );
        }
	struct Agua * agua;
        agua = (struct Agua * ) shmat( id, NULL, 0 );
	
        srand( time( NULL ) );

        for(i=0; i<N; i++) {
		int r = rand();
			if ( ! fork()) {  
				usleep(1000);     
             			if ( r % 2 ) {
                			printf( "Se toma un atomo de oxigeno [%d]\n", i );
                			O( i, m);
             			}else{
                			printf( "Se toma un atomo de hidrogeno [%d]\n", i );
                			H( i, m );
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



int O( int i, Buzon b ){
	b.Recibir(b.a.cO, b.a.cH, 2020);
	if ( b.a.cH > 1 ) {
	   b.a.cH -= 2;
	  // MakeWater();
	  b.Enviar(b.a.cO, b.a.cH, 2020);
	  printf( "Molecula de agua creada [%d] \n", i );
	} else {
	   b.a.cO++;
	   b.Enviar(b.a.cO, b.a.cH, 2020);
	}
        exit( 0 );
        return 0;
}

int H( int i, Buzon b ){
	b.Recibir(b.a.cO, b.a.cH, 2020);
	if ( ( b.a.cH > 0) && (b.a.cO > 0) ) {
	   b.a.cH --;
	   b.a.cO --;
	   //MakeWater();
	   b.Enviar(b.a.cO, b.a.cH, 2020);
	   printf( "Molecula de agua creada [%d] \n", i );
	} else {
	   b.a.cH++;
	   b.Enviar(b.a.cO, b.a.cH, 2020);
	}
	exit( 0 );
	return 0;
}
