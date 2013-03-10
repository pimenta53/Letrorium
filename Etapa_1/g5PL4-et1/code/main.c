/**
 * @file main.c
 * @brief main do jogo
 * @author André Pimenta,João Gomes,Nelson Carvalho
 * @date 5 Março de 2010
 */
#include"tabuleiro.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * A função main é um ciclo que apenas termina quando o utilizador insere o comando "q"
 * Esta função vai então ser responsável por receber os comandos continuamente, e imprimir o resultado enquanto o jogo decorrer
 */
int main(){


	char *line;

	system("clear");	
	while(1){	
	line = readline ("Letrorium> ");
	add_history (line);		
	system("clear");			
	executa_comando(line);	
	if(Tab!=NULL) printTabuleiro();	
	printf("\n\n");
	}
	
return 0;
}

