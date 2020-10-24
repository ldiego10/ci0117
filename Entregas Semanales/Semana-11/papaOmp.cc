/*Modificacion de papa.cc para usar omp
  Se trabajó en la clase 
  Autores:
  Carlos Yulian Loaiza Ledezma B74197
  Luis Diego Esquivel Viquez B82806

  Para compilar:
  g++ -g -Wall -fopenmp papa.cc -lpthread
*/

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
#include <omp.h>
#define MAXPARTICIPANTES 10

int participantes = MAXPARTICIPANTES;
int participanteDeseado;
int valorPapa;
int participantesActivos; 

omp_lock_t lock;
int cambiarPapa( int papa ) {
  if ( 1 == (papa & 0x1) ) {		
    papa = (papa << 1) + papa + 1;	
  } else {
    papa >>= 1;			
  }
  return papa;
}

int participante( int partId) { 
  bool activo = true; 
  while(1>0){
    omp_set_lock(&lock);
    if(participanteDeseado == partId && activo && valorPapa>=0){ 
      printf( "Llego la papa al participante %d\n", partId );
      if(participantesActivos ==1){
        valorPapa= -1;
        activo=false;
        participantesActivos--;
        printf( "HAY UN GANADOR! El participante %d ha ganado la ronda! \n", partId );
      }else{
        valorPapa= cambiarPapa(valorPapa);
        if(valorPapa== 1){
          activo=false;
          participantesActivos--;
          valorPapa= rand()%998+2; 
          printf( "\n\n\nESTALLA LA PAPA al participante %d,se genera un nuevo valor de la papa.\n", partId  );
        }else{
          printf( "Nuevo valor de la papa: %d \n", valorPapa );
        }
      }
      participanteDeseado = (partId % participantes) + 1; 
    }
    if(participanteDeseado == partId && !activo){ ;
      participanteDeseado = (partId % participantes) + 1;
    }
    if(valorPapa<0){
      _exit( 0 );	
    }
    omp_unset_lock(&lock);
    usleep(100);
  }
}

int main( int argc, char ** argv ) {
  int i;
  
  if ( argc > 1 ) {
    participantes = atoi( argv[ 1 ] );
  }
  if ( participantes <= 0 ) {
    participantes = MAXPARTICIPANTES;
  }

  srand(time(NULL));
  int participanteinicial= rand()%(participantes)+1; 
  
  participanteDeseado = participanteinicial;
  valorPapa=-1; 
  if ( argc > 2 ) {
    valorPapa = atoi( argv[ 2 ] );
  }
  if ( (valorPapa <= 0 ) || (valorPapa > 1000)) {
    valorPapa = rand()%998+2;
  }
  printf( "Creando una ronda de %d participantes\nPrimer valor de papa: %d\n", participantes, valorPapa );
  printf( "Empieza el participante %d \n", participanteinicial);
  participantesActivos = participantes;
  omp_init_lock(&lock);
#pragma omp parallel for num_threads(participantes) schedule(dynamic) shared(i, valorPapa, participanteDeseado, participantesActivos)
  for ( i = 1; i <= participantes; i++ ) { 
      participante(i);
  }

  printf( "\nTermina el programa. \n" );
  return 0;
}

