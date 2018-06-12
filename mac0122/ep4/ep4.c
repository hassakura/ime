/*  **************************************************************************  */
/*  Nome:  Hélio Hideki Assakura Moreira					*/
/*  Numero  USP: 8941064							*/
/*  EP4: Artista Aleatorio							*/
/*  **************************************************************************  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX 2147483648		/*2^31*/

typedef char * string;

/* Lista de sufixos */

struct cel{
	char suffix;
	int occur;
	float freq;
	float freqacum;
	struct cel * prox;
};
typedef struct cel celula;
typedef celula * sufixo;

/*Estrutura feita para a montagem da arvore*/

typedef struct cel4 {
	string palavra;
	int NroVezes;
	float freq;
	float freqacum;
	sufixo ProxLetra;
	struct cel4 * esq;
	struct cel4 * dir;
} no;
typedef no * apontador;

/*Variaveis Globais */

int nos = 0;

/* Funções Gerais */

/* Recebe uma string s e devolve uma copia da string */

string CopiaString (string s) {
	string str;
	str = malloc (strlen (s) + 1);
	if (str == NULL) exit( EXIT_FAILURE);
	strcpy (str, s);
	return str;
}

/* Lista de Ocorrencias */

/* Cria uma nova estrutura Sufixo, com determinado char x*/

sufixo CriaSufixo (char x){
	sufixo novo;
	novo = malloc (sizeof (celula));
	novo->suffix = x;
	novo->occur = 1;
	novo->freq = 0;
	novo->freqacum = 0;
	return (novo);
}

/*Recebe o inicio da lista e um char x, e caso ja exista uma ocorrencia de x na lista,
soma-se 1 em occur, senão, essa ocorrencia eh colocada no final da lista. Retorna-se o
inicio da lista*/

sufixo InsereNoFimLista (sufixo inicio, char x) {
	sufixo novo, p;
	novo = CriaSufixo (x);
	if (novo == NULL) printf ("ERRO \n");
	if (inicio == NULL) return novo;
	p = inicio;
	while (p->prox != NULL && p->suffix != novo->suffix)
		p = p->prox;
	if (p->prox == NULL && p->suffix != novo->suffix)
		p->prox = novo;
	else{
		free (novo);
		p->occur++;
	}
	return inicio;
}

/* Retorna um char de acordo com a Frequencia acumulada da lista */

char RandomChar (apontador raiz){
	float a;
	sufixo suf;
	a = (float)(rand () % MAX)/MAX;
	suf = raiz->ProxLetra; 
	while (suf->freqacum <= a)
		suf = suf->prox;
	return suf->suffix;
}

/* Conta-se o numero de ocorrencias de cada elemento na lista. Depois,
calcula-se a frequencia relativa e acumulada de cada elemento */

void UpdateFreqList (apontador raiz){
	int i = 0;
	float acum = 0;
	sufixo suf;
	for (suf = raiz->ProxLetra; suf != NULL; suf = suf->prox)
		i += suf->occur;
	for (suf = raiz->ProxLetra; suf != NULL; suf = suf->prox){
		suf->freq = (float)(suf->occur) / i;
		suf->freqacum = acum + suf->freq;
		acum = suf->freqacum;
	}
}

/* ARVORES */

/* Cria um novo no com a string x */

apontador CriaNo (string x){
	apontador novo;
	novo = malloc (sizeof (no));
	novo->palavra = CopiaString (x);
	novo->NroVezes = 1;
	novo->freq = 0;
	novo->freqacum = 0;
	novo->ProxLetra = NULL;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

/* A função recebe a raiz e retorna o no p que contem a string x */

apontador SearchTree (apontador raiz, string x){
	apontador p;
	p = raiz;
	while (p != NULL && strcmp (p->palavra, x) != 0)
		if (strcmp (p->palavra, x) < 0) p = p->esq;
	else p = p->dir;
	return p;
}

/* Recebe uma string x e um char c, e insere um novo no na arvore na posicao correta
caso nao exista ou acresce 1 em NroVezes caso ele exista, e insere c na lista ligada.
Soma-se 1 na variavel global nos, para a contagem de nos na arvore. */

apontador InsertTree (apontador raiz, string x, char c){
	apontador p, pai, novo;
	int cmp;
	p = raiz, pai = NULL;
	while (p != NULL){
		pai = p;
		cmp = strcmp (p->palavra, x);
		if (cmp == 0){
			p->NroVezes++;
			p->ProxLetra = InsereNoFimLista (p->ProxLetra, c);
			nos++;
			return raiz;
		}
		else if (cmp < 0) p = p->esq; 
		else p = p->dir;
	}
	novo = CriaNo (x);
	if (pai == NULL) {
		novo->ProxLetra = InsereNoFimLista (novo->ProxLetra, c);
		nos++;
		return (novo);
	}
	else if (strcmp (pai->palavra, x) < 0) {
		pai->esq = novo;
		pai->esq->ProxLetra = InsereNoFimLista (pai->esq->ProxLetra, c); 
	}
	else {
		pai->dir = novo;
		pai->dir->ProxLetra = InsereNoFimLista (pai->dir->ProxLetra, c);
	}
	nos++;
	return raiz;
}

/* Percorre a arvore atualizando a frequencia relativa e acumulada de cada no
e de sua lista correspondente. */

void UpdateFreqTree (apontador raiz, int nos, float * acum){
	if (raiz != NULL){
		raiz->freq = (float) (raiz->NroVezes) / nos;
		raiz->freqacum = * acum + raiz->freq;
		* acum = raiz->freqacum;
		UpdateFreqList (raiz);
		UpdateFreqTree (raiz->esq, nos, acum);
		UpdateFreqTree (raiz->dir, nos, acum);
	}
}

/* Essa funcao le char por char do texto, montando strings com k caracteres, e inserindo 
essas strings na arvore, alem dos caracteres subsequentes que serao inseridos
na lista ligada. */

apontador BuildTree (FILE * texto, int k, apontador raiz){
	string a;
	int j;
	char letra, proxletra;
	float acum = 0.0;
	a = malloc ((k + 1) * sizeof (char));
	if (k == 0){		/* Para k = 0, nao serao considerados os caracteres subsequentes */
		a[0] = fgetc (texto);
		proxletra = fgetc (texto);
		while (proxletra != EOF){
			raiz = InsertTree (raiz, a, '\0');
			a[0] = proxletra;
			proxletra = fgetc (texto);
		}
	}
	else {			
		for (j = 0; j < k; j++)
			a[j] = fgetc (texto);
		letra = fgetc (texto);
		proxletra = fgetc (texto);
		if (letra != EOF) raiz = InsertTree (raiz, a, letra);
		while (proxletra != EOF){
			for (j = 0; j < k - 1; j++)
				a[j] = a[j+1];
			a[j] = letra;
			letra = proxletra;
			proxletra = fgetc (texto);
			if (letra == EOF) break;
			/* Condicao usada para verificar se letra e proxletra nao sao os 2 ultimos caracteres do texto (\n e EOF). */
			if (letra == '\n' && proxletra == EOF) raiz = InsertTree (raiz, a, '\0'); 
			else raiz = InsertTree (raiz, a, letra);
		}
	}
	UpdateFreqTree (raiz, nos, &acum);
	free (a);
	return raiz;
}

/* Escolhe aleatoriamente um no da arvore de acordo com as probabilidades de ocorrencia de cada no */

void RandomNode (apontador raiz, float a, int * achei, string * str){	
	if (raiz != NULL && * achei == 0){
		if (a < raiz->freqacum){
			* achei = 1;
			strcpy (*str, raiz->palavra);
		}
		RandomNode (raiz->esq, a, achei, str);
		RandomNode (raiz->dir, a, achei, str);
	}
}

/* Funcao base do EP. Para k = 0, ela gera t caracteres aleatorios de acordo com as suas probabilidades.
Para k > 0, sera gerado uma palavra com k caracteres, e em seguida, sao gerados t-k caracteres. Caso nao
houver ocorrencia de caracteres seguintes a cada palavra de k caracteres, uma nova palavra eh gerada,
e o processo continua ate que sejam gerados t caracteres */

void BuildText (apontador raiz, int t, int k){
	int j, achei = 0, cont;
	string a;
	float rnd;
	char letra;
	apontador atual;
	cont = t;
	rnd = (float)(rand () % MAX)/MAX;
	a = malloc ((k + 1) * sizeof (char)); 
	/* Para k = 0, ele irá sortear t nos da arvore, ja que nao ha lista */
	if (k == 0){
		while (cont > 0){
			rnd = (float)(rand () % MAX)/MAX;
			RandomNode (raiz, rnd, &achei, &a);
			achei = 0;
			printf ("%s", a);
			cont--;
		}
	}
	else{
		/* Geracao dos k primeiros caracteres. */
		RandomNode (raiz, rnd, &achei, &a);
		for (j = 0; j < k; j++)
		if (cont > 0) {
			printf ("%c", a[j]);
			cont--;
		}
		else break;
		achei = 0;
		/* E gerado o proximo caracter, segundo a frequencia de ocorrencias no texto */
		if (cont > 0){
			atual = SearchTree (raiz, a);
			letra = RandomChar (atual);
			for (j = 0; j < k - 1; j++)
				a[j] = a[j+1];
			a[j] = letra;
			printf ("%c", a[j]);
			cont--;
		}
		/* Looping para gerar caracteres, ate que sejam gerados t caracteres */
		while (cont > 0){
			atual = SearchTree (raiz, a);
			/* Caso haja um proximo caracter na lista */
			if (atual != NULL && atual->ProxLetra->suffix != '\0'){
				for (j = 0; j < k - 1; j++)
					a[j] = a[j+1];
				a[j] = RandomChar (atual);
				printf ("%c", a[j]);
				cont--;
			}
			/*Senao, sao sorteados mais k caracteres aleatoriamente */
			else {
				rnd = (float)(rand () % MAX)/MAX;
				RandomNode (raiz, rnd, &achei, &a);
				achei = 0;
				for (j = 0; j < k; j++)
				if (cont > 0) {
					printf ("%c", a[j]);
					cont--;
				}
				else break;
			}
		}
	}
	printf ("\n");
	free (a);
}

/* LIBERACAO DE MEMORIA */

void FreeList (sufixo inicio){
	if (inicio != NULL){
		FreeList (inicio->prox);
		free (inicio);
	}
}

void FreeTree (apontador raiz){
	if (raiz != NULL){
		FreeTree (raiz->esq);
		FreeTree (raiz->dir);
		FreeList (raiz->ProxLetra);
		free (raiz->palavra);
		free (raiz);
	}
}

int main (){
	FILE * text;
	int k, t;
	apontador raiz = NULL;
	string a;
	srand ((unsigned) time (NULL));
	a = malloc (200 * sizeof (char));
	printf ("k: ");
	if (scanf ("%d", &k));
	printf ("t: ");
	if (scanf ("%d", &t));
	printf ("Caminho do texto: ");
	if (scanf ("%s", a));
	printf ("\n");
	text = fopen (a, "r");
	raiz = BuildTree (text, k, raiz);
	BuildText (raiz, t, k);
	FreeTree (raiz);
	fclose (text);
	free (a);
	return 0;
}
