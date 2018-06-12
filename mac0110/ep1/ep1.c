/* ************************************************************************** */
/* Nome: Hélio Hideki Assakura Moreira*/
/* Numero USP: 8941064 */
/* Exercício-programa 1 */
/* Qual versão foi implementada: "espartana" */
/* ************************************************************************** */
	

#include <stdio.h>
int main(){
  int n1000=0, n100=0, n10=0, n1=0, k; /* n1000~n1: Variáveis usadas para guardar os dígitos do milhar(n1000) até n1(unidade) / k: número a ser convertido */
  printf("Digite o número a ser convertido: \n");
  scanf("%d", &k);
  n1=k%10; /* Separando os dígitos da unidade, dezena, centena e milhar */
  k=k/10;
  n10=k%10;
  k=k/10;
  n100=k%10;
  k=k/10;
  n1000=k;
  while(n1000>0){  /* Conversão do milhar */ 
     printf("M");
     n1000=n1000-1;
  }
  if(n100==9){ /* Conversão da centena para numerais romanos, com exceções para 900, 500 e 400 */
  printf("CM");
  }
  else{
    if(n100>5){
      printf("D");
      while(n100>5){
        printf("C");
        n100=n100-1;
      }
    }
    else{
      if(n100==5){
        printf("D");
      }
      else{
        if(n100==4){
          printf("CD");
        }
        else{
          while(n100>0){
          printf("C");
	  n100=n100-1;
          }
        }
      }
    }
  }
  if(n10==9){ /* Conversão da dezena para numerais romanos, com exceções para 90, 50 e 40 */
    printf("XC");
    }
    else{
      if(n10>5){
        printf("L");
        while(n10>5){
          printf("X");
          n10=n10-1;
        }
      }
      else{
        if(n10==5){
          printf("L");
        }
        else{
          if(n10==4){
            printf("XL");
          }
          else{
            while(n10>0){
            printf("X");
	    n10=n10-1;
            }
          }
        }
      }
    }
  if(n1==9){ /* Conversão da unidade para numerais romanos, com exceções para 9, 5 e 4 */
    printf("IX\n");
    }
    else{
      if(n1>5){
        printf("V");
        while(n1>5){
          printf("I");
          n1=n1-1;
        }
	printf("\n"); /*Quebra de linha para melhorar a visualização do resultado*/
      }
      else{
        if(n1==5){
          printf("V\n");
        }
        else{
          if(n1==4){
            printf("IV\n");
          }
          else{
            while(n1>0){
            printf("I");
            n1=n1-1;
            }
	    printf("\n");
          }
        }
      }
    }
  return 0;
}
