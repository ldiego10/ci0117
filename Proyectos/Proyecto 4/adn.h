/**
 * Represent a DNA sequence
 *
 * @author	Programacion Concurrente
 *   Grupos 2 y 3
 *
 * @version	2020/Nov/13
 *
**/

#include <string>


class ADN {
   public:
      ADN( int = 100 );
      ADN( const char * );
      ~ADN();
      std::string toString();
      void printSeqs();
      void printSeqs( std::string, int, int, std::string = "" );
      char getCaracter(int id);

   private:
      std::string sequence;
};

