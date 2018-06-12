/*  *************************************************************************** */
/*  Nome:  Hélio Hideki Assakura Moreira					*/
/*  Numero  USP:  8941064							*/
/*  Exercício-­‐programa  3							*/
/*  *************************************************************************** */

#define MAX 140000
#define PI 3.141592653589793
#define expon 2.718281828
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*----------------------------------------------------------UTILIDADES----------------------------------------------------------*/

float raiz(float x, float eps){     /*Raiz quadrada*/
      float r0, rn, tmp;
      int ok;
      r0=x;
      ok=1;
      while(ok){
           rn=0.5*(r0+x/r0);
       tmp=rn-r0;
       if(tmp<0)
        tmp=-tmp;
       if(tmp<eps)
        ok=0;
       else
        r0=rn;
      }
      return rn;
}

unsigned int pot2(unsigned int x, unsigned int a){  /*Cálculo de potências para a geração de numeros aleatórios (Congruências Lineares) do EP2*/
    unsigned int valor=1, aux;
    aux = a;
    while(aux>=1){
        valor=valor*x;
        aux=aux-1;
    }
    return valor;
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

int busca_binaria(float v[], int n, float x){
    int e, m=0, d;
    e=0;
    d=n-1;
    while(e<=d){
        m=(e+d)/2;
        if(v[m]==x)
            return m;
        if(v[m]<x)
            e=m+1;
        else
            d=m-1;
    }
    return m+1;
}

/*----------------------------------------------CONSTRUÇÃO DE GRÁFICOS----------------------------------------------------------*/

unsigned int random(int p){    /*Geraçao do numero aleatorio"*/
     unsigned int a=22695477u, num=0;
     int b=1;
     num=(a*p+b)%(pot2(2, 32)-1);
     return num;
}

void montecarlo(float V_MC[], int n, int semente){   /*Pontos aleatórios pelas Congruencias Lineares (entre 0 e 1)*/
    unsigned int x0=0, x1=0, y0=0, y1=0, i, p;
    float px1=0;
    p=semente;
    x0=random(p);
    y0=random(x0);
    for(i=0;i<n;i++){
        x1=random(y0);
        y1=random(x1);
        px1=(float)x1/(pot2(2, 32)-1); /*<< Ponto entre 0 e 1*/
        y0=x1;
        x1=y1;
        V_MC[i]=px1;
    }
}

void gera_func_dens_prob(float mi, float var, float V_DENSIDADE[], float V_SOMA[], float dp, int n){  /*Cria os vetores V_DENSIDADE e V_DENSIDADE_Y, que guardam os valores do EIXO Y do grafico de densidade de probabilidade (V_DENSIDADE usa o MI e SIGMA*/
    int i;											      /*do usuario, e V_DENSIDADE_Y usa MI=0 e SIGMA=1, para a construçao da normal) e o vetor V_SOMA, que guarda o eixo X, que sera usado por outras funçoes*/
    float delta, soma;
    delta=(8.0*dp)/n;	/*A multiplicaçao por 8 deve-se ao fato de que o delta deve percorrer entre -4*dp e 4*dp */
    soma=-4.0*dp+mi;	/*Marca o inicio dos valores a serem considerados para o calculo do eixo X*/
    for(i=0;i<n;i++){
        V_DENSIDADE[i]=(1.0/(sqrt(2.0*PI*var)))*(pow(expon, (-1.0/(2.0*var))*(pow(((float)(soma-mi)), 2))));
        soma=soma+delta;
        V_SOMA[i]=soma;
    }
}

void gera_func_acumulada(float V_DENSIDADE[], float V_ACUMULADA[], int n, float dp){ 
    int i;
    float delta=(8.0*dp)/n;
    for(i=0;i<n;i++){
        V_ACUMULADA[i+1]=(delta*V_DENSIDADE[i])+V_ACUMULADA[i];			/*Criaçao da acumulada pela soma de "n" deltas*/
    }
}

void gera_normal(float V_MC[], float V_ACUMULADA[], float V_NORMAL[], float V_SOMA[], int n){		/*Uso do metodo da inversa, para a criaçao do grafico da normal, que sera usada para gerar X e Y*/
    int i;
    for(i=0;i<n;i++){
        V_NORMAL[i]=V_SOMA[busca_binaria(V_ACUMULADA, n, V_MC[i])];
    }
}

/*------------------------------------------------GERAÇÃO DE X e Y--------------------------------------------------------*/

void gera_Y(float V_Y[], float V_X[], float V_EPS[], float k, int n){
    int i;
    for(i=0;i<n;i++)
        V_Y[i]=(k*V_X[i])+V_EPS[i];
}

void gera_X(float V_X[], float V_NORMAL[], int n){
    int i;
    for(i=0;i<n;i++)
        V_X[i]=V_NORMAL[i];
}

void gera_EPS(float V_MC[], float V_ACUMULADA_Y[], float V_EPS[], float V_SOMA_Y[], int n){     /*ok*/
    int i;
    float elem;
    for(i=0;i<n;i++){
        elem=V_MC[i];   
        V_EPS[i]=V_SOMA_Y[busca_binaria(V_ACUMULADA_Y, n, elem)];	/*V_SOMA_Y eh o eixo X da Normal padrao, de -3 a 3*/
    }
}

/*------------------------------------------------CORRELAÇÃO------------------------------------------------*/

/*--------------------------------Funçoes usadas para o calculo da correlaçao-------------------------------*/

float media_corr(float v[], int n){
    int i;
    float soma=0, media=0;
    for(i=0;i<n;i++)
        soma=soma+v[i];
    media=(float)soma/n;
    return media;
}

float dp_corr(float v[], int n, float media){					
    int i;
    float somadp=0;
    for(i=0;i<n;i++)
        somadp=somadp+((v[i]-media)*(v[i]-media));
    return sqrt(somadp);
}

float correlacao(float media_x, float media_y, float dp_x, float dp_y, float V_X[], float V_Y[], int n){
    int i=0;
    float corr=0;
    for(i=0;i<n;i++)
        corr=corr+(float)(((V_X[i]-media_x)*(V_Y[i]-media_y))/(dp_x*dp_y));
    return corr;
}

void gera_corr(float V_X[], float V_Y[], float V_CORR[], int N, int n){
   
    float media_x=0, media_y=0, dp_x=0, dp_y=0;
    media_x=media_corr(V_X, n);
    media_y=media_corr(V_Y, n);
    dp_x=dp_corr(V_X, n, media_x);
    dp_y=dp_corr(V_Y, n, media_y);
    V_CORR[N]=correlacao(media_x, media_y, dp_x, dp_y, V_X, V_Y, n);
}
       
/*------------------------------------------------MAIN------------------------------------------------*/

int main(){
    float V_MC[MAX], V_MC_2[MAX], V_DENSIDADE[MAX], V_DENSIDADE_Y[MAX], V_ACUMULADA[MAX], V_ACUMULADA_Y[MAX], V_NORMAL[MAX], V_NORMAL_Y[MAX], V_SOMA[MAX], V_SOMA_Y[MAX], V_X[MAX], V_Y[MAX], V_EPS[MAX], V_CORR[MAX],  dp, mi, var, k, Q1=0, Q2=0, Q3=0;
    int i, n, N, j;
    printf("\nInsira a média (MI), o desvio padrão (SIGMA), a quantidade de pontos aleatórios (n), a constante (k) e o número de Correlações de Pearson (N):\n");
    printf("<< ATENÇÃO: (n) máximo = 140000 >>\n\n");
    scanf("%f %f %d %f %d",&mi, &dp, &n, &k, &N);
    var=dp*dp;
    for(i=0;i<n;i++){
        V_MC[i]=0;
        V_DENSIDADE[i]=0;
        V_ACUMULADA[i]=0;
        V_NORMAL[i]=0;
        V_X[i]=0;
        V_Y[i]=0;
        V_EPS[i]=0;
        V_SOMA_Y[i]=0;
        V_SOMA[i]=0;
        V_CORR[i]=0;
        V_ACUMULADA_Y[i]=0;
        V_MC_2[i]=0;
        V_NORMAL_Y[i]=0;
        V_DENSIDADE_Y[i]=0;
    }
    montecarlo(V_MC, n, i);
    gera_func_dens_prob(mi, var, V_DENSIDADE, V_SOMA, dp, n);    			 /*Gera o grafico de densidade de probabilidade com os parâmetros do usuário*/
    gera_func_dens_prob(0, 1, V_DENSIDADE_Y, V_SOMA_Y, 1, n);   			 /*Grafico de densidade de probabilidade padrão (N(0,1))*/
    gera_func_acumulada(V_DENSIDADE, V_ACUMULADA, n, dp);       			 /*Acumulada com os parâmetros do usuário*/
    gera_func_acumulada(V_DENSIDADE_Y, V_ACUMULADA_Y, n, 1);   				 /*Acumulada a partir da NORMAL PADRÃO*/
    for(i=0;i<N;i++){
        j=100*V_MC[i];							/*Uso de um valor das Congruencias para gerar a proxima semente)*/
        montecarlo(V_MC_2, n, j);					/*Cria outro vetor com valores aleatorios uniformes diferentes*/
        gera_normal(V_MC, V_ACUMULADA, V_NORMAL, V_SOMA, n);  		/*Gera a normal que será usada para o cálculo de X*/
        gera_X(V_X, V_NORMAL, n);    					/*Gera os valores de X*/
        gera_normal(V_MC_2, V_ACUMULADA_Y, V_NORMAL_Y, V_SOMA_Y, n);    /*Gera normal padrão, para o cálculo de EPS*/
        gera_X(V_EPS, V_NORMAL_Y, n);  					/*Gera EPS*/
        gera_Y(V_Y, V_X, V_EPS, k, n);    				/*Gera os pontos de Y*/
        gera_corr(V_X, V_Y, V_CORR, i, n);				/*Calculo da correlaçao*/
    }
    bubble_sort(V_CORR, N);
    if(N%2==0)
        Q2=V_CORR[N/2];
    else
        Q2=V_CORR[(N+1)/2];
    if((N/2)%2==0)							/*Calculo dos Quartis*/
        Q1=V_CORR[(N/4)];
    else
        Q1=V_CORR[(((N+1)/2)+1)/2];
    if((3*N)%4==0)
        Q3=V_CORR[(3*N)/4];
    else
        Q3=V_CORR[((N+1)/2)+(((N+1)/2)+1)/2];
    printf("\n1 Quartil: %f\n2 Quartil: %f\n3 Quartil: %f\n\n", Q1, Q2, Q3);
    return 0;
}
	
	
