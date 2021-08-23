all: main clear

main: leitura.o coloracao.o main.o
	gcc leitura.o coloracao.o main.o -o tp3

main.o: main.c coloracao.h leitura.h
	gcc -g -c main.c

coloracao.o: coloracao.c coloracao.h
	gcc -g -c coloracao.c

leitura.o: leitura.c leitura.h
	gcc -g -c leitura.c

clear:
	rm *.o
