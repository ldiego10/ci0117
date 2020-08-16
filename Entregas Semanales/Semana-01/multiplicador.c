#include <stdio.h>
#include <ctype.h> 

int main() {
    char tamanoC = ' ';

    while(!isdigit(tamanoC)){
        printf("Ingrese un numero entero para la cantidad de filas en la matriz cuadrada: ");
        scanf(" %c", &tamanoC);
    }
    int tamano = tamanoC - '0';
    int matrizA[tamano][tamano];
    int matrizB[tamano][tamano];
    
    for(int x = 0; x < tamano; x++){
        for(int y = 0; y < tamano; y++){
            printf("Ingrese el valor de la fila %d y la columna %d para la primera matriz: ", x, y);
            scanf("%d", &matrizA[x][y]);
        }
    }
    printf("\n");
    
    for(int x = 0; x < tamano; x++){
        for(int y = 0; y < tamano; y++){
            printf("Ingrese el valor de la fila %d y la columna %d para la segunda matriz: ", x, y);
            scanf("%d", &matrizB[x][y]);
        }
    }
    int matrizC[tamano][tamano];
    
    for (int x = 0; x < tamano; x++) {
      for (int y = 0; y < tamano; y++) {
         matrizC[x][y] = 0;
      }
   }

   for (int x = 0; x < tamano; x++) {
      for (int y = 0; y < tamano; y++) {
         for (int z = 0; z < tamano; z++) {
            matrizC[x][y] += matrizA[x][z] * matrizB[z][y];
         }
      }
   }
   
   for (int x = 0; x < tamano; x++) {
      for (int y = 0; y < tamano; y++) {
         printf("%d ", matrizC[x][y]);
      }
      printf("\n");
   }
   return 0;
}