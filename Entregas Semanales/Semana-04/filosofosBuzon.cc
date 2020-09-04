#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "Buzon.h"		
int N=5; 
int id; 
int id2; 
int *filosofo;  
void mostrar(Buzon b)
{
 
  int i;
   b.Recibir(filosofo[i], 1);  
  for(i=0;i<N;i++){
    printf("F%d:%d ",i+1,filosofo[i]);
  }
  printf("\n");  
}


void tomar(int i, Buzon b)
{
  struct sembuf mem;

  if(filosofo[i] == 1 && filosofo[(i+N-1)%N]!=2 && filosofo[(i+1)%N]!=2)
  {
       filosofo[i]=2;
	b.Enviar(filosofo[i], 1);
     }
     
}



int main(int argc, char *argv[])
{
  int i,a = 0;
  int temp;
  struct sembuf mem;
  Buzon m;
  id=shmget(IPC_PRIVATE,N*sizeof(int), IPC_CREAT | 0600);
  

  for(i=0;i<N;i++)
  {
    if(fork())
    {
	filosofo=(int *)shmat(id, 0, 0);
        while(a < N) 
	{
	    m.Enviar(filosofo[i], 1);
	    mostrar(m);
            sleep(1);  
  	    filosofo[i]= 1;
 	    tomar(i, m);  
 	    m.Recibir(filosofo[i], 1); 
	    mostrar(m);
            sleep(1);
	    filosofo[i]= 0;
 	    tomar((i+N-1)%N, m);
 	    tomar((i+1)%N, m); 
	    m.Recibir(filosofo[i], 1); 
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
