#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "Semaforo.h"		
int N=5; 
int id; 
int id2; 
int *filosofo;  
Semaforo *sem;
void mostrar(void)
{
 
  int i;

  
  sem->Wait(0, -1, 0, id2);  
  for(i=0;i<N;i++){
    printf("F%d:%d ",i+1,filosofo[i]);
  }
  printf("\n");  
  sem->Signal(0,1,0,id2);
}


void tomar(int i)
{
  struct sembuf mem;

  if(filosofo[i] == 1 && filosofo[(i+N-1)%N]!=2 && filosofo[(i+1)%N]!=2)
  {
       filosofo[i]=2;

        
       sem->Signal(i+1, 1, 0, id2);
     }
}



int main(int argc, char *argv[])
{
  sem = new Semaforo(0);
  int i,a;
  struct sembuf mem;

  id=shmget(IPC_PRIVATE,N*sizeof(int), IPC_CREAT | 0600);
  
  id2=semget(IPC_PRIVATE, N+1, IPC_CREAT | 0600);

  
  sem->Signal(0,1,0,id2);

  for(i=0;i<N;i++)
  {
    if(fork())
    {
	filosofo=(int *)shmat(id, 0, 0);
        while(a < N) 
	{
	    mostrar();
            sleep(1);
 	    sem->Wait(0, 1, 0, id2);  
  	    filosofo[i]= 1;
 	    tomar(i);  
 	    sem->Signal(0, 1, 0, id2);
 	    sem->Wait(i+1, -1, 0, id2); 
	    mostrar();
            sleep(1);
 	    sem->Wait(0,-1, 0, id2);  
	    filosofo[i]= 0;
 	    tomar((i+N-1)%N);
 	    tomar((i+1)%N); 
	    sem->Signal(0,1,0,id2); 
	    a++;
	}
	if(a == N){
	   sleep(5);
	   exit(0);
	}
        
    }else{
    	if(a == N){
    	sleep(5);
	   exit(0);
	}
    }
    
  }

}
