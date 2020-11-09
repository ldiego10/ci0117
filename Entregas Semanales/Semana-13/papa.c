//Ejecutar como  mpiexec -n 4 ./papa.out  El 4 representa 4 jugadores, pueden ser mas o menos.

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
#include <mpi.h>

int vivos;
int valorActual;


int anterior(int id, int N){
   if(id == 0)
   {
     return N - 1;
   }
   return id-1;
}

int cambiarPapa(int papa){
    if (1 == (papa & 0x1))
    {                                  
        papa = (papa << 1) + papa +  1; 
    }
    else
    {
        papa >>= 1; 
    }
    return papa;
}

int participante(int IdActual, int N, int siguiente, int antiguo){                       
    int vivo = 1; 
    while (vivos != 0)
    {
    MPI_Recv(&valorActual,1,MPI_INT,antiguo,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    MPI_Recv(&vivos,1,MPI_INT,antiguo,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);  
    if(vivos != 0){
    	if(vivo == 1){
    		printf("El jugador %d tiene la papa con valor %d\n",IdActual,valorActual);
    		valorActual=cambiarPapa(valorActual);
    		if(valorActual == 1){
            	printf("Perdio el jugador %d\n\n",IdActual);
            	valorActual= rand()%100+2;
            	vivos--;
            	vivo = 0;
            }
        }
    }
    else{
    	if(vivo == 1){
    		printf("Gano el jugador %d\n",IdActual);
        }
    }  	
    if(vivos==1){
    	vivos = 0;
    }
    MPI_Send(&valorActual,1,MPI_INT,siguiente,0,MPI_COMM_WORLD);   
    MPI_Send(&vivos,1,MPI_INT,siguiente,0,MPI_COMM_WORLD);   
    }   
}

int main(int argc, char **argv){
    int rank;
    int commsz;
    int actual;
    srand(time(NULL));
    valorActual = rand()%100+2;                             
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &commsz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vivos=commsz;
    actual=rand()%commsz;
    if(rank==anterior(actual, commsz)){
        MPI_Send(&valorActual,1,MPI_INT,actual,0,MPI_COMM_WORLD);
        MPI_Send(&vivos,1,MPI_INT,actual,0,MPI_COMM_WORLD);
    }
    participante(rank, commsz, (rank+1)%commsz, anterior(rank, commsz));
    MPI_Finalize();
    return 0;
}
