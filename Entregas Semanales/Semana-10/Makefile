all:
	g++ piPorSeries.cc -DEBUG -g -Wall -fopenmp -o piPorSeries.out -pthread
	g++ sumaUno.cc -g -Wall -fopenmp -o sumaUno.out -pthread
	g++ matrixPar.cc -g -lgomp -fopenmp -o matrixPar.out -pthread
	
piPorSeries.out: piPorSeries.cc
	g++ piPorSeries.cc -DEBUG -g -Wall -fopenmp -o piPorSeries.out -pthread

sumaUno.out: sumaUno.cc
	g++ sumaUno.cc -g -Wall -fopenmp -o sumaUno.out -pthread

matrizPar.out: matrzPar.cc
	g++ matrixPar.cc -g -lgomp -fopenmp -o matrixPar.out -pthread



