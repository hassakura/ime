/* ************************************************************************** */
/* Nome: Hélio Hideki Assakura Moreira					      */
/* Numero USP: 8941064							      */
/* Exercicio-Programa 2 						      */
/* ************************************************************************** */


#include <stdio.h>
float raiz(float x, float eps){ 	/*Cálculo de raizes*/
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
float pot (float x, int a){     /*Cálculo de potências*/
	float valor=1;
	int aux;
	aux=a;
	while(aux>=1){
		valor=valor*x;
		aux=aux-1;
	}
	return valor;
}
unsigned int pot2(unsigned int x, unsigned int a){  /*Cálculo de potências para o método de Monte Carlo*/
	unsigned int valor=1, aux;
	aux = a;
	while(aux>=1){
		valor=valor*x;
		aux=aux-1;
	}
	return valor;
}
float arctan(float x, float eps){   /*Cálculo de arctan*/
	int k=1;
	float termo, soma;
	termo=soma=x;
	while(termo<-eps || termo>eps){
		k=k+2;
		termo=(float)(-termo*x*x*(k-2)/k);
		soma=soma+termo;
	}
	return soma;
}

unsigned int random(unsigned int p){    /*Gera um número "aleatório"*/
	unsigned int a=22695477u, num=0;
	int b=1;
	num=(a*p+b)%(pot2(2, 32)-1);
	return num;
}
float johnmachin (float eps){
      float pi;
      pi=4*(4*arctan((float)1/5, eps)-arctan((float)1/239, eps));
      return pi;
}
float francoisviete (int a, float eps){   /*Esse método, dependendo da quantidade de termos, exibe "-nan" como resposta*/
	float pi=0, den, num, soma=0;
	int cont=0;
	den=raiz(2, eps);
	soma=den;
	num=pot(2, a+2);
	while(cont<a){
		den=raiz(2+den, eps);
		soma=soma*den;
		cont++;
	}
	pi=num/soma;
	return pi;
}
float johnwallis(int a){
	int x=-1, y=0, cont=0;
	float pi, k1=2, k2=1, prod=1;
	while(cont<a){
		if(x==1){		/*k1 = Numerador*/
			k1=k1+2;	/*k2 = Denominador*/
			x=0;
		}
		else
		x++;
		if(y==1){
			k2=k2+2;
			y=0;
		}
		else
		y++;
		prod=prod*(k1/k2);
		cont++;
	}
	pi=2*prod;
	return pi;
}

float leibniz(int a){
	int cont=1;
	float pi=0, soma=0, aux=0;
	aux=soma=1;
	while(cont<a){
		aux=(pot(-1, cont)*((float)1/(2*cont+1)));
		soma=soma+aux;
		cont++;
	}
	pi=4*soma;
	return pi;
}

float gregoryleibniz(int a){
	int cont=0, k=2;
	float pi=3;		/*valor fixo ("3"+(4/2*3*4)-...)*/ 
	while(cont<a){
		pi=pi+pot(-1, cont)*((float)4/(k*(k+1)*(k+2)));
		k=k+2;
		cont++;
	}
	return pi;
}

float euler(int a, float eps){     
	int cont=0, k=1;
	float pi, soma=0;
	while(cont<a){
		soma=soma+((float)1/pot(k, 2));
		cont++;
		k++;
	}
	pi=raiz((6*soma), eps);
	return pi;
}

float montecarlo(int p, float eps){
	unsigned int x0=0, x1=0, y0=0, y1=0;
	int cont=0, pontodentro=0, pontofora=0;
	float px1=0, py1=0, pi=0;
	x0=random(p);
	y0=random(x0);
	while(cont<p){
		x1=random(y0);
		y1=random(x1);
		px1=x1/(pot(2, 32)-1);
		py1=y1/(pot(2, 32)-1);
		if(raiz((px1*px1)+(py1*py1), eps)<=1)
			pontodentro++;
		else
			pontofora++;
		y0=x1;
		x1=y1;
		cont++;
	}
	pi=4*((float)pontodentro/(pontodentro+pontofora));
	return pi;
}
int main(){
	int n, j;
	float eps, s1=0, s2=0, s3=0, s4=0, s5=0, s6=0, s7=0;
	printf("Insira o numero de termos a calcular: \n");
    	scanf("%d", &n);
	printf("Insira o eps: \n");
	scanf("%f", &eps);
	printf("Insira a quantidade de pontos a sortear: \n");
	scanf("%d", &j);
	s1=johnmachin(eps);
	s2=francoisviete(n, eps);
	s3=johnwallis(n);
	s4=leibniz(n);
	s5=gregoryleibniz(n);
	s6=euler(n, eps);
	s7=montecarlo(j, eps);
	printf("Johnmachin: %f\n", s1);
	printf("FrancoisViete: %f\n", s2);
	printf("Johnwallis: %f\n", s3);
	printf("Leibniz: %f\n", s4);
	printf("Gregory-Leibniz: %f\n", s5);
	printf("Euler: %f\n", s6);
	printf("Monte Carlo: %f\n", s7);
	return 0;
}

