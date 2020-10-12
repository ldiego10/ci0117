#include "FileReader.h"
#include <functional>

FileReader::FileReader(string nombreArchivo, int instruccion, map <string, int> mapaLector)
{
	this->nombreArchivo = nombreArchivo;
	this->instruccion = instruccion;
	this->mapaLector = mapaLector;
	this->file.open(nombreArchivo);
  	this->itMapa = mapaLector.begin();
	contar();
}

FileReader::~FileReader()
{

}

void FileReader::contar()
{
	string linea;
	int counter = 0;
	while(getline(file, linea))
	{
		counter++;
	}
	

	file.clear();
	file.seekg(0, std::ios::beg);
	setCantidadLineas(counter);
	counter = 0;
}

int FileReader::getInstruccion(){
	return this->instruccion;
}


char * FileReader::getNext(char * buffer, int indiceInicial, bool bandera, int siguiente){

	string temp;
	char* temp2 = (char *) malloc(512 * sizeof(char));
	int contador = 0;
	file.clear();
	file.seekg(0, std::ios::beg);
	if(bandera != false){
		if(file.is_open()){
			while(temp != buffer && !file.eof()){
				getline(file, temp);
			}
			if(!file.eof())
			{
					while(contador < siguiente)
					{
						getline(file, temp);
						contador++;
					}
			}
		}
	}else{
		if(file.is_open()){
			while(contador <= indiceInicial){
				getline(file, temp);
				contador++;
			}
			bandera = false;
		}
	}
	if(temp.size() > 512){
		cout << "Lineas mayor a 512" << endl;
		exit(0);
	}

	strcpy(temp2, temp.c_str());
	return &temp2[0];
}


map <string, int> FileReader::getMapa()
{
	return this->mapaLector;
}

void FileReader::setCantidadLineas(int cantidad)
{
	this->cantidadLineas = cantidad;
}

void FileReader::setValor(int valor, string e)
{
	std::map<string, int>::iterator it = mapaLector.find(e);
	if(it != mapaLector.end())
	it->second = valor;
}

string FileReader::getNombre()
{
	return this->nombreArchivo;
}

void FileReader::cerrar()
{
	file.close();
}



int FileReader::getCantidadLineas()
{
	return this->cantidadLineas;
}


