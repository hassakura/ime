/*   NOME: Hélio Hideki Assakura Moreira 
     N USP: 8941064
     MATÉRIA: MAC0122
     EP2 - Pentaminós
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 12
/*Struct*/

typedef struct{
  int tampeca;
  int ** matriz;
  int rotacoes;
  int espelhavel;	
  char letra;
  int indice;
  int linhas;
  int colunas;
  int tanamatriz;
} peca;

typedef struct{
  peca *v;
  int topo;
  int pecas;
} pilha;

typedef struct{
  int ** matriz;
  int linhas;
  int colunas;
  int linatual;
  int colatual;
  int pecasencaixadas;
} tabuleiro;
/*-------------------*/

/*Funcoes de pilha*/

int pilhavazia (pilha p){
  return (p.topo == 0);
}
void empilha (pilha *p, peca peca){
  if (p -> topo == MAX)
    printf ("OVERFLOW");
  p -> v[p -> topo] = peca;
  (p -> topo)++;
  (p -> pecas)++;
}

peca desempilha (pilha *p){
  peca pa;
  if (pilhavazia (*p))
    printf ("UNDERFLOW");
  pa = p -> v[--p -> topo];
  (p -> pecas)--;
  return pa;
}

void criapilha (pilha *p, int tam) {
  p -> v = calloc (tam, sizeof (peca));
  p -> topo = 0;
  p -> pecas = 0;
}

void destroipilha (pilha *p){
  free (p);
}

int **aloca_matriz (int m, int n) {
  int **v; 		
  int i;				
  v = (int**) calloc (m , sizeof (int*));	
  for (i = 0; i < m; i++) {
    v[i] = (int*) calloc (n , sizeof (int));	
  }
  return (v);
}

void criatabuleiro (tabuleiro *TAB, int linha, int coluna){
  TAB -> linhas = linha;
  TAB -> colunas = coluna;
  TAB -> linatual = 0;
  TAB -> colatual = 0;
  TAB -> matriz = aloca_matriz (TAB -> linhas, TAB -> colunas);
  TAB -> pecasencaixadas = 0;
}

void imprimematriz (peca peca) {
  int i, j;
  for (i = 0; i < peca.tampeca; i++){
    for (j = 0; j < peca.tampeca; j++){
      if (peca.matriz[i][j] != 1 && peca.matriz[i][j] != 0) printf ("%c ", peca.letra);
      else if (peca.matriz[i][j] == 1) printf ("* ");
      else printf ("0 ");
    }
    printf ("\n");
  }
}
/*Essa função esquematiza a saída da matriz na resposta*/
void imprimetabuleiro (tabuleiro TAB){
  int linmatriz, colmatriz;
  for (linmatriz = 0; linmatriz < TAB.linhas; linmatriz++){
    for (colmatriz = 0; colmatriz < TAB.colunas; colmatriz++){
      switch (TAB.matriz[linmatriz][colmatriz]){
      case 0:
	printf ("0 ");
	break;
      case 1:
	printf ("* ");
	break;
      case 2:
	printf ("F ");
	break;
      case 3:
	printf ("I ");
	break;
      case 4:
	printf ("L ");
	break;
      case 5:
	printf ("N ");
	break;
      case 6:
	printf ("P ");
	break;
      case 7:
	printf ("T ");
	break;
      case 8:
	printf ("U ");
	break;
      case 9:
	printf ("V ");
	break;
      case 10:
	printf ("W ");
	break;
      case 11:
	printf ("X ");
	break;
      case 12:
	printf ("Y ");
	break;
      case 13:
	printf ("Z ");
	break;
      }
    }
    printf ("\n");
  }
}

peca transposta (peca pec, int tam){
  int i, j, temp;
  peca mtransp = pec;
  mtransp.matriz = aloca_matriz (tam, tam);
  for(i = 0; i < tam; i++)
    for(j = 0; j < tam; j++)
      mtransp.matriz[j][i] = pec.matriz[i][j];
  temp = mtransp.linhas;
  mtransp.linhas = mtransp.colunas;
  mtransp.colunas = temp;
  return mtransp;
} 



/*________________PECAS_________________*/

peca F () {
  peca peca;
  peca.indice = 2;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[1][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[2][1] = peca.indice;
  peca.matriz[0][2] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 1;
  peca.letra = 'F';
  peca.linhas = 3;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca; 
}

peca I () {
  peca peca;
  peca.indice = 3;
  peca.tampeca = 5;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[1][0] = peca.indice;
  peca.matriz[2][0] = peca.indice;
  peca.matriz[3][0] = peca.indice;
  peca.matriz[4][0] = peca.indice;
  peca.rotacoes = 1;
  peca.espelhavel = 0;
  peca.letra = 'I';
  peca.linhas = 5;
  peca.colunas = 1;
  peca.tanamatriz = 1;
  return peca;
}

peca L () {
  peca peca;
  peca.indice = 4;
  peca.tampeca = 4;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[1][0] = peca.indice;
  peca.matriz[2][0] = peca.indice;
  peca.matriz[3][0] = peca.indice;
  peca.matriz[3][1] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 1;
  peca.letra = 'L';
  peca.linhas = 4;
  peca.colunas = 2;
  peca.tanamatriz = 1;
  return peca;
}

peca N () {
  peca peca;
  peca.indice = 5;
  peca.tampeca = 4;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[1][2] = peca.indice;
  peca.matriz[1][3] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 1;
  peca.letra = 'N';
  peca.linhas = 2;
  peca.colunas = 4;
  peca.tanamatriz = 1;
  return peca;
}

peca P () {
  peca peca;
  peca.indice = 6;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[1][0] = peca.indice;
  peca.matriz[2][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 1;
  peca.letra = 'P';
  peca.linhas = 3;
  peca.colunas = 2;
  peca.tanamatriz = 1;
  return peca;
}

peca T () {
  peca peca;
  peca.indice = 7;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[0][2] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[2][1] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 0;
  peca.letra = 'T';
  peca.linhas = 3;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca;
}

peca U () {
  peca peca;
  peca.indice = 8;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[0][2] = peca.indice;
  peca.matriz[1][0] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[1][2] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 0;
  peca.letra = 'U';
  peca.linhas = 2;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca;
}

peca V () {
  peca peca;
  peca.indice = 9;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[0][2] = peca.indice;
  peca.matriz[1][2] = peca.indice;
  peca.matriz[2][2] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 0;
  peca.letra = 'V';
  peca.linhas = 3;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca;
}

peca W () {
  peca peca;
  peca.indice = 10;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[1][0] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[2][1] = peca.indice;
  peca.matriz[2][2] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 0;
  peca.letra = 'W';
  peca.linhas = 3;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca;
}

peca X () {
  peca peca;
  peca.indice = 11;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[1][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[1][2] = peca.indice;
  peca.matriz[2][1] = peca.indice;
  peca.rotacoes = 0;
  peca.espelhavel = 0;
  peca.letra = 'X';
  peca.linhas = 3;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca;
}

peca Y () {
  peca peca;
  peca.indice = 12;
  peca.tampeca = 4;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[1][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[1][2] = peca.indice;
  peca.matriz[1][3] = peca.indice;
  peca.rotacoes = 3;
  peca.espelhavel = 1;
  peca.letra = 'Y';
  peca.linhas = 3;
  peca.colunas = 4;
  peca.tanamatriz = 1;
  return peca;
}

peca Z () {
  peca peca;
  peca.indice = 13;
  peca.tampeca = 3;
  peca.matriz = aloca_matriz (peca.tampeca, peca.tampeca);
  peca.matriz[0][0] = peca.indice;
  peca.matriz[0][1] = peca.indice;
  peca.matriz[1][1] = peca.indice;
  peca.matriz[2][1] = peca.indice;
  peca.matriz[2][2] = peca.indice;
  peca.rotacoes = 2;
  peca.espelhavel = 1;
  peca.letra = 'Z';
  peca.linhas = 3;
  peca.colunas = 3;
  peca.tanamatriz = 1;
  return peca;
}

/*________________________________________#####_______________________________*/

/*-----------------*/

/*Essa função desloca todas as peças para que fiquem o mais a esquerda e o mais pra cima possivel de suas matrizes*/
peca padroniza (peca pa, int tam){
  int i, j, coluna = 0, linha = 0, encontrou = 0;
  for  (i = 0; i < tam; i++){
    for (j = 0; j < tam && !encontrou; j++)
      if (pa.matriz[i][j] != 0)
	encontrou = 1;
    if (!encontrou)
      linha++;
  }
	
  encontrou = 0;
	
  for  (j = 0; j < tam; j++){
    for (i = 0; i < tam && !encontrou; i++)
      if (pa.matriz[i][j] != 0)
	encontrou = 1;
    if (!encontrou)
      coluna++;
  }
	
  if(linha){
    for (i = 0; i < (tam - linha); i++)
      for (j = 0; j < tam; j++){
	pa.matriz[i][j] = pa.matriz[i + linha][j];
	pa.matriz[i + linha][j] = 0;
      }
  }
	
  if(coluna){
    for (j = 0; j < (tam - coluna); j++)
      for (i = 0; i < tam; i++){
	pa.matriz[i][j] = pa.matriz[i][j + coluna];
	pa.matriz[i][j + coluna] = 0;
      }
  }
  return pa;
}

/* Espelha a peça*/
peca espelhapeca (peca pa, int tam){
  int i, j, temp = 0;
  for (i = 0; i < tam; i++)
    for (j = 0; j < tam; j++){
      temp = pa.matriz[i][j];
      pa.matriz[i][j] = pa.matriz[i][tam-j-1];
      pa.matriz[i][tam-j-1] = temp;
    }
  return pa;
}


void criavetordepecas (peca *vetor_de_pecas) {
  vetor_de_pecas[0] = F ();
  vetor_de_pecas[1] = I ();
  vetor_de_pecas[2] = L ();
  vetor_de_pecas[3] = N ();
  vetor_de_pecas[4] = P ();
  vetor_de_pecas[5] = T ();
  vetor_de_pecas[6] = U ();
  vetor_de_pecas[7] = V ();
  vetor_de_pecas[8] = W ();
  vetor_de_pecas[9] = X ();
  vetor_de_pecas[10] = Y ();
  vetor_de_pecas[11] = Z ();
}

/*Essa função recebe uma peça pa, de tamanho máximo 'tam' (linhas e colunas)
  e devolve a peca rotacionada 90 graus no sentido horario*/	

peca girapeca (peca pa, int tam){				
  int i, j, aux;
  pa = transposta (pa, tam);
  for (i = 0;i<tam;i++)
    for(j = 0;j<tam/2;j++){
      aux = pa.matriz[i][tam-j-1];
      pa.matriz[i][tam-j-1] = pa.matriz[i][j];
      pa.matriz[i][j] = aux;
    }	
  return pa;
}
/*Essa função recebe uma peça peca1, e gira ou espelha ela a partir das configurações originais dela*/
void girapecacontrole (peca *peca1, peca *peca2){
  if (peca1 -> rotacoes){
    *peca1 = girapeca (*peca1, peca1 -> tampeca);
    *peca1 = padroniza (*peca1, peca1 -> tampeca);
    (peca1 -> rotacoes)--;
  }
  else{
    peca1 -> rotacoes = peca2[(peca1 -> indice)-2].rotacoes ;
    if (peca1 -> espelhavel == 1){
      *peca1 = espelhapeca (*peca1, peca1 -> tampeca);
      *peca1 = padroniza (*peca1, peca1 -> tampeca);
      (peca1 -> espelhavel) = 0;
    }
    else peca1 -> espelhavel = peca2[(peca1 -> indice)-2].espelhavel ;
  }
}

/*Recenbendo a peca 'peca', verifica se ela pode ser encaixada na primeira posição livre do tabuleiro TAB*/

int verifica_encaixa (peca peca, tabuleiro TAB){
  int linmatriz, colmatriz=0, linpeca, colpeca=0, X, Y, encontrou1 = 0, encontrou2 = 0;
	
  for (linmatriz=0 ; linmatriz<TAB.linhas && !encontrou1 ; ++linmatriz)
    for (colmatriz=0 ; colmatriz<TAB.colunas ; ++colmatriz)
      if (!(TAB.matriz[linmatriz][colmatriz])) {
	encontrou1 = 1;
	break;
      }
		
  for (linpeca=0 ; linpeca<peca.tampeca && !encontrou2 ; ++linpeca)
    for (colpeca=0 ; colpeca<peca.tampeca ; ++colpeca)
      if (peca.matriz[linpeca][colpeca] != 0) {
	encontrou2 = 1;
	break;
      }
			
  X = linmatriz - linpeca;
  Y = colmatriz - colpeca;
			
  if (X < 0 || Y < 0)
    return 0;
			
  for (linmatriz=X, linpeca=0 ; linpeca<peca.linhas ; ++linmatriz, ++linpeca)
    for (colmatriz=Y, colpeca=0 ; colpeca<peca.colunas ; ++colmatriz, ++colpeca){
      if (colmatriz + 1 > TAB.colunas || linmatriz + 1 > TAB.linhas)
	return 0;
      if ((TAB.matriz[linmatriz][colmatriz] != 0) && (peca.matriz[linpeca][colpeca] != 0))
	return (0);
    }
			
  return (1);
}
/*Recenbendo a peca 'peca', encaixa na primeira posição livre do tabuleiro TAB*/
void encaixa (peca peca, tabuleiro *TAB){
  int linmatriz, colmatriz, colpeca, linpeca, X, Y, encontrou1 = 0, encontrou2 = 0;
	
  for (linmatriz=0 ; linmatriz < TAB -> linhas && !encontrou1; ++linmatriz)
    for (colmatriz=0 ; colmatriz< TAB -> colunas; ++colmatriz)
      if (!(TAB -> matriz[linmatriz][colmatriz])) {
	encontrou1 = 1;
	break;
      }
		
  for (linpeca=0 ; linpeca<peca.tampeca && !encontrou2 ; ++linpeca)
    for (colpeca=0 ; colpeca<peca.tampeca ; ++colpeca)
      if (peca.matriz[linpeca][colpeca] != 0) {
	encontrou2 = 1;
	break;
      }
			
  X = linmatriz - linpeca;
  Y = colmatriz - colpeca;
			
  for (linmatriz=X, linpeca=0 ; linpeca < peca.linhas ; ++linmatriz, ++linpeca)
    for (colmatriz=Y, colpeca=0 ; colpeca < peca.colunas ; ++colmatriz, ++colpeca)
      if (peca.matriz[linpeca][colpeca] != 0){
	TAB -> matriz [linmatriz][colmatriz] = peca.indice;
      }
}

/* Remove a peça do tabuleiro */

void tirapeca (peca peca, tabuleiro *TAB){
  int i, j;
  for (i = 0; i < TAB -> linhas; i++)
    for (j = 0; j < TAB -> colunas; j++)
      if (TAB -> matriz [i][j] == peca.indice)
	TAB -> matriz [i][j] = 0;
}	

/*Verifica o estado da peca em relação as rotações e se ela é espelhavel*/

int daprarodar (peca peca){
  return (peca.rotacoes != 0 || peca.espelhavel != 0);
}

int achaprimeirapeca (peca *VET) {
  int i;
  for (i = 0; i < MAX; i++)
    if (VET[i].tanamatriz == 1)
      return i;
  return MAX;
}

int achaprimeirapeca2 (peca *VET, int atual) {
  int i;
  for (i = atual; i < MAX; i++)
    if (VET[i].tanamatriz == 1)
      return i;
  return MAX;
}

/*Marca o índice da peça como 0, dizendo que ela já está no tabuleiro*/

void tiradamatriz (peca *VET,  peca peca){
  int i;
  i = (peca.indice) - 2;
  VET[i].tanamatriz = 0;
}

/*Marca o índice da peça como 1, dizendo que ela ainda não foi colocada*/

void colocanamatriz (peca *VET,  peca peca){
  int i;
  i = (peca.indice) - 2;
  VET[i].tanamatriz = 1;
}

/*Função que empilha a peca pecaatual em p, encaixa ela no tabuleiro e marca como usada*/

void empilhamain (peca pecaatual, tabuleiro *TAB, pilha *p, peca *vetor_de_pecas){
  encaixa (pecaatual, TAB);
  empilha (p, pecaatual);
  tiradamatriz (vetor_de_pecas, pecaatual);
}

/*Função que desempilha a peca pecaatual em p, desencaixa ela do tabuleiro e marca como não usada*/
void desempilhamain (peca pecaatual, tabuleiro *TAB, pilha *p, peca *vetor_de_pecas){
  pecaatual = desempilha (p);
  tirapeca (pecaatual, TAB);
  colocanamatriz (vetor_de_pecas, pecaatual);
}
int dapraencaixar (peca pa, peca *vetor_de_pecas, tabuleiro TAB){
  while (!verifica_encaixa (pa, TAB)){
    if (daprarodar (pa))
      girapecacontrole (&pa, &vetor_de_pecas[pa.indice-2]);
    else
      return 0;
  }
  return 1;
}

int main(){
  int i, j, linhas, colunas, celula, achou = 0, solucao = 0, desempilhar = 0, inicio = 0;
  tabuleiro TAB;
  pilha p;
  peca *vetor_de_pecas;
  peca pa;
  vetor_de_pecas = (peca*) calloc (MAX, sizeof (peca));
  criapilha (&p, MAX);
  criavetordepecas (vetor_de_pecas);
  if(scanf ("%d %d", &linhas, &colunas));
  criatabuleiro (&TAB, linhas, colunas);
  for (i = 0; i < linhas; i++)
    for (j = 0; j < colunas; j++){
      if(scanf (" %d", &celula));
      TAB.matriz[i][j] = celula;
    }
  while (!solucao){
    /*Não tem que desempilhar, ou seja, procura pela proxima peça disponivel para ser colocada no tabuleiro*/
    if (!desempilhar){
      for (i = inicio; i < MAX; i++){
	pa = vetor_de_pecas[i];
	/* Verifica se é possivel, dentre todas as rotações, colocar a peça no tabuleiro. Caso consiga, coloca a peça. Caso não tenha conseguido, temos que desencaixar a peça anterior*/
	if (vetor_de_pecas[i].tanamatriz==1 && dapraencaixar(pa, vetor_de_pecas, TAB)){
	  while (!verifica_encaixa (pa, TAB)){
	    girapecacontrole (&pa, &vetor_de_pecas[pa.indice-2]);
	  }
	  empilhamain(pa, &TAB, &p, vetor_de_pecas);
	  if (p.topo == 12){
	    solucao = 1;
	    printf ("\n");
	    imprimetabuleiro(TAB);
	    return 0;
	  }
	  achou = 1;
	}
	else achou = 0;
      }
      if (i == 12){
	if (achou){
	  inicio = 0;
	}
	else{
	  desempilhar = 1;
	  inicio = 0;
	}
      }
      achou = 0;
    }
    /*Se não conseguimos achar uma peça que dê pra entrar no espaço, desempilhamos a anterior*/
    if (desempilhar){
      if (p.topo == 0){
	solucao = 1;
	printf ("impossivel \n");
	return 0;
      }
      if (p.topo == 12){
	solucao = 1;
	printf ("\n");
	imprimetabuleiro(TAB);
	return 0;
      }
      pa = desempilha (&p);
      tirapeca (pa, &TAB);
      colocanamatriz (vetor_de_pecas, pa);
      /*Imediatamente após tirar a peça, verificamos se há alguma rotação dela que consiga encaixar*/
      while (daprarodar(pa)){
	girapecacontrole (&pa, &vetor_de_pecas[pa.indice-2]);
	if (verifica_encaixa (pa, TAB) && vetor_de_pecas[pa.indice-2].tanamatriz==1){
	  empilhamain(pa, &TAB, &p, vetor_de_pecas);
	  desempilhar = 0;
	  achou = 1;
	  if (p.topo == 12){
	    solucao = 1;
	    printf ("\n");
	    imprimetabuleiro(TAB);
	    return 0;
	  }
	}
      }
      /*Se não achamos, começamos a procurar a partir da peça seguinte, se ela encaixa*/
      if (!achou){
	if (inicio >= 12) inicio = 0;
	else ( inicio = pa.indice-1);
      }
      else inicio = 0;
      desempilhar = 0;
      achou = 0;
    }
		
  }
  return 0;
}
