letrorium:main.o tabuleiro.o
	gcc -Wall -O3 -o letrorium main.o tabuleiro.o -lreadline
tabuleiro.o:tabuleiro.c tabuleiro.h
	gcc -c -Wall tabuleiro.c
main.o:main.c tabuleiro.h
	gcc -c -Wall main.c -lreadline
clean:
	rm *.o
