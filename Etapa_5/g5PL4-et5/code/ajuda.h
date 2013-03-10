int pretasAuto(int x,int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr,int *cores);
int brancasAuto(int x,int y,Elem **Tab, int *DIM,int *flagAP,int *flagAB,Gravados *gr,int *cores);
int ajuda();
/*int p_brancas(Elem **Tab, int i, int j, int *DIM,Gravados *gr);
int auto_black(Elem **Tab, int *DIM,Gravados *gr,int x,int y);
int p_preta(Elem **Tab, int i, int j,char letra,int *DIM,Gravados *gr);
int auto_white(Elem **Tab,int *DIM,Gravados *gr,int x,int y);*/
int rsv(Elem **Tab,int *DIM,Gravados *gr);
int control (Elem **Tab, int *DIM, int *flagAB, int *flagAP,Gravados *gr,int erro);
int executa_tc(char *args,int *DIM,Elem **Tab,int *flagAP,int *flagAB,Gravados *gr);
int vc (Elem **Tab, int *DIM, Gravados *gr);
int count_i (Elem **Tab, int *DIM);
int imp (Elem **Tab, int *DIM, Gravados *gr,int *flagAP, int *flagAB);
int crg(Elem **Tab,int *DIM,Gravados *gr);
