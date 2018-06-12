#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* struct que fará papel do barco B do usuário*/
struct Barco{
	char name;
	int linha;
	int coluna;
};
typedef struct Barco brc;
typedef brc * barco;

/*struct para o mapa*/
struct cmp{
	char ** matriz;
	int linhas;
	int colunas;
};
typedef struct cmp Campo;
typedef Campo * cpp;

/*struct para os tiros*/
typedef struct{
	int c_linha;
	int c_coluna;
} tiro;

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro */
void afunda_destroyer(int i,int j,cpp c){
	int k,g;
	for(k = i-1; k < i+2; k++){
        for(g = j-1; g < j+2; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='D')
                c->matriz[k][g]='*';

        }
	}
}

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro*/
void afunda_cruzador(int i,int j,cpp c){
    int k,g,l,cont=0,lin[2],col[2];
	for(k = i-1; k < i+2 && cont < 3; k++){
        for(g = j-1; g < j+2 && cont < 3; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='C'){
                c->matriz[k][g]='*';
                cont++;
                lin[cont-1]=k;
                col[cont-1]=g;
             }
        }
	}
	if(cont < 3){
        for(l = 0; l < 3 && cont < 3; l++){
            for(k = lin[l]-1; k < lin[l]+2 && cont < 3; k++){
                for(g = col[l]-1; g < col[l]+2 && cont < 3; g++){
                    if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='C'){
                        c->matriz[k][g]='*';
                        cont++;
                        lin[cont-1]=k;
                        col[cont-1]=g;
                    }
                }
            }
        }
	}
}

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro*/
void afunda_porta_aviao(int i,int j,cpp c){
    int k,g,l,cont=0,lin[3],col[3];
	for(k = i-1; k < i+2 && cont < 4; k++){
        for(g = j-1; g < j+2 && cont < 4; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='P'){
                c->matriz[k][g]='*';
                cont++;
                lin[cont-1]=k;
                col[cont-1]=g;
             }
        }
	}
	if(cont < 4){
        for(l = 0;l < 3 && cont < 4;l++){
            for(k = lin[l]-1; k < lin[l]+2 && cont < 4; k++){
                for(g = col[l]-1; g < col[l]+2 && cont < 4; g++){
                    if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='P'){
                        c->matriz[k][g]='*';
                        cont++;
                        lin[cont-1]=k;
                        col[cont-1]=g;
                    }
                }
            }
        }
	}
}

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro*/
void afunda_hidro_aviao(int i,int j,cpp c){
	int k,g,cont=0,lin=0,col=0;
	for(k = i-1; k < i+2 && cont < 2; k++){
        for(g = j-1; g < j+2 && cont < 2; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='H'){
                c->matriz[k][g]='*';
                cont++;
                lin=k;
                col=g;
             }
        }
	}
    if(cont < 2){
        for(k = lin-1; k < lin+2 && cont < 2; k++){
            for(g = col-1; g < col+2 && cont < 2; g++){
                if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='H'){
                    c->matriz[k][g]='*';
                    cont++;
                }
            }
        }
    }
}

/*função que recebe o caminho de um arquivo que contém o mapa com os barcos inimigos já posicionados*/
cpp leia_mapa(char* arq){
	cpp cp=malloc(sizeof(Campo));
	char str[100],linha[100];
	int i,j;

	FILE* fq = fopen(arq,"r");

    if(fq==NULL){
        printf("Erro na leitura do caminho do arquivo\n");
        return 0;
    }

	fgets(str,20,fq);
	sscanf(str," %d %d",&cp->linhas,&cp->colunas);


	cp->matriz = malloc(cp->linhas*sizeof(char*));

	for(i = 0; i < cp->linhas; i++){
		cp->matriz[i]=malloc(cp->colunas*sizeof(char));
	}

	for(i = 0; i < cp->linhas; i++){
		fgets(str,100,fq);
		sscanf(str,"%[^|]",linha);
		for(j = 0; j < cp->colunas; j++){
			cp->matriz[i][j]=linha[j];
		}

	}

	fclose(fq);

	return cp;
}

/*função que recebe como parametro o tipo cmp que representa o campo(mapa) e o escreve na tela*/
void escreva_mapa_tela(cpp cp){
	int i,j;
	printf("    ");
	for (i = 1; i <= cp->colunas; i++) printf("%3d",i);
	printf("\n");

	for(i = 0; i < cp->linhas; i++){
		printf("%3d|",i+1);
		for(j = 0; j < cp->colunas; j++) {
			if((cp->matriz[i][j]>'B' && cp->matriz[i][j]<'T')||cp->matriz[i][j]==' ') printf("%3c",'-');
			else printf("%3c",cp->matriz[i][j]);
		}
		printf("\n");
	}
}

/**FUNÇÃO EXTRA**/
/*função que serve como uma espécie de resposta pro usuário, a qual mostra num arquivo de saída, a cada rodada o que tem
 * em cada posição do campo,podendo o usuário analisar qual teria sido o melhor comando para tal rodada*/
void escreva_mapa_resposta(char *arq,cpp cp){
	int i,j;
	FILE* fl = fopen(arq,"a");

	fprintf(fl,"    ");
	for(i = 1; i <= cp->colunas; i++) fprintf(fl,"%3d",i);
	fprintf(fl,"\n");
	for(i = 0; i < cp->linhas; i++){
		fprintf(fl,"%3d|",i+1);
		for(j = 0; j < cp->colunas; j++) {
			if (cp->matriz[i][j]==' ') fprintf(fl,"%3c",'~');
			else fprintf(fl,"%3c",cp->matriz[i][j]);
		}
		fprintf(fl,"\n");
	}
	fprintf(fl,"\n\n\n\n");
	fclose(fl);

}
/*função que escreve num arquivo o passo a passo do mapa, depois dos movimentos do usuário e os tiros da rodada*/
void escreva_mapa_arquivo(char *arq,cpp cp){
	int i,j;
	FILE* fl = fopen(arq,"a");

	fprintf(fl,"    ");
	for(i = 1; i <= cp->colunas; i++) fprintf(fl,"%3d",i);
	fprintf(fl,"\n");
	for(i = 0; i < cp->linhas; i++){
		fprintf(fl,"%3d|",i+1);
		for(j=0;j<cp->colunas;j++){
			if((cp->matriz[i][j]>'B' && cp->matriz[i][j]<'T') || cp->matriz[i][j]==' ') fprintf(fl,"%3c",'-');
			else fprintf(fl,"%3c",cp->matriz[i][j]);
		}
		fprintf(fl,"\n");
	}
	fprintf(fl,"\n\n\n\n");
	fclose(fl);

}

/*função que servirá para mover o barco*/
int rema_barco(cpp c,  barco ba, char cmd){
	char next_move;
	switch(cmd){
		case 'a':
			if(ba->coluna > 0){
				next_move = c->matriz[ba->linha][ba->coluna - 1];
				if (next_move != 'D' && next_move != 'C' && next_move != 'H' && next_move != 'P' && next_move != 'S'){
					c->matriz[ba->linha][ba->coluna] = 'T';
					ba->coluna = ba->coluna - 1;
					c->matriz[ba->linha][ba->coluna] = 'B';
					return 1;
				}
				else return 0;
			}
			else return 0;
		case 'd':
			if(ba->coluna < c->colunas - 1){
				next_move = c->matriz[ba->linha][ba->coluna + 1];
				if(next_move != 'D' && next_move != 'C' && next_move != 'H' && next_move != 'P' && next_move != 'S'){
					c->matriz[ba->linha][ba->coluna] = 'T';
					ba->coluna = ba->coluna + 1;
					c->matriz[ba->linha][ba->coluna] = 'B';
					return 1;
				}
				else return 0;
			}
			else return 0;
		case 'w':
			if(ba->linha > 0){
				next_move = c->matriz[ba->linha - 1][ba->coluna];
				if(next_move != 'D' && next_move != 'C' && next_move != 'H' && next_move != 'P' && next_move != 'S'){
					c->matriz[ba->linha][ba->coluna] = 'T';
					ba->linha = ba->linha - 1;
					c->matriz[ba->linha][ba->coluna] = 'B';
					return 1;
				}
				else return 0;
			}
			else return 0;
		case 's':
			if(ba->linha != c->linhas - 1){
				next_move = c->matriz[ba->linha + 1][ba->coluna];
				if(next_move != 'D' && next_move != 'C' && next_move != 'H' && next_move != 'P' && next_move != 'S'){
					c->matriz[ba->linha][ba->coluna] = 'T';
					ba->linha = ba->linha + 1;
					c->matriz[ba->linha][ba->coluna] = 'B';
					return 1;
				}
				else return 0;
			}
			else return 0;
	}
	return 0;
}

/*função que recebe as coordenadas de um tiro e faz as devidas modificações*/
int identifica_alvo_atingido(cpp c,tiro t){
    char obj;
    obj = c->matriz[t.c_linha][t.c_coluna];
    if(obj == 'B'){
        c->matriz[t.c_linha][t.c_coluna] = '!';
        printf("Seu barco foi atingido :(\n");
        return -1;
    }
    else if(obj == 'T')
        c->matriz[t.c_linha][t.c_coluna] = '+';
    else if(obj == ' ' || obj == '=' || obj == '+' || obj == '*')
        c->matriz[t.c_linha][t.c_coluna] = '=';
    else{
        if(c->matriz[t.c_linha][t.c_coluna] == 'D'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            afunda_destroyer(t.c_linha,t.c_coluna,c);
        }
        else if(c->matriz[t.c_linha][t.c_coluna] == 'C'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            afunda_cruzador(t.c_linha,t.c_coluna,c);
        }
        else if(c->matriz[t.c_linha][t.c_coluna] == 'P'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            afunda_porta_aviao(t.c_linha,t.c_coluna,c);
        }
        else if(c->matriz[t.c_linha][t.c_coluna] == 'H'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            afunda_hidro_aviao(t.c_linha,t.c_coluna,c);
        }
        else
            c->matriz[t.c_linha][t.c_coluna] = '*'; /*considera o submarino*/
    }
    return 1;
}

/*funçao que soteará um número entre 0 e k-1*/
int sorteia(int k){
	return (int)(rand()/(RAND_MAX + 1.0)*k);
}

/*função que recebe o tamanho do campo e sorteará a posição de um tiro*/
tiro coordenadas_tiro(int l, int c){
	tiro t;
	t.c_linha = sorteia(l);
	t.c_coluna = sorteia(c);
	printf("Um tiro acertou a coordenada (%d,%d)\n",t.c_linha+1,t.c_coluna+1);
	return t;
}

/*função que recebe o campo e dispara o tiro, podendo afundar as embarcações ou não*/
void dispara_tiros(cpp c){
	tiro t;
	int i;
	for(i = 0; i < 3; i++){
		t = coordenadas_tiro(c->linhas, c->colunas);
		if(identifica_alvo_atingido(c,t)==-1) return;
    }
}

/*função que verifica se acabou*/
int acabou(cpp c, barco b, int cfim){
	if(b->linha == c->linhas - 1){
		printf ("\nFIM DE JOGO,VOCÊ GANHOU\n");
		return 1;
	}
	else if(c->matriz[b->linha][b->coluna] == '!' || cfim == 3){
		printf ("\nGAME OVER\n");
		return 1;
	}
	else return 0;
}

/*função que recebe o campo e posiciona o barco no mesmo*/
barco posiciona_barco(cpp c){
	int col;
	printf("Insira a posição inicial do barco (coluna):\n");
	scanf("%d",&col);

	while(col-1 > c->colunas || c->matriz[0][col-1]!=' '){
		printf("Posição invalida. \n Insira a posição inicial do barco (coluna): \n");
		scanf("%d",&col);
	};

	barco b;
	b = malloc(sizeof(brc));
	b->name = 'B';
	b->linha = 0;
	b->coluna = col-1;
	if (col >=1 && col-1 < c->colunas) c->matriz[0][col-1] = 'B';
	return b;
}

/*função que recebe um campo e o imprime na tela*/
void imprime_campo(cpp c){
	int i,j;
	for (i = 0; i < c->linhas; i++){
		for (j = 0; j < c->colunas; j++){
			printf ("%c ", c->matriz[i][j]);
		}
		printf ("\n");
	}
}

int main(){
	int gotit,i, /* variável que auxiliará no movimento do barco*/
        count = 0; /* variável que conta se o usuário executa um movimento inválido 3x seguidas*/
	cpp c = NULL; /* variável que servirá como campo(mapa) */
	barco b; /* variável do tipo barco que será o barco do usuário */
	char mov = ' '; /* variável que servirá para verificar a posição do campo durante a movimentação */
	srand((unsigned int) time(NULL));
	char *arq; /*variável para o caminho do arquivo contendo o campo */
	printf("Digite o caminho do arquivo mapa\n");
	scanf("%ms",&arq);

	c = leia_mapa(arq);
	if(c==0)
        return 0;

    printf("Movimentos do barco descritos a seguir:\n"
           "-a esquerda\n-s baixo\n-w cima\n"
           "-d direita\n");
	b = posiciona_barco(c);
	escreva_mapa_tela(c);
	escreva_mapa_arquivo("saida_ep.txt",c); /* manda o mapa c para saida_ep.txt */
	escreva_mapa_resposta("resposta_ep.txt",c); /* manda o mapa c para resposta_ep.txt */
	while(!acabou(c, b, count)){
		if(scanf(" %c", &mov));
		gotit = rema_barco (c, b, mov);
		escreva_mapa_tela(c);
		printf("\n");
		dispara_tiros(c);
		printf("\n");
		escreva_mapa_tela(c);
		escreva_mapa_arquivo("saida_ep.txt",c);
		escreva_mapa_resposta("resposta_ep.txt",c);
		if(gotit)
			count = 0;
		else{
			count++;
			printf("Movimento invalido\n");
		}
	}

	for(i = 0; i < c->linhas; i++){
        free(c->matriz[i]);
	}
	free(c->matriz);
	free(arq);
	free(c);
	free(b);
	return 0;
}
