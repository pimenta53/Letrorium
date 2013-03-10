/**
 * @file ajuda.c
 * @brief ajuda do jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 1 Maio de 2010
 */
#include "tabuleiro.h"
#include "erro.h"
#include "jogadas.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define CHUNK_SIZE  32

/**
 * Função que vai imprimir as intruçoes de ajuda guardada no ficheiro com as instruões de ajuda
 */
int ajuda(){
	
	int fd;
	char buf[CHUNK_SIZE];
	int bytes_r,bytes_w;
	bytes_r=0;
	bytes_w=0;
	
	fd=open("ajuda.help", O_RDONLY);
	if(fd==-1) return 0;
	
	bytes_r=read(fd,buf,CHUNK_SIZE);
	while(bytes_r!=0){
		bytes_w=write(1,buf,bytes_r);
		bytes_r=read(fd,buf,CHUNK_SIZE);
	}
	close(fd);
	
return 0;

}

/**
 * A função p_branca pinta de branco todas as letras avolta da letra da posição (i,j).
 * @param Tab tabuleiro.
 * @param i linha.
 * @param j coluna.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int p_brancas(Elem **Tab, int i, int j,int *DIM,Gravados *gr){
	int n,o,s,e,mudou1,mudou2,mudou3,mudou4;
	mudou1=1;mudou2=1;mudou3=1;mudou4=1;
		
	if (i==0) n=0;else n=1;
	if (j==0) o=0;else o=1;
	if (i==((*DIM)-1)) s=0; else s=-1;
	if (j==((*DIM)-1)) e=0; else e=-1;
	
	if (n!=0) {
		if ((mudou1=jogada('b',j+1,(i-n)+1,Tab,gr))>0) return -1;
	}
	if (s!=0) {
		if ((mudou2=jogada('b',j+1,(i-s)+1,Tab,gr))>0) return -1;
	}
	if (e!=0) {
		if ((mudou3=jogada('b',j-e+1,i+1,Tab,gr))>0) return -1;
	}
	if (o!=0) {
		if ((mudou4=jogada('b',j-o+1,i+1,Tab,gr))>0) return -1;
	}
	if(mudou1==0 || mudou2==0 || mudou3==0 || mudou4==0) return 1;
	else return 0;

}

/**
 * A função auto_black procura no tabuleiro uma letra preta e chama a função p_brancas,
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int auto_black(Elem **Tab, int *DIM,Gravados *gr){
	int i,j, result, aux;
	aux=0;
	result=0;
	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++){
				if ((*Tab)[i][j].cor=='p') {
					aux = p_brancas(Tab,i,j,DIM,gr);
					if(aux==-1) return -1;
					if (result==0) result = aux;
				}
			}
		}
		return result;
}

/**
 * A função p_preta procura na linha (i) e na coluna (j) uma letra igual á letra passada e pinta essa letra de preto.
 * @param Tab tabuleiro.
 * @param i linha.
 * @param j coluna.
 * @param letra letra.
 * @param DIM dimenção do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */
	
int p_preta(Elem **Tab, int i, int j,char letra,int *DIM,Gravados *gr){
	int a,mudou1,mudou2;
	mudou1=-1;mudou2=-1;
	
	for (a=0;a<(*DIM);a++){
		if(letra==(*Tab)[a][j].letra && a!=i) {
			if ((mudou1=jogada('p',j+1,a+1,Tab,gr))>0) return -1;
		}
		if(letra==(*Tab)[i][a].letra && a!=j) {
			if ((mudou2=jogada('p',a+1,i+1,Tab,gr))>0) return -1;
		}
	}
	
	if(mudou1==0 || mudou2==0) return 1;
	else return 0;

}

/**
 * A função auto_white procura no tabuleiro uma letra branca e chama a função p_preta,
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int auto_white(Elem **Tab,int *DIM,Gravados *gr){
	int i,j, result, aux;
	result=0;
	aux=0;
	
	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++){
				if ((*Tab)[i][j].cor=='b') {
					aux = p_preta(Tab,i,j,(*Tab)[i][j].letra,DIM,gr);
					if(aux==-1) return -1;
					if (result==0) result = aux;
				}
			}
		}
	return result;
}

/**
 * A função control recebe, o tabuleiro as dimensoes do mesmo, bem como as flags dos automaticos,
 * e dependendo das flags que estão activas chamas auto_white e/ou auto_black sucessivamente até que estas já não façam nenhuma alteração no tabuleiro
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que foram introduzidas todas as cores possiveis.
 */
	
int control (Elem **Tab, int *DIM, int *flagAB, int *flagAP,Gravados *gr){
	int a, b;
	a=0;
	b=0;
	while (1) {
		
	if ((*flagAP)==1) a = auto_black(Tab,DIM,gr);
	if ((*flagAB)==1) b = auto_white(Tab,DIM,gr);
	if (((a==0) && (b==0)) || a==-1 || b==-1) break;
}
	return 0;
}
