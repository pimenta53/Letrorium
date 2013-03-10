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
/**
 * @var Tab
 * @brief é o apontador associado ao Tabuleiro, atravez deste podemos ter a referencia ao tabuleiro guardado na memoria.
 */
Elem *Tab;

/**
 * @var DIM
 * @brief é a variavel global onde se guarda a dimenção do tabuleiro quando esta é lida
 */
int DIM;

int dimencao(FILE *fp);
int ficheiroValido(FILE *fp);
void freeTab();
int criarTabuleiro(char *nome);
int ajuda();
int jogada(char cor,int x,int y);
void printTabuleiro();
void gravaJogo (char *nome);
int executaJogada(char *args,char *cor);
int executaCriaJogo(char *args);
int executaGravaJogo(char *args);
int executa_comando(char *linha);

