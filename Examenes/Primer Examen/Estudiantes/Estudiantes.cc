/**
 * Problema del comedor estudiantil
 * 
 * Author: Programacion Concurrente (Francisco Arroyo)
 * Version: 2020/Oct/02
 *
 * Primer examen parcial
 * Grupo-2
 *
 * Suposicion:
 * Cada estudiante puede esperar lo que sea necesario
 * Aunque un estudiante se el primero en compraralmuerzo igual el junto a otro pueden ser los ultimos en irse.
**/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "Monitor.h"
#include "Mutex.h"

Mutex *mutex;
Monitor *monitor;

/**
 *
**/
int ComprarAlmuerzo( int cual ) {
   int espera;
   printf("El estudiante %d compra\n", cual);
   mutex->Lock();
   espera = random() & 0x3;
   mutex->Unlock();
   sleep( espera );

   return espera;

}


/**
 *
**/
int Almorzar( int cual ) {
   int espera;
   printf("El estudiante %d almuerza\n", cual);
   mutex->Lock();
   espera = random() & 0x3;
   mutex->Unlock();
   sleep( espera );

   return espera;

}


/**
 *
**/
int Salir( int cual ) {
   int espera;
   mutex->Lock();
   espera = random() & 0x3;
   mutex->Unlock();
   sleep( espera );
   printf("El estudiante %d se va\n", cual);
   
   if(cual % 2 == 0){
   	monitor->Wait(cual, cual+1);
   }else{
   	monitor->Signal(cual-1, cual);
   }

   return espera;

}


/**
 *  Código para los estudiantes
**/
int Estudiante( int cual ) {

   srand( getpid() );
   printf( "Se produjo un estudiante %d\n", cual );

   ComprarAlmuerzo( cual );

   Almorzar( cual );

   Salir( cual );

   exit( 0 );

}


/*
 *
 */
int main( int argc, char ** argv ) {
   long workers;
   int worker, pid, memId;
   mutex = new Mutex();
   workers = 100;
   if ( argc > 1 ) {
      workers = atol( argv[ 1 ] );
   }
   monitor = new Monitor(workers);
   for ( worker = 0; worker < workers; worker++ ) {
      pid = fork();
      if ( ! pid ) {
         Estudiante( worker );
      }
   }

   for ( worker = 0; worker < workers; worker++ ) {
      int status;
      pid_t pid = wait( &status );
   }
   free(mutex);
   free(monitor);
}


