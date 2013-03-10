/**
 * @file comandos.c
 * @brief Comandos do jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 1 Abril de 2010
 */
#include "tabuleiro.h"
#include "erro.h"
#include "jogadas.h"
#include "ajuda.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "estado_tabuleiro.h"


/**A função executajogada recebe os argumentos da linha de comandos e a cor que vai passar para a jogada.
 * Vai verificar se tem os argumetos certos, e se tal vou verdade, chama a função jogada, para que esta se possa realizar.
 * @param args Recebe ums string com os argumentos do comando do utilizador. 
 * @param cor Corresponde ao próprio comado que irá ser utilizado como a cor que se pretende mudar.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @returns Retorna um inteiro que verifica se foi ou não bem sucedida a função.
 */
int executaJogada(char *args,char *cor,int *DIM,Elem **Tab,int *flagAP,int *flagAB,Gravados *gr) {
  char buf[1024];
  int x, y,sair;
	char teste1[1024],teste2[1024];
	
	int nargs = sscanf(args, "%s %s %[^\n]", teste1,teste2, buf);
	if(!isdigit(teste1[0]) || !isdigit(teste2[0])) {
     return mensagem_de_erro(E_INVARGS);
  }
	
	nargs = sscanf(args, "%d %d %[^\n]", &x, &y, buf);

  if(nargs != 2) {
     return mensagem_de_erro(E_ARGS);
  }
	grava_movimento(gr);
	sair=jogadaManual(*cor,x,y,DIM,Tab,gr);
	

		/*if(cor[0]=='p' && *flagAP) ap_function(y-1,x-1,Tab,DIM,flagAP,flagAB);
		if(cor[0]=='b' && *flagAB) ab_function(y-1,x-1,Tab,DIM,flagAP,flagAB);
	*/
	if(!sair) control(Tab,DIM,flagAB,flagAP,gr,1);

return 0;
}

/**A função executaCriaJog recebe os argumentos da linha de comando, vai verificar se tem os argumentos, certos se tal ocorre, executa criarJogo com o nome do argumento no formato ".ltr".
 * @param args Recebe uma string com os argumentos associados ao comando em questão ("cr").
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @returns torna um inteiro que verifica se foi ou não bem sucedida a função.
 */
int executaCriaJogo(char *args,int *DIM,Elem **Tab,Gravados *gr,int *flagAP,int *flagAB) {
	char buf[1024];
	char nome[256];

	int nargs = sscanf(args, "%s %[^\n]", nome, buf);


  if(nargs != 1) {
      return mensagem_de_erro(E_INVARGS);
  }
	
	strcat(nome,".ltr");
	if(criarTabuleiro(nome,DIM,Tab)==0){
		(*flagAP)=0;
		(*flagAB)=0;
		 free_jogadasGR(gr);/* limpar tudo o que foi gravado */
	 }

return 0;
}

/**A função executaGravaJogo recebe os argumentos da linha de comando e vai verificar se tem os argumetos certos, se tal for verdade, executa gravaJogo com o nome do argumento no formato ".ltr".
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro 
 * @param args Recebe uma string com os argumentos associados ao comando em questão("gr").
 * @returns torna um inteiro que verifica se foi ou não bem sucedida a função.
 */
int executaGravaJogo(char *args,int *DIM,Elem **Tab) {
	char buf[1024];
	char nome[256];
	
  int nargs = sscanf(args, "%s %[^\n]", nome, buf);


  if(nargs != 1) {
      return mensagem_de_erro(E_ARGS);
  }
	
	if(Tab){	
		strcat(nome,".ltr");
		gravaJogo(nome,DIM,Tab);
	}
	else return mensagem_de_erro(E_NO_BOARD);
return 0;
}


/**
 * A função executa_comando é uma das funções mais importantes pois é ela que vai reagir aos comandos dados pelo utilizador.
 * A função irá receber a linha de comando separa la em dois, no comando e nos argumentos do comando, e passa los para as funções associadas aos comandos.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param linha Recebe uma string que corresponde á linha lida da shell.
 * @param gr apontador para a estrutura de dados onde se encontram guardados todos os movimentos e jogadas.
 * @param flagAP flag para controlo do automatico preto.
 * @param flagAB flag para controlo do automatico branco.
 * @param gr apontador para a estrutura de dados onde se guarda as jogadas e moviemntos efectuados.
 * @returns torna um inteiro que verifica se foi ou não bem sucedida a função. 
 */
int executa_comando(char *linha,int *DIM,Elem **Tab,int *flagAP,int *flagAB,Gravados *gr) {
	char cmd[1025],args[1025];
	int nargs;
	args[0]='\0';
	
	nargs=sscanf(linha, "%s %[^\n]", cmd, args);

	if(strcmp(cmd, "ap")==0 && nargs==1) {
		if((*flagAP)==0) (*flagAP)=1;else (*flagAP)=0;
		return 0;}
	if(strcmp(cmd, "ab") == 0 && nargs==1) {
		if((*flagAB)==0) (*flagAB)=1;else (*flagAB)=0;
		return 0;}
	if((strcmp(cmd, "b") == 0 || strcmp(cmd, "p") == 0 || strcmp(cmd, "i") == 0))return executaJogada(args,cmd,DIM,Tab,flagAP,flagAB,gr);
	if(strcmp(cmd, "cr") == 0 )return executaCriaJogo(args,DIM,Tab,gr,flagAP,flagAB);	
	if(strcmp(cmd,"gr")==0 )return executaGravaJogo(args,DIM,Tab);  
	if(strcmp(cmd,"?")==0 && nargs==1)return ajuda();	
	if(strcmp(cmd,"trp")==0 && nargs==1){
		grava_movimento(gr);
		return trp(Tab,DIM,flagAP,flagAB,gr);}
	if(strcmp(cmd,"snd")==0 && nargs==1){
		grava_movimento(gr);
		return snd(Tab,DIM,flagAP,flagAB,gr);}
	if(strcmp(cmd,"pis")==0 && nargs==1){
		grava_movimento(gr);
		return pis(Tab,DIM,flagAP,flagAB,gr);}
	if(strcmp(cmd,"pds")==0 && nargs==1){
		grava_movimento(gr);
		return pds(Tab,DIM,flagAP,flagAB,gr);}
	if(strcmp(cmd,"vb")==0 && nargs==1)return vb(Tab,DIM,1);
	if(strcmp(cmd,"vp")==0 && nargs==1)return vp(Tab,DIM,1);
	if(strcmp(cmd,"vl")==0 && nargs==1)return vl(Tab,DIM,1);
	if(strcmp(cmd,"st")==0 && nargs==1)return st(Tab,DIM,1);
	if(strcmp(cmd,"rsv")==0 && nargs==1){
		grava_movimento(gr);
		return rsv(Tab,DIM,gr);
	}
	if(strcmp(cmd,"anc")==0 && nargs==1)return anc(Tab,gr);
	if(strcmp(cmd,"anm")==0 && nargs==1)return anm(Tab,gr);
	if(strcmp(cmd,"it")==0 && nargs==1)	return it(gr);
	if(strcmp(cmd,"rb")==0 && nargs==1)	return rb(Tab,gr);
	if((strcmp(cmd, "tc") == 0))return executa_tc(args,DIM,Tab,flagAP,flagAB,gr);
	if(strcmp(cmd,"vc")==0 && nargs==1)	return vc (Tab,DIM,gr);
	if(strcmp(cmd,"imp")==0 && nargs==1) return imp (Tab,DIM,gr,flagAP,flagAB);
	if(strcmp(cmd,"crg")==0 && nargs==1) return  crg(Tab,DIM,gr);
	if(strcmp(cmd,"q")==0){
		free_jogadasGR(gr);
		freeTab(DIM,Tab);
		exit(0);
	}
	return mensagem_de_erro(E_COMMAND);
}	
