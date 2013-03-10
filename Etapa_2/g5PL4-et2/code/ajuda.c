/**
 * @file ajuda.c
 * @brief Comandos de ajuda ao jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 3 Abril de 2010
 */
#include "tabuleiro.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define CHUNK_SIZE  32

/**
 * Função que vai imprimir as intruçoes de ajuda guardada no ficheiro com as instruões de ajuda
 */
int ajuda(){
	
	int fd;
	char buf[CHUNK_SIZE];
	int bytes_r=0; 
	
	fd=open("ajuda.help", O_RDONLY);
	if(fd==-1) return 0;
	
	bytes_r=read(fd,buf,CHUNK_SIZE);
	while(bytes_r!=0){
		write(1,buf,bytes_r);
		bytes_r=read(fd,buf,CHUNK_SIZE);
	}
	close(fd);
	
return 0;

}

/**
 * Função que procura triplos no tabuleiro(tres letras iguais na mesma linha/coluna).
 * Para tal vai se percorrer todas as posiçoes do tabuleiro, ver caso exitam quais letras de cima e de baixo, para verificar se existe triplo na vertical, e a daesquerda e a da direita para a horizontal.
 * É também tido em contam o caso de exitirem quadroplos não serem considerados triplos.
 * Confirmando se a presença de um triplo atriubui se as cores correctas caso nenhuma das celulas não tenha um cor contraria, se não envia uma mensagem de erro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int trp(Elem **Tab,int *DIM){
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	if((*DIM)<3) return mensagem_de_erro(E_WRONG_SOLUTION);
	
	char c1,c2,c3,c4,c5=' ',c6=' ';
	int i,j; 
	
	for(i=0;i<(*DIM);i++){	
		for(j=0;j<(*DIM);j++){	
			if((i-1>=0)&&(i+1<(*DIM))){
				c1=(*Tab)[i-1][j].letra;
				c2=(*Tab)[i][j].letra;
				c3=(*Tab)[i+1][j].letra;
				if(i+2<*DIM) c4=(*Tab)[i+2][j].letra;
				else c4=' ';
				if(c1!=c5 && c1==c2 && c2==c3 && c3!=c4){
					if((*Tab)[i-1][j].cor=='b' || (*Tab)[i][j].cor=='p' || (*Tab)[i+1][j].cor=='b'){
						return mensagem_de_erro(E_WRONG_SOLUTION);}
				(*Tab)[i-1][j].cor='p';
				(*Tab)[i][j].cor='b';
				(*Tab)[i+1][j].cor='p';
				}
			c5=c1;
			}
			if((j-1>=0)&&j+1<(*DIM)){
				c1=(*Tab)[i][j-1].letra;
				c2=(*Tab)[i][j].letra;
				c3=(*Tab)[i][j+1].letra;
				if(j+2<*DIM) c4=(*Tab)[i][j+2].letra;
				else c4=' ';
				if(c1!=c6 && c1==c2 && c2==c3 && c3!=c4){
					if((*Tab)[i][j-1].cor=='b' || (*Tab)[i][j].cor=='p' || (*Tab)[i][j+1].cor=='b'){
						return mensagem_de_erro(E_WRONG_SOLUTION);}
				(*Tab)[i][j-1].cor='p';
				(*Tab)[i][j].cor='b';
				(*Tab)[i][j+1].cor='p';
				}
			c6=c1;
			}
		}
	}
	
return 0;
}

/**
 * Função que procura sandes no tabuleiro(tres letras onde apenas a do meio é diferente na mesma linha/coluna).
 * Para tal vai se percorrer todas as posiçoes do tabuleiro, ver caso exitam quais letras de cima e de baixo, para verificar se existe triplo na vertical, e a daesquerda e a da direita para a horizontal.
 * Confirmando se a presença de uma sandes de letras, atriubui se as cores correctas caso nenhuma das celulas não tenha um cor contraria, se não envia uma mensagem de erro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */			
int snd(Elem **Tab,int *DIM){
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	if(*DIM<3) return mensagem_de_erro(E_WRONG_SOLUTION);
	int i,j; 
	
	for(i=0;i<(*DIM);i++){	
		for(j=0;j<(*DIM);j++){	
			if((i-1>=0)&&(i+1<(*DIM))){
				if((*Tab)[i-1][j].letra==(*Tab)[i+1][j].letra && (*Tab)[i][j].letra!=(*Tab)[i+1][j].letra){
					if((*Tab)[i][j].cor=='p'){
						return mensagem_de_erro(E_WRONG_SOLUTION);}
				(*Tab)[i][j].cor='b';
				}
			}
			if((j-1>=0)&&j+1<(*DIM)){
				if((*Tab)[i][j-1].letra==(*Tab)[i][j+1].letra && (*Tab)[i][j].letra!=(*Tab)[i][j+1].letra){
					if((*Tab)[i][j].cor=='p'){
						return mensagem_de_erro(E_WRONG_SOLUTION);}
				(*Tab)[i][j].cor='b';
				}
			}
		}
	}
	
return 0;
}

/**
 * Função auxiliar que verifica se existem pares de letras numa linha ou numa coluna
 * Para tal vai percorrer a linha ou coluna e verifica se exite.
 * A função tem em conta o caso de tres letras seguidas não ser um par mas sim um triplo.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param pos Linha ou coluna onde vai procurar os pares
 * @param letra a letra que se pretende saber se existe pares ou não
 * @param local Para decidir se se procura nas linhas ou nas colunas
 * @return Inteiro que comfirma se existe ou não um para na coluna/linha.
 */	
int E_Par(Elem **Tab,int pos,char letra,int *DIM,char *local){
	
	int j;
	char c1,c2,c3,c4;
	
	if(strcmp(local,"linha")==0){
		for(j=0;j<(*DIM)-1;j++){/* para as linhas*/
			c1=(*Tab)[pos][j].letra;
			c2=(*Tab)[pos][j+1].letra;
			if(j+2<*DIM) c3=(*Tab)[pos][j+2].letra;else c3=' ';/* para verificar se é mesmo um par*/
			if(j-1>=0) c4=(*Tab)[pos][j-1].letra;else c4=' ';/* para verificar se é mesmo um par*/
			if(c1==c2 && c2!=c3 && c1!=c4 && c1==letra) return 1;
		}
	}
	if(strcmp(local,"coluna")==0){
		for(j=0;j<(*DIM)-1;j++){/* para as colunas*/
			c1=(*Tab)[j][pos].letra;
			c2=(*Tab)[j+1][pos].letra;
			if(j+2<*DIM) c3=(*Tab)[j+2][pos].letra;else c3=' ';/* para verificar se é mesmo um par*/
			if(j-1>=0) c4=(*Tab)[j-1][pos].letra;else c4=' ';/* para verificar se é mesmo um par*/
			if(c1==c2 && c2!=c3 && c1!=c4 && c1==letra) return 1;
		}
	}
			
return 0;
}	

/**
 * Função que procura pares isolados no tabuleiro(numa coluna ou numa linha).
 * Para tal vai se percorrer todas as posiçoes do tabuleiro, e ver se a letra é diferente das que a rodeiam na horizontal ou na vertical.
 * Confirmando se a presença de uma letra isola,chama a função auxiliar Epar que vai ver se exite um par dessa letra na coluna ou na linha.
 * Caso se verifiquem as duas condições irá ver se a letra não está de uma cor contraria á que se vai atribuir, caso não esteja atribui se uma nova cor, se não uma mensagem de erro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */	
int pis(Elem **Tab,int *DIM){
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	int i,j;
	char c1,c2,c3,c4,c5;
	
	
	for(i=0;i<(*DIM);i++){
		for(j=0;j<(*DIM);j++){
			if(i-1>=0) c1=(*Tab)[i-1][j].letra;else c1=' ';/* para verificar se é mesmo uma letra isolada*/
			if(i+1<*DIM) c3=(*Tab)[i+1][j].letra;else c3=' ';/* para verificar se é mesmo uma letra isolada*/
			c2=(*Tab)[i][j].letra;
			if(j-1>=0) c4=(*Tab)[i][j-1].letra;else c4=' ';/* para verificar se é mesmo uma letra isolada*/
			if(j+1<*DIM) c5=(*Tab)[i][j+1].letra;else c5=' ';/* para verificar se é mesmo uma letra isolada*/
			if((c4!=c2 && c2!=c5) && E_Par(Tab,i,c2,DIM,"linha")){
				if((*Tab)[i][j].cor=='b'){
					return mensagem_de_erro(E_WRONG_SOLUTION);}
				(*Tab)[i][j].cor='p';
			}
			if((c1!=c2 && c2!=c3) && E_Par(Tab,j,c2,DIM,"coluna")){
				if((*Tab)[i][j].cor=='b'){
					return mensagem_de_erro(E_WRONG_SOLUTION);}
				(*Tab)[i][j].cor='p';
			}
		}
	}
		
return 0;
}

/**Função que percorre todas as posições do tabuleiro caso sejam pretas, verifica se não têm vizinas na vertical ou na horinzontal com a cor preta.
 * Caso exitam retorna uma mensagem de erro. 
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int vb (Elem **Tab,int *DIM) {
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	int i, j, x, y;
	
	for (i=0;i<(*DIM);i++) {
		for (j=0;j<(*DIM);j++) {
			for (x=j;x<(*DIM);x++) {
				if (((*Tab)[i][j].letra == (*Tab)[i][x].letra) && ((*Tab)[i][x].cor == 'b') && ((*Tab)[i][j].cor == 'b') && (x!=j)) {
					return mensagem_de_erro(E_WRONG_SOLUTION);
				}
			}
			for (y=i;y<(*DIM);y++) {
				if (((*Tab)[i][j].letra == (*Tab)[y][j].letra) && ((*Tab)[y][j].cor == 'b') && ((*Tab)[i][j].cor == 'b') && (y!=i)) {
					return mensagem_de_erro(E_WRONG_SOLUTION);
				}
			}
		}
	}
	
	return 0;
}

/**
 * Função que percorre uma linha/coluna e ve se existem duas letras iguais com mesma cor(branca), fazendo o mesmo para todas as linhas/colunas.
 * Caso exitam retorna uma mensagem de erro. 
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */	
int vp(Elem **Tab,int *DIM) {
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	int a=0, i, j;
	
	for (i=0;i<((*DIM)-1);i++) {
		for (j=0;j<((*DIM)-1);j++) {
			if ((*Tab)[i][j].cor=='p') a=a+1;
			if ((*Tab)[i+1][j].cor=='p') a=a+1;
			if ((*Tab)[i][j+1].cor=='p') a=a+1;
			if ((*Tab)[i+1][j+1].cor=='p') a=a+1;
			if (a>2) {
				return mensagem_de_erro(E_WRONG_SOLUTION);
				return 0;
			}
			a=0;
		}
	}
	return 0;
}

/**
 * Função que procura a existencia de caminho entre todas as celulas brancas ou indefinidas.
 * Caso não exita retorna uma mensagem de erro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int vl(Elem **Tab, int *DIM){
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	int i, j, lim, k=0, n, s, e, o;
	int **tab_aux=NULL;
	
	
	tab_aux =malloc((*DIM)*sizeof(int*));
	for (i=0;i<(*DIM);i++) {
		tab_aux[i] =malloc(((*DIM))*sizeof(int));
	}

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
		}
		

	for (lim=0;lim<=(*DIM);lim++){
		for (j=0;j<lim;j++){
			for (i=0;i<lim;i++){
				n=1;
				s=-1;
				e=-1;
				o=1;
				if (i==0) n=0;
				if (j==0) o=0;
				if (i==(lim-1)) s=0;
				if (j==(lim-1)) e=0;
				if (tab_aux[i][j]!=0 && (tab_aux[i][j-o]==2 || tab_aux[i][j-e]==2 || tab_aux[i-n][j]==2 || tab_aux[i-s][j]==2)){
					if (tab_aux[i][j]==1) tab_aux[i][j]=2;
					if (tab_aux[i][j-o]==1) tab_aux[i][j-o]=2;
					if (tab_aux[i][j-e]==1) tab_aux[i][j-e]=2;
					if (tab_aux[i-n][j]==1) tab_aux[i-n][j]=2;
					if (tab_aux[i-s][j]==1) tab_aux[i-s][j]=2;
					}
				}
			}

			if (k<2*(*DIM)) {
				if (lim==(*DIM)) lim--;
				k++;
				}
		}

	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++){
			if (tab_aux[i][j]==1) {
				for (i=0;i<(*DIM);i++) {
						free((tab_aux)[i]);	
					}
				free(tab_aux);
				return mensagem_de_erro(E_WRONG_SOLUTION);
				}
		}
	}

	for (i=0;i<(*DIM);i++) {
		free((tab_aux)[i]);	
	}
	free(tab_aux);
	
		
return 0;
}

/**
 * Função auxiliar que verifica se existem pares de letras tanto nas linhas como nas colunas passdas como parametro.
 * Para tal vai percorrer a linha ou coluna e verifica se exite.
 * @param Tab Tabuleiro do jogo
 * @param letra1 Primeira letra da diagonal.
 * @param letra2 Segunda letra da diagonal
 * @param DIM dimensão do tabuleiro
 * @param line1 Linha da primeira letra
 * @param line2 Linha da segunda letra
 * @param cl1 Coluna da primeira letra
 * @param cl2 Coluna da segunda letra
 * @return Inteiro que comfirma se existe ou não um para na coluna/linha.
 */	 
int E_Par_des(Elem **Tab,char letra1,char letra2,int *DIM,int line1,int cl1,int line2,int cl2){
	
	int j;
	
	for(j=0;j<*DIM;j++){
		/* para as linhas*/
		if(j!=cl1 && j!=cl2 && (*Tab)[line1][j].letra==letra1 && (*Tab)[line2][j].letra==letra2) return 1;
		/* para as colunas*/
		if(j!=line1 && j!=line2 && (*Tab)[j][cl1].letra==letra1 && (*Tab)[j][cl2].letra==letra2) return 1;
	}
			
return 0;
}

/** 
 * Função responsavel por ver se existem ou não pares isolados no tabuliro.
 * Para tal esta função vai pegar em quatro celulas, formando um quadrado.Neste quadrado verifica se as duas diagonais pertencem ou não a regra pares desencontrados,com a ajuda da função auxiliar EpParDes.
 * Caso pertence ve se a diagonal contraria tem cores contrarias, se tiver dá uma mensagem de erro, se não muda as corres.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */	
int pds (Elem **Tab,int *DIM){
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	int i,j;
	
	
	for(i=0;i<(*DIM)-1;i++){
		for(j=0;j<(*DIM)-1;j++){
			if(E_Par_des(Tab,(*Tab)[i][j].letra,(*Tab)[i+1][j+1].letra,DIM,i,j,i+1,j+1)){ //i e j para vereficar se são diferentes das posiçoes passadas
				if((*Tab)[i][j+1].cor=='p' || (*Tab)[i+1][j].cor=='p'){
					return mensagem_de_erro(E_WRONG_SOLUTION);
				}
				(*Tab)[i][j+1].cor='b';
				(*Tab)[i+1][j].cor='b';
			}
			if(E_Par_des(Tab,(*Tab)[i+1][j].letra,(*Tab)[i][j+1].letra,DIM,i+1,j,i,j+1)){ //i e j para vereficar se são diferentes das posiçoes passadas
				if((*Tab)[i][j].cor=='p' || (*Tab)[i+1][j+1].cor=='p'){
					return mensagem_de_erro(E_WRONG_SOLUTION);
				}
				(*Tab)[i][j].cor='b';
				(*Tab)[i+1][j+1].cor='b';
			}
		}	
	}
	
return 0;
}
			
