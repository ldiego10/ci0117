/**
 * Represent a DNA sequence
 *
 * @author	CI0117 Programacion Concurrente
 *    Grupos 2 y 3
 *
 * @version	2020/Nov/13
 *
**/

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "adn.h"

/**
 * Default contructor
 * Create a random length sequence and fill with (allowed) components
 *
**/

using namespace std;

ADN::ADN( int length ) {
   int posicion;
   char base = 'A';
   time_t ran;

   this->sequence = (char *) calloc( length + 1, sizeof( char ) );
   for ( posicion = 0; posicion < length; posicion++ ) {
      switch ( rand() % 4 ) {
         case 0:
            base = 'G';	// Nucleotids
            break;
         case 1:
            base = 'T';
            break;
         case 2:
            base = 'C';
            break;
         case 3:
            base = 'A';
            break;
      }
      this->sequence.push_back( base );
   }
   
}


/**
 * Parameter constructor
 * @param	char	an array of chars with DNA components
 *
**/
ADN::ADN( const char * string ) {
   char base;
   int posicion;

   for (int posicion = 0; posicion < strlen( string ); posicion++ ) {
      switch ( string[ posicion ] ) {	// The sequence can only have A, C, G, T components, any other letter is changed to T
         case 'A':
         case 'C':
         case 'G':
         case 'T':
            this->sequence.push_back( string[ posicion ] );
            break;
         default:
            this->sequence.push_back( 'T' );
            break;
      }
   }
}


/**
 *
 *
**/
ADN::~ADN() {
}


/**
 * Return a String with sequence
**/
std::string ADN::toString() {
   return this->sequence;
}


char  ADN::getCaracter(int id)
{
   return this->sequence[id];
}


/**
 *
**/
void ADN::printSeqs() {
   printSeqs( this->sequence, -1, this->sequence.size() );
}


/**
 *
**/
void ADN::printSeqs( std::string str, int start, int end, std::string curStr ) {
	//base case
	if (start == end) {
		return;
	}
	//print current string permutation
	printf( "%s\n", curStr.c_str() );
	for ( int i = start + 1; i< end; i++ ) {
		curStr += str[i];
		printSeqs( str, i, end, curStr );
		curStr = curStr.erase( curStr.size() - 1 );
	}
}

