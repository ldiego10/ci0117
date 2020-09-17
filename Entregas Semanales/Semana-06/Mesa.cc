#include <stdio.h>

#include "Mesa.h"

/*
 *
**/
Mesa::Mesa() {
   int filo;

   this->mutex = new Mutex(); 
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      this->state[ filo ] = THINKING;
      this->self[ filo ] = new Condition();
   }
}

Mesa::~Mesa() {
   int filo;

   delete this->mutex;
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      delete this->self[ filo ];
   }

}


int Mesa::pickup( int filosofo ) {

   this->mutex->Lock();
   this->state[ filosofo ] = HUNGRY;
   printf("El filosofo %d tiene hambre\n", filosofo);
   test( filosofo );
   if ( this->state[ filosofo ] != EATING ) {
      this->self[ filosofo ]->Wait( this->mutex );
   }

   this->mutex->Unlock();
   return 0;
}

int Mesa::putdown( int filosofo ) {

   this->mutex->Lock();

   this->state[ filosofo ] = THINKING;
   printf( "El filósofo %d está pensando\n", filosofo );
   test( (filosofo + 4 ) % 5 );
   test( (filosofo + 1 ) % 5 );

   this->mutex->Unlock();
   return 0;
}

int Mesa::test( int filosofo ) {

   if ( this->state[ (filosofo + 4) % 5 ] != EATING &&
        this->state[ (filosofo + 1) % 5 ] != EATING &&
        this->state[ filosofo ] == HUNGRY ) {
      this->state[ filosofo ] = EATING;
       printf( "El filósofo %d está comiendo\n", filosofo );
       this->self[ filosofo ]->Signal();
   }
   return 0;
}
