#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>


#include <stdio.h>
#include <string>
#include <unistd.h>

using namespace std;

int tamano1;
string secuencia;
string secuencia2;




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


string invertirString(string& sec) 
{ 
    int n =  sec.length(); 
  
    // corners 
    for (int i = 0; i < n / 2; i++) 
        swap( sec[i],  sec[n - i - 1]); 
        
    return sec;
} 


void palindromoSerial(string& sec2, string& sec){
	string temp = "";
	string temp2 = "";
	int contadorTemp = 0;
	int contadorTemp2 = 0;
	int contador = 0;
	int contador2 = 0;
	for(int i = 0; i < sec2.length(); i++){
	
		contador2 = i;
		for(int j = 0; j< sec.length(); j++){
		//cout << sec[j] << endl;
		
			
		
			if(sec[j] == sec2[contador2]){
				contador = j;
				while(sec[contador] == sec2[contador2]){
					temp2 += sec[contador];
					contador--;
					contador2++;
				}
				
				
				if(temp2.length() > temp.length()){
					temp = temp2;
					
				} 
				
				contador= j;
				contador2 = i;
			}else{
				contador2 = i;
				contador = j;
				
				temp2 = "";
			}
		}
		contadorTemp2++;
	}
	if(temp2.length() > temp.length()){
					temp = temp2;
					
				}  
	
	cout << "Temp es: " <<temp << endl;
}


int main( int argumentos, char ** valores ) {
    struct timeval timerStart;
    int ingresoSecuencia = 1;
    double used;
    string secuencia = "";
	string secuencia2 = "";
    
      cout << "Ingrese la oracion: " << endl;
	getline(cin, secuencia);
	tamano1 = secuencia.length();

      
       

        if(ingresoSecuencia == 1)
        {
        
            secuencia2 = secuencia;
        }
        else
        {
            secuencia2 =  secuencia;
        }
        secuencia2 = invertirString(secuencia2);
	
	
	
	
        startTimer( & timerStart );
        palindromoSerial(secuencia2, secuencia);
        used = getTimer( timerStart );
        printf( "El tiempo serial fue de: %g ms \n", used );

       
    
    
   
}
