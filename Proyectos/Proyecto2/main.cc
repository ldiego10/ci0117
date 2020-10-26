#include "FileReader.h"
#include <math.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <pthread.h>
#include <map>

using namespace std;



pthread_mutex_t * mut;
pthread_mutex_t * mute;

int modifica = 0;
int num = 0;
int cuentan = 0;
string * parseo(char * linea);
map <string, int> mapCreate();
void * contarEtiquetas(void * x);
void * Trabajador(void * trabajador);


struct Contando
{
  int  estrategia = 0;
  string nombreArchivo;
  map <string, int> etiquetas;
};

void * contarEtiquetas(void * x)
{


 FileReader * l = (FileReader *) x;
 if(l->getInstruccion() == 2){
 
  int id = 0;
  bool bandera = false;
  pthread_mutex_lock(mut);
  cout << "entra" << endl;
    id = modifica;
  	modifica++;
  pthread_mutex_unlock(mut);

  
  map <string, int> mapa1;
  mapa1 = l->getMapa();

  char buffer[512];
  char * bufferT = buffer;
  string * strtok_r = new string [2];
  int indice = id;

  for(long i = indice; i < l->getCantidadLineas(); i+= cuentan)
  {

    bufferT = l->getNext(bufferT, i, bandera,cuentan);
     bandera = true;
pthread_mutex_lock(mut);
     strtok_r = parseo(bufferT);
     pthread_mutex_unlock(mut);

     for(int t = 0; t < 2; t++)
     {
       if(strtok_r[t] != "False")
       {
         std::map<string, int>::iterator it = mapa1.find(strtok_r[t]);
         if(it != mapa1.end())
         it->second += 1;

       }
     }
   }
     pthread_mutex_lock( mut );
     for(auto its = mapa1.begin(); its != mapa1.end(); its++)
     {
         l->setValor( its->second, its->first);

     }
     pthread_mutex_unlock( mut );
     //cout << "sale: " << id << endl;
     }
     else if(l->getInstruccion() == 1){
     		int id = 0;
  bool bandera = false;
  pthread_mutex_lock(mut);
    id = modifica;
  modifica++;
  pthread_mutex_unlock(mut);

  map <string, int> mapa1;
  mapa1 = l->getMapa();

  char buffer[512];
  char * bufferT = buffer;
  string * strtok_r = new string [2];
  double t = (double)l->getCantidadLineas()/cuentan;
  int tareas = 0;
  if(id < l->getCantidadLineas())
  {
     tareas = ceill(t);
  }else
  {
    tareas = floor(t);
  }
  int indice = id * tareas;

  for(long i = indice; i < indice+tareas; i++)
  {

     bufferT = l->getNext(bufferT, i, bandera,1);
     bandera = true;
     //cout << i << bufferT<< endl;

     strtok_r = parseo(bufferT);


     for(int t = 0; t < 2; t++)
     {
       if(strtok_r[t] != "False")
       {
         std::map<string, int>::iterator it = mapa1.find(strtok_r[t]);
         if(it != mapa1.end())
         it->second += 1;
       }
     }


   }


  pthread_mutex_lock( mut );
  for(auto its = mapa1.begin(); its != mapa1.end(); its++){
      l->setValor( its->second, its->first);

  }
  pthread_mutex_unlock( mut );
     	
     	
     }else if(l->getInstruccion() == 3){
     	 int id = 0;
  bool bandera = false;
  pthread_mutex_lock(mut);
  id = modifica;
  modifica++;
  pthread_mutex_unlock(mut);
 // cout << "Consiguio id: " << id <<  endl;
  map <string, int> mapa1;
  mapa1 = l->getMapa();
  
  char buffer[512];
  char * bufferT = buffer;
  string * strtok_r = new string [2];
  int indice = id;
  int i = 0;
  
  while(l->counter < l->getCantidadLineas())
  {
  
    //cout << id <<  endl;
    if(i==0)
    {
    pthread_mutex_lock(mut);
      bufferT = l->getNext(bufferT, id, bandera, l->counter);
      l->counter++;
      bandera = true;
      pthread_mutex_unlock(mut);
      // cout << "sale: " << id << endl;
      i++;
    }else
    {
      pthread_mutex_lock(mut);
      bufferT = l->getNext(bufferT, cuentan, bandera, l->counter);
      l->counter++;
      pthread_mutex_unlock(mut);
       // cout << "sale: " << id << endl;
    }
  
   // cout << id << bufferT<< endl;
    usleep(50);
    strtok_r = parseo(bufferT);
    for(int t = 0; t < 2; t++)
    {
      if(strtok_r[t] != "False")
      {
        std::map<string, int>::iterator it = mapa1.find(strtok_r[t]);
        if(it != mapa1.end())
        it->second += 1;
  
      }
    }
  }
  
  pthread_mutex_lock( mut );
  for(auto its = mapa1.begin(); its != mapa1.end(); its++)
  {
      l->setValor( its->second, its->first);
  
  }
  pthread_mutex_unlock( mut );
 // cout << "sale: " << id << endl;
     }else{
     	 int id = 0;
  bool bandera = false;
  pthread_mutex_lock(mut);
  id = modifica;
  modifica++;
  pthread_mutex_unlock(mut);
 // cout << "Consiguio id: " << id <<  endl;
  FileReader * fileR = (FileReader *) x;
  map <string, int> mapa1;
  mapa1 = fileR->getMapa();
  
  char buffer[512];
  char * bufferT = buffer;
  string * strtok_r = new string [2];
  int indice = id;
  int i = 0;
  int cuenta = 0;
  while(cuenta < fileR->getCantidadLineas())
  {
  
    //cout << id <<  endl;
    if(i==0)
    {
    pthread_mutex_lock(mut);
      bufferT = fileR->getNext(bufferT, id, bandera, fileR->counter);
      fileR->counter++;
      bandera = true;
      pthread_mutex_unlock(mut);
      // cout << "sale: " << id << endl;
      i++;
    }else
    {
      pthread_mutex_lock(mut);
      bufferT = fileR->getNext(bufferT, cuentan, bandera, fileR->counter);
      fileR->counter++;
      pthread_mutex_unlock(mut);
       // cout << "sale: " << id << endl;
    }
  
   // cout << id << bufferT<< endl;
    usleep(40);
    strtok_r = parseo(bufferT);
    for(int t = 0; t < 2; t++)
    {
      if(strtok_r[t] != "False")
      {
        std::map<string, int>::iterator it = mapa1.find(strtok_r[t]);
        if(it != mapa1.end())
        it->second += 1;
  
      }
    }
  }
  
  pthread_mutex_lock( mut );
  for(auto its = mapa1.begin(); its != mapa1.end(); its++)
  {
      fileR->setValor( its->second, its->first);
  
  }
  
  pthread_mutex_unlock( mut );
 // cout << "sale: " << id << endl;
   }
     
     pthread_exit(0);

	return 0;
}



void * Trabajador(void * trabajador)
{

  pthread_mutex_lock( mute );
  
  int id = num+1;
  num++;
  struct Contando * m = (struct Contando*) trabajador;

  FileReader * lectores = new FileReader(m->nombreArchivo, m->estrategia, m->etiquetas );
  lectores->contar();
  
  //cout << "id: " << id << "lineas:" << lectores->contar()<< endl;
  pthread_t * contadores;
  contadores = (pthread_t *) calloc(cuentan, sizeof( pthread_t ) );
  map <string, int> mapa1;
  mapa1 = lectores->getMapa();
 // cout << &mapa1 << endl;

	for(int x = 0; x < cuentan; x++)
  {
  //  cout << x << endl;

    	//		printf("\nEntro\n");
			pthread_create(&contadores[x], NULL, contarEtiquetas, (void *) lectores);
   
	}



	for ( int hilo = 0; hilo < cuentan; hilo++ )
  {
    pthread_join( contadores[ hilo ], NULL );
  }
   pthread_mutex_lock( mut );
  mapa1 = lectores->getMapa();
  for(auto it = mapa1.begin(); it != mapa1.end(); ++it)
  {
    if(it->second != 0){
      std::cout << it->first << " " << it->second << "\n";
    }
  }
  lectores->cerrar();
  pthread_mutex_unlock( mut );

  modifica = 0;
  pthread_mutex_unlock( mute );
  pthread_exit(0);
}

map <string, int> mapCreate()
{
	map <string, int> mapaTemp;
	ifstream archivoF;
	archivoF.open("etiquetas.txt");
	string line;
	while (std::getline( archivoF, line ))
  {
    mapaTemp[line] = 0;
  }

	return mapaTemp;
}

string * parseo(char*  linea)
{
 int incremento = 0; 
  int i = 0 ;
  int j = 0;
  string * guarda = new string[2];
  guarda[1] = "False";
  
// cout << linea << endl;

  while(incremento < strlen(linea)){
      if(linea[incremento-1] == '<' && i < 2){
      
          while(linea[incremento] != ' ' && linea[incremento] != '>'){
              if(j == 1){
                guarda[1].clear();
                j++;
              }
             // cout << i << endl;
              guarda[i] = guarda[i] + linea[incremento];
              incremento++;
         }
          i++;
          j++;
      }else{
        incremento++;
      }
  }
 return guarda;

}

int main(int argc, char** argv)
{
  int trabajadores;
  if(argc <= 3){
      cout << "No tiene suficientes argumentos" << endl;
      exit(0);
  }


  std::regex t ("^\\-[t]\\=[\\[0-9]*$");
  if (!std::regex_match (argv[1],t)){
       cout <<"\nIngrese correctamente cantidad de contadores" << endl;
      exit(0);
  }

  mut = (pthread_mutex_t *) calloc( 1, sizeof( pthread_mutex_t ) );
  pthread_mutex_init( mut, NULL );
	 mute = (pthread_mutex_t *) calloc( 1, sizeof( pthread_mutex_t ) );
  pthread_mutex_init( mute, NULL );  

  int cantidadArchivos = argc -3;
  char * pch;
  pch = strtok (argv[1]," -t=");
  cuentan = atoi(pch);
  std::regex a ("^[^\\/]+\\.html$");
  for(int i = 2; i < cantidadArchivos+2; i++)
  {
      if(!std::regex_match(argv[i], a))
      {
         cout << "Archivo no aceptado" << endl;
          exit(0);
      }
  }

  string x = "";
  x = to_string((cantidadArchivos + cantidadArchivos) - 1);
  string bar = "^\\-[e]\\=[\\d\\,]{" + x + "}$";
  regex e(bar);

  if (!std::regex_match (argv[argc-1],e))
  {
    std::cout << "Objetos no validos" << endl; 
  }
  

  map <string, int> mapaOriginal = mapCreate();
  int tipo = 0;
  for(int z =0; z < cantidadArchivos; z++)
  {
      if(argv[argc-1][3+ tipo] - '0' > 4 || argv[argc-1][3+ tipo] - '0' < 1)
      {
           cout << "Instrucciones incorrectas" << endl;
           exit(0);
      }
      tipo+=2;
  }

  tipo = 0;
  pthread_t * hilomodi;
  hilomodi = (pthread_t *) calloc( cantidadArchivos, sizeof( pthread_t ) );
  cout << cantidadArchivos << endl;
  for(int y = 0; y < cantidadArchivos;  y++)
  {
      Contando d;
      d.nombreArchivo = argv[2+y];
      d.estrategia = argv[argc-1][3+ tipo] - '0';
      d.etiquetas = mapaOriginal;
      tipo+=2;
      pthread_create(&hilomodi[y], NULL, &Trabajador, (void *) &d);
  }

  for ( int hilo = 0; hilo < cantidadArchivos; hilo++ ) {
      pthread_join( hilomodi[ hilo ], NULL );
  }

 
  
  return 0;
}
  
