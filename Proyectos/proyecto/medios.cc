/**
 *  Programa base para la construcción de centros en una muestra de datos
 *  La muestra de datos está representada por la variable "puntos", todos los puntos generados al azar
 *  Los centros están representados por la variable "centros", todos los puntos colocados en el origen
 *
 *  CI0117 Programación paralela y concurrente
 *  Tercera tarea programada, grupos 2 y 3
 *  2020-ii
 *
**/

#include <cstdio>
#include <iostream>
#include "VectorPuntos.h"
#include <omp.h>
#include <math.h>
#include <regex>

#define PUNTOS 10000
#define CLASES 15

using namespace std;
long totalCambios = 0;	// Contabiliza la totalidad de los cambios realizados al grupo de puntos


/**vaegwd
 *  Coloca a cada punto en una clase de manera aleatoria
 *  Utiliza el vector de clases para realizar la asignación
 *
**/
void asignarPuntosAClases( long * clases, int modo, long cantidadPuntos, long cantidadCentros ) {
   long clase, pto;
   double cant = (double)cantidadPuntos/cantidadCentros;
   long cantidad = ceill(cant);
   long counter = 0;
   long indiceCentro = 0;
   srand(time(NULL));
   switch ( modo ) {
      case 0:	// Aleatorio
         for ( pto = 0; pto < cantidadPuntos; pto++ ) {
            clase = rand() % cantidadCentros;
            clases[ pto ] = clase;
         }
         break;
      case 1:	// A construir por los estudiantes
          for(pto = 0; pto <  cantidadPuntos; pto++)
          {
            counter++;
            clases[pto] = indiceCentro;
            if(counter == cantidad)
            {
              indiceCentro++;
              counter = 0;
            }
          }
         break;
   }

}


/**
 *  Programa muestra
 *  Variable: clases, almacena la clase a la que pertenece cada punto, por lo que debe ser del mismo tamaño que las muestras
 *  Variable: contClases, almacena los valores para la cantidad de puntos que pertenecen a un conjunto
**/
int main( int cantidad, char ** parametros ) {
  long cambios = 0;
  long cantidadCentros = CLASES;
  long cantidadPuntos = PUNTOS;
  long cuenta = 0;
  char * nombre = new char[20];
  int tipo = 0;
  int modo;

  printf("Escoga la forma en que se ejecutara el programa:\n1.Paralelo 2.Serial\n");
  scanf("%d", &tipo);
  printf("Escoga como desea asignar los puntos:\n0.Random 1.Bloques\n");
  scanf("%d", &modo);
  printf("Ingrese el total de puntos a utilizar: \n");
  scanf("%ld", &cantidadPuntos);
  printf("Ingrese el total de centros a utilizar: \n");
  scanf("%ld", &cantidadCentros);
  printf("Ingrese el nombre del archivo: \n");
  cin >> nombre;
  bool correcto = true;
  printf("Tipo: %d  Modo: %d  CantidadPuntos: %ld  CantidadCentros: %ld  Nombre: %c \n", tipo, modo, cantidadPuntos, cantidadCentros , 'a');
  std::regex a ("^[a-z0-9_()-]+.eps$");
  while(correcto)
  {
    correcto = regex_match(nombre, a);
    if(correcto)
    {
      correcto = false;
    }
    else 
    {
      printf("Archivos no valido, debe terminar con .eps\n");
      printf("Ingrese el nombre del archivo que desea utilizar: \n");
      cin >> nombre;
    }
  }

// Procesar los parámetros del programa

   VectorPuntos * centros = new VectorPuntos( cantidadCentros, 10);
   VectorPuntos * puntos  = new VectorPuntos( cantidadPuntos, 10 );	// Genera un conjunto de puntos limitados a un círculo de radio 10
   long centroPuntos[ cantidadPuntos ];		// Almacena la clase a la que pertenece cada punto
   long contCentro[ cantidadCentros ];
   asignarPuntosAClases( centroPuntos, modo, cantidadPuntos, cantidadCentros );	// Asigna los puntos a las clases establecidas

   do {
     cambios = 0;

     for(int i = 0; i < cantidadPuntos; i++)
     {
       int nCentro;
       nCentro = centros->masCercano(puntos->getPunto(i));
       if(centroPuntos[i]!= nCentro)
       {
         cambios++;
         centroPuntos[i] = nCentro;
       }
     }

     for(int j = 0; j < cantidadCentros; j++)
     {
       cuenta = 0;
       for(int k = 0; k < cantidadPuntos; k++)
       {
         if(centroPuntos[k] == j)
         {
           cuenta++;
         }
       }
       contCentro[j] = cuenta;

     }
     int i =0;
     if(tipo == 1)
     {
       #pragma omp parallel for num_threads(cantidadCentros) shared(i,centros, puntos, centroPuntos, contCentro)
       for(i = 0; i < cantidadCentros; i++)
       {
         centros->nuevoCentroOMP( i, puntos, centroPuntos, contCentro);
       }

     }
     else
     {
         centros->nuevoCentro( puntos, centroPuntos, contCentro);

     }
      totalCambios += cambios;

   } while ( cambios > 0   );	// Si no hay cambios el algoritmo converge

   printf( "Valor de la disimilaridad en la solución encontrada %g, con un total de %ld cambios\n", centros->disimilaridad( puntos, centroPuntos ), totalCambios );

// Con los valores encontrados genera el archivo para visualizar los resultados
   puntos->genEpsFormat( centros, centroPuntos, (char *)nombre);

}
