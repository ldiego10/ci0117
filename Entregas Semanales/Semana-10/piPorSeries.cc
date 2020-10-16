#define DEBUG
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <omp.h>


//#ifdef DEBUG
int*    iterations;
//#endif

double calcularSumaParcialPi( double &pi, int proceso, long inicial, long terminos ) {
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   long termino;

   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		
      casiPi += alterna/divisor;		
      alterna *= -1;				
   }
  
   pi += casiPi;
   return 0;
}

void Print_iters(int iterations[], long n) {
   int i, start_iter, stop_iter, which_thread;

   printf("\n");
   printf("Thread\t\tIterations\n");
   printf("------\t\t----------\n");
   which_thread = iterations[0];
   start_iter = stop_iter = 0;
   for (i = 0; i <= n; i++)
      if (iterations[i] == which_thread)
         stop_iter = i;
      else {
         printf("%4d  \t\t%d -- %d\n", which_thread, start_iter,
               stop_iter);
         which_thread = iterations[i];
         start_iter = stop_iter = i;
      }
   printf("%4d  \t\t%d -- %d\n", which_thread, start_iter,
               stop_iter);
}  /* Print_iters */


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   double pi = 0;
   if (argc <= 1){
   	printf("Debe ingresar la cantidad de terminos\n");
   	exit(0);
   }
   int thread_count = strtol(argv[1], NULL, 10);
  // #  ifdef DEBUG
   iterations = (int *) malloc((thread_count+1)*sizeof(int));
//#  endif

   int proceso;
   terminos = 1000000;
   double start_time = omp_get_wtime();
   #pragma omp parallel for num_threads(thread_count)\
   reduction(+:pi) private(proceso) shared(thread_count)
   for (proceso = 0; proceso < thread_count; proceso++ ) {
      inicio = proceso * terminos/thread_count;
      fin = (proceso + 1) * terminos/thread_count;
      calcularSumaParcialPi(pi, proceso, inicio, fin);
   //   #    ifdef DEBUG
     iterations[proceso] = omp_get_thread_num();
//#    endif
   }
   double time = omp_get_wtime() - start_time;

   printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos con tiempo %lfms\n", pi, terminos, time );
//   #  ifdef DEBUG
   Print_iters(iterations, thread_count);
   free(iterations);
//#  endif
   return 0;

}
