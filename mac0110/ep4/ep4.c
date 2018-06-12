/*  *************************************************************************** */
/*  Nome:  Hélio Hideki Assakura Moreira					*/
/*  Numero  USP:  8941064							*/
/*  Exercício-­‐programa  4							*/
/*  *************************************************************************** */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14159265358979323846
#define M (unsigned int) 4294967295u
#define DX 0.00001
#define SIZE 100000
#define MAX (int) (SIZE * 0.9974)

/*------------------------Codigo disponibilizado pelo monitor---------------------*/

/* Calcula o valor da funcao densidade de probabilidade gaussiana 
* (com media mu e variancia var) para x, f(x).
*/
float densidade_probabilidade_gaussiana (float mu, float var, float x) {
	return exp(-(x-mu)*(x-mu)/(2*var)) / sqrt(2*PI*var);
}

/* Usa a soma de Riemann para calcular a area sob a curva da funcao 
* densidade de probabilidade no intervalo ate que o valor acumulado
* da soma das areas seja maior ou igual ao valor limite.
*/
float soma_Riemann (float mu, float var, float *F, int pos, float x, float acumulada, float limite) {
	
	while (acumulada < limite) {
		x += DX;
		acumulada += DX * densidade_probabilidade_gaussiana(mu,var,x);
	}
	F[pos] = x;
	return acumulada;
}

/* Calcula a funcao acumulada da densidade de probabilidade com media
* mu e variancia var, F(x). Utiliza o intervalo [mu-3dp ; mu+3dp]
* (onde dp eh o desvio padrao) para o calculo. A funcao armazena, na
* i-esima posicao de F, o valor de x tal que F(i) > i * DX, onde F(i)
* eh DX * ( f(mu-3dp) + f(mu-3dp+DX) + f(mu-3dp+2DX) + ... + f(x) ).
*/
int obtem_densidade_acumulada_gaussiana(float mu, float dp, float *F, int max) {
	int i;
	float x = mu - 3 * dp, acumulada = 0;
	
	for (i = 0; i < max-1 && x < mu + 3 * dp; i++) {
		acumulada = soma_Riemann(mu, dp*dp, F, i, x, acumulada, i / (float) SIZE);
		x = F[i];
	}
	if (x > mu + 3 * dp)
		F[i-1] = mu + 3 * dp;
	else
		F[i] = mu + 3 * dp;
	
	return i;
}

/* Busca o indice i de F tal que F(i) ~ num_unif. */
int busca_indice(float num_unif, int ultima_posicao) {
	return (int) (num_unif * (ultima_posicao-1) + 0.5);
}

/* Gera um numero aleatorio a partir de uma distribuicao uniforme no
* intervalo [0 ; M-1] usando o metodo das congruencias lineares.
*/
unsigned int rand_unif (unsigned int rand_x) {
	unsigned int a = 22695477u, b = 1;
	return (a * rand_x + b) % M;
}

/* Gera um numero aleatorio a partir de uma distribuicao gaussiana
* atraves do metodo da funcao inversa. O metodo sorteia um numero
* U a partir de uma uniforme no intervalo [0;1] e devolve o valor
* x tal que F(i) ~ U e F(i) = DX * ( f(mu-3dp) + ... + f(x) ).
*/
float rand_gaussiana (float *F, int ultima_posicao, unsigned int *rand_x) {
	*rand_x = rand_unif(*rand_x);
	return F[busca_indice(*rand_x / (float) (M-1), ultima_posicao)];
}

/*------------------------FIM do codigo disponibilizado pelo monitor---------------------*/


/*Retira uma linha e uma coluna de uma matriz*/

float **reduzmatriz(float **X, float **XMENOR, int n, int coluna){
	int i, j, k=0;
	for(i=1;i<n;i++){
		k=0;
		for(j=0;j<n;j++)
		if(j!=coluna){
			XMENOR[i-1][k]=X[i][j];
			k++;
		}
	}
	return XMENOR;
}

/*Alocação de matrizes com calloc, inicializando zerada*/

float **aloca_matriz(int m,int n) {
	float **v; 		
	int i;				
	v =(float**) calloc (m,sizeof(float*));	
	for (i=0;i<m;i++) {
		v[i]=(float*) calloc (n, sizeof(float));	
	}
	return(v);
}

float *aloca_vetor (int n) {
	float *v;
	
	v = malloc(n * sizeof(float));
	if (v == NULL) {
		printf("Erro ao alocar vetor.\n");
		exit(-1);
	}
	return v;
}

/*Alocação de vetores com calloc*/

float *aloca_vetor_c (int n){
	float *v;
	v = (float*) calloc(n, sizeof(float*));
	return v;
}

/*Calculo da determinante. Recursivamente, ele usa LaPlace para o determinante, até n=3*/

float determinante(float **X, int n){
	float **XMENOR=NULL, det=0, **X1;
	int i;
	X1=aloca_matriz(n,n);
	X1=X;
	if(n==1)
		return X[0][0];
	else if(n==2)
		return X[0][0]*X[1][1]-X[1][0]*X[0][1];
	else if(n==3)
		return X[0][0]*X[1][1]*X[2][2]+X[0][1]*X[1][2]*X[2][0]+X[0][2]*X[1][0]*X[2][1]-(X[2][0]*X[1][1]*X[0][2]+X[2][1]*X[1][2]*X[0][0]+X[2][2]*X[1][0]*X[0][1]);
	else{
		for(i=0;i<n;i++){
			XMENOR=aloca_matriz(n-1,n-1);
			reduzmatriz(X1,XMENOR,n,i);
			det+=pow(-1.0, i+2.0)*X1[0][i]*determinante(XMENOR, n-1);
		}
		return det;
	}
}

/*Percorre o vetor, e joga para o elemento anterior a linha e coluna correspondente, até o final da matriz*/

float **montacofator(float **X, float **AUX, int n, int linha, int coluna){
	int i, j, l, m;
	m=0;
	for(i=0;i<n;i++){
		if(i!=linha){
			l=0;
			for(j=0;j<n;j++){
				if(j!=coluna)
					AUX[i-m][j-l]=X[i][j];
				else
					l=1;
			}
		}
		else
			m=1;
	}
	return AUX;
} 


float **cofator(float **X, int n){
	int i, j;
	float **COF, **AUX=NULL;
	COF=aloca_matriz(n, n);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++){
		AUX=aloca_matriz(n-1, n-1);
		montacofator(X, AUX, n, i, j);
		COF[i][j]=pow(-1.0, i+j+2)*determinante(AUX, n-1);
	}
	return COF;  	
}

/*Transposição de matrizes pela simples troca dos indices*/

float **transposta(float **X, int n, int p){
	int i, j;
	float **TRANSP=NULL;
	TRANSP=aloca_matriz(n, p);
	for(i=0;i<p;i++){
		for(j=0;j<n;j++){
			TRANSP[j][i]=X[i][j];
		}
	}	
	return TRANSP;
}

/*Multiplicação de matrizes (passado em aula)*/

float **multiplica(float **A, float **B, int n){
	float **MULT=NULL, soma;
	int i, j, k;
	MULT=aloca_matriz(n, n);
	for(k=0;k<n;k++){
		for(j=0;j<n;j++){
			soma=0;
			for(i=0;i<n;i++)
				soma=soma+A[k][i]*B[i][j];
			MULT[k][j]=soma;
		}
	}
	return MULT;
}

/*Multiplicação para uma matriz e um vetor, que sera usado posteriormente para o calculo do yi*/

float *multiplica2(float **A, float *B, int n){
	float *M1=NULL, soma;
	int i, j;
	M1=aloca_vetor(n);
	for(j=0;j<n;j++){
		soma=0;
		for(i=0;i<n;i++)
			soma=soma+A[j][i]*B[i];
		M1[j]=soma;
	}
	return M1;
}


float **inversa(float **X, int n){
	float **INVERSA=NULL, **ADJUNTA=NULL;
	int i, j;
	INVERSA=aloca_matriz(n, n);
	ADJUNTA=aloca_matriz(n, n);
	ADJUNTA=cofator(X, n);	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		INVERSA[j][i]=(1.0/determinante(X, n))*ADJUNTA[i][j];
	return INVERSA;
}	

/*Realiza a operaçao com as matrizes para estimar o valor de BETA CHAPEU*/
/*Deixo uma forma mais facil de se compreender o que se passa nessa funçao, deixando mais claro os indices de cada funçao*/

float *fazconta(float **X, float *Y, int n, int p){
	float *AUX1, *AUX2, **AUX3 ;
	AUX3=aloca_matriz(p, p);
	AUX2=aloca_vetor(p);
	AUX1=aloca_vetor(p);
	AUX3=inversa(multiplica(transposta(X, n, p), X, p), p);
	AUX2=multiplica2(transposta(X, n, p), Y, p);
	AUX1=multiplica2(AUX3, AUX2, p);
	return AUX1; 
	/* return multiplica2(inversa(multiplica(transposta(X, n, p), X, p), p), multiplica2(transposta(X, n, p), Y, p), p); */
}

void bubble_sort(float v[], int n){
	int houvetroca=1, i;
	float aux;
	while(houvetroca){
		houvetroca=0;
		for(i=0;i<n-1;i++){
			if(v[i]>v[i+1]){
				aux=v[i];
				v[i]=v[i+1];
				v[i+1]=aux;
				houvetroca=1;
			}
		}
	}
}

/*------------------------------------------------MAIN------------------------------------------------*/


int main(){
	float mu=0, dp=1, *F, **X, *BETA, *Y, *BETAEST, **MATCOEF;
	int n, p, i, j,  ultima_posicao = MAX,  N, cont, aux, col ;
	unsigned int rand_x = SIZE;
	printf("Insira n, p e N, sendo n o numero de observacoes, p a quantidade de variaveis aleatorias, e N o numero de repeticoes\n");
	scanf("%d %d %d", &n, &p, &N);
	BETA = aloca_vetor(p);
	F = aloca_vetor(MAX);
	X=aloca_matriz(n, p); 
	BETAEST = aloca_vetor(p);
	MATCOEF=aloca_matriz(N, p);
	Y = aloca_vetor(n);
	printf("Insira os BETAS [-1, 1]:\n");
	for(aux=0;aux<p;aux++)
		scanf("%f", &BETA[aux]);
						/*Repetição de (3) e (4) do enunciado do EP (Obter y e os betas estimados)*/
	for(cont=0;cont<N;cont++){ 					
		for(i=0;i<p;i++){ 		/*Gera o vetor nxp preenchido com variaveis aleatorias a partir de uma Gaussiana*/
			ultima_posicao = obtem_densidade_acumulada_gaussiana(mu, dp, F, MAX); 
			for (j = 0; j<n; j++){
				X[i][j] =  rand_gaussiana(F, ultima_posicao, &rand_x) ;
			} 
		} 
		for(i=0;i<n;i++)	/*Zera o vetor Y, excluindo o resultado obtido anteriormente*/
			Y[i]=0;	
		for(i=0;i<n;i++){	/*Gera o vetor Y, com os yi's calculados a partir dos coeficientes fornecidos pelo usuario*/
			for(j=0;j<p;j++){
				Y[i]+=X[i][j]*BETA[j];
			}
			Y[i]+=rand_gaussiana(F, obtem_densidade_acumulada_gaussiana(mu, dp, F, MAX), &rand_x);
		}
		
		BETAEST = fazconta(X, Y, n, p);			/*Recebe o vetor dos B chapeus*/
		bubble_sort(BETAEST, p);
		for(col=0;col<n;col++){		/*Matriz dos coeficientes estimados*/
			MATCOEF[cont][col]=BETAEST[col];
		}
	}
	for(i=0;i<p;i++){
		printf("\n");
		printf("Q1: %f \n", MATCOEF[i][p/4]);
		printf("Q2: %f \n", MATCOEF[i][p/2]);
		printf("Q3: %f \n", MATCOEF[i][(3*p)/4]);
		printf("\n");
	} 
	
    	free(F);
    	free(X);
    	free(BETA);
    	free(BETAEST);
    	free(MATCOEF);
    	free(Y);    	
    	return 0;
}


