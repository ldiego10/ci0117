/**
 *  Cantidad de cores en su equipo: 4
 *
 *	┌────────┬────────┬───────┐
 *	│ Serial │ OpenMP │ Hilos │
 *	├────────┼────────┼───────┤
 *	│6.2200ms│1.3800ms│   2   │
 *	├────────┼────────┼───────┤
 *	│5.5940ms│2.0230ms│   4   │
 *	├────────┼────────┼───────┤
 *	│6.4210ms│3.7690ms│   16  │
 *	├────────┼────────┼───────┤
 *	│9.1470ms│5.7260ms│   32  │
 *	├────────┼────────┼───────┤
 *	│6.7630ms│5.5970ms│   64  │
 *	└────────┴────────┴───────┘
 *   Tiempo empleado en mili-segundos (ms) para matrices de dimensión 100
**/


#include <bits/stdc++.h> 
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <cmath>

using namespace std; 
 pthread_mutex_t * mutexT; 
int tamano;
int threadsCant;
struct Matriz{
	int **matA;
	int **matB;
	int **matC;
} m;
    
int procI = 0; 

void startTimer( struct timeval * timerStart) {
   gettimeofday( timerStart, NULL );
}

double getTimer( struct timeval timerStart ) {
   struct timeval timerStop, timerElapsed;

   gettimeofday(&timerStop, NULL);
   timersub(&timerStop, &timerStart, &timerElapsed);
   return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}

void* multiplicarMatrix(void* arg) 
{ 
    struct Matriz *args = (struct Matriz *) arg;
    int procesos = procI++;
    int i = procesos;
    long resultado = 0;
      while(i < procesos+1){
        if(i < tamano){
        for (int j = 0; j < tamano; j++) { 
            for (int k = 0; k < tamano; k++){ 
               resultado += args->matA[i][k] * args->matB[k][j];
            } 
            pthread_mutex_lock( mutexT );
               args->matC[i][j] += resultado;
                pthread_mutex_unlock( mutexT );
        }
        }
        i++;
        }
  
   pthread_exit( 0 );
} 
  

int main() 
{ 
    pthread_t * threads;
    struct timeval timerStart;
    char tamanoC = ' ';

    clock_t comienzo;
    clock_t fin;
    double used, wused;
   
        printf("Ingrese un numero entero para la cantidad de filas en la matriz cuadrada: ");
        scanf(" %d", &tamano);
        printf("Ingrese la cantidad de threads a usar: ");
        scanf(" %d", &threadsCant);
    
    struct Matriz r;
    
    r.matA = new int*[tamano];
for(int i = 0; i < tamano; i++)
    r.matA[i] = new int[tamano];
    
    r.matB = new int*[tamano];
for(int i = 0; i < tamano; i++)
    r.matB[i] = new int[tamano];
    
    r.matC = new int*[tamano];
for(int i = 0; i < tamano; i++)
    r.matC[i] = new int[tamano];
    
    int contador = 0;
    srand(time(NULL));
    for (int i = 0; i < tamano; i++) { 
        for (int j = 0; j < tamano; j++) { 
            r.matA[i][j] = rand() % 10; 
            r.matB[i][j] = rand() % 10; 
        } 
    } 
  
    
    printf("Primera matriz\n"); 
    for (int i = 0; i < tamano; i++) { 
        for (int j = 0; j < tamano; j++)  
            printf("%d ",r.matA[i][j]); 
        printf("\n"); 
    } 
  
    
    printf("Segunda matriz\n");
    for (int i = 0; i < tamano; i++) { 
        for (int j = 0; j < tamano; j++)  
           printf("%d ",r.matB[i][j]);           
        printf("\n"); 
    } 
  
  
   

   mutexT = (pthread_mutex_t *) calloc( 1, sizeof( pthread_mutex_t ) );
   pthread_mutex_init( mutexT, NULL );
   threads = (pthread_t *) calloc( threadsCant, sizeof( pthread_t ) );
    startTimer( & timerStart );
   while(contador < tamano){ 
    for (int i = 0; i < threadsCant; i++) { 
        contador++;
        int* p; 
        pthread_create(&threads[i], NULL, &multiplicarMatrix, (void*) &r);
   
    }
    }
  used = getTimer( timerStart );
    for (int i = 0; i < threadsCant; i++)  
        pthread_join(threads[i], NULL);     
  

    free( threads );
   pthread_mutex_destroy( mutexT );
   free( mutexT );
   
   
   printf( "Version paralela: con %d hilos el tiempo es %lf ms.\n", threadsCant, used);
    
    
    
    
    printf("Resultado\n"); 
    for (int i = 0; i < tamano; i++) { 
        for (int j = 0; j < tamano; j++)  
           printf("%d ",r.matC[i][j]);           
        printf("\n");  
    } 
    
    
   startTimer( & timerStart );

   for (int x = 0; x < tamano; x++) {
      for (int y = 0; y < tamano; y++) {
         for (int z = 0; z < tamano; z++) {
            r.matC[x][y] += r.matA[x][z] * r.matB[z][y];
         }
      }
   }
   
    used = getTimer( timerStart );
   printf( "Version Serial: Dura %lf ms\n", used );
    
    for(int i = 0; i < tamano; i++)
        delete[] r.matA[i];
    delete[] r.matA;
    
    for(int i = 0; i < tamano; i++)
       delete[] r.matB[i];
    delete[] r.matB;
    
    for(int i = 0; i < tamano; i++)
       delete[] r.matC[i];
    delete[] r.matC;
    
    return 0; 
} 
