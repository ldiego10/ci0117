#include <iostream>
#include <unistd.h>
#include <thread>
#include "Mutex.h"

#include "Mesa.h"

using namespace std;

#define NUMTHRDS 5
int status;

Mesa *dp;
Mutex *mtx;

void Philo(int arg);

int main(int argc, char *argv[])
{
   mtx = new Mutex();
   dp = new Mesa();
  int i;
  thread philosphers [NUMTHRDS];
  for(int i = 0; i< NUMTHRDS; i++)
  {
    philosphers[i] = thread(Philo, i);
  }
  for(i = 0; i < NUMTHRDS; i++)
  {
    philosphers[i].join();
  }

  cout << "\n" << "Normal end of execution. \n";

  return 0;
}

void Philo(int who)
{
  int eats, thinks;
  for(int i = 0; i < 10; i++)
  {
    mtx->Lock();
    cout << "Round" << i << "filosofo #" << who + 1 << endl;
    mtx->Unlock();

    dp->pickup( who );
    eats = rand() % 6;
    sleep(eats);

    dp->putdown (who);
    thinks = rand() % 6;
    sleep(thinks);
  }

}
