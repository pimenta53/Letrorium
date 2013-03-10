/**
 * @file main.c
 * @brief main do jogo
 * @author André Pimenta,João Gomes,Nelson Carvalho
 * @date 5 Março de 2010
 */
#include "tabuleiro.h"
#include "jogadas.h"
#include "comandos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * A função main é um ciclo que apenas termina quando o utilizador insere o comando "q"
 * Esta função vai então ser responsável por receber os comandos continuamente, e imprimir o resultado enquanto o jogo decorrer
 */
int main(){

	int flagAP=0;
	int flagAB=0;
	int DIM=0;
	Elem *Tab=NULL;
	Gravados gr;
	char *line;
	inicia_GR(&gr);

	
	while(1){	
	line = readline ("Letrorium> ");
	add_history (line);					
	executa_comando(line,&DIM,&Tab,&flagAP,&flagAB,&gr);	
	printf("\n");
	if(Tab) printTabuleiro(&DIM,&Tab);	
	printf("\n");
	if(flagAP) printf("Automaticas pretas:on\n");
	else printf("Automaticas pretas:off\n");
	if(flagAB) printf("Automaticas brancas:on\n");
	else printf("Automaticas brancas:off\n");
	}
	
return 0;
}

