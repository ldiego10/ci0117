
#include "Mutex.h"
#include "Condition.h"

#define FILOMAX 5

class Mesa {

   public:
      Mesa();
      ~Mesa();
      int pickup( int );
      int putdown( int );


   private:
     Mutex * mutex;
     int test( int );
     enum { THINKING, HUNGRY, EATING } state[ 5 ];
     Condition  * self[ 5 ];	// inanición (starvation)

};
