/*#ifndef _BUZON_H
#define _BUZON_H
/*
   C++ class to encapsulate Unix message passing intrinsic structures and
   system calls

*/



#define KEY 0xA134	// Valor de la llave del recurso

class Buzon {
   public:
      Buzon(int);
      ~Buzon();
      int Enviar(int valorV, long tipo = 1);
      int Recibir(int valorV, long tipo = 1);
      
      struct papaBuf{
        long tipo;
        int valor;
        
      }pa;
      
   private:
      int id;		// Identificador del buzon
      int creador;
};
//#endif
