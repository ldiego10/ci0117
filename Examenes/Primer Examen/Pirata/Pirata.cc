#include <iostream>
#include <list>
#include <pthread.h>
#include <thread>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include <mutex>
using namespace std;

char *collar;
pthread_mutex_t * mutexT;

void collarSerial(int cantidad, char *collar){
int indice = 0;
int contador3 = 0;
int y = 0;
	for(int w = 0; w < cantidad; w++){
	indice =0;
	int indice2 =0;
	int contador = 0;
	int contador2 = 0;
    	for(int x = 0; x < cantidad; ++x){
    		if(collar[contador2] != collar[indice2] && collar[contador2] != 'T'){
    			if(contador < contador2){
    				contador = contador2;
    				contador2 = 0;
    				indice = indice2;
    			}
    			indice2 = x;
    		}else{
    			contador2++;
    			
    		}
    	}
    	y = 0;
    	int contador4 = indice;
    	while(collar[contador4] == collar[indice] || collar[contador4] == 'T' ){
    		if (contador4 == cantidad){
    			contador4 = 0;
    			y++;
    		}else{
    			contador4++;
    			y++;
    		}
    	}
    	int z = indice -1;
    	contador3 = 0 ;
    	
    	while((collar[z] == collar[indice-1] || collar[z] == 'T') ){
    		if(z == 0){
    			z = cantidad;
    			contador3++;
    		}else{
    			z--;
    		        contador3++;
    		}       
    	}
    	}	
    	printf("El punto donde cortar es %d y se gana %d perlas.\n", indice, contador3 + y );

}

struct Cantidad{
   	int empieza = 0;
   	int acaba = 0;
   };

int indice =0;
	int indice2 =0;
	int contador = 0;
	int contador2 = 0;
	int y = 0;
	int contador3 = 0 ;
    	
void collarThread(Cantidad * c){

    	for(int x =c->empieza; x < c->acaba; ++x){
    		if(collar[contador2] != collar[indice2] && collar[contador2] != 'T'){
    			if(contador < contador2){
    				contador = contador2;
    				indice = indice2;
    			}
    			indice2 = x;
    		}else{
    			contador2++;
    			
    		}
    	}
    	int contador4 = indice;
    	while(collar[contador4] == collar[indice] || collar[contador4] == 'T' ){
    		if (contador4 == c->acaba){
    			contador4 = 0;
    			y++;
    		}else{
    			contador4++;
    			y++;
    		}
    	}
    	int z = indice -1;
    	while((collar[z] == collar[indice-1] || collar[z] == 'T') ){
    		if(z == 0){
    			z = c->acaba;
    			contador3++;
    		}else{
    			z--;
    		        contador3++;
    		}       
    	}
    	pthread_exit(0);	
    	printf("El punto donde cortar es %d y se gana %d perlas.\n", indice, contador3 + y );


    	
}

void versionParalela(long hilos, int cantidad){
   long hilo;
   std::vector< std::thread * > trabajadores;
   
   Cantidad *c = new Cantidad();
   c->acaba = cantidad;

   mutexT = (pthread_mutex_t *) calloc( 1, sizeof( pthread_mutex_t ) );
   pthread_mutex_init( mutexT, NULL );

   for ( hilo = 0; hilo < hilos; hilo++ ) {
      c->empieza = hilo;
      std::thread * nuevo  = new std::thread( collarThread, c);
      trabajadores.push_back( nuevo );
   }

   for ( auto h: trabajadores ) {
      h->join();
   }

   pthread_mutex_destroy( mutexT );
   free( mutexT );

   

}

void startTimer( struct timeval * timerStart) {
   gettimeofday( timerStart, NULL );
}

double getTimer( struct timeval timerStart ) {
   struct timeval timerStop, timerElapsed;

   gettimeofday(&timerStop, NULL);
   timersub(&timerStop, &timerStart, &timerElapsed);
   return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}


int main(int argc, char **argv){
	 struct timeval timerStart;
	 double used;
	int aleatorio;
	int cantidad;
	int hilos = 200;
	srand(time(NULL));
	
	if(argc>1){
		cantidad = atoi(argv[1]);
	}else{
		cantidad = 2000;
	}
	
	if(argc > 2){
		hilos = atoi(argv[2]);
	}
	collar = (char *) malloc(sizeof(char) * (cantidad + 1));
	for(int x = 0; x < cantidad; x++){
		aleatorio = rand() % 3;
		if(aleatorio == 0){
			collar[x] = 'N';
		}else if(aleatorio == 1){
			collar[x] = ('B');
		
		}else{
			collar[x] = ('T');
		}
		
	}
	startTimer( & timerStart );
	collarSerial(cantidad, collar);
	used = getTimer( timerStart );
   printf( "Version Serial: Dura %lf ms\n", used );
   
        int division = cantidad/hilos;
        
        startTimer( & timerStart );
        versionParalela(hilos, cantidad);
        used = getTimer( timerStart );
        printf( "Version paralela: Dura %lf ms\n", used );
	
}
