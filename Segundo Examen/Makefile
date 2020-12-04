all:
	g++ -g -Wall palindromoOMP.cc -o palindromo.out -fopenmp
	mpicc factorialMPI.cc -o factorialMPI.out
	
palindromoOMP.out: palindromoOMP.cc
	g++ -g -Wall palindromoOMP.cc -o palindromo.out -fopenmp
	
factorialMPI.out: factorialMPI.cc
	mpicc factorialMPI.cc -o factorialMPI.out
