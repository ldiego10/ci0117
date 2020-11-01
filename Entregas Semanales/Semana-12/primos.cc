
/**
 *  Tabla comparativa

	┌────────┬────────┬───────────┐
	│ Trabaj │ Serial │  OpenMP   │
	├────────┼────────┼───────────┤
	│    2   │0.013ms │0.000164ms │
	├────────┼────────┼───────────┤
	│    4   │0.014ms │0.000816ms │
	├────────┼────────┼───────────┤
	│    8   │0.0110ms│0.000322ms │
	├────────┼────────┼───────────┤
	│   16   │0.0150ms│0.001243ms │
	├────────┼────────┼───────────┤
	│   64   │0.0130ms│0.005787ms │
	└────────┴────────┴───────────┘
	Tiempo empleado en segundos (ms) para 10 términos
 *
 *  Tabla comparativa

	┌────────┬────────┬───────────┐
	│ Trabaj │ Serial │  OpenMP   │
	├────────┼────────┼───────────┤
	│    2   │0.7460ms│0.000534ms │
	├────────┼────────┼───────────┤
	│    4   │0.6170ms│0.001992ms │
	├────────┼────────┼───────────┤
	│    8   │0.8880ms│0.000944ms │
	├────────┼────────┼───────────┤
	│   16   │0.4790ms│0.001010ms │
	├────────┼────────┼───────────┤
	│   64   │0.6170ms│0.002822ms │
	└────────┴────────┴───────────┘
	Tiempo empleado en segundos (ms) para 100 términos
 *
 *  Tabla comparativa

	┌────────┬─────────┬───────────┐
	│ Trabaj │ Serial  │  OpenMP   │
	├────────┼─────────┼───────────┤
	│    2   │388.326ms│0.278493ms │
	├────────┼─────────┼───────────┤
	│    4   │396.107ms│0.276533ms │
	├────────┼─────────┼───────────┤
	│    8   │453.687ms│0.288661ms │
	├────────┼─────────┼───────────┤
	│   16   │380.619ms│0.292735ms │
	├────────┼─────────┼───────────┤
	│   64   │401.067ms│0.273952ms │
	└────────┴─────────┴───────────┘
	Tiempo empleado en segundos (ms) para 1000 términos
 *
**/

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

omp_lock_t lock;

using namespace std;
bool esPrimo(int number){
 for (int i = 2; i < number; i++) {
        if (number % i == 0 && i != number) return false;
    }
    return true;

}

bool esPar(int num){
	if(num % 2 == 0){
		return true;
	}
return false;
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

void serial(int num){
int total = 0;
	for(int k = 6; k <= num; k++){
	total = 0;
		if(esPar(k)){
			for(int  i = 2; i < num && total < num; i++){
				if(esPrimo(i)){
					for(int j = 2; j < num && total < num; j++){
						if(esPrimo(j)){
							if(i+j == k){
								cout << k << "=" << i << "+" << j << endl;
								total = num;	
							}
						}		
					}
				}
			}
		}
	}

}


void paralelo(int num, int trabajadores){
int total = 0;
int  k;
	#pragma omp parallel for num_threads(trabajadores) schedule(dynamic) shared(k) private(total)
	for(k = 6; k <= num; k++){
	total = 0;
		if(esPar(k)){
			for(int  i = 2; i < num && total < num; i++){
				if(esPrimo(i)){
					for(int j = 2; j < num && total < num; j++){
						if(esPrimo(j)){
							if(i+j == k){
								omp_set_lock(&lock);
								cout << k << "=" << i << "+" << j << endl;
								total = num;
								omp_unset_lock(&lock);	
							}
						}		
					}
				}
			}
		}
	}

}




int main (int argc, char *argv[]){
	struct timeval timerStart;
	double used;
	
	omp_init_lock(&lock);
	int n = 0;	
	int t = 0;
	if(argc >= 2){
		n = atoi(argv[1]);
		t = atoi(argv[2]);
	}
	if(n >= 3 && t > 0){
		
		cout << "Version serial:" << endl;
		startTimer( & timerStart );
		serial(n);
		used = getTimer( timerStart );
		printf( "Serial version: Dura %lfms\n", used );
		cout << "\nVersion paralela:" << endl;
		 double start_time = omp_get_wtime();
		paralelo(n, t);
		double time = omp_get_wtime() - start_time;
		printf( "Version OMP: Dura %lfms\n", time );
	}else{
		cout << "Debe ingresar un numero mayor que 3 y trabajadores validos." << endl;
	}	
	return 0;
}


