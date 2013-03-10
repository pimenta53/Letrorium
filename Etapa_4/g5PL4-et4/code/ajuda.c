/**
 * @file ajuda.c
 * @brief ajuda do jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 1 Maio de 2010
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "tabuleiro.h"
#include "erro.h"
#include "jogadas.h"
#include "estado_tabuleiro.h"
#include "ajuda.h"
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

int p_brancas(Elem **Tab, int i, int j,int *DIM,Gravados *gr,int erro){
	int n,o,s,e,mudou1,mudou2,mudou3,mudou4;
	mudou1=1;mudou2=1;mudou3=1;mudou4=1;
		
	if (i==0) n=0;else n=1;
	if (j==0) o=0;else o=1;
	if (i==((*DIM)-1)) s=0; else s=-1;
	if (j==((*DIM)-1)) e=0; else e=-1;
	
	if (n!=0) {
		if ((mudou1=jogada('b',j+1,(i-n)+1,Tab,gr,erro))>0) return -1;
	}
	if (s!=0) {
		if ((mudou2=jogada('b',j+1,(i-s)+1,Tab,gr,erro))>0) return -1;
	}
	if (e!=0) {
		if ((mudou3=jogada('b',j-e+1,i+1,Tab,gr,erro))>0) return -1;
	}
	if (o!=0) {
		if ((mudou4=jogada('b',j-o+1,i+1,Tab,gr,erro))>0) return -1;
	}
	if(mudou1==0 || mudou2==0 || mudou3==0 || mudou4==0) return 1;
	else return 0;

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
	
int p_preta(Elem **Tab, int i, int j,int *DIM,Gravados *gr,int erro){
	int a,mudou1,mudou2,letra;
	mudou1=-1;mudou2=-1;
	
	letra=(*Tab)[i][j].letra;
	for (a=0;a<(*DIM);a++){
		if(letra==(*Tab)[a][j].letra && a!=i) {
			if ((mudou1=jogada('p',j+1,a+1,Tab,gr,erro))>0) return -1;
		}
		if(letra==(*Tab)[i][a].letra && a!=j) {
			if ((mudou2=jogada('p',a+1,i+1,Tab,gr,erro))>0) return -1;
		}
	}
	
	if(mudou1==0 || mudou2==0) return 1;
	else return 0;

}

/**
 * A função verificaAB verifica se pinta a nova celula ou se esta já está pintada.
 * @param x coordenada das linhas.
 * @param y coordenada das colunas.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int verificaAB(int x, int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr){
	
	if (*flagAP){
		if (pretasAuto(x,y,Tab,DIM,flagAP,flagAB,gr)==0) return 0;
	}
	else{
		if (jogada('p',y+1,x+1,Tab,gr,0)>0) return 0;
	}
  
return 1;
}

/**
 * A função brancasAuto, infere a cor branca a celula, e chama a função vericaAB para ver s pode inferir outras cores sobre a cor inferida
 * @param x coordenada das linhas.
 * @param y coordenada das colunas.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int brancasAuto(int x, int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr){
  
  int i=0,valid=1;
  char letra;

  if (jogada('b',y+1,x+1,Tab,gr,0)>0) return 0;
  letra=(*Tab)[x][y].letra;

  while (i<(*DIM) && valid){
	if (i!=x && (*Tab)[i][y].letra==letra && (*Tab)[i][y].cor!='p'){
		if (!verificaAB(i,y,Tab,DIM,flagAP,flagAB,gr)) valid=0;
    }
    if (valid && i!=y && (*Tab)[x][i].letra==letra && (*Tab)[x][i].cor!='p'){
		if (!verificaAB(x,i,Tab,DIM,flagAP,flagAB,gr)) valid=0;
    }
    i++;
  }
return valid;
}

/**
 * A função verificaAP verifica se pinta a nova celula ou se esta já está pintada.
 * @param x coordenada das linhas.
 * @param y coordenada das colunas.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int verificaAP(int x, int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr){
  
	if (*flagAB) {
		if (brancasAuto(x,y,Tab,DIM,flagAP,flagAB,gr)==0) return 0;
	}
	else{ 
		if (jogada('b',y+1,x+1,Tab,gr,0)>0) return 0;
	}
	
return 1;
}

/**
 * A função pretasAuto, infere a cor preta a celula, e chama a função vericaAP para ver s pode inferir outras cores sobre a cor inferida
 * @param x coordenada das linhas.
 * @param y coordenada das colunas.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int pretasAuto(int x,int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr)
{

	if (jogada('p',y+1,x+1,Tab,gr,0)>0) return 0;

	if (x>0){
		if ((*Tab)[x-1][y].cor!='b')
			if (!verificaAP(x-1,y,Tab,DIM,flagAP,flagAB,gr)) return 0;
	}
	if (x+1<(*DIM)){
		if ((*Tab)[x+1	][y].cor!='b')
			if (!verificaAP(x+1,y,Tab,DIM,flagAP,flagAB,gr)) return 0;
	}
	if (y>0){
		if ((*Tab)[x][y-1].cor!='b')
			if (!verificaAP(x,y-1,Tab,DIM,flagAP,flagAB,gr)) return 0;
	}
	if (y+1<(*DIM)){
		if ((*Tab)[x][y+1].cor!='b')
			if (!verificaAP(x,y+1,Tab,DIM,flagAP,flagAB,gr)) return 0;
	}

return 1;
}

/**
 * A função auto_black procura no tabuleiro uma letra preta e chama a função p_brancas,
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int auto_black(Elem **Tab, int *DIM,Gravados *gr,int erro){
	int i,j, result, aux;
	aux=0;
	result=0;
	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++){
				if ((*Tab)[i][j].cor=='p') {
					aux = p_brancas(Tab,i,j,DIM,gr,erro);
					if(aux==-1) return -1;
					if (result==0) result = aux;
				}
			}
		}
		return result;
}



/**
 * A função auto_white procura no tabuleiro uma letra branca e chama a função p_preta,
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int auto_white(Elem **Tab,int *DIM,Gravados *gr,int erro){
	int i,j, result, aux;
	result=0;
	aux=0;
	
	for (i=0;i<(*DIM);i++){
		for (j=0;j<(*DIM);j++){
				if ((*Tab)[i][j].cor=='b') {
					aux = p_preta(Tab,i,j,DIM,gr,erro);
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
	
int control (Elem **Tab, int *DIM, int *flagAB, int *flagAP,Gravados *gr,int erro){
	int a, b,sair;
	a=0;b=0;sair=0;
	while (sair!=1 && sair!=-1) {
		if ((*flagAP)==1) a = auto_black(Tab,DIM,gr,erro);
		if(a==-1) return -1;
		if ((*flagAB)==1) b = auto_white(Tab,DIM,gr,erro);
		if(b==-1) return -1;
		if (((a==0) && (b==0))) sair=1;
	}
return sair;
}

/**
 * Funcao que tenta inferir uma cor a celula indicada, segundo as regras do jogo
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @returns Retorna um inteiro que irá indicar que foi introduzida a cor possivel.
 */

int change_tc(int i,int j,Elem **Tab,int *DIM,Gravados *gr,int *flagAP,int *flagAB){
	
	int preta=0,branca=0,flagON=1;
	
	grava_movimento(gr);
	jogada('p',j,i,Tab,gr,0);
	if(pretasAuto(i-1,j-1,Tab,DIM,&flagON,&flagON,gr)==0) preta=1;
	else{ if(st(Tab,DIM,0)) preta=1;}
	anm(Tab,gr);
	
	
	grava_movimento(gr);
	jogada('b',j,i,Tab,gr,0);
	if(brancasAuto(i-1,j-1,Tab,DIM,&flagON,&flagON,gr)==0) branca=1;
	else {if(st(Tab,DIM,0)) branca=1;}
	anm(Tab,gr);
	
	if(preta && branca) return mensagem_de_erro(E_WRONG_SOLUTION);
	if(!preta && branca) {
		grava_movimento(gr);
		jogada('p',j,i,Tab,gr,1);
		control(Tab,DIM,flagAB,flagAP,gr,1);
		return 1;}
	if(preta && !branca){
		grava_movimento(gr);
		jogada('b',j,i,Tab,gr,1);
		control(Tab,DIM,flagAB,flagAP,gr,1);
		return 1;}

return 0;
}

/**
 * Funcao que caso a 'executa_tc' não envie uma posição especifica, percorre todo o tabuleiro a procura de cores indefinidas e chama a funcao tc para tentar inferir uma cor a essa celula
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @returns Retorna um inteiro que irá indicar que foi percorrido todo o tabuleiro.
 */

int tc_auto(Elem **Tab,int *DIM,Gravados *gr,int *flagAP,int *flagAB){
	
	int i,j;
	
	for(i=0;i<(*DIM);i++){
		for(j=0;j<(*DIM);j++){
			if((*Tab)[i][j].cor=='i'){
				if(change_tc(i+1,j+1,Tab,DIM,gr,flagAP,flagAB)) return 0;
			}
		}
	}
return 0;
}

/**
 * Funcao que tenta inferir uma cor a celula indicada, segundo as regras do jogo
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @returns Retorna um inteiro que irá indicar que foi introduzida a core possivel.
 */

int tc(Elem **Tab,int *DIM,int x,int y,Gravados *gr,int *flagAP,int *flagAB){
	
	if((*DIM)==0) return mensagem_de_erro(E_NO_BOARD);
	if(y>=0 && x>=0){
		if((((x-1)<0) || ((x-1)>=(*DIM))) || (((y-1)<0) || ((y-1)>=(*DIM)))) {
			return mensagem_de_erro(E_COORDS);
		}
	}

	if(y==-1 && x==-1){
		 tc_auto(Tab,DIM,gr,flagAP,flagAB);
	}
	else { 
		if((*Tab)[x-1][y-1].cor=='i'){
			change_tc(x,y,Tab,DIM,gr,flagAP,flagAB);
		}
	}
return 0;
}

/**
 * Função que tal como o nome indica executa a função tc, esta funcao e responsavel por ver s a funcao tc irá receber a celula especifica ou caso contrario indica a funcao tc que irá ter de percorrer todo o tabuleiro
 * @param args argumentos a tratar.
 * @param DIM dimensão do tabuleiro.
 * @param Tab tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que foram introduzidas todas as cores possiveis.
 */
	
int executa_tc(char *args,int *DIM,Elem **Tab,int *flagAP,int *flagAB,Gravados *gr) {
  
	char buf[1024],teste1[1024],teste2[1024];
	int x, y,nargs;
	x=-1;y=-1;
	
	if(args[0]!='\0'){
		nargs = sscanf(args, "%s %s %[^\n]", teste1,teste2, buf);
		if(nargs != 2) {
			return mensagem_de_erro(E_ARGS);
		}
		if(!isdigit(teste1[0]) || !isdigit(teste2[0])) {
				return mensagem_de_erro(E_INVARGS);
		}

		nargs = sscanf(args, "%d %d %[^\n]", &x, &y, buf);
	}
	tc(Tab,DIM,y,x,gr,flagAP,flagAB);
	
return 0;
}

/**
 * A função vc percorre o tabuleiro e aplica as regras das pretas e das brancas ate que não seja possivel aplicar mais nenhuma regra
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que foram introduzidas todas as cores possiveis.
 */

int vc (Elem **Tab, int *DIM, Gravados *gr){
	int a, b,sair;
	a=0;b=0;sair=0;
	
	grava_movimento(gr);
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD);
	while (!sair) {
		a = auto_black(Tab,DIM,gr,1);
		if(a==-1 || vp(Tab,DIM,1)) return 1;
		b = auto_white(Tab,DIM,gr,1);
		if(b==-1 
		|| vb(Tab,DIM,1) ) return 1;
		if (((a==0) && (b==0))) sair=1;
	}
return sair;
}

