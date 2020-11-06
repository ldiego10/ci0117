/**
 *   Representa un conjunto de puntos en dos dimensiones
 *
**/


#include "Punto.h"


class VectorPuntos {
   public:
      VectorPuntos( long, double );
      VectorPuntos( long );
      ~VectorPuntos();
      long getElementos();
      long masCercano( Punto * );
      double variabilidad( Punto *, long, long * );
      double disimilaridad( VectorPuntos *, long * );
      void genEpsFormat( VectorPuntos *, long *, char * );
      Punto * operator [] ( long );
      int nuevoCentro(VectorPuntos * muestras, long * clases, long *);
      void Sumatoria( Punto * centro, long clase, long * clases );
      void imprimitCentros();
      void nuevoCentroOMP( long id, VectorPuntos * muestras,long * clases, long * contCentro);
      Punto * getPunto(int indice);


   private:
      long elementos;
      Punto ** bloque;


};
