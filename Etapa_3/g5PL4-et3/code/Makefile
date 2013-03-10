CFLAGS=-Wall -Wextra -pedantic -ansi -O2

letrorium:main.o tabuleiro.o erro.o comandos.o ajuda.o estado_tabuleiro.o jogadas.o
	gcc $(CFLAGS) -o letrorium main.o  tabuleiro.o erro.o comandos.o ajuda.o estado_tabuleiro.o jogadas.o  -lreadline
comandos.o:comandos.c comandos.h tabuleiro.h erro.h ajuda.h estado_tabuleiro.h
	gcc -c $(CFLAGS) comandos.c
erro.o:erro.c erro.h 
	gcc -c $(CFLAGS) erro.c
tabuleiro.o:tabuleiro.c tabuleiro.h erro.h
	gcc -c $(CFLAGS) tabuleiro.c
ajuda.o:ajuda.c ajuda.h tabuleiro.h erro.h 
	gcc -c $(CFLAGS) ajuda.c
estado_tabuleiro.o:estado_tabuleiro.c tabuleiro.h ajuda.h erro.h
	gcc -c $(CFLAGS) estado_tabuleiro.c
jogadas.o:jogadas.c jogadas.h tabuleiro.h erro.h ajuda.h
	gcc -c $(CFLAGS) jogadas.c
main.o:main.c tabuleiro.h comandos.h
	gcc -c $(CFLAGS) main.c -lreadline
clean:
	rm *.o
