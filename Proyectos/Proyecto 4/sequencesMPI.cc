/*
	Luis Diego Esquivel - B82806
	Andres David Ramirez - B86426

	Correr como : mpiexec -n # ./sequencesMPI.out
	
	Nota: Podria ocurrir que el resultado paralelo sea diferente al serial, sin embargo poseen el mismo tamano, esto se debe a que la forma de encontrar
	la subsecuencia se hace diferente en los metodos. Sin emabrgo, tener en cuenta que ambas pueden ser respuestas correctas ya que ambas tienen el mismo
	tamano que es el tamano maximo que puede tener la subsecuencia.
	
	
	Nota2: La siguiente tabla es ejecutada con el mismo tamano para filas y columnas y con 4 cores. 
	
	┌────────┬────────┬────────┐
	│ Tamano │ Serial │  MPI   │
	├────────┼────────┼────────┤
	│    10  │0.036ms │0.0076ms│
	├────────┼────────┼────────┤
	│   100  │0.614ms │0.0185ms│
	├────────┼────────┼────────┤
	│   500  │34.71ms │0.1159ms│
	├────────┼────────┼────────┤
	│   750  │141.58ms│0.2625ms│
	├────────┼────────┼────────┤
	│  1000  │230.69ms│0.7774ms│
	└────────┴────────┴────────┘
	
	
	
	
*/

#include <stdio.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <mpi.h>




#include "adn.h"


int ** matriz;
int tamano1;
int tamano2;
ADN * adn1;
ADN * adn2;
int id;
using namespace std;


void startTimer( struct timeval * timerStart) {
   gettimeofday( timerStart, NULL );
}


/*
 *  time elapsed in ms
 */
double getTimer( struct timeval timerStart ) {
   struct timeval timerStop, timerElapsed;

   gettimeofday(&timerStop, NULL);
   timersub(&timerStop, &timerStart, &timerElapsed);
   return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}


char * secuenciaManual(int tamano)
{
   char * secuencia = (char *) calloc (tamano,sizeof(char *));
   printf("\nIngrese la secuencia de ADN: ");
   cin >> secuencia;

  // cout << secuencia <<  endl;
   return secuencia;
}


void obtenerSubsecuencia(int rank)
{

    int tamanoRecv1;
    int tamanoRecv2;
    int tamanoTotal;
    int  ** matriz1;
    int posicion = 0;
    int comprueba = 0;
    int numero = 0;
    int rango = 1;
    
    MPI_Recv(&tamanoRecv1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&tamanoRecv2, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    while (rango != -1)
    {
        MPI_Recv(&rango, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if(rango != -1)
        {   
            tamanoTotal = (tamanoRecv1 + 1) * (tamanoRecv2 + 1);
        
            matriz1 = (int **) calloc (tamanoRecv1+1, sizeof(int *));

            for(int i = 0; i < tamanoRecv1+1; i++ )
            {
                matriz1[i] = (int*) calloc (tamanoRecv2+1, sizeof(int));
            }

            MPI_Recv(&comprueba, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&posicion, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if(comprueba == 0)
            {
                MPI_Recv(&(matriz1[posicion-1][0]), tamanoRecv2+1, MPI_INT, 0, rank+3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&(matriz1[posicion][0]), tamanoRecv2+1, MPI_INT, 0, rank+3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);            
            }
            else
            {
                MPI_Recv(&(matriz1[posicion][0]), tamanoRecv2+1, MPI_INT, 0, rank+3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        
            MPI_Recv(&numero, 1, MPI_INT, 0, rank+3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        
            int pos = 0;
            bool encontro = false;
            for(int i = 0; i < tamanoRecv2+1 && encontro == false; i++)
            {
                if(matriz1[posicion][i] == numero)
                {
                    if(matriz1[posicion-1][i] == numero)
                    {
                        pos = posicion-1;                    
                        MPI_Send(&(pos), 1, MPI_INT, 0, rank+3, MPI_COMM_WORLD);
                    }
                    else
                    {
                        pos = posicion;                                    
                    
                        if(matriz1[posicion][i] == matriz1[posicion-1][i+1])
                        {
                            if(matriz1[posicion-1][i+1] < matriz1[posicion][i+2])
                            {
                                pos = posicion - 1;
                                MPI_Send(&(pos), 1, MPI_INT, 0, rank+3, MPI_COMM_WORLD);
                            }
                            else
                            {
                                MPI_Send(&(posicion), 1, MPI_INT, 0, rank+3, MPI_COMM_WORLD);
                            }
                        }
                        else
                        {
                            MPI_Send(&(posicion), 1, MPI_INT, 0, rank+3, MPI_COMM_WORLD);
                        }
                    

                    
                    }
                
                    encontro = true;
                
                }
            }
        }
    }   
}


string obtenerSubsecuenciaSerial()
{
   int tamanoSub = matriz[tamano1][tamano2];
   int iniciaX = tamano1;
   int iniciaY = tamano2;
   char subsecuencia [tamanoSub] = " ";

   
   while(tamanoSub != 0 )
   {  
      // cout << "Primero " << iniciaX << " " << iniciaY << matriz[iniciaX][iniciaY]  <<endl;
      while(matriz[iniciaX][iniciaY-1] == tamanoSub)
      {      
         iniciaY -= 1; 
      }
      // cout << "Segundo " << iniciaX << " " << iniciaY << matriz[iniciaX][iniciaY] <<endl;
      while(matriz[iniciaX-1][iniciaY] == tamanoSub)
      {
         iniciaX -= 1;
      }
      subsecuencia [tamanoSub-1] = adn2->getCaracter(iniciaY-1);
      tamanoSub -= 1 ;
      iniciaX -= 1;
      iniciaY -= 1;

   }

   cout << "\nResultado serial: ";
   for(int i= 0; i < matriz[tamano1][tamano2]; i++)
   {
      cout << subsecuencia[i];

   }
   cout << endl;
   // cout << subsecuencia << endl;
   return subsecuencia;
}


/**
 *  Parallel test
**/
void parallelTest( int tamanoFinal, int commsz) {
   int contador = 0;
   int verifica2 = 0;
   int comprueba = 0;
   int verifica = 0;
   int contador2 = 1;
   int entro = 0;
   int contador3 = 0;
   int rango = 1;
   int actual = 1;
   
    for(int i = 1; i < commsz; i++)
    {
       MPI_Send(&tamano1, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
       MPI_Send(&tamano2, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
    }
   
   
   for(int i = 1; i < tamano1+1; i++)
   {
     
    for(int j = 1; j < tamano2+1; j++)
    {

        if(adn1->getCaracter(i-1) == adn2->getCaracter(j-1))
        {
            matriz[i][j] = matriz[i-1][j-1] + 1;
        }
        else
        {
            if(matriz[i][j-1] > matriz[i-1][j])
            {
                matriz[i][j] = matriz[i][j-1];
            }
            else
            {
                matriz[i][j] = matriz[i-1][j];
            }
        }
       
        if(matriz[i][j] > contador)
        {
            contador++;
            verifica = 1;
        }
       
    }

    if(verifica2 == 1)
    {
   
        MPI_Send(&rango, 1, MPI_INT, contador2, 1, MPI_COMM_WORLD);
    
        if(contador2 < tamano1)
        {
         
            MPI_Send(&comprueba, 1, MPI_INT, contador2, 3, MPI_COMM_WORLD);
            MPI_Send(&i, 1, MPI_INT, contador2, 4, MPI_COMM_WORLD);
            MPI_Send(&(matriz[i-1][0]), tamano2+1, MPI_INT, contador2, contador2+3, MPI_COMM_WORLD);
            MPI_Send(&(matriz[i][0]), tamano2+1, MPI_INT, contador2, contador2+3, MPI_COMM_WORLD);
            contador3++;
        }
        else
        {      
         
            comprueba++;
            MPI_Send(&comprueba, 1, MPI_INT, contador2, 3, MPI_COMM_WORLD);
            comprueba = 0;
            MPI_Send(&i, 1, MPI_INT, contador2, 4, MPI_COMM_WORLD);
            MPI_Send(&(matriz[i][0]), tamano2+1, MPI_INT, contador2, contador2+3, MPI_COMM_WORLD);        
        }
       
       

        MPI_Send(&actual, 1, MPI_INT, contador2, contador2+3, MPI_COMM_WORLD);
        actual++;
        contador2 = (contador2%(commsz-1))+1;  
        verifica2 = 0;
    }
     
    if(verifica == 1)
    {
      verifica2 = 1;
    }
   
    verifica = 0;  
           
   }
   
    if(contador > contador3 && entro == 0){

        MPI_Send(&rango, 1, MPI_INT, contador2, 1, MPI_COMM_WORLD);
        comprueba++;
        MPI_Send(&comprueba, 1, MPI_INT, contador2, 3, MPI_COMM_WORLD);
        comprueba = 0;
        MPI_Send(&tamano1, 1, MPI_INT, contador2, 4, MPI_COMM_WORLD);
        MPI_Send(&(matriz[tamano1][0]), tamano2+1, MPI_INT, contador2, contador2+3, MPI_COMM_WORLD);
        MPI_Send(&actual, 1, MPI_INT, contador2, contador2+3, MPI_COMM_WORLD);
    }

    rango = -1;
    for(int i = 1; i < commsz; i++)
    {
      MPI_Send(&rango, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
    }
   
   
   
    string subsecuencia = " ";
    int formula = 0;
    for(int i = 1; i < matriz[tamano1][tamano2]+1; i++)
    {
        int pos =  0;

        MPI_Recv(&pos, 1, MPI_INT, (formula % (commsz - 1) + 1), (formula % (commsz - 1) + 1)+3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         
        subsecuencia += adn1->getCaracter(pos-1);
        
        formula++;
    }

    cout << "\nResultado paralelo: " << subsecuencia << endl;
}

void serialTest( ) {

   // chain->printSeqs();
   
   for(int i = 1; i < tamano1+1; i++)
   {
      
      for(int j = 1; j < tamano2+1; j++)
      {
      

         if(adn1->getCaracter(i-1) == adn2->getCaracter(j-1))
         {
            matriz[i][j] = matriz[i-1][j-1] + 1;             
         }
         else
         {
            if(matriz[i][j-1] > matriz[i-1][j])
            {
               matriz[i][j] = matriz[i][j-1];               
            }
            else
            {
               matriz[i][j] = matriz[i-1][j];               
            }
         }
      }
   }

   string final = obtenerSubsecuenciaSerial();
}



int main( int argumentos, char ** valores ) {
    struct timeval timerStart;
    int ingresoSecuencia;
    double used;
    int rank, commsz;
    int counter = 0;
    int tamanoFinal = 0;
    srand( time(NULL) );

    

    MPI_Init(NULL,NULL);
    
    MPI_Comm_size(MPI_COMM_WORLD, &commsz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        printf("Como desea generar las secuencias de adn?\n1. Manual\n2. Aleatoria\nIngrese el numero con la opcion deseada: ");
        cin >> ingresoSecuencia;
        printf("\nIngrese el tamano de la primera secuencia: ");
        cin >> tamano1;
        printf("\nIngrese el tamano de la segunda secuencia: ");
        cin >> tamano2;
       



        int next = 1;
        tamanoFinal = (tamano1 + 1) * (tamano2 + 1);

        matriz = (int **) calloc (tamano1+1, sizeof(int *));

        for(int i = 0; i < tamano1+1; i++ )
        {
            matriz[i] = (int*) calloc (tamano2+1, sizeof(int));
        }

       

        if(ingresoSecuencia == 1)
        {
            adn1 = new ADN(secuenciaManual(tamano1));
            adn2 = new ADN(secuenciaManual(tamano2));
        }
        else
        {
            adn1 = new ADN(tamano1);
            adn2 = new ADN(tamano2);
        }

        startTimer( & timerStart );
        serialTest(  );
        used = getTimer( timerStart );
        printf( "El tiempo serial fue de: %g ms \n", used );

        for(int i = 0; i < tamano1+1; i++)
        {
            for(int j = 0; j < tamano2+1; j++)
            {
                matriz[i][j] = 0;
            }
        }
    }
    double start = MPI_Wtime(); 
    if(rank == 0)
    {
        parallelTest(tamanoFinal, commsz);   

    }
    else
    {      
       obtenerSubsecuencia(rank);
    }
    double end = MPI_Wtime();
    MPI_Finalize();
    if(rank == 0)
    {
        printf("El tiempo paralelo fue de: %f ms \n", (end-start)/commsz);
    }
   
}
