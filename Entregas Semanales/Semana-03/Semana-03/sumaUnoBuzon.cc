
/*
 * Suma uno a un total mil veces por cada proceso generado
 * Recibe como parametro la cantidad de procesos que se quiere arrancar
 * Author: Programacion Concurrente (Francisco Arroyo)
 * Version: 2020/Ago/08
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include "Buzon.h"


long total = 0;

/*
 *  Do some work, by now add one to a variable
 */
long AddOne( long * suma, Buzon buz ) {
   int i;

   for ( i = 0; i < 1000; i++ ) {
      usleep( 1 );
      (* suma)++;			// Suma uno
   }
   //printf("Suma %ld", *suma);
   buz.Enviar( *suma, 2020 );
   exit( 0 );

}


/*
  Serial test
*/
int SerialTest( int procesos, long * total ) {
   int i, proceso;

   for ( proceso = 0; proceso < procesos; proceso++ ) {

      for ( i = 0; i < 1000; i++ ) {
         (* total)++;	
         	// Suma uno
      }

   }
   return 0;
}


/*
  Fork test
*/
long ForkTest( int procesos, long * total, Buzon buz) {
   int proceso, pid;
   long temp;
   for ( proceso = 0; proceso < procesos; proceso++ ) {
      pid = fork();
      if ( ! pid ) {
         
         AddOne( total, buz );
        // buz.Recibir(temp, 2020);
        // temp = temp + buz.s.sumaU;   
      }
      
     // temp = temp + 1000;
   }
   buz.Enviar(*total, 2020);
   for ( proceso = 0; proceso < procesos; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }
   return temp;
}

/*
 *
 */
void startTimer( struct timeval * timerStart) {
   gettimeofday( timerStart, NULL );
}


/*
 *  time elapsed in ms
 */
double getTimer( struct timeval timerStart ) {
   struct timeval timerStop, timerElapsed;

   gettimeofday(&timerStop, NULL);
   timersub(&timerStop, &timerStart, &timerElapsed);
   return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}


int main( int argc, char ** argv ) {
   long procesos;
   int proceso;
   struct timeval timerStart;
   double used;
   long temp2 = 0;
   Buzon buz;
   procesos = 100;
   if ( argc > 1 ) {
      procesos = atol( argv[ 1 ] );
   }

   startTimer( & timerStart );
   total = 0;
   SerialTest( procesos, & total );
   used = getTimer( timerStart );
   printf( "Serial version:      Valor acumulado por %ld procesos es \033[91m %ld \033[0m en %f ms\n", procesos, total, used );

   startTimer( & timerStart );
   total = 0;
 //  temp2 = ForkTest( procesos, & total, buz);
   used = getTimer( timerStart );
   printf( "Fork   version:      Valor acumulado por %ld procesos es \033[91m %ld \033[0m en %f ms\n", procesos, temp2, used );

}
