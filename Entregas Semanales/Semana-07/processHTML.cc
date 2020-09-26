
/**
 *  Programa para procesar un archivo de texto línea por línea
 *
 *  Autor: Programacion Paralela y Concurrente
 *  Fecha: 2020/Set/19
 *
**/
#include <iostream>
#include <stdio.h>
#include <string>
#include <regex>
#include <fstream>
#include <pthread.h>

/**
 *  Divide la línea en sus componentes
 *  Utiliza la función strtok que es insegura para usar con PThreads
 *  Utiliza expresiones regulares para separar la línea en los tokens indicados
 *
**/
std::ifstream file;
void processLine( const char * line ) {
   char * token;
   std::regex texto( ">[^<]*<" );

   regex_replace( line, texto, "> <" ); 
   /*El regex_replace reemplaza el patron con la expresion regular por
     un string. En este caso con el texto tenga un expresion como >[^<]*<
     va a ser remplazado por > < para luego ser separado en token */

   token = strtok( (char * ) line, "< >\t\n");
   printf( "Tokens: " );
   while ( NULL != token ) {
      printf( "%s, ", token );
      token = strtok( NULL, "< >\t\n" );
   }
   printf( "\n" );

}

void * countLines(void * archivo){
    int cantidad = 0;
    std::string line;
    
    while ( std::getline( file, line ) ) {
        cantidad++;
    }
    printf("La cantidad de lineas son: %d\n", cantidad);
    return 0;
}

/**
 *  Abre un archivo que es pasado por parámetro y lo procesa línea por línea
 *
**/

int main( int count, char ** values ) {
   file.open(values[1]);
   std::string line;
   pthread_t threadID;
   if ( file.is_open() ) {
   	      pthread_create(&threadID, NULL, countLines, (std::ifstream *) &file);
	       pthread_join(threadID, NULL); 
	       file.clear();
	       file.seekg(0, std::ios::beg);
	      while ( std::getline( file, line ) ) {
 	        processLine(line.c_str());
	      }
	      file.close();
   }
}


