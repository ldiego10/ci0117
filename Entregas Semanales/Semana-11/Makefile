all:
	g++ -g -Wall papaOmp.cc -fopenmp -o papaOmp.out
	g++ -g -Wall Mesa.h Mesa.cc Lock.h Lock.cc Condition.h Condition.cc filoOMP.cc -fopenmp -o filoOMP.out
	
papaOmp.out: papaOmp.cc
	g++ -g -Wall papaOmp.cc -fopenmp -o papaOmp.out

filoOMP.out: filoOMP.cc
	g++ -g -Wall Mesa.h Mesa.cc Lock.h Lock.cc Condition.h Condition.cc filoOMP.cc -fopenmp -o filoOMP.out 

