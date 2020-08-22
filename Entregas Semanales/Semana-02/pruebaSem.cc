#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "Semaforo.h"


/*
 * 
 */
int primero() {
   printf( "Voy primero\n" );
   return 0;
}


/*
 * 
 */
int segundo() {
   usleep(1000);
   printf( "Voy segundo\n" );
   return 0;
}


/*
 *  Este método explícitamente llama a los métodos "Primero" y "Segundo" para que la salida
 *  se despliegue en orden
 */
int pruebaSerial() {

   primero();
   segundo();
   return 0;

}

int main() {
    Semaforo s( 0 );	// El semáforo debe estar inicializado en cero

    pruebaSerial();

    if ( ! fork() ) {
       primero();
       // Para tener el mismo orden que la versión serial, aqui debemos esperar por el semáforo (wait)
    }
    else {
       segundo();
       // Aqui debemos indicar que esta primera parte ya finalizó (signal)
    }
    //return 0;

}
/*
   Salida esperada:
     Voy primero
     Voy segundo
     Voy primero
     Voy segundo
*/
