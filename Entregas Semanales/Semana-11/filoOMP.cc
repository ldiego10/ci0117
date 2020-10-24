#include <iostream>
#include <unistd.h>
#include <omp.h>
#include <unistd.h>
#include "Lock.h"
#include "Mesa.h"

using namespace std;

#define NUMTHRDS 5
int status;

Mesa *dp;
Lock *mtx;

void Philo(int arg);

int main(int argc, char *argv[])
{
   mtx = new Lock();
   dp = new Mesa();
  int i;
#pragma omp parallel for num_threads(NUMTHRDS) schedule(dynamic) shared(i)
  for(i = 0; i< NUMTHRDS; i++)
  {
    Philo(i);
  }

  cout << "\n" << "Normal end of execution. \n";

  return 0;
}

void Philo(int who)
{
  int eats, thinks;
  for(int i = 0; i < 10; i++)
  {
    mtx->Acquire();
    cout << "Round " << i << " filosofo #" << who + 1 << endl;
    mtx->Release();

    dp->pickup( who );
    eats = rand() % 6;
    sleep(eats);

    dp->putdown (who);
    thinks = rand() % 6;
    sleep(thinks);
  }

}
