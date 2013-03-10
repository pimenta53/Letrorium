/**
 * @file jogadas.c
 * @brief Jogadas possiveis de efectuar e gravar do jogo e 
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 1 Maio de 2010
 */
#include "tabuleiro.h"
#include "erro.h"
#include "jogadas.h"
#include "ajuda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A função jogada é responsável por alterar os dados do tabuleiro introduzidos pelo utilizador. Ela irá receber o novo dado e as poisções onde vai ficar o novo dado,
 * actualizando assim o tabuleiro com os novos dados
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param cor nova cor para um elemento do tabuleiro
 * @param x Corresponde á linha que vamos substituir no tabuleiro.
 * @param y Corresponde á coluna que vamos substituir no tabuleiro.
 * @param gr apontador para a estrutura de dados onde se guardas as jogadas e movimentos.
 * @returns Retorna um inteiro que verifica se a jogada foi ou não bem sucedida.
 */

int jogadaManual(char cor,int x,int y,int *DIM,Elem **Tab,Gravados *gr){

	if((*DIM)==0) return mensagem_de_erro(E_NO_BOARD);
	if((((x-1)<0) || ((x-1)>=(*DIM))) || (((y-1)<0) || ((y-1)>=(*DIM)))) {
		return mensagem_de_erro(E_COORDS);
		}
	if((*Tab)[y-1][x-1].cor==cor) return -1;
	
	if(cor=='i' || cor=='b' || cor=='p'){
		grava_jogada(y-1,x-1,(*Tab)[y-1][x-1].cor,gr);
		(*Tab)[y-1][x-1].cor=cor;}
	else {
		return mensagem_de_erro(E_INVARGS);}
return 0;
}

/**
 * A função jogada é responsável por alterar os dados do tabuleiro que são atribuidos automaticamente. Ela irá receber o novo dado e as poisções onde vai ficar o novo dado,
 * actualizando assim o tabuleiro com os novos dados
 * @param Tab Tabuleiro do jogo
 * @param cor nova cor para um elemento do tabuleiro
 * @param x Corresponde á linha que vamos substituir no tabuleiro.
 * @param y Corresponde á coluna que vamos substituir no tabuleiro.
 * @param gr apontador para a estrutura de dados onde se guardas as jogadas e movimentos.
 * @returns Retorna um inteiro que verifica se a jogada foi ou não bem sucedida.
 */
int jogada(char cor,int x,int y,Elem **Tab,Gravados *gr){
	

	if((*Tab)[y-1][x-1].cor==cor) return -1;
	
	if(cor=='i'){
		grava_jogada(y-1,x-1,(*Tab)[y-1][x-1].cor,gr);
		(*Tab)[y-1][x-1].cor=cor;
	}
	if(cor=='b'){
		if((*Tab)[y-1][x-1].cor!='p'){
			grava_jogada(y-1,x-1,(*Tab)[y-1][x-1].cor,gr);
			(*Tab)[y-1][x-1].cor=cor;
		}
		else return mensagem_de_erro(E_WRONG_SOLUTION);
	}
	if(cor=='p'){
		if((*Tab)[y-1][x-1].cor!='b'){
			grava_jogada(y-1,x-1,(*Tab)[y-1][x-1].cor,gr);
			(*Tab)[y-1][x-1].cor=cor;
		}
		else return mensagem_de_erro(E_WRONG_SOLUTION);
	}

return 0;
}
/**
 * Função responsavel por vereficar se existe um triplo a partir das cordenadas i e j na vertical.
 * Se existir atribui as cores correspondentes.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param i linha da celula.
 * @param j coluna da celula.
 * @param gr apontador para a estrutura de dados onde se guardas as jogadas e movimentos.
 */
int E_trp_col(Elem **Tab,int *DIM,int i,int j,Gravados *gr){
	
	char c1,c2,c3,c4,c5;
	int mudou1,mudou2,mudou3;
	mudou1=0;mudou2=0;mudou3=0;
	
	if((j>0)&&j+1<(*DIM)){
		c1=(*Tab)[i][j-1].letra;
		c2=(*Tab)[i][j].letra;
		c3=(*Tab)[i][j+1].letra;
		if(j+2<*DIM) c4=(*Tab)[i][j+2].letra;
		else c4=' ';
		if(j-1>0) c5=(*Tab)[i][j-2].letra;
		else c5=' ';
		if(c1!=c5 && c1==c2 && c2==c3 && c3!=c4){
			mudou1=jogada('p',j,i+1,Tab,gr);
			mudou2=jogada('b',j+1,i+1,Tab,gr);
			mudou3=jogada('p',j+2,i+1,Tab,gr);
		}
	}
	if(mudou1==-1 && mudou1==mudou2 && mudou2==mudou3) return 1;
	else return 0;
}

/**
 * Função responsavel por vereficar se existe um triplo a partir das cordenadas i e j na horinzontal.
 * Se existir atribui as cores correspondentes.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param i linha da celula.
 * @param j coluna da celula.
 * @param gr apontador para a estrutura de dados onde se guardas as jogadas e movimentos.
 */
int E_trp_row(Elem **Tab,int *DIM,int i,int j,Gravados *gr){
	
	char c1,c2,c3,c4,c5;
	int mudou1,mudou2,mudou3;
	mudou1=0;mudou2=0;mudou3=0;
	
	if((i>0)&&i+1<(*DIM)){
		c1=(*Tab)[i-1][j].letra;
		c2=(*Tab)[i][j].letra;
		c3=(*Tab)[i+1][j].letra;
		if(i+2<*DIM) c4=(*Tab)[i+2][j].letra;
		else c4=' ';
		if(i-1>0) c5=(*Tab)[i-2][j].letra;
		else c5=' ';
		if(c1!=c5 && c1==c2 && c2==c3 && c3!=c4){
			mudou1=jogada('p',j+1,i,Tab,gr);
			mudou2=jogada('b',j+1,i+1,Tab,gr);
			mudou3=jogada('p',j+1,i+2,Tab,gr);
		}
	}
	if(mudou1==-1 && mudou1==mudou2 && mudou2==mudou3) return 1;
	else return 0;
}


/**
 * Função que procura triplos no tabuleiro(tres letras iguais na mesma linha/coluna).
 * Para tal vai se percorrer todas as posiçoes do tabuleiro, ver caso exitam quais letras de cima e de baixo, para verificar se existe triplo na vertical, e a daesquerda e a da direita para a horizontal.
 * É também tido em contam o caso de exitirem quadroplos não serem considerados triplos.
 * Confirmando se a presença de um triplo atriubui se as cores correctas caso nenhuma das celulas não tenha um cor contraria, se não envia uma mensagem de erro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @param gr apontador para a estrutura de dados onde se guarda as jogadas e moviemntos efectuados.
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */
int trp(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr){
	
	int i,j,sair1,sair2;
	sair1=0;sair2=0;
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	if((*DIM)<3) return mensagem_de_erro(E_WRONG_SOLUTION);
	 
	for(i=0;i<(*DIM);i++){	
		for(j=0;j<(*DIM);j++){	
			sair1=E_trp_row(Tab,DIM,i,j,gr);
			sair2=E_trp_col(Tab,DIM,i,j,gr);
		}
	}
	
	if(!sair1 && !sair2) control(Tab,DIM,flagAB,flagAP,gr);
	
return 0;
}

/**
 * Função que procura sandes no tabuleiro(tres letras onde apenas a do meio é diferente na mesma linha/coluna).
 * Para tal vai se percorrer todas as posiçoes do tabuleiro, ver caso exitam quais letras de cima e de baixo, para verificar se existe triplo na vertical, e a daesquerda e a da direita para a horizontal.
 * Confirmando se a presença de uma sandes de letras, atriubui se as cores correctas caso nenhuma das celulas não tenha um cor contraria, se não envia uma mensagem de erro.
 * @param Tab Tabuleiro do jogo
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @param gr apontador para a estrutura de dados onde se guarda as jogadas e moviemntos efectuados.
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */			
int snd(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr){
	
	int i,j,sair1,sair2;
	sair1=0;sair2=0;
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	if(*DIM<3) return mensagem_de_erro(E_WRONG_SOLUTION);
	 
	for(i=0;i<(*DIM);i++){	
		for(j=0;j<(*DIM);j++){	
			if((i-1>=0)&&(i+1<(*DIM))){
				if((*Tab)[i-1][j].letra==(*Tab)[i+1][j].letra && (*Tab)[i][j].letra!=(*Tab)[i+1][j].letra){
					sair1=jogada('b',j+1,i+1,Tab,gr);
					if(sair1>0) return 1;
				}
			}
			if((j-1>=0)&&j+1<(*DIM)){
				if((*Tab)[i][j-1].letra==(*Tab)[i][j+1].letra && (*Tab)[i][j].letra!=(*Tab)[i][j+1].letra){
					sair2=jogada('b',j+1,i+1,Tab,gr);
					if(sair2>0) return 1;
				}
			}
		}
	}
	
	if(!sair1 && !sair2) control(Tab,DIM,flagAB,flagAP,gr);
	
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
	char c1,c2;
	
	if(strcmp(local,"linha")==0){
		for(j=0;j<(*DIM)-1;j++){/* para as linhas*/
			c1=(*Tab)[pos][j].letra;
			c2=(*Tab)[pos][j+1].letra;
			if(c1==c2 && c1==letra) return 1;
		}
	}
	if(strcmp(local,"coluna")==0){
		for(j=0;j<(*DIM)-1;j++){/* para as colunas*/
			c1=(*Tab)[j][pos].letra;
			c2=(*Tab)[j+1][pos].letra;
			if(c1==c2 &&  c1==letra) return 1;
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
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @param gr apontador para a estrutura de dados onde se guarda as jogadas e moviemntos efectuados.
 * @param DIM dimensão do tabuleiro
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */	
int pis(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr){
	
	int i,j,sair1,sair2;
	char c1,c2,c3,c4,c5;
	sair1=0;sair2=0;
	
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );
	
	for(i=0;i<(*DIM);i++){
		for(j=0;j<(*DIM);j++){
			if(i-1>=0) c1=(*Tab)[i-1][j].letra;else c1=' ';/* para verificar se é mesmo uma letra isolada*/
			if(i+1<*DIM) c3=(*Tab)[i+1][j].letra;else c3=' ';/* para verificar se é mesmo uma letra isolada*/
			c2=(*Tab)[i][j].letra;
			if(j-1>=0) c4=(*Tab)[i][j-1].letra;else c4=' ';/* para verificar se é mesmo uma letra isolada*/
			if(j+1<*DIM) c5=(*Tab)[i][j+1].letra;else c5=' ';/* para verificar se é mesmo uma letra isolada*/
			if((c4!=c2 && c2!=c5) && E_Par(Tab,i,c2,DIM,"linha")){
				sair1=jogada('p',j+1,i+1,Tab,gr);
				if(sair1>0) return 1;
			}
			if((c1!=c2 && c2!=c3) && E_Par(Tab,j,c2,DIM,"coluna")){
				sair2=jogada('p',j+1,i+1,Tab,gr);
				if(sair2>0) return 1;
			}
		}
	}
	
	if(!sair1 && !sair2) control(Tab,DIM,flagAB,flagAP,gr);
		
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
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @param gr apontador para a estrutura de dados onde se guarda as jogadas e moviemntos efectuados.
 * @return Inteiro que em caso de correr tudo bem retorna 0, caso exista um erro,é exibido atraves da função mensagem de erro.
 */	
int pds (Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr){

	int i,j,mudou1,mudou2,sair1,sair2;
	mudou1=0;mudou2=0;sair1=0;sair2=0;

	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD );	
	for(i=0;i<(*DIM)-1;i++){
		for(j=0;j<(*DIM)-1;j++){
			if(E_Par_des(Tab,(*Tab)[i][j].letra,(*Tab)[i+1][j+1].letra,DIM,i,j,i+1,j+1)){ /*i e j para vereficar se são diferentes das posiçoes passadas*/
				mudou1=jogada('b',j+2,i+1,Tab,gr);
				if(mudou1>0) return 1;
				mudou2=jogada('b',j+1,i+2,Tab,gr);
				if(mudou1==-1 && mudou2==mudou1) sair1=1;
				if(mudou2>0) return 1;
			}
			if(E_Par_des(Tab,(*Tab)[i+1][j].letra,(*Tab)[i][j+1].letra,DIM,i+1,j,i,j+1)){ /*i e j para vereficar se são diferentes das posiçoes passadas*/
				mudou1=jogada('b',j+1,i+1,Tab,gr);
				if(mudou1>0) return 1;
				mudou2=jogada('b',j+2,i+2,Tab,gr);
				if(mudou1>0) return 1;
				if(mudou1==-1 && mudou2==mudou1) sair2=1;
			}
		}	
	}
	
	control(Tab,DIM,flagAB,flagAP,gr);
	
return 0;
}
			
/**
 * Função que irá guardar a cor a linha e a coluna de um tabuleiro que correspondente á celula que vai ser substituida.
 * Esta função será chamada sempre que se mude uma cor.
 * @param row linha da celula que se vai guardar.
 * @param col coluna da celula que se vai guardar.
 * @param color Cor da celula que vai ser substituida
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
*/
int grava_jogada(int row,int col,char color,Gravados *gr){

	Jogadas *new;
	new=malloc(sizeof(Jogadas));
	gr->totalGr=((gr->totalGr)+1);
	(new)->col=col;
	(new)->row=row;
	(new)->color=color;
	(new)->next=gr->jgs;
	gr->jgs=new;
	
return 0;
}


/**
 * Função responsavel por anular uma cor guardada quando é chamada.
 * A função vai anular a ultima cor guardada.
 * @param Tab tabuleiro onde vão ser efectuadas as mudanças de cor até chegar ao estado desejado.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int anc(Elem **Tab,Gravados *gr){
	
	
	Jogadas *aux;
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD);
	if(!gr) return mensagem_de_erro(E_NO_MOVES);
	if(!gr->totalGr) return mensagem_de_erro(E_NO_MOVES);

	aux=(gr)->jgs;
	if((gr)->jgs){
		(*Tab)[gr->jgs->row][gr->jgs->col].cor=((gr)->jgs)->color;
		((gr)->jgs)=(gr)->jgs->next;
		free(aux);
		gr->totalGr=((gr->totalGr)-1);
	}
	else return mensagem_de_erro(E_NO_MOVES);
return 0;
}

/**
 * Função resonsavel tal como a guarda movimentos, de guardar na estrutura de dados de IT's o numero de cores que foram guardadas até ao momento da sua chamada.
 * Para postriormente poder se recoperar o estado do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int it(Gravados *gr){

	IT *new;
	new=malloc(sizeof(IT));
	new->next=gr->its;
	new->pos=(gr->totalGr)+1;
	gr->its=new;
		
return 0;
}	


/**Função responsavel por anular cores até chegar ao estado de tabuleiro marcado pela função it.
 * Desta forma será possivel retornar o estado do tabuleiro tal como foi marcado na função it.
 * @param Tab tabuleiro onde vão ser efectuadas as mudanças de cor até chegar ao estado desejado.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int rb(Elem **Tab,Gravados *gr){
	
	IT *aux;
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD);
	if(!gr) return mensagem_de_erro(E_NO_BOARD);  
	if(!gr->its) return mensagem_de_erro(E_NO_MOVES);

		aux=gr->its;
		while((gr->its->pos)<=((gr->totalGr))){
			anc(Tab,gr);
		}
	gr->its=gr->its->next;
	free(aux);

return 0;
}	

/**
 * Função reponsavel por inicializar e alocar espaço para as estruturas de dados responsaveis por guardar informação relativa a movimentos e jogadas efectuadas.
 * Aloca espaço para It, para moviemntos e para jogadas
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */ 
int inicia_GR(Gravados *gr){

	gr->totalGr=0;
	gr->its=malloc(sizeof(IT));
	gr->its->next=NULL;
	gr->jgs=malloc(sizeof(Jogadas));
	gr->jgs->next=NULL;
	gr->mvs=malloc(sizeof(Movimentos));
	gr->mvs->next=NULL;

return 0;
}

/**
 * Função que irá guardar na estrutura de dados de movimentos o numero de cores que foram guardadas até ao momento da sua chamada.
 * Para postriormente poder se recoperar o estado do tabuleiro.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int grava_movimento(Gravados *gr){
	
	Movimentos *new;
	new=malloc(sizeof(Movimentos));
	new->next=gr->mvs;
	new->pos=gr->totalGr;
	gr->mvs=new;
	
return 0;
}
/**
 * Função responsavel por anular um movimento quando é chamada.
 * A função vai anular cores até chegar á ultima cor gravada quando foi guardado o movimento.
 * @param Tab tabuleiro onde vão ser efectuadas as mudanças de cor até chegar ao estado desejado.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int anm(Elem **Tab,Gravados *gr){
	
	Movimentos *aux;
	if(!(*Tab)) return mensagem_de_erro(E_NO_BOARD);
	if(!gr) return mensagem_de_erro(E_NO_BOARD);  
	if(!gr->mvs) return mensagem_de_erro(E_NO_MOVES);

	if(gr->totalGr){
		aux=gr->mvs;
		while((gr->mvs->pos)<(gr->totalGr)){
			anc(Tab,gr);
		}
	gr->mvs=gr->mvs->next;
	free(aux);
	}
	else return mensagem_de_erro(E_NO_MOVES);
		
return 0;
}	

/**
 * Função responsavel por limpar da memoria todos os movimentos guardados em memoria.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */	
int freeMvs(Gravados *gr){
	
	Movimentos *auxM;
	if(gr->mvs){
		while(gr->mvs->next!=NULL){
			auxM=(gr->mvs);
			gr->mvs=gr->mvs->next;
			free(auxM);
		}
		free(gr->mvs);
		gr->mvs=NULL;
	}
return 0;
}

/**
 * Função responsavel por limpar da memoria todas as jogadas guardadas em memoria.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int freeJgs(Gravados *gr){
	
	Jogadas *auxJ;
	
	if(gr->jgs){
		while(gr->jgs->next){
			auxJ=(gr->jgs);
			gr->jgs=gr->jgs->next;
			free(auxJ);
		}
		free(gr->jgs);
		gr->jgs=NULL;
	}
return 0;
}


/**
 * Função responsavel por limpar da memoria todos os estados de tabuleiros marcados com o comando it.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int freeIts(Gravados *gr){
	
	IT *auxI;
	
	if(gr->its){
		while(gr->its->next!=NULL){
			auxI=(gr->its);
			gr->its=gr->its->next;
			free(auxI);
		}
		free(gr->its);
		gr->its=NULL;
	}
return 0;
}
/**
 * Função responsavel por limpar da memoria todos os dados guardados,em relação ás cores e mvimentos guardados.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 */
int free_jogadasGR(Gravados *gr){
	
	if(!gr) return 1;

	freeIts(gr);
	freeMvs(gr);
	freeJgs(gr);
	gr->totalGr=0;
	
return 0;
}
