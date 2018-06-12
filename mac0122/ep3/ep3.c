/*  **************************************************************************  */
/*  Nome:  Hélio Hideki Assakura Moreira					*/
/*  Numero  USP: 8941064							*/
/*  EP3: Indice Remissivo							*/
/*  **************************************************************************  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/* STRUCTS */

typedef char * string;

/*Estrutura feita para a montagem da Lista com as linhas que ocorreram cada palavra*/

struct cel{
	int info;
	struct cel * prox;
};
typedef struct cel celula;
typedef celula * linha;

/*Estrutura feita para os elementos*/

struct celElemento{
	string palavra;
	int NroVezes;
	linha ProxLinha;
};
typedef struct celElemento celula2;
typedef celula2 * elemento;

/*Estrutura feita para a montagem da Tabela De Simbolos*/

struct celT{
	elemento info;
	struct celT * prox;
};
typedef struct celT celula3;
typedef celula3 *TdS;

/*Estrutura feita para a montagem da arvore*/

typedef struct cel4 {
	elemento info;
	struct cel4 * esq;
	struct cel4 * dir;
} no;
typedef no * apontador;

/* ---------------------------- */

/* Lista de Ocorrencias */

linha CriaLinha (int x){
	linha novo;
	novo = malloc (sizeof (celula));
	novo->prox = NULL;
	novo->info = x;
	return (novo);
}

/* Função para cópia de string, já alocando a memória para a cópia*/

string CopiaString (string s) {
	string str;
	str = malloc (strlen (s) + 1);
	if (str == NULL) exit( EXIT_FAILURE);
	strcpy (str, s);
	return str;
}

linha InsereNoFimLinha (linha inicio, int x) {
	linha novo, p;
	novo = CriaLinha (x);
	if (novo == NULL) printf ("ERRO \n");
	if (inicio == NULL) return novo;
	p = inicio;
	while (p->prox != NULL)
		p = p->prox;
	p->prox = novo;
	return inicio;
}

void ImprimeLista (linha inicio){
	linha p;
	for (p = inicio; p != NULL; p = p->prox)
		printf ("%d ", p->info);
} 

/* --------------------- */

/*Elemento */

elemento CriaElemento (string str, int vezes, linha p){	
	elemento novo;
	novo = malloc (sizeof (celula2));
	novo->palavra = CopiaString (str);
	novo->NroVezes = vezes;
	novo->ProxLinha = p;
	return novo;
}


void ImprimeElemento (elemento e){
	printf ("%s ", e->palavra);
	printf ("%d ", e->NroVezes);
	printf ("[");
	ImprimeLista (e->ProxLinha);
	printf ("] \n\n");
}

/* --------------------------------  */

/* Tabela de Simbolos */

TdS CriaTabela (elemento e){
	TdS t;
	t = malloc (sizeof (celula3));
	t->prox = NULL;
	t->info = e;
	return t;
}

void ImprimeTabela (TdS inicio){
	TdS p;
	for (p = inicio; p != NULL; p = p->prox)
		ImprimeElemento (p->info);
} 

/* Recebe o inicio da Lista (Tabela) e um elemento x, e insere esse elemento
no final da lista*/

TdS InsereNoFimTabela (TdS inicio, elemento x) {
	TdS novo, p;
	novo = CriaTabela (x);
	if (novo == NULL) printf ("ERRO \n");
	if (inicio == NULL) return novo;
	p = inicio;
	while (p->prox != NULL)
		p = p->prox;
	p->prox = novo;
	return inicio;
}

/* ---------------------------------- */

/* Arvore de Busca Binaria */

apontador CriaNo (elemento x){
	apontador novo;
	novo = malloc (sizeof (no));
	novo->info = x;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

/* A função recebe a raiz e um elemento x e insere x na posição correta*/

apontador InsereArvore (apontador raiz, elemento x){
	apontador p, pai, novo;
	novo = CriaNo (x);
	p = raiz, pai = NULL;
	while (p != NULL){
		pai = p;
		if (strcmp (p->info->palavra, x->palavra) == -1) p = p->dir;
		else p = p->esq;
	}
	if (pai == NULL) return (novo);
	if (strcmp (pai->info->palavra, x->palavra) == -1) pai->dir = novo;
	else pai->esq = novo;
	return raiz;
}

/* Funções para impressão em Pré, In e Pós Ordem*/

void ImprimeArvorePre (apontador raiz){
	if (raiz != NULL){
		ImprimeElemento (raiz->info);
		ImprimeArvorePre (raiz->esq);
		ImprimeArvorePre (raiz->dir);
	}
}

void ImprimeArvoreIn (apontador raiz){
	if (raiz != NULL){
		ImprimeArvoreIn (raiz->esq);
		ImprimeElemento (raiz->info);
		ImprimeArvoreIn (raiz->dir);
	}
}

void ImprimeArvorePos (apontador raiz){
	if (raiz != NULL){
		ImprimeArvorePos (raiz->esq);
		ImprimeArvorePos (raiz->dir);
		ImprimeElemento (raiz->info);
	}
}


/* ---------------------------- */

/* A função Imprime recebe a linha lin, a palavra PProcurar (palavra a ser procurada), um texto e uma tabela
e devolve um elemento e, com o numero de ocorrencias (ocorreu) da palavra PProcurar, uma lista p com
as linhas (nlinhas) que PProcurar ocorreu e a palavra pesquisada*/

elemento Imprime (string lin, string PProcurar, FILE * texto, TdS t){	/* Aparentemente correto */
	string a, token;
	linha p = NULL;
	elemento e;
	int ocorreu = 0, nlinhas = 1, i;
	a = malloc (2000 * sizeof(char));
	token  = malloc (20 * sizeof (char));
	while (fgets (lin, 2000, texto) != NULL){
		for (i = 0; lin[i] != '\0'; i++) 
			lin[i] = tolower ( lin[i]);
		while (strstr (lin, PProcurar)){
			a = strstr (lin, PProcurar);	
			token = strtok (a, "\n,.;!?): ");
			if (!strcmp (PProcurar, token) && !isalpha(token[-1])){
				p = InsereNoFimLinha (p, nlinhas);
				ocorreu++; 
			}
			strcpy (lin,a + strlen (token) + 1);
		}
		nlinhas++;
	}
	e = CriaElemento (PProcurar, ocorreu, p);
	return e;
}

void ImprimeCabecalho (){
	printf ("\n |-----------------------------------------| \n");
	printf ("\n  Escolha o tipo de Tabela a ser utilizada:  \n");
	printf (" 0 - Sair \n");
	printf (" 1 - Lista Desordenada \n");
	printf (" 2 - Lista Ordenada (lexicografica) \n");
	printf (" 3 - Arvore de Busca Binaria (Saida Pre-Ordem) \n");
	printf (" 4 - Arvore de Busca Binaria (Saida In-Ordem) \n");
	printf (" 5 - Arvore de Busca Binaria (Saida Pos-Ordem) \n");
	printf ("\n |-----------------------------------------| \n");
}


int main(){
	string caminhotexto, PProcurar, lin, *VetorDePalavras, temp, caminhopalavras;
	TdS t = NULL;
	apontador a = NULL;  
	FILE * texto;
	FILE * palavras; 
	elemento e;
	int i = 0, escolha = 0, QtdePalavras = 0, j;
	caminhotexto = malloc (200 * sizeof(char));
	caminhopalavras = malloc (200 * sizeof(char));
	PProcurar = malloc (20 * sizeof(char));
	temp = malloc (20 * sizeof(char));
	lin = malloc (2000 * sizeof(char));
	printf ("Caminho Texto: ");
	scanf ("%s", caminhotexto);
	printf ("Caminho Palavras: ");
	scanf ("%s", caminhopalavras);
	ImprimeCabecalho ();
	scanf ("%d", &escolha);
	while (escolha != 0){
		t = NULL;
		a = NULL;
		e = NULL;
		palavras = fopen (caminhopalavras, "r");
		if (palavras == NULL){
			printf ("ERRO \n");
			exit (EXIT_FAILURE);
		}
		if (escolha == 1){
			/* Após receber o arquivo com as palavras a serem pesquisadas, elas serão ser separadas
			em "tokens", pela função strtok(). Assim, para cada palavra, será criado um elemento
			com as informações necessárias (Palavra, Ocorrencias e Linhas das ocorrencias), e esse
			elemento será inserido na tabela t*/
			while (fgets (PProcurar, 20, palavras) != NULL){
				for (i = 0; PProcurar[i] != '\0'; i++) 
					PProcurar[i] = tolower( PProcurar[i]);
				strtok (PProcurar, "\n");
				texto = fopen (caminhotexto, "r");
				if (texto == NULL){
					printf ("ERRO \n");
					exit (EXIT_FAILURE);
				}
				e = Imprime (lin, PProcurar, texto, t);
				t = InsereNoFimTabela (t, e);
				fclose (texto);
			}
			ImprimeTabela (t);
			free (e);
			free (t);
		}
		else if (escolha == 2){
			/* Para a Lista Ordenada, as palavras também são separadas em tokens, mas antes são
			guardadas num vetor, e colocadas em ordem (lexicograficamente) crescente. Como as
			palavras não terão acento, essas palavras estarao em ordem alfabetica*/
			VetorDePalavras = malloc (20000 * sizeof (char));
			while (fgets (PProcurar, 20, palavras) != NULL){
				for (i = 0; PProcurar[i] != '\0'; i++) 
					PProcurar[i] = tolower( PProcurar[i]);
				strtok (PProcurar, "\n");
				VetorDePalavras[QtdePalavras] = malloc (strlen (PProcurar) * sizeof (char));
				strcpy (VetorDePalavras[QtdePalavras], PProcurar);
				QtdePalavras++;
			}
			for(i = 1; i < QtdePalavras; i++)
				for (j = 0; j < QtdePalavras -1 ; j++)
				if(strcmp (VetorDePalavras[j],VetorDePalavras[j+1]) > 0)
				{  
					strcpy (temp,VetorDePalavras[j]);
					strcpy (VetorDePalavras[j],VetorDePalavras[j+1]);
					strcpy (VetorDePalavras[j+1],temp);                              
				}
				for (i = 0; i < QtdePalavras; i++){
					strcpy (PProcurar, VetorDePalavras[i]);
					texto = fopen (caminhotexto, "r");
					if (texto == NULL){
						printf ("ERRO \n");
						exit (EXIT_FAILURE);
					}
					e = Imprime (lin, PProcurar, texto, t);
					t = InsereNoFimTabela (t, e);
					fclose (texto);
				}
				ImprimeTabela (t);
				for (i = 0; i < QtdePalavras; i++)
					free (VetorDePalavras[i]);
				free(VetorDePalavras);
				free (e);
				free (t);
		}
		else{
			/*Implementaçao da arvore binaria. A saida poderá ser escolhida: Pré, In ou Pós Ordem*/
			while (fgets (PProcurar, 20, palavras) != NULL){
				for (i = 0; PProcurar[i] != '\0'; i++) 
					PProcurar[i] = tolower( PProcurar[i]);
				strtok (PProcurar, "\n");
				texto = fopen (caminhotexto, "r");
				if (texto == NULL){
					printf ("ERRO \n");
					exit (EXIT_FAILURE);
				}
				e = Imprime (lin, PProcurar, texto, t);
				a = InsereArvore (a, e);
				fclose (texto);
			}
			if (escolha == 3)
				ImprimeArvorePre (a);
			else if (escolha == 4)
				ImprimeArvoreIn (a);
			else
				ImprimeArvorePos (a);
			free (e);
			free (t);
			free (a);
		}		
		fclose (palavras);
		i = 0, QtdePalavras = 0;
		ImprimeCabecalho ();
		scanf ("%d", &escolha);
	}
	free(caminhotexto);
	free(caminhopalavras);
	free(PProcurar);
	free(temp);
	free(lin);
	return 0;
}
