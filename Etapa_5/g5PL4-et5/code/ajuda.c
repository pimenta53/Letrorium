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
 * Função que vai imprimir as intruçoes de ajuda guardada no ficheiro com as instruões de ajuda.
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
 * A função p_branca pinta de branco todas as letras à volta da letra da posição (i,j).
 * @param Tab tabuleiro.
 * @param i linha.
 * @param j coluna.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param erro flag que permite ou não enviar mensagens de erro
 * @returns Retorna um inteiro que irá indicar se houve ou não alguma alteração no tabuleiro.
 */

int p_brancas(Elem **Tab, int i, int j,int *DIM,Gravados *gr,int erro){
	int n,o,s,e,mudou1,mudou2,mudou3,mudou4;
	mudou1=1;mudou2=1;mudou3=1;mudou4=1;
		
	if (i==0) n=0;else n=1;
	if (j==0) o=0;else o=1;
	if (i==((*DIM)-1)) s=0; else s=-1;
	if (j==((*DIM)-1)) e=0; else e=-1;
	
	if (n!=0) {
		if ((mudou1=jogada('b',j+1,(i-n)+1,Tab,gr,erro,NULL))>0) return -1;
	}
	if (s!=0) {
		if ((mudou2=jogada('b',j+1,(i-s)+1,Tab,gr,erro,NULL))>0) return -1;
	}
	if (e!=0) {
		if ((mudou3=jogada('b',j-e+1,i+1,Tab,gr,erro,NULL))>0) return -1;
	}
	if (o!=0) {
		if ((mudou4=jogada('b',j-o+1,i+1,Tab,gr,erro,NULL))>0) return -1;
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
 * @param erro flag que permite ou não enviar mensagens de erro
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar se houve ou não alguma alteração no tabuleiro.
 */
	
int p_preta(Elem **Tab, int i, int j,int *DIM,Gravados *gr,int erro){
	int a,mudou1,mudou2,letra;
	mudou1=-1;mudou2=-1;
	
	letra=(*Tab)[i][j].letra;
	for (a=0;a<(*DIM);a++){
		if(letra==(*Tab)[a][j].letra && a!=i) {
			if ((mudou1=jogada('p',j+1,a+1,Tab,gr,erro,NULL))>0) return -1;
		}
		if(letra==(*Tab)[i][a].letra && a!=j) {
			if ((mudou2=jogada('p',a+1,i+1,Tab,gr,erro,NULL))>0) return -1;
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
 * @param cores apontador para um inteiro que irá guardar o num de cores que foram alteradas por esta acção
 * @returns Retorna um inteiro que irá indicar se houve ou não alguma alteração no tabuleiro.
 */

int verificaAB(int x, int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr,int *cores){
	
	if (*flagAP){
		if (pretasAuto(x,y,Tab,DIM,flagAP,flagAB,gr,cores)==0) return 0;
	}
	else{
		if (jogada('p',y+1,x+1,Tab,gr,0,cores)>0) return 0;
	}
  
return 1;
}

/**
 * A função brancasAuto, infere a cor branca à célula, e chama a função vericaAB para ver se pode inferir outras cores mediante a cor inferida.
 * @param x coordenada das linhas.
 * @param y coordenada das colunas.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param cores apontador para um inteiro que irá guardar o num de cores que foram alteradas por esta acção
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar se houve ou não alguma alteração no tabuleiro.
 */

int brancasAuto(int x, int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr,int * cores){
  
  int i=0,valid=1;
  char letra;

  if (jogada('b',y+1,x+1,Tab,gr,0,cores)>0) return 0;
  letra=(*Tab)[x][y].letra;

  while (i<(*DIM) && valid){
	if (i!=x && (*Tab)[i][y].letra==letra && (*Tab)[i][y].cor!='p'){
		if (!verificaAB(i,y,Tab,DIM,flagAP,flagAB,gr,cores)) valid=0;
    }
    if (valid && i!=y && (*Tab)[x][i].letra==letra && (*Tab)[x][i].cor!='p'){
		if (!verificaAB(x,i,Tab,DIM,flagAP,flagAB,gr,cores)) valid=0;
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
 * @param cores apontador para um inteiro que irá guardar o num de cores que foram alteradas por esta acção
 * @param flagAP flag do automático preto.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar se houve ou não alguma alteração no tabuleiro.
 */

int verificaAP(int x, int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr,int *cores){
  
	if (*flagAB) {
		if (brancasAuto(x,y,Tab,DIM,flagAP,flagAB,gr,cores)==0) return 0;
	}
	else{ 
		if (jogada('b',y+1,x+1,Tab,gr,0,cores)>0) return 0;
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
 * @param cores apontador para um inteiro que irá guardar o num de cores que foram alteradas por esta acção
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que houve alguma alteração no tabuleiro.
 */

int pretasAuto(int x,int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr,int *cores)
{

	if (jogada('p',y+1,x+1,Tab,gr,0,cores)>0) return 0;

	if (x>0){
		if ((*Tab)[x-1][y].cor!='b')
			if (!verificaAP(x-1,y,Tab,DIM,flagAP,flagAB,gr,cores)) return 0;
	}
	if (x+1<(*DIM)){
		if ((*Tab)[x+1	][y].cor!='b')
			if (!verificaAP(x+1,y,Tab,DIM,flagAP,flagAB,gr,cores)) return 0;
	}
	if (y>0){
		if ((*Tab)[x][y-1].cor!='b')
			if (!verificaAP(x,y-1,Tab,DIM,flagAP,flagAB,gr,cores)) return 0;
	}
	if (y+1<(*DIM)){
		if ((*Tab)[x][y+1].cor!='b')
			if (!verificaAP(x,y+1,Tab,DIM,flagAP,flagAB,gr,cores)) return 0;
	}

return 1;
}

/**
 * A função auto_black procura no tabuleiro uma letra preta e quando encontra chama a função p_brancas,
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param erro flag que permite ou não enviar mensagens de erro
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar se houve ou não alguma alteração no tabuleiro.
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
 * A função auto_white procura no tabuleiro uma letra branca e quando encontra chama a função p_preta,
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param erro flag que permite ou não enviar mensagens de erro
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
 * A função control recebe, o tabuleiro as dimensões do mesmo, bem como as flags dos automaticos,
 * e dependendo das flags que estão activas chamas auto_white e/ou auto_black sucessivamente até que estas já não façam nenhuma alteração no tabuleiro
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param erro flag que permite ou não enviar mensagens de erro
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
 * Funcao que recebe as coordenadas de uma celula do tabuleiro e verifica se nessas coordenadas a célula é
 * branca ou preta e se a respectiva flag está activa e caso esteja chama a funcao brancasAuto/pretasAuto.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param x coordenada da linha.
 * @param y coordenada da coluna.
 * @param cores apontador para um inteiro que irá guardar o num de cores que foram alteradas por esta acção
 */

void automatico(Elem **Tab,int *DIM,Gravados *gr,int *flagAP,int *flagAB,int x, int y,int *cores){

	if((*flagAB) && (*Tab)[x][y].cor=='b') brancasAuto(x,y,Tab,DIM,flagAP,flagAB,gr,cores);
	if((*flagAP) && (*Tab)[x][y].cor=='p') pretasAuto(x,y,Tab,DIM,flagAP,flagAB,gr,cores);
}



/**
 * Funcao que testa se não posição que é passada pode ser inserida a cor preta a célula ou cor branca, ou as duas ou nenhum, caso apenas uma delas possa ser inferida
 * a função infere essa mesma cor.
 * @param i coordenada da linha.
 * @param j coordenada da coluna.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param cores apontador para um inteiro que irá guardar o num de cores que foram alteradas por esta acção
 * @returns Retorna um inteiro que irá indicar que foi introduzida a cor possivel ou se não foi possivel inferir qualquer cor.
 */

int change_tc(int i,int j,Elem **Tab,int *DIM,Gravados *gr,int *flagAP,int *flagAB,int *cores){
	
	int preta=0,branca=0,flagON=1;
	
	grava_movimento(gr);
	jogada('p',j,i,Tab,gr,0,NULL);
	if(pretasAuto(i-1,j-1,Tab,DIM,&flagON,&flagON,gr,NULL)==0) preta=1;
	else{ if(st(Tab,DIM,0)) preta=1;}
	anm(Tab,gr);
	
	
	grava_movimento(gr);
	jogada('b',j,i,Tab,gr,0,NULL);
	if(brancasAuto(i-1,j-1,Tab,DIM,&flagON,&flagON,gr,NULL)==0) branca=1;
	else {if(st(Tab,DIM,0)) branca=1;}
	anm(Tab,gr);
	
	if(preta && branca) return mensagem_de_erro(E_WRONG_SOLUTION);
	if(!preta && branca) {
		grava_movimento(gr);
		jogada('p',j,i,Tab,gr,1,cores);
		automatico(Tab,DIM,gr,flagAP,flagAB,i-1,j-1,cores);
		return 1;}
	if(preta && !branca){
		grava_movimento(gr);
		jogada('b',j,i,Tab,gr,1,cores);
		automatico(Tab,DIM,gr,flagAP,flagAB,i-1,j-1,cores);
		return 1;}

return 0;
}

/**
 * Funcao chamada pela função 'tc' caso esta não receba uma posição especifica, percorre todo o tabuleiro a procura de cores indefinidas e chama a funcao change_tc para tentar inferir uma cor a essa celula
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
				if(change_tc(i+1,j+1,Tab,DIM,gr,flagAP,flagAB,NULL)) return 1;
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
 * @returns Retorna um inteiro que irá indicar que foi introduzida a cor possível.
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
			change_tc(x,y,Tab,DIM,gr,flagAP,flagAB,NULL);
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
		if(b==-1 || vb(Tab,DIM,1) ) return 1;
		if (((a==0) && (b==0))) sair=1;
	}
return sair;
}

/**
 * Função que vai dar o numero de celulas que são mudadas, devido à celula com as cordenadas j e i, mudarem de cor, passa tambem para o apontador cor, qual a cor que mudou.
 * Para isso a função vai executar a tc e ve se muda a cor e se mudar tem na variavel mudadas o total de cores mudadas, após isto voçta a por o tabuleiro como estava, apenas serve para dar o "impacto" de uma cor no tabuleiro
 * @param cor apontador para a cor que provaca mudança nas outras.
 * @param i linha da celula
 * @param j coluna da celula
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que foram introduzidas todas as cores possiveis.
 */
			
int impacto(Elem **Tab,int *DIM,int i,int j,char *cor,Gravados *gr){
	
	int flagON=1,mudou,mudadas=0;
	
	grava_movimento(gr);
	mudou=change_tc(i+1,j+1,Tab,DIM,gr,&flagON,&flagON,&mudadas);		
	if(mudou){
		if((*Tab)[i][j].cor=='b') (*cor)='b';
		else (*cor)='p';
		anm(Tab,gr);
	}

return mudadas;
}

/**
 * A função 'imp' percorre o tabuleiro e onde a cor for indefinida chama a função 'impaco' que lhe irá retorna o num de
 * células mudadas e vai comparando e guardando caso a célula seguinte tenha alterado mais celula que a anterior, e no fim depois
 * de o tabuleiro todo percorrido infere a cor a célula com mais impacto.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @returns Retorna um inteiro que irá indicar que foi inferida uma cor à célula de maior impacto.
 */
			
int imp (Elem **Tab, int *DIM, Gravados *gr,int *flagAP, int *flagAB) {
	int i=0,j=0,x=0,y=0,maior=0,imp=0;	
	char cor='i',cor_aux='i';
	
	for(i=0;i<(*DIM);i++){
		for(j=0;j<(*DIM);j++){
			if((*Tab)[i][j].cor=='i'){
				imp=impacto(Tab,DIM,i,j,&cor_aux,gr);
				if(imp>maior){
					maior=imp;x=i;y=j;cor=cor_aux;
				}
			}
		}
	}
	if(cor!='i'){
		grava_movimento(gr);	
		jogada(cor,y+1,x+1,Tab,gr,0,NULL);
		automatico(Tab,DIM,gr,flagAP,flagAB,x,y,NULL);
	}
	else return 0;

return 1;
}

/**
 * A função 'corPossivel' vai colocar quantas celulas muda a cor naquela celula, ou seja vai tentar branco e conta quantas mudou, se não mudar nenhuma devido a ser jogada imposivel poem nos apontadores para as mudadas correspondentes.
 * Pode se então dizer a funcionalidade desta função é dar a cor/cores possiveis de serem jogadas na celula em questão e o numero  de alterações que esta provoca.
 * @param x linha da celula
 * @param y coluna da celula
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAB flag do automático branco.
 * @param flagAP flag do automático preto.
 * @param brancas apontador destinado a armazenar o numero de celulas mudadas caso a celula com as cordenadas x e y seja branca.
 * @param pretas apontador destinado a armazenar o numero de celulas mudadas caso a celula com as cordenadas x e y seja preta.
 * @returns Retorna um inteiro que irá indicar que foi inferida uma cor à célula de maior impacto.
 */

void corPossivel(int x, int y,Elem **Tab, int *DIM,Gravados *gr, int *brancas, int *pretas) {
    int flagON=1,branca=0,preta=0,jogou;
                
    it(gr);
	jogou=jogada('p',y+1,x+1,Tab,gr,0,pretas);
	if(pretasAuto(x,y,Tab,DIM,&flagON,&flagON,gr,pretas)==0) preta=1;
	else{ if(st(Tab,DIM,0)) preta=1;}
	if(preta) *pretas=0;
	rb(Tab,gr);
        
        
    it(gr);
	jogada('b',y+1,x+1,Tab,gr,0,brancas);
	if(brancasAuto(x,y,Tab,DIM,&flagON,&flagON,gr,brancas)==0) branca=1;
	else{ if(st(Tab,DIM,0)) branca=1;}
	if(branca) *brancas=0;
	rb(Tab,gr);
}

/**
 * A função 'tentativa' testa se qual a cor a puder ser inferida, e caso seja possível inferir apenas uma única
 * cor, esta é inferida. 
 * @param x coordenada da linha.
 * @param y coordenada da coluna.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param brancas apontador destinado a armazenar o numero de celulas mudadas caso a celula com as cordenadas x e y seja branca.
 * @param pretas apontador destinado a armazenar o numero de celulas mudadas caso a celula com as cordenadas x e y seja preta.
 * @returns Retorna um inteiro que irá indicar que foi inferida uma cor à célula de maior impacto.
 */

int tentativa(int x, int y,Elem **Tab, int *DIM,Gravados *gr,int *brancas, int *pretas) {
	
	int flagON=1;
	
	corPossivel(x,y,Tab,DIM,gr,brancas,pretas);
	if (*brancas && *pretas) return 0;
	if (!(*brancas) && !(*pretas)) return -1;

	if (*brancas) {
		jogada('b',y+1,x+1,Tab,gr,0,NULL);
		brancasAuto(x,y,Tab,DIM,&flagON,&flagON,gr,NULL);
	}
	else {
		jogada('p',y+1,x+1,Tab,gr,0,NULL);
		automatico(Tab,DIM,gr,&flagON,&flagON,x,y,NULL);
	}
	
	return 1;
}

/**
 * A função 'tentarFinais' vai pintando as cores finais possiveis de adivinhar (comando tc),das qu não são possiveis as duas vai guardando a que tem maior impacto ao ser branca, se existir uma celula que não pode ter nenhuma cor, então irá returna o erro em return -1;
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param x onde irá guardar a coordenada do linha
 * @param y onde irá guardar a coordenada da coluna
 * @returns Retorna um inteiro que irá indicar se foi ou não possivel inferir uma cor na célula.
 */

int tentarFinais(Elem **Tab, int *DIM,Gravados *gr,int *x, int *y) {
	int i,j, brancas, pretas, res,maior=0;

	for (j = 0; j<*DIM; j++) {
		for (i = 0; i<*DIM; i++) {
			if ((*Tab)[i][j].cor == 'i') {
				brancas = pretas = 0;
				res = tentativa(i,j,Tab,DIM,gr,&brancas,&pretas);
				if (res == 0) {
					if (brancas > maior) {
						maior = brancas;
						*x=i;
						*y=j;
					}
				} else return res;
			}
		}
	}

	return 0;
}

/**
 * A função 'resolve' é chamada quando existe uma celululas que não são pintadas pela tc, ou seja que no estado actual do tabuleiro podem ter qualquer cor.
 * Ela vai tentar pintar de branco e chama a rsv, que vai pintar o resto, caso, não seja a cor, retocede e pinta de preto, esta função vai ser chamada para as celulas que podem ter as duas cores no estado actual do tabuleiro. 
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param x coordenada do linha
 * @param y coordenada da coluna
 * @returns Retorna um inteiro 
 */

int resolve(Elem **Tab,int *DIM,Gravados *gr, int x ,int y) {
		int preta=0,branca=0,flagON=1;
		
		
		it(gr);
		jogada('b',y+1,x+1,Tab,gr,0,NULL);
		if(brancasAuto(x,y,Tab,DIM,&flagON,&flagON,gr,NULL)==0) branca=1;
		else{ if(st(Tab,DIM,0)) branca=1;}
		if (!branca)
			if (rsv(Tab,DIM,gr))return 1;
		rb(Tab,gr);
		
		
		it(gr);
		jogada('p',y+1,x+1,Tab,gr,0,NULL);
		if(pretasAuto(x,y,Tab,DIM,&flagON,&flagON,gr,NULL)==0) preta=1;
		else{ if(st(Tab,DIM,0)) preta=1;}
		if(!preta)
			if (rsv(Tab,DIM,gr))return 1;
		rb(Tab,gr);

return 0;
}

/**
 * A função 'rsv' resolve o tabuleiro, para isso vai chamar a tentar finais , onde são atribuidas as cores finais do tabuleiro que conseguimos saber no momento, caso ainda não esteja resolvido devolve caso tal seja possivel as coredenadas de uma celula que pode ter as duas cores e caso seja brnaca tem maior impacto no tabuleiro.
 * Esta celula vai ser passada a função resolve que vai lhe atribuir a cor final, a função resolve funciona de forma recursiva e vai chamar a rsv após atribuir a cor, para que esta atribua as cores as novas celulas desbloqueadas.
 * Este processo repetece até o tabuleiro estar resolvido. 
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que indica se o tabuleiro tem ou não resolução.
 */

int rsv(Elem **Tab, int *DIM,Gravados *gr) {
	int x=-1, y=-1, res=1;
		
	while (res!=0 && res!=-1) {
		res = tentarFinais(Tab,DIM,gr,&x,&y);
	}

	if (res == -1) return 0;
	if (res == 0  && x==-1 && y==-1) return 1;

	if (!resolve(Tab,DIM,gr,x,y)) return 0;
	return 1;
}

/**
 * A função 'copy_board' faz uma cópia do tabuleiro original mas coloca todas as celulas com uma cor indefinida. 
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que foi inferida uma cor à célula de maior impacto.
 */

Elem* copy_board(Elem **Tab,int *DIM,Gravados *gr){
	
	int i,j;
	int gv=gr->totalGr;
	Jogadas *auxJ;
	
	
	Elem *newTab = (Elem *)malloc((*DIM)*sizeof(Elem));
	for (i=0;i<(*DIM);i++) {
		(newTab)[i] = (Elem )malloc(((*DIM))*sizeof(struct elemento));
	}
	
	for(i=0;i<(*DIM);i++){
		for(j=0;j<(*DIM);j++){
			newTab[i][j].letra=((*Tab)[i][j]).letra;
			newTab[i][j].cor='i';
		}
	}
	rsv(&newTab,DIM,gr);
	while(gr->totalGr!=gv){
			auxJ=(gr->jgs);
			gr->jgs=gr->jgs->next;
			free(auxJ);
			gr->totalGr--;
		}
		

return newTab;
}


/**
 * A função corrige irá anular movimentos até que a celula em causa tenha cor indefinida ou a cor do tabuleiro final, que é passada como argumento.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param cor cor a que deve corresponder a celula no tab final
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar se foi corrigida ou já não dá pra corrigir mais.
 */

int corrige(Elem **Tab,Gravados *gr,char cor,int x,int y){
	int end=0;
	
	while((gr->totalGr) && !end ){
		if((*Tab)[x][y].cor==cor || (*Tab)[x][y].cor=='i' ) end=1;
		else anc(Tab,gr);
	}
	if(!gr->totalGr) return 0;

return 1;
}

/**
 * A função 'crg' chama a função 'copy_board' que retorna a um tabuleiro igual mas resolvido, depois percorre
 * o tabuleiro original a procura de incompatibilidade, quando encontra uma célula com uma cor diferente da solução
 * retrocede até ao ponto antes da cor ter sido inferida a essa célula, faz o mesmo para todas as celulas até que 
 * todas as células pintadas estejam de acordo com a solução.
 * @param Tab tabuleiro.
 * @param DIM dimensão do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @returns Retorna um inteiro que irá indicar que o tabuleiro foi corrigido.
 */

int crg(Elem **Tab,int *DIM,Gravados *gr){

	int i,j;
	Elem *resl=NULL;
	resl=copy_board(Tab,DIM,gr);

	for(i=0;i<*DIM;i++){
		for(j=0;j<*DIM;j++){
			if((*Tab)[i][j].cor!='i'){
				if((*Tab)[i][j].cor!=resl[i][j].cor){
					if(!corrige(Tab,gr,resl[i][j].cor,i,j)) return 1;
				}
			}
		}
	}
		
return 0;
}
