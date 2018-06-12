/* ****************************************************** */
/* Nome: Hélio Hideki Assakura Moreira	 */
/* Numero  USP: 8941064                                	 */
/* EP1 - Descobrindo os numeros	 */
/* MAC0122 - Segundo semestre de 2014	 */
/* ****************************************************** */

#define MAX 2000000000
#include <stdio.h>
#include <math.h>
#include <limits.h>

/* A função recebe o inteiro a e devolve o número de dígitos */
int digitos (int a) {
	int b = 0;
	while (a != 0) {
		a = a / 10;
		b++;
	}
	return b;
}

int main () {
	long double logmaior = 0, logmenor = 0;
	int encontrou = 0;
	long long unsigned m, num=1;
	printf ("Insira um numero n, 0 <= n <= 2000000000\n\n");
	printf ("Entrada: ");
	while (num != 0) {
		if (scanf ("%llu", &num) && num > 0 && num <= MAX) {
			m = digitos (num) + 1;
			while (!encontrou && (long long unsigned) logmaior < ULLONG_MAX) {
				logmenor = ((log10l (num) + m) / log10l (2));
				logmaior = ((log10l (num+1) + m) / log10l (2));
				encontrou = ((long long unsigned) logmaior - (long long unsigned) logmenor);
				//encontrou não é 0 sse logmaior for maior que a potencia procurada
				m++;
			}
			if ((long long unsigned) logmaior < ULLONG_MAX) {
				printf ("k:    %llu\n" , (long long unsigned) logmaior);
				encontrou = 0;
				printf ("Entrada: ");
			}
			else {
				printf ("Limite maximo calculavel");
				return 0;
			}	
		}
		else {
			if (num == 0) return 0;
			else {
				printf ("Dados fora do padrão");
				return 0;
			}
		}
	}
	return 0;
}
