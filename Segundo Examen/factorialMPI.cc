#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <mpi.h>

//El equipo tiene 4 cores

using namespace std;

int primerN;


int obtenerSiguiente(int actual, int commsz){
	int siguiente = 0;
	if(actual == commsz-1){
		siguiente = 0;
	}else{
		siguiente = actual + 1;
	}
	return siguiente;
}


int obtenerAnterior(int actual, int commsz){
	int anterior = 0;
	if(actual == 0){
		anterior = commsz - 1;
	}else{
		anterior = actual - 1;
	}
	return anterior;
}


void calcularFactorial(int rank, int commsz){
	int entra = 0;
	long valorActual = 0;
	int numSiguiente = 0;
	while(entra != -1){
		int anterior = obtenerAnterior(rank, commsz);
		MPI_Recv(&entra, 1, MPI_INT, anterior, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(entra != -1){
	
			MPI_Recv(&valorActual, 1, MPI_LONG, anterior, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&numSiguiente, 1, MPI_INT, anterior, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(numSiguiente > 1){
				
				
			    numSiguiente--;
			    valorActual = valorActual * numSiguiente;
			    
			    
				int siguiente = obtenerSiguiente(rank, commsz);
				MPI_Send(&siguiente, 1, MPI_INT, siguiente, 1, MPI_COMM_WORLD);
		    	MPI_Send(&valorActual, 1, MPI_LONG, siguiente, 2, MPI_COMM_WORLD);
		    	MPI_Send(&numSiguiente, 1, MPI_INT, siguiente, 3, MPI_COMM_WORLD); 
		    }else{
		    	entra = -1;
		    	cout << "Entra rank: " << rank << " con valor total " << valorActual << endl;
		    	
		    }
		    
			
		}
	}

}


int main(int argc, char ** argv){
	int rank, commsz;
	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &commsz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	primerN = atoi(argv[1]);
	
	if(rank == 0){
		int siguiente = 1;
		long valorActual = primerN;
		int numSiguiente = valorActual ;
		MPI_Send(&siguiente, 1, MPI_INT, siguiente, 1, MPI_COMM_WORLD);
		MPI_Send(&valorActual, 1, MPI_LONG, siguiente, 2, MPI_COMM_WORLD);
		MPI_Send(&numSiguiente, 1, MPI_INT, siguiente, 3, MPI_COMM_WORLD); 
	}
	
	calcularFactorial(rank, commsz);
	
	

}
