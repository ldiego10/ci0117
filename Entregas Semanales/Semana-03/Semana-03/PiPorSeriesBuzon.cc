#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include "Buzon.h"

/*
   Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/
double calcularSumaParcialPi( double Pi[], int proceso, long inicial, long terminos, Buzon b ) {
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   long termino;

   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		
      casiPi += alterna/divisor;		
      alterna *= -1;				
   }
   Pi[ proceso ] = casiPi;
   b.Enviar( casiPi, 2020 ); 
   exit( 0 );
}


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   int proceso;
   int pid;
   double temp;
   double casiPi[ 10 ] = { 0 };
   Buzon m;
   
   terminos = 1000000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      inicio = proceso * terminos/10;
      fin = (proceso + 1) * terminos/10;
      pid = fork();
      if ( ! pid ) {
 
         calcularSumaParcialPi( casiPi, proceso, inicio, fin, m);
      } else {
         usleep(1);
         printf("Creating process %d: starting value %ld, finish at %ld\n", pid, inicio, fin );
         m.Recibir( temp, 2020 );
         casiPi[ proceso ] = m.p.piResp;
      }
   }

   for ( proceso = 0; proceso < 10; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }

   for ( proceso = 1; proceso < 10; proceso++ ) {
      casiPi[ 0 ] += casiPi[ proceso ];
   }

   printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos\n", casiPi[ 0 ], terminos );


}
