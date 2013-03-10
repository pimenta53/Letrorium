/**
 * @file tabuleiro.h
 * @brief header file do tabuleiro.c
 * @author André Pimenta,Miguel Gomes,Nelson Cravalho
 * @date 5 Março de 2010
 */
#include<stdio.h>
/**
 * @struct elemento tabuleiro.h  
 * @brief É  constituida por dois chars, que correspondem ás caracteristicas de cada celula do tabuliro, a cor e aletra.
 */
typedef struct elemento{
/**
 * @var letra 
 * @brief Letra da celula do tabuleiro
 */	
	char letra;
/**
 * @var cor 
 * @brief Cor da celula do tabuleiro
 */
	char cor;
}Elemento,*Elem;



int dimencao(FILE *fp,int *DIM);
int ficheiroValido(FILE *fp,int *DIM);
void freeTab(int *DIM,Elem **Tab);
int criarTabuleiro(char *nome,int *DIM,Elem **Tab);
int jogada(char cor,int x,int y,int *DIM,Elem **Tab);
void printTabuleiro(int *DIM,Elem **Tab);
int gravaJogo (char *nome,int *DIM,Elem **Tab);
