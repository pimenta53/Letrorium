/**
 * @file tabuleiro.c
 * @brief Tabuleiro do jogo
 * @author André Pimenta, João Gomes, Nelson Carvalho
 * @date 5 Março de 2010
 */
#include "tabuleiro.h"
#include "erro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * A unçao dimensão é responsável por carregar a dimensão do tabuleiro que estamos a abrir, para a variável DIM. Para isso ela usa o fscanf da biblioteca stdio.
 * @param DIM dimensão do tabuleiro
 * @param fp Recebe o ficheiro do qual irá verificar se existe o valor da dim e passa-lo para a variável Global DIM.
 * @returns retorna um valor lógico 1 ou 0 que confirma se conseguiu ou não ler o valor correspondente á dimenção.  
 */
int dimencao(FILE *fp,int *DIM) {

	int i;
	i = fscanf(fp,"%d",DIM);

return i;
}


/**
 * A função ficheiroValido recebe o ficheiro do qual queremos importar o tabuleiro e verifica se este é válido para o nosso jogo.
 * Para ser válido irá vereficar se tem o número de elementos correspondentes a dimenção, se são elementos do tipo predefenido do tabuleiro(ex:"[A]")
 * @param DIM dimensão do tabuleiro
 * @param fp Recebe o ficheiro que está aberto na função criarTabuleiro
 * @returns Retorna um inteiro que irá confirmar se o ficheiro é válido ou não.
 */
int ficheiroValido(FILE *fp,int *DIM){
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
		if ((n_linha)==(*DIM)) c1=getc(fp);
		if (c1==EOF) break;
		if(c1=='\r') c1=getc(fp);
		if(c1=='\n') {
			n_linha++;
			if ((n_coluna)!=(*DIM)) return 0;
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
	if ((n_linha)!=(*DIM)) return 0;
	return 1;
}

/**
 * A função freeTab irá apagar da memória do tabuleiro antigo caso estejamos a abrir um novo tabuleiro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro 
 * @remarks Esta função apenas é usada se existir um tabuleiro carregado e queremos carregar outro.
 */
void freeTab(int *DIM,Elem **Tab){

	int i;
	
	if(!(*Tab)) return ;	
	for (i=0;i<(*DIM);i++) {
		free((*Tab)[i]);	
		}
	free(*Tab);
	*Tab=NULL;
}
/**
 * A função criarTabuleiro recebe o nome do ficheiro que queremos abrir e irá tentar abir este.
 * Depois irá chamar a funçao freeTab caso exista já um tabuleiro carregado e em seguida chama a função ficheiroValido para ver verificar se o mesmo é válido.
 * Após todas verificações a função cria espaço para o tabuleiro na memória e carrega este para lá, ficando guardado no apontador Tab.
 * Os valores lidos do ficheiro irão ser associados por duas características, a letra e a cor, eta ultima será "i" correspondente a indefinida caso a letra esteja rodeada por dois espaços brancos, preta caso esteja rodeada por dois parênteses rectos e branca caso esteja rodeada por dois parênteses curvos.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param fp ficheiro a ser lido
 * @returns Retorna um inteiro que verifica se conseguiu ou não criar o Tabuleiro.
 */
int lerficheiro(int *DIM,Elem **Tab,FILE *fp){
	int i,j,k,linha_1;
	char c1;
	linha_1=0;
	
	while(linha_1==0){ /* para eliminar a primeira linha*/
		c1=getc(fp);
		if(c1=='\n') linha_1=1;
	}
	for(i=0;i<(*DIM);i++){
		for(j=0;j<(*DIM);j++){
			for(k=0;k<3;k++){
				c1=getc(fp);
				if(c1=='\n') k=-1;
				else{ 
					if(k==0){ /* para a cor */
						switch (c1) {
							case (' '): 
							(*Tab)[i][j].cor='i';			
							break;
							case ('('): 
							(*Tab)[i][j].cor='b';			
							break;
							case ('['): 
							(*Tab)[i][j].cor='p';			
							break;
						}		
					}					
					if(k==1) (*Tab)[i][j].letra=(toupper(c1));/* para a letra */
				}
			}
		}
	}	
	
	return 1;
	}



int criarTabuleiro(char *nome,int *DIM,Elem **Tab){

	int i;
		
	FILE *fp = fopen(nome, "r");
		
	if(fp == NULL){
		return mensagem_de_erro(E_NO_FILE);
	}

	if (*Tab) freeTab(DIM,Tab);
	dimencao(fp,DIM);
	fseek(fp,0,SEEK_SET);
	
	if (!ficheiroValido(fp,DIM)) {
		return mensagem_de_erro(E_FILE_FORMAT );
	}
	fseek(fp,0,SEEK_SET);
	
/*Alocar espaco para a matriz*/
	(*Tab) = (Elem *)malloc((*DIM)*sizeof(Elem));
	for (i=0;i<(*DIM);i++) {
		(*Tab)[i] = (Elem )malloc(((*DIM))*sizeof(struct elemento));
	}

	lerficheiro(DIM,Tab,fp);
		
	fclose(fp);
return 0;
}

	

/**
 * A função printTAbuleiro é responsável por imprimir no ecrã o nosso tabuleiro.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 */
void printTabuleiro(int *DIM,Elem **Tab){
	
	int i,j;
	int linha=1;
	for(i=0;i<(*DIM);i++){				
		if(linha<10)	printf("%d   ",linha);
		else printf("%d  ",linha);
		for(j=0;j<(*DIM);j++){
			switch ((*Tab)[i][j].cor) {
				case ('i'): 
				printf("\033[44;33m %c \033[0m" ,(*Tab)[i][j].letra);		
				break;
				case ('b'): 
				printf("\033[47;31m %c \033[0m",(*Tab)[i][j].letra);		
				break;
				case ('p'): 
				printf("\033[40;31m %c \033[0m",(*Tab)[i][j].letra);				
				break;
			}	
		}
		printf("\n");		
		linha++;	
	}
	printf("   ");
	for(i=1;i<=(*DIM);i++){
		if(i<10)	printf("  %d",i);
		else printf(" %d",i);
	}
}

/**A função gravaJogo é responsável por gravar o nosso tabuleiro num ficheiro cujo o nome é dado como argumento e que está no formato ".ltr".
 * O tabuleiro será imprimido para o ficheiro seguindo as regras de representação deste, para que possa ser lido de novo e seja considerado válido.
 * @param Tab Tabuleiro do jogo
 * @param DIM dimensão do tabuleiro
 * @param nome Recebe uma string que representa o nome que vai dar ao ficheiro que vai guardar
 */
int gravaJogo (char *nome,int *DIM,Elem **Tab) {
	
	int i,j;
	
	FILE *f = fopen(nome, "w+");

	if(f == NULL){
		return mensagem_de_erro(E_SAVE);
	}
	else {
		fprintf( f,"%d\n",(*DIM));			
		for(i=0;i<(*DIM);i++){	
			for(j=0;j<(*DIM);j++){
				switch ((*Tab)[i][j].cor) {
					case ('i'): 
					fprintf(f," %c ",(*Tab)[i][j].letra);			
					break;
					case ('b'): 
					fprintf(f,"(%c)",(*Tab)[i][j].letra);		
					break;
					case ('p'): 
					fprintf(f,"[%c]",(*Tab)[i][j].letra);			
					break;
				}					
			}
		fprintf(f,"\n");
		}
	}
	fclose (f);
return 0;
}


