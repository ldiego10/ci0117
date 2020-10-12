#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <string.h>
#include <fstream>
#include <mutex>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <cstring>


using namespace std;
class FileReader{

	public:
		FileReader(string, int, map <string, int>);
		~FileReader();
	 	char * getNext(char*, int, bool,int);
		bool hasNext();
		void contar();
		string getNombre();
		void setCantidadLineas(int cantidad);
		void cerrar();
		int getInstruccion();
		int counter = 0;
		std::map<std::string, int>::iterator itMapa;
		void setValor(int valor, string);
		int getCantidadLineas();
		map <string, int> getMapa();


	private:
		map <string, int> mapaLector;
		int instruccion;
		std::string nombreArchivo;
		int cantidadLineas;
		ifstream file;
};
#endif

