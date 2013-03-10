letrorium:main.o tabuleiro.o erro.o comandos.o ajuda.o
	gcc -Wall -O3 -o letrorium main.o  tabuleiro.o erro.o comandos.o ajuda.o  -lreadline
comandos.o:comandos.c comandos.h tabuleiro.h erro.h
	gcc -c -Wall comandos.c
erro.o:erro.c erro.h 
	gcc -c -Wall erro.c
tabuleiro.o:tabuleiro.c tabuleiro.h ajuda.h erro.h
	gcc -c -Wall tabuleiro.c
ajuda.o:ajuda.c ajuda.h tabuleiro.h erro.h
	gcc -c -Wall ajuda.c
main.o:main.c tabuleiro.h ajuda.h comandos.h
	gcc -c -Wall main.c -lreadline
clean:
	rm *.o
