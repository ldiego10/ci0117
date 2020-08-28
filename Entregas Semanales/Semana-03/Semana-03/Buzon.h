
/*
   C++ class to encapsulate Unix message passing intrinsic structures and
   system calls

*/

#define KEY 0xA12345	// Valor de la llave del recurso

class Buzon {
   public:
      Buzon();
      ~Buzon();
      int Enviar( char *mensaje );
      int Enviar( char *mensaje, int cantidad, long tipo = 1 );
      int Enviar( double respPi, long tipo = 1);
      int Enviar( long sumaUno, long tipo = 1);
      int Recibir( void *mensaje, long tipo = 1 );	// len: space in mensaje
      int Recibir( double piRespuesta, long tipo = 1);
      int Recibir( long sumaResp, long tipo = 1);
      struct msgbuf{
    	long tipo;
    	int times;	// Times that label appears
    	char label[ 64 ];
    
	}m,r;
      struct PiBuf{
	long tipo;
	double piResp;
      }p;
      struct sumaBuf{
        long tipo;
        long sumaU;
      }s;
   private:
      int id;		// Identificador del buzon
      int creador;
};
