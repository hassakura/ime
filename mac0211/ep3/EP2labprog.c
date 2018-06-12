#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "xwc.h"

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
void afunda_destroyer(int i,int j,cpp c, PIC *barcomov, WINDOW *janela, PIC *explosions){
	int k,g, timer,h;
	for(k = i-1; k < i+2; k++){
        for(g = j-1; g < j+2; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='D'){
               for (timer = 0; timer < 13; timer++){
                	PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                	for(h=0;h<25000000;h++); /* Delay */
                }
                c->matriz[k][g]='*';
            }

        }
	}
}

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro*/
void afunda_cruzador(int i,int j,cpp c, PIC *barcomov, WINDOW *janela, PIC *explosions){
    int k,g,l,cont=0,lin[2],col[2], timer, h;
	for(k = i-1; k < i+2 && cont < 3; k++){
        for(g = j-1; g < j+2 && cont < 3; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='C'){
                for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                			for(h=0;h<25000000;h++);/* Delay */
                }
                c->matriz[k][g]='*';
                lin[cont]=k;
                col[cont]=g;
                cont++;
            }
        }
	}
	if(cont < 3){
        for(l = 0; l < 3 && cont < 3; l++){
            for(k = lin[l]-1; k < lin[l]+2 && cont < 3; k++){
                for(g = col[l]-1; g < col[l]+2 && cont < 3; g++){
                    if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='C'){
                    	for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                			for(h=0;h<25000000;h++);/* Delay */
                		}
                        c->matriz[k][g]='*';
                        lin[cont]=k;
                        col[cont]=g;
                        cont++;
                    }
                }
            }
        }
	}
}

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro*/
void afunda_porta_aviao(int i,int j,cpp c, PIC *barcomov, WINDOW *janela, PIC *explosions){
    int k,g,l,cont=0,lin[3],col[3], timer, h;
	for(k = i-1; k < i+2 && cont < 4; k++){
        for(g = j-1; g < j+2 && cont < 4; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='P'){
             	for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                			for(h=0;h<25000000;h++);/* Delay */
                }
                c->matriz[k][g]='*';
                lin[cont]=k;
                col[cont]=g;
                cont++;
            }
        }
	}
	if(cont < 4){
        for(l = 0;l < 3 && cont < 4;l++){
            for(k = lin[l]-1; k < lin[l]+2 && cont < 4; k++){
                for(g = col[l]-1; g < col[l]+2 && cont < 4; g++){
                    if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='P'){
                    	for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                			for(h=0;h<25000000;h++);/* Delay */
                		}
                        c->matriz[k][g]='*';
                        lin[cont]=k;
                        col[cont]=g;
                        cont++;
                    }
                }
            }
        }
	}
}

/* função que recebe a posição(i,j) que um tiro acerta e o mapa
 * e atribui * as posições do barco inteiro*/
void afunda_hidro_aviao(int i,int j,cpp c, PIC *barcomov, WINDOW *janela, PIC *explosions){
	int k,g,cont=0,lin=0,col=0, timer, h;
	for(k = i-1; k < i+2 && cont < 2; k++){
        for(g = j-1; g < j+2 && cont < 2; g++){
             if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='H'){
				for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                			for(h=0;h<25000000;h++);/* Delay */
                }
                c->matriz[k][g]='*';
                lin=k;
                col=g;
                cont++;
            }
        }
	}
    if(cont < 2){
        for(k = lin-1; k < lin+2 && cont < 2; k++){
            for(g = col-1; g < col+2 && cont < 2; g++){
                if(k >= 0 && k < c->linhas && g >= 0 && g < c->colunas && c->matriz[k][g]=='H'){
                	for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(g)*32, k * 32);
                			for(h=0;h<25000000;h++);/* Delay */
                		}
                        c->matriz[k][g]='*';
                        lin=k;
                        col=g;
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
int rema_barco(cpp c,  barco ba, char cmd,PIC *barcomov, WINDOW *janela,PIC barcopassou){
	char next_move;
	switch(cmd){
		case 'a':
			if(ba->coluna > 0){
				next_move = c->matriz[ba->linha][ba->coluna - 1];
				if (next_move != 'D' && next_move != 'C' && next_move != 'H' && next_move != 'P' && next_move != 'S'){
					c->matriz[ba->linha][ba->coluna] = 'T';
					PutPic(janela,barcopassou,0,0,32,32,(ba->coluna)*32, ba->linha * 32);
					ba->coluna = ba->coluna - 1;
					PutPic(janela,barcomov[3],0,0,32,32,(ba->coluna)*32, ba->linha * 32);
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
					PutPic(janela,barcopassou,0,0,32,32,(ba->coluna)*32, ba->linha * 32);
					ba->coluna = ba->coluna + 1;
					PutPic(janela,barcomov[0],0,0,32,32,(ba->coluna)*32, ba->linha * 32);
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
					PutPic(janela,barcopassou,0,0,32,32,(ba->coluna)*32, ba->linha * 32);
					ba->linha = ba->linha - 1;
					PutPic(janela,barcomov[1],0,0,32,32,(ba->coluna)*32, ba->linha * 32);
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
					PutPic(janela,barcopassou,0,0,32,32,(ba->coluna)*32, ba->linha * 32);
					ba->linha = ba->linha + 1;
					PutPic(janela,barcomov[2],0,0,32,32,(ba->coluna)*32, ba->linha * 32);
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
int identifica_alvo_atingido(cpp c,tiro t, PIC *barcomov, WINDOW *janela, PIC *explosions,PIC *aguatiro, PIC *barcoafunda, PIC *aguapassou){
    char obj;
    int timer, h;
    obj = c->matriz[t.c_linha][t.c_coluna];
    if(obj == 'B'){
        c->matriz[t.c_linha][t.c_coluna] = '!';
        printf("Seu barco foi atingido :(\n");
        for (timer = 0; timer < 4; timer++){
        	PutPic(janela,barcoafunda[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
        	for(h=0;h<100000000;h++);/* Delay */
        }
        return -1;
    }
    else if(obj == 'T'){
        c->matriz[t.c_linha][t.c_coluna] = '+';
        for (timer = 0; timer < 4; timer++){
        	PutPic(janela,aguapassou[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
        	for(h=0;h<25000000;h++);/* Delay */
        }
    }
    else if(obj == ' ' || obj == '=' || obj == '+' || obj == '*'){
        c->matriz[t.c_linha][t.c_coluna] = '=';
        for (timer = 0; timer < 4; timer++){
            PutPic(janela,aguatiro[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
        	for(h=0;h<25000000;h++);
        }
    }
    else{
        if(c->matriz[t.c_linha][t.c_coluna] == 'D'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
                			for(h=0;h<25000000;h++);
                		}
            afunda_destroyer(t.c_linha,t.c_coluna,c, barcomov, janela, explosions);
        }
        else if(c->matriz[t.c_linha][t.c_coluna] == 'C'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
                			for(h=0;h<25000000;h++);
                		}
            afunda_cruzador(t.c_linha,t.c_coluna,c, barcomov, janela, explosions);
        }
        else if(c->matriz[t.c_linha][t.c_coluna] == 'P'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
                			for(h=0;h<25000000;h++);
                		}
            afunda_porta_aviao(t.c_linha,t.c_coluna,c, barcomov, janela, explosions);
        }
        else if(c->matriz[t.c_linha][t.c_coluna] == 'H'){
            c->matriz[t.c_linha][t.c_coluna] = '*';
            for (timer = 0; timer < 13; timer++){
                			PutPic(janela,explosions[timer],0,0,32,32,(t.c_coluna)*32, t.c_linha * 32);
                			for(h=0;h<25000000;h++);
                		}
            afunda_hidro_aviao(t.c_linha,t.c_coluna,c, barcomov, janela, explosions);
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
void dispara_tiros(cpp c, PIC *barcomov, WINDOW *janela, PIC *explosions,PIC *aguatiro, PIC *barcoafunda, PIC *aguapassou){
	tiro t;
	int i;
	for(i = 0; i < 3; i++){
		t = coordenadas_tiro(c->linhas, c->colunas);
		if(identifica_alvo_atingido(c,t, barcomov, janela, explosions,aguatiro, barcoafunda, aguapassou)==-1) return;
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
barco posiciona_barco(cpp c,PIC *barcomov,WINDOW *janela){
	int col;
	printf("Insira a posição inicial do barco (coluna):\n");
	scanf("%d",&col);

	while(col-1 > c->colunas || c->matriz[0][col-1]!=' '){
		printf("Posição invalida. \n Insira a posição inicial do barco (coluna): \n");
		scanf("%d",&col);
	}

	barco b;
	b = malloc(sizeof(brc));
	b->name = 'B';
	b->linha = 0;
	b->coluna = col-1;
	if (col >=1 && col-1 < c->colunas) {
		c->matriz[0][col-1] = 'B';
		PutPic(janela,barcomov[2],0,0,32,32,(col-1)*32,0);

	}

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
	int gotit,i,j, /* variável que auxiliará no movimento do barco*/
        count = 0; /* variável que conta se o usuário executa um movimento inválido 3x seguidas*/
	cpp c = NULL; /* variável que servirá como campo(mapa) */
	barco b; /* variável do tipo barco que será o barco do usuário */
	char mov = ' '; /* variável que servirá para verificar a posição do campo durante a movimentação */
	srand((unsigned int) time(NULL));
	char *arq; /*variável para o caminho do arquivo contendo o campo */
	printf("Digite o caminho do arquivo mapa\n");
	scanf("%ms",&arq);

	c = leia_mapa(arq);

	/*******************************************Inicialização da janela **********************************/
	WINDOW *janela;
	PIC barcomov[4],barcopassou, explosions[13],aguatiro[4], barcoafunda[7], aguapassou[4];

	janela=InitGraph(32*c->colunas,32*c->linhas,"Bombardeio Naval");
	PIC agua;

	agua= ReadPic(janela,"AguaFundo.xpm",NULL);
	barcopassou=ReadPic(janela,"Sprites EP3/barcopassou.xpm",NULL);

	aguatiro[0]=ReadPic(janela,"Sprites EP3/Agua/Agua1.xpm",NULL);
	aguatiro[1]=ReadPic(janela,"Sprites EP3/Agua/Agua2.xpm",NULL);
	aguatiro[2]=ReadPic(janela,"Sprites EP3/Agua/Agua3.xpm",NULL);
	aguatiro[3]=ReadPic(janela,"Sprites EP3/Agua/Agua4.xpm",NULL);

	aguapassou[0]=ReadPic(janela,"Sprites EP3/Agua/Aguatiro1.xpm",NULL);
	aguapassou[1]=ReadPic(janela,"Sprites EP3/Agua/Aguatiro2.xpm",NULL);
	aguapassou[2]=ReadPic(janela,"Sprites EP3/Agua/Aguatiro3.xpm",NULL);
	aguapassou[3]=ReadPic(janela,"Sprites EP3/Agua/Aguatiro4.xpm",NULL);


	barcomov[0]=ReadPic(janela,"Sprites EP3/barcoE.xpm",NULL);
	barcomov[1]=ReadPic(janela,"Sprites EP3/barcoN.xpm",NULL);
	barcomov[2]=ReadPic(janela,"Sprites EP3/barcoS.xpm",NULL);
	barcomov[3]=ReadPic(janela,"Sprites EP3/barcoW.xpm",NULL);

	barcoafunda[0]=ReadPic(janela,"Sprites EP3/anihilation/afundando1.xpm",NULL);
	barcoafunda[1]=ReadPic(janela,"Sprites EP3/anihilation/afundando2.xpm",NULL);
	barcoafunda[2]=ReadPic(janela,"Sprites EP3/anihilation/afundando3.xpm",NULL);
	barcoafunda[3]=ReadPic(janela,"Sprites EP3/anihilation/afundando4.xpm",NULL);
	barcoafunda[4]=ReadPic(janela,"Sprites EP3/anihilation/afundando5.xpm",NULL);
	barcoafunda[5]=ReadPic(janela,"Sprites EP3/anihilation/afundando6.xpm",NULL);
	barcoafunda[6]=ReadPic(janela,"Sprites EP3/anihilation/afundando7.xpm",NULL);

	explosions[0]=ReadPic(janela,"Sprites EP3/Explosions/explosion1.xpm",NULL);
	explosions[1]=ReadPic(janela,"Sprites EP3/Explosions/explosion2.xpm",NULL);
	explosions[2]=ReadPic(janela,"Sprites EP3/Explosions/explosion3.xpm",NULL);
	explosions[3]=ReadPic(janela,"Sprites EP3/Explosions/explosion4.xpm",NULL);
	explosions[4]=ReadPic(janela,"Sprites EP3/Explosions/explosion5.xpm",NULL);
	explosions[5]=ReadPic(janela,"Sprites EP3/Explosions/explosion6.xpm",NULL);
	explosions[6]=ReadPic(janela,"Sprites EP3/Explosions/explosion7.xpm",NULL);
	explosions[7]=ReadPic(janela,"Sprites EP3/Explosions/explosion8.xpm",NULL);
	explosions[8]=ReadPic(janela,"Sprites EP3/Explosions/explosion9.xpm",NULL);
	explosions[9]=ReadPic(janela,"Sprites EP3/Explosions/explosion10.xpm",NULL);
	explosions[10]=ReadPic(janela,"Sprites EP3/Explosions/explosion11.xpm",NULL);
	explosions[11]=ReadPic(janela,"Sprites EP3/Explosions/explosion12.xpm",NULL);
	explosions[12]=ReadPic(janela,"Sprites EP3/Explosions/explosion13.xpm",NULL);

	for(i=0;i<32*c->linhas;i+=32){
		for(j=0;j<32*c->colunas;j+=32)
			PutPic(janela, agua, 0, 0, 32, 32, j, i);
	}

	/***********************************************************************8**********************************/

	if(c==0)
        return 0;

    printf("Movimentos do barco descritos a seguir:\n"
           "-a esquerda\n-s baixo\n-w cima\n"
           "-d direita\n");
	b = posiciona_barco(c,barcomov,janela);
	escreva_mapa_tela(c);
	escreva_mapa_arquivo("saida_ep.txt",c); /* manda o mapa c para saida_ep.txt */
	escreva_mapa_resposta("resposta_ep.txt",c); /* manda o mapa c para resposta_ep.txt */
	while(!acabou(c, b, count)){
		if(scanf(" %c", &mov));
		gotit = rema_barco (c, b, mov, barcomov, janela, barcopassou);

		if(gotit){
			count = 0;
			escreva_mapa_tela(c);
			printf("\n");
			dispara_tiros(c, barcomov, janela, explosions,aguatiro, barcoafunda, aguapassou);
			printf("\n");
			escreva_mapa_tela(c);
			escreva_mapa_arquivo("saida_ep.txt",c);
			escreva_mapa_resposta("resposta_ep.txt",c);
		}
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
