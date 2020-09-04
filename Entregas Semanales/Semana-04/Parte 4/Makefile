# CI-0117 Programacion Concurrente
# Makefile Semana-04
#
# Dining philosophers problem with fork and NON global variables
#
# Date: 2020/Ago/24
#

all: filoFork-ngv.out filoFork-gv.out

Lock.o: Lock.h Lock.cc
	g++ -g -c Lock.cc

Mutex.o: Mutex.h Mutex.cc
	g++ -g -c Mutex.cc

Semaforo.o: Semaforo.h Semaforo.cc
	g++ -g -c Semaforo.cc

filoFork-gv.o: filoFork-gv.cc Semaforo.h Mutex.h
	g++ -g -c filoFork-gv.cc

filoFork-ngv.out: filoFork-ngv.c
	gcc -g filoFork-ngv.c -o filoFork-ngv.out -lcurses

filoFork-gv.out: filoFork-gv.o Semaphore.o Mutex.o
	g++ -g -o filoFork-gv.out filoFork-gv.o Semaforo.o Lock.o Mutex.o -lcurses
