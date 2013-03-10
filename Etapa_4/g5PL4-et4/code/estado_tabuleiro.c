/**
 * @file estado_tabuleiro.c
 * @brief Comandos de ajuda ao jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 3 Abril de 2010
 */
#include "tabuleiro.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**Função que percorre todas as posições do tabuleiro caso sejam pretas, verifica se não têm vizinas na vertical ou na horinzontal com a cor preta.
 * Caso exitam retorna uma mensagem de erro. 
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param erro flag que avisa se deve emitir mensagem de erro ou não para o utilizador
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int vb (Elem **Tab,int *DIM,int erro) {
	
	int i, j, x, y;
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	for (i=0;i<(*DIM);i++) {
		for (j=0;j<(*DIM);j++) {
			for (x=j;x<(*DIM);x++) {
				if (((*Tab)[i][j].letra == (*Tab)[i][x].letra) && ((*Tab)[i][x].cor == 'b') && ((*Tab)[i][j].cor == 'b') && (x!=j)) {
					if(erro)return mensagem_de_erro(E_WRONG_SOLUTION);
					else return 1;
				}
			}
			for (y=i;y<(*DIM);y++) {
				if (((*Tab)[i][j].letra == (*Tab)[y][j].letra) && ((*Tab)[y][j].cor == 'b') && ((*Tab)[i][j].cor == 'b') && (y!=i)) {
					if(erro)return mensagem_de_erro(E_WRONG_SOLUTION);
					else return 1;
				}
			}
		}
	}
	
	return 0;
}

/**
 * Função que percorre uma linha/coluna e ve se existem duas letras iguais com mesma cor(brABa), fazendo o mesmo para todas as linhas/colunas.
 * Caso exitam retorna uma mensagem de erro. 
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param erro flag que avisa se deve emitir mensagem de erro ou não para o utilizador
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */	
int vp(Elem **Tab,int *DIM,int erro) {
	
	int i,j;
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	for (i=0;i<((*DIM));i++) {
		for (j=0;j<((*DIM));j++) {
			if ((*Tab)[i][j].cor=='p') {
				if (i!=((*DIM)-1)) {
					if ((*Tab)[i+1][j].cor=='p'){
						if(erro)return mensagem_de_erro(E_WRONG_SOLUTION);
						else return 1;}
					}
				if (j!=((*DIM)-1)) {
					if ((*Tab)[i][j+1].cor=='p'){
						if(erro)return mensagem_de_erro(E_WRONG_SOLUTION);
						else return 1;
					}
				}
			}
		}
	}
	return 0;
}

/**
 * Função que procura a existencia de caminho entre todas as celulas brABas ou indefinidas.
 * Caso não exita retorna uma mensagem de erro.
 * @param tab_aux Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
void free_tab(int **tab_aux, int *DIM){
	int i;
	
	for (i=0;i<(*DIM);i++) {
						free((tab_aux)[i]);	
					}
				free(tab_aux);
	}

int prepara_tab(Elem **Tab, int **tab_aux, int *DIM){
	int i, j;
	
	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++) {
			if ((*Tab)[i][j].cor=='p') tab_aux[i][j]=0;
			else tab_aux[i][j]=1;
		}
	}
	
	for (j=0;j<(*DIM);j++){
			for (i=0;i<(*DIM);i++){
				if (tab_aux[i][j]==1) {
					tab_aux[i][j]=2;
					break;
					}
			}
		if (tab_aux[i][j]==2) break;
		}
	return 1;
	}


int caminho(int **tab_aux, int *DIM) {
	int lim, i,j,n,s,e,o;
	
	for (lim=0;lim<10;lim++){
		for (j=0;j<(*DIM);j++){
			for (i=0;i<(*DIM);i++){
				n=1;
				s=-1;
				e=-1;
				o=1;
				if (i==0) n=0;
				if (j==0) o=0;
				if (i==((*DIM)-1)) s=0;
				if (j==((*DIM)-1)) e=0;
				if (tab_aux[i][j]!=0 && (tab_aux[i][j-o]==2 || tab_aux[i][j-e]==2 || tab_aux[i-n][j]==2 || tab_aux[i-s][j]==2)){
					if (tab_aux[i][j]==1) tab_aux[i][j]=2;
					if (tab_aux[i][j-o]==1) tab_aux[i][j-o]=2;
					if (tab_aux[i][j-e]==1) tab_aux[i][j-e]=2;
					if (tab_aux[i-n][j]==1) tab_aux[i-n][j]=2;
					if (tab_aux[i-s][j]==1) tab_aux[i-s][j]=2;
					}
				}
			}
		}
		
	return 1;
	}

/**Função que percorre todas as posições do tabuleiro e verifica se existe um caminho entre todas elas(indefinidas ou brancas)
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param erro flag que avisa se deve emitir mensagem de erro ou não para o utilizador
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int vl(Elem **Tab, int *DIM,int erro){
	
	int **tab_aux=NULL;
	int i,j;
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
			
	tab_aux =malloc((*DIM)*sizeof(int*));
	for (i=0;i<(*DIM);i++) {
		tab_aux[i] =malloc(((*DIM))*sizeof(int));
	}

	prepara_tab(Tab,tab_aux,DIM);
		
	caminho(tab_aux, DIM);

	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++){
			if (tab_aux[i][j]==1) {
				free_tab (tab_aux,DIM);
				if(erro)return mensagem_de_erro(E_WRONG_SOLUTION);
				else return 1;
			}
		}
	}

	free_tab(tab_aux, DIM);
	
		
return 0;
}

/**Função que aplica todos os teste ao mesmo tempo de verificação do estado do tabuleiro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param erro flag que avisa se deve emitir mensagem de erro ou não para o utilizador
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int st(Elem **Tab, int *DIM,int erro) {
	
	if (vb(Tab,DIM,erro)) return 1;/*sair para não mandar varias mensagens de erro caso não passe nos testes todos*/
	if (vp(Tab,DIM,erro)) return 1;
	if (vl(Tab,DIM,erro)) return 1;

return 0;
}
