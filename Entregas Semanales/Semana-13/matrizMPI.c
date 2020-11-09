/**
 *  Tabla comparativa para mi algoritmo de multiplicación de matrices

	┌────────┬────────┬────────┬────────┬────────┐
	│ Trabaj │ Serial │PThreads│ OpenMP │  MPI   │
	├────────┼────────┼────────┼────────┼────────┤
	│    2   │7.6860ms│2.7080ms│0.005467│0.000179│
	├────────┼────────┼────────┼────────┼────────┤
	│    4   │4.8980ms│2.1550ms│0.006858│0.017702│
	├────────┼────────┼────────┼────────┼────────┤
	│    8   │11.006ms│8.7540ms│0.016751│0.046099│
	├────────┼────────┼────────┼────────┼────────┤
	│   16   │4.1440ms│2.0920ms│0.006657│0.146192│
	├────────┼────────┼────────┼────────┼────────┤
	│   64   │9.5290ms│2.5350ms│0.014358│0.895027│
	└────────┴────────┴────────┴────────┴────────┘
	Tiempo empleado en segundos (ms) para matrices de dimensión 100
	
	//Ejecutar como mpiexec -n 16 ./matrizMPI.out  EL 16 representa la cantidad de trabajadores	
 *
**/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int rank;
  int commsz;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &commsz);
  int tamano = 100; //Debe modificar el tamano directamente desde el codigo.
  int contador = 0;
  double comienza,termina;
  int** matB = (int**)malloc((tamano*tamano*sizeof(int)));
  for (int i = 0; i < tamano; i++) {
        matB[i] = (int*)malloc((tamano*sizeof(int)));
  }
  srandom(time(NULL)); 
  int *matA=(int*) malloc(tamano*tamano*sizeof(int));
  for(int i=0; i < tamano; i++){
    for(int j=0; j < tamano; j++){
          matA[j+i*tamano]= (rand() % 10)+1; 
          matB[i][j] = (rand() % 10)+1;
    }
  } 
  comienza=MPI_Wtime();
  int* resultado=(int*)malloc(tamano*sizeof(int));
  MPI_Scatter(matA,tamano,MPI_INT,resultado,tamano,MPI_INT,0,MPI_COMM_WORLD);
  int i, j, total = 0;
  int* totales = (int*)malloc(tamano*sizeof(int));
  for(i = 0; i < tamano; i++){
      int* matrizArreglo = (int*)malloc(tamano*sizeof(int));
      for (int k=0;k<tamano;k++){
        matrizArreglo[k] = matB[k][i];
      }
      int* columna = matrizArreglo; 
      for (j = 0; j < tamano; j++) {
        total += resultado[j] * columna[j];
      }
      totales[i] = total;
      total = 0;
  }
  resultado = totales;
  if(rank == 0){
   /* printf("Primera matriz\n"); 
    for (int i = 0; i < tamano*tamano; i++) { 
       printf("%d ", matA[i]);
       contador++;
       if(contador == tamano){
           contador = 0;
           printf("\n");	
       }
    } */
   /* printf("Segunda matriz\n");
    for (int i = 0; i < tamano; i++) { 
        for (int j = 0; j < tamano; j++) {
           printf("%d ",matB[i][j]);  
        }         
        printf("\n");
    } */
  }
  int *matC=(int*)malloc(tamano*tamano*sizeof(int));
  MPI_Gather(resultado,tamano,MPI_INT,matC,tamano,MPI_INT,0,MPI_COMM_WORLD);
  if(rank == 0){
    printf("Resultado\n"); 
     for (int i = 0; i < tamano*tamano; i++) { 
        /* printf("%d ", matC[i]);
         contador++;
         if(contador == tamano){
             contador = 0;
             printf("\n");	
         }*/
     }
     termina=MPI_Wtime();
     printf("El tiempo total es de: %fms\n",termina-comienza); 
  }
  MPI_Finalize();
  free(matA);
  free(matB);
  free(matC);
}

