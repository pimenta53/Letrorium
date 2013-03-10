/**
 * @struct jogadas jogada.h  
 * @brief Estrutura responsavel por guardar a coluna,linha e cor de uma celula a gravar. 
 */
typedef struct jogadas{
	int col;
	int row;
	char color;
	struct jogadas* next;
}Jogadas;
/**
 * @struct movimentos jogada.h  
 * @brief Estrutura responsavel por guardar a posição a que corresponde o tabuleiro nas cores guardadas até ao momento que é invocada. 
 */
typedef struct movimentos{
	int pos;
	struct movimentos *next;
}Movimentos;

/**
 * @struct It jogada.h  
 * @brief Estrutura responsavel por guardar a posição a que corresponde o tabuleiro nas cores guardadas até ao momento que é invocada. 
 */
typedef struct It{
	int pos;
	struct It *next;
}IT;

/**
 * @struct gravados jogada.h  
 * @brief Estrutura onde é armazenada toda a informação relativa a movimentos e jogadas guardadas
 */
typedef struct gravados{
	int totalGr;
	IT *its;
	Jogadas *jgs;
	Movimentos *mvs;
}Gravados;

int grava_jogada(int col,int row,char cor,Gravados *gr);
int jogada(char cor,int x,int y,Elem **Tab,Gravados *gr,int erro);
int E_Par_des(Elem **Tab,char letra1,char letra2,int *DIM,int line1,int cl1,int line2,int col2);
int jogadaManual(char cor,int x,int y,int *DIM,Elem **Tab,Gravados *gr);
int pds(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr);
int E_trp_row(Elem **Tab,int *DIM,int i,int j,Gravados *gr);
int E_trp_col(Elem **Tab,int *DIM,int i,int j,Gravados *gr);
int trp(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr);
int snd(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr);
int E_Par(Elem **Tab,int pos,char letra,int *DIM,char *local);
int pis(Elem **Tab,int *DIM,int *flagAP,int *flagAB,Gravados *gr);
int anc(Elem **Tab,Gravados *gr);
int free_jogadasGR(Gravados *gr);
int it(Gravados *gr);
int rb(Elem **Tab,Gravados *gr);
int inicia_GR(Gravados *gr);
int grava_movimento(Gravados *gr);
int anm(Elem **Tab,Gravados *gr);
int free_jogadasGR(Gravados *gr);

