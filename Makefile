#make file

all:
	gcc multiplicador.c -o multiplicador.out
	gcc sumaUno.c -o sumaUno.out
	gcc PiPorSeries.c -o PiPorSeries.out

multiplicador.out: multiplicador.c
	gcc -g multiplicador.c -o multiplicador.out

sumaUno.out: sumaUno.c
	gcc -g sumaUno.c -o sumaUno.out

PiPorSeries.out: PiPorSeries.c
	gcc -g PiPorSeries.c -o PiPorSeries.out