/**
 * @file tabuleiro.c
 * @brief Tabuleiro do jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 5 Março de 2010
 */
#include"tabuleiro.h"
#include<stdlib.h>
#include<stdio.h>
#include <sys/dir.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * A unçao dimencao é responsável por carregar a dimenção do tabuleiro que estamos a abrir, para a variavel global DIM. Para isso ela usa o fscanf da biblioteca stdio.
 * @param fp Recebe o ficheiro do qual irá verificar se existe o valor da dim e passa-lo para a variável Global DIM.
 * @returns retorna um valor lógico 1 ou 0 que confirma se conseguiu ou não ler o valor correspondente á dimenção.  
 */
int dimencao(FILE *fp) {

	int i;
	i = fscanf(fp,"%d",&DIM);
	if (i==0) {
		fprintf(stderr,"Não conseguiu ler a dimenção.\n");
		return i;
	}
return i;
}


/**
 * A função ficheiroValido recebe o ficheiro do qual queremos importar o tabuleiro e verifica se este é válido para o nosso jogo.
 * Para ser válido irá vereficar se tem o número de elementos correspondentes a dimenção, se são elementos do tipo predefenido do tabuleiro(ex:"[A]")
 * @param fp Recebe o ficheiro que está aberto na função criarTabuleiro
 * @returns Retorna um inteiro que irá confirmar se o ficheiro é válido ou não.
 */
int ficheiroValido(FILE *fp){
	char c1,c2,c3;
	int n_linha=0, n_coluna=0, num=0;
	
	while ((c1=getc(fp))!='\n'){
		if ((isdigit(c1)) && (num==0)) {
			while (isdigit(c1)) {
				c1 = getc(fp);
			}
		num=1;
		}
		if ((c1!=' ') && (c1!='\r') && (c1!='\n')) return 0;
		if (c1=='\n') break;
		}
	if (num==0) return 0;

	while ((c1=getc(fp))!=EOF) {
		if(c1=='\r') c1=getc(fp);
		if(c1=='\n') {
			n_linha++;
			if ((n_coluna)!=DIM) return 0;
			n_coluna=0;
			}
		else{
			c2=getc(fp);
			c3=getc(fp);
			if ((c1==EOF) || (c2==EOF) || (c3==EOF)) break;
			if (!(isalpha(c2))) return 0;
			switch (c1) {
				case (' '):
					if (c3!=' ') return 0;
					break;
				case ('('):
					if (c3!=')') return 0;
					break;
				case ('['):
					if (c3!=']') return 0;
					break;
				default:
					return 0;
				}
			n_coluna++;
		}
	}
	if ((n_linha)!=DIM) return 0;
	return 1;
}

/**
 * A função freeTab irá apagar da memória do tabuleiro antigo caso estejamos a abrir um novo tabuleiro.
 * @remarks Esta função apenas é usada se existir um tabuleiro carregado e queremos carregar outro.
 */
void freeTab(){

	int i;
		
	for (i=0;i<DIM;i++) {
		free(Tab[i]);	
		}
	free(Tab);
	Tab=NULL;
}
/**
 * A função criarTabuleiro recebe o nome do ficheiro que queremos abrir e irá tentar abir este.
 * Depois irá chamar a funçao freeTab caso exista já um tabuleiro carregado e em seguida chama a função ficheiroValido para ver verificar se o mesmo é válido.
 * Após todas verificações a função cria espaço para o tabuleiro na memória e carrega este para lá, ficando guardado no apontador Tab.
 * Os valores lidos do ficheiro irão ser associados por duas características, a letra e a cor, eta ultima será "i" correspondente a indefinida caso a letra esteja rodeada por dois espaços brancos, preta caso esteja rodeada por dois parênteses rectos e branca caso esteja rodeada por dois parênteses curvos.
 * @param nome Recebe uma string com o nome do ficheiro que vai abrir.
 * @returns Retorna um inteiro que verifica se conseguiu ou não criar o Tabuleiro.
 */
int criarTabuleiro(char *nome){

	int i,j,k;
	int linha_1=0;
	char c1;
	
	

	FILE *fp = fopen(nome, "r");
	
	
	if(fp == NULL){
		fprintf(stderr, "Erro ao abrir ficheiro '%s', tente outro nome.\n", nome);
		return(0);// forma de não sair do jogo caso este não exista
	}

	if (Tab) freeTab();
	dimencao(fp);
	fseek(fp,0,SEEK_SET);
	
	if (!ficheiroValido(fp)) {
		printf("Ficheiro inválido ou danificado.\n");
		return 0;
	}
	fseek(fp,0,SEEK_SET);
	
/*Alocar espaco para a matriz*/
	Tab = (Elem *)malloc((DIM)*sizeof(Elem));
	for (i=0;i<DIM;i++) {
		Tab[i] = (Elem )malloc((DIM)*sizeof(struct elemento));
	}


	while(linha_1==0){ // para eliminar a primeira linha
		c1=getc(fp);
		if(c1=='\n') linha_1=1;
	}
	for(i=0;i<DIM;i++){
		for(j=0;j<DIM;j++){
			for(k=0;k<3;k++){
				c1=getc(fp);
				if(c1=='\n') k=-1;
				else{ 
					if(k==0){ // para a cor
						switch (c1) {
							case (' '): 
							Tab[i][j].cor='i';			
							break;
							case ('('): 
							Tab[i][j].cor='b';			
							break;
							case ('['): 
							Tab[i][j].cor='p';			
							break;
						}		
					}					
					if(k==1) Tab[i][j].letra=(toupper(c1));// para a letra
				}
			}
		}
	}	
	fclose(fp);
return 0;
}
/**
 * A função ajuda irá imprimir no ecrã o ficheiro com as instruções de ajuda
 * @todo por a função a carregar o ficheiro ajuda e a imprimir, para a proxima etapa
 */
int ajuda(){
	
	printf("Imprimir ficheiro de ajuda.\n");// ler ficheiro ajuda
return 0;
}

/**
 * A função jogada é responsável por alterar os dados do tabuleiro. Ela irá receber o novo dado e as poisções onde vai ficar o novo dado,
 * actualizando assim o tabuleiro com os novos dados
 * @param cor nova cor para um elemento do tabuleiro
 * @param x Corresponde á linha que vamos substituir no tabuleiro.
 * @param y Corresponde á coluna que vamos substituir no tabuleiro.
 * @returns Retorna um inteiro que verifica se a jogada foi ou não bem sucedida.
 */
int jogada(char cor,int x,int y){
	
	if((((x-1)<0) || ((x-1)>=DIM)) || (((y-1)<0) || ((y-1)>=DIM))) {
		printf("\nJogou fora dos limites do tabuleiro ou ainda não abriu o jogo.\n\n");
		return 0;
		}
	if(cor=='i' || cor=='b' || cor=='p'){
		Tab[y-1][x-1].cor=cor;}
	else {
		printf("Escolheu a cor errada.\n");return 0;}
return 1;
}
	

/**
 * A função printTAbuleiro é responsável por imprimir no ecrã o nosso tabuleiro.
 */
void printTabuleiro(){
	
	int i,j;
	int linha=1;
	for(i=0;i<DIM;i++){				
		printf("%d ",linha);
		for(j=0;j<DIM;j++){
			switch (Tab[i][j].cor) {
				case ('i'): 
				printf("\e[44;31m %c \e[0m" ,Tab[i][j].letra);		
				break;
				case ('b'): 
				printf("\e[47;31m %c \e[0m",Tab[i][j].letra);		
				break;
				case ('p'): 
				printf("\e[40;31m %c \e[0m",Tab[i][j].letra);				
				break;
			}	
		}
		printf("\n");		
		linha++;	
	}
	printf("  ");
	for(i=1;i<=DIM;i++){
		printf(" %d ",i);}	
}

/**A função gravaJogo é responsável por gravar o nosso tabuleiro num ficheiro cujo o nome é dado como argumento e que está no formato ".ltr".
 * O tabuleiro será imprimido para o ficheiro seguindo as regras de representação deste, para que possa ser lido de novo e seja considerado válido.
 * @param nome Recebe uma string que representa o nome que vai dar ao ficheiro que vai guardar
 */
void gravaJogo (char *nome) {
	
	int i,j;
	
	FILE *f = fopen(nome, "w+");

	if(f == NULL){
		fprintf(stderr, "Erro ao criar o ficheiro '%s'.\n", nome);
		exit(0);
	}
	else {
		fprintf( f,"%d\n",DIM);			
		for(i=0;i<DIM;i++){	
			for(j=0;j<DIM;j++){
				switch (Tab[i][j].cor) {
					case ('i'): 
					fprintf(f," ");			
					break;
					case ('b'): 
					fprintf(f,"(");		
					break;
					case ('p'): 
					fprintf(f,"[");			
					break;
				}				
				fprintf(f,"%c",Tab[i][j].letra);
				switch (Tab[i][j].cor) {
					case ('i'): 
					fprintf(f," ");			
					break;
					case ('b'): 
					fprintf(f,")");		
					break;
					case ('p'): 
					fprintf(f,"]");			
					break;
				}	
			}
		fprintf(f,"\n");
		}
	}
	fclose (f);
}


/**A função executajogada recebe os argumentos da linha de comandos e a cor que vai passar para a jogada.
 * Vai verificar se tem os argumetos certos, e se tal vou verdade, chama a função jogada, para que esta se possa realizar.
 * @param args Recebe ums string com os argumentos do comando do utilizador. 
 * @param cor Corresponde ao próprio comado que irá ser utilizado como a cor que se pretende mudar.
 * @returns Retorna um inteiro que verifica se foi ou não bem sucedida a função.
 */
int executaJogada(char *args,char *cor) {
  char buf[1024];
  int x, y;

  int nargs = sscanf(args, "%d %d %[^\n]", &x, &y, buf);

  if(nargs != 2) {
      fprintf(stderr, "Comando inválido, está a passar um número de argumentos invalido ou de forma inválida, para mais informações consulte a ajuda.\n");
      return -1;
  }

  jogada(*cor,x,y);

  return 0;
}

/**A função executaCriaJog recebe os argumentos da linha de comando, vai verificar se tem os argumentos, certos se tal ocorre, executa criarJogo com o nome do argumento no formato ".ltr".
 * @param args Recebe uma string com os argumentos associados ao comando em questão ("cr").
 * @returns torna um inteiro que verifica se foi ou não bem sucedida a função.
 */
int executaCriaJogo(char *args) {
	char buf[1024];
	char nome[55];

	if(strlen(args)>50){
		fprintf(stderr,"Nome do ficheiro que pretende abrir é demasiado grande, apenas pode carregar ficheiros com nome até 50 caracteres.\n");
		return 0;
	}

  int nargs = sscanf(args, "%s %[^\n]", nome, buf);

  if(nargs != 1) {
      fprintf(stderr, "Comando inválido, está a passar um número de argumentos inválido ou de forma inválida, para mais informaçoes consulte a ajuda.\n");
      return -1;
  }
	
	strcat(nome,".ltr");
	criarTabuleiro(nome);

  return 0;
}

/**A função executaGravaJogo recebe os argumentos da linha de comando e vai verificar se tem os argumetos certos, se tal for verdade, executa gravaJogo com o nome do argumento no formato ".ltr".
 * @param args Recebe uma string com os argumentos associados ao comando em questão("gr").
 * @returns torna um inteiro que verifica se foi ou não bem sucedida a função.
 */
int executaGravaJogo(char *args) {
	char buf[1024];
	char nome[55];

	if(strlen(args)>50){
		fprintf(stderr,"Nome que pretende gravar é demasiado grande, o nome do ficheiro apenas pode conter até 50 caracteres.\n");
		return 0;
	}
	
  int nargs = sscanf(args, "%s %[^\n]", nome, buf);


  if(nargs != 1) {
      fprintf(stderr, "Comando inválido, está a passar um número errado de argumentos, consulte a ajuda para mais informações.\n");
      return -1;
  }
	
	if(Tab){	
		strcat(nome,".ltr");
		gravaJogo(nome);
	}
	else printf("Ainda não abriu nenhum jogo para poder gravar.\n");
  return 0;
}


/**
 * A função executa_comando é uma das funções mais importantes pois é ela que vai reagir aos comandos dados pelo utilizador.
 * A função irá receber a linha de comando separa la em dois, no comando e nos argumentos do comando, e passa los para as funções associadas aos comandos.
 * @param linha Recebe uma string que corresponde á linha lida da shell.
 * @returns torna um inteiro que verifica se foi ou não bem sucedida a função. 
 */
int executa_comando(char *linha) {
  char cmd[1025];
  char args[1025];

	sscanf(linha, "%s %[^\n]", cmd, args);

	if(strcmp(cmd, "b") == 0 || strcmp(cmd, "p") == 0 || strcmp(cmd, "i") == 0)
		return executaJogada(args,cmd);
	if(strcmp(cmd, "cr") == 0)
		return executaCriaJogo(args);	
	if(strcmp(cmd,"gr")==0)
		return executaGravaJogo(args);  
	if(strcmp(cmd,"?")==0)
		return ajuda();	
	if(strcmp(cmd,"q")==0)
		exit(1);// perguntar ao prof como é a melhor forma para exit

	fprintf(stderr, "Comando inválido, para saber quais os comados suportados digite:  ? \n");
	return -1;
}	
