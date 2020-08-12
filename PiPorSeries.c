
/*
 * Calcula el numero PI utilizando una serie "infinita"
 * Debe recibir la cantidad de iteraciones como parametro
 *
 *   pi = (-1)^i x 4/(2xi + 1)
 *
 *  Autor: Programacion Paralela y Concurrente (Francisco Arroyo)
 *  Fecha: 2020/Ago/08
*/

/*
 * Con 1000000 terminos el valor de Pi es 3.141591654 en 3.126ms
 * Con 1000 terminos el valor de Pi es 3.141592654 en 0.003ms
 * Con 5000000 terminos Pi es 3.1415922454 en 22.451ms
 * Con 1000000000 terminos Pi es 3.141592653 terminos en 3996.13ms
 * Con 3000000000 terminos Pi es 3.141592653 terminos en 11183.3ms*/
 * Es decir, entre mas terminos, mas exacto el valor de Pi

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

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
   long termino, terminos;
   double alterna = 4;
   long divisor = 0;
   double casiPi;
   struct timeval timerStart;
   double used;

   terminos = 1000000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }

   startTimer( & timerStart );
   for ( termino = 0; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		// 2 x termino + 1
      casiPi += alterna/divisor;		// 4 / (2xi + 1)
      alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
   }
   used = getTimer( timerStart );

   printf( "Valor calculado de Pi es \033[91m %.10g \033[0m con %ld terminos en %g ms\n", casiPi, terminos, used );

}

