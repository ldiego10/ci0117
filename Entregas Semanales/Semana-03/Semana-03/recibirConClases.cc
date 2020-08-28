#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Buzon.h"

#define LABEL_SIZE 64


int main( int argc, char ** argv ) {
   int id, size, st;
   Buzon b;

   st = b.Recibir( (void *) &b.m, 2020 ); 
   while ( st > 0 ) {
      printf("Label: %s, times %d \n", b.m.label, b.m.times );
      st = b.Recibir( (void *) &b.m, 2020 );
   }
   msgctl( id, IPC_RMID, NULL );

}

