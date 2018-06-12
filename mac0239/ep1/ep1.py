#	Gabriel Baptista				8941300
#	Helio Hideki Assakura Moreira	8941064

from pyeda.inter import *

def expression_lines (x):

#	A funcao recebe as variaveis de x e retorna a expressao correspondente
#	ao nao ataque das rainhas nas linhas e a existencia de uma rainha na
#	linha.

	for i in range (0, n):
		first_expression = x[i, 0]
		#Montando a clausula para a existencia de uma rainha na linha
		for h in range (1, n):
			first_expression = first_expression | x[i, h]
		if (i == 0):
			full_expression = first_expression
		else:
			full_expression = full_expression & first_expression
		#Colocando as possibilidades de ataque pra cada linha
		for j in range (0, n - 1):
			for k in range (j + 1, n):
				full_expression = full_expression & (~x[i,j] | ~x[i,k])
	return full_expression;

def expression_columns (x):

#	A funcao recebe as variaveis de x e retorna a expressao correspondente
#	ao nao ataque das rainhas nas colunas e a existencia de uma rainha na
#	coluna.

	for j in range (0, n):
		first_expression = x[0, j]
		#Montando a clausula para a existencia de uma rainha na coluna
		for h in range (1, n):
			first_expression = first_expression | x[h, j]
		if (j == 0):
			full_expression = first_expression
		else:
			full_expression = full_expression & first_expression
		#Colocando as possibilidades de ataque pra cada coluna
		for i in range (0, n - 1):
			for k in range (i + 1, n):
				full_expression = full_expression & (~x[i,j] | ~x[k,j])
	return full_expression;

def expression_diagonal (x, n, full_expression):

#	A funcao recebe as exprvars de x, o tamanho do tabuleiro e a expressao parcialmente
#	montada, e coloca na expressao todas as combinacoes possiveis duas a duas de rainhas
#	que podem se atacar nas diagonais.

	# 	Partindo do penultimo elemento da primeira coluna, percorre de cima para baixo,
	#	a partir de cada elemento da coluna, indo da esquerda para a direita, montando
	#	as possiveis combinacoes de ataque das rainhas.

	for inicio_i in range (n - 2, -1, -1):
		i_fixo = inicio_i
		j_fixo = 0
		while (i_fixo < n - 1):
			i_prox = i_fixo + 1
			j_prox = j_fixo + 1
			while (i_prox < n):
				full_expression = full_expression & (~x[i_fixo, j_fixo] | ~x[i_prox, j_prox])
				i_prox += 1
				j_prox += 1
			i_fixo += 1
			j_fixo += 1

	# 	Partindo do segundo elemento da primeira linha, percorre da esquerda para a direita,
	#	a partir de cada elemento da linha, indo de cima para baixo, montando as possiveis 
	#	combinacoes de ataque das rainhas.

	for inicio_j in range (1, n - 1):
		i_fixo = 0
		j_fixo = inicio_j
		while (j_fixo < n - 1):
			i_prox = i_fixo + 1
			j_prox = j_fixo + 1
			while (j_prox < n):
				full_expression = full_expression & (~x[i_fixo, j_fixo] | ~x[i_prox, j_prox])
				i_prox += 1
				j_prox += 1
			i_fixo += 1
			j_fixo += 1

	# 	Partindo do penultimo elemento da ultima coluna, percorre de cima para baixo,
	#	a partir de cada elemento da coluna, indo da direita para a esquerda, montando
	#	as possiveis combinacoes de ataque das rainhas.

	for fim_i in range (n - 2, -1, -1):
		i_fixo = fim_i
		j_fixo = n - 1
		while (i_fixo < n - 1):
			i_prox = i_fixo + 1
			j_prox = j_fixo - 1
			while (i_prox < n):
				full_expression = full_expression & (~x[i_fixo, j_fixo] | ~x[i_prox, j_prox])
				i_prox += 1
				j_prox -= 1
			i_fixo += 1
			j_fixo -= 1

	# 	Partindo do segundo elemento da primeira linha, percorre da direita para a esqueda,
	#	a partir de cada elemento da linha, indo de cima para baixo, montando as possiveis 
	#	combinacoes de ataque das rainhas.

	for fim_j in range (n - 2, 0, -1):
		i_fixo = 0
		j_fixo = fim_j
		while (j_fixo > 0):
			i_prox = i_fixo + 1
			j_prox = j_fixo - 1
			while (j_prox > -1):
				full_expression = full_expression & (~x[i_fixo, j_fixo] | ~x[i_prox, j_prox])
				i_prox += 1
				j_prox -= 1
			i_fixo += 1
			j_fixo -= 1

	return full_expression;



def print_solution (x, n, full_expression):

#	Recebe a expressão/bdd x e imprime o tabuleiro correspondente
#	à uma das respostas, caso o problema seja SAT. Caso contrario,
#	diz que eh UNSAT

	y = full_expression.satisfy_one()
	if (y != None):
		for i in range (0, n):
			for j in range (0, n):
				if (x[i,j].is_one()): print (' Q ', end=""),
				elif (y[x[i,j]]): print (' Q ', end=""),
				else: print (' . ', end=""),
			print ('');
		print ('\n')
	else:
		print("UNSAT")

n = int(input('N: '))
x = exprvars("r", n, n)
x_bdd = bddvars("r", n, n)
k = int(input('K: '))
for i in range (0, k):
	x_rainha = int(input('Rainha X: '))
	y_rainha = int(input('Rainha Y: '))
	x = x.restrict({x[x_rainha, y_rainha]: 1})
	x_bdd = x_bdd.restrict({x_bdd[x_rainha, y_rainha]: 1})

full_expression = expression_lines(x) & expression_columns(x)
full_expression = expression_diagonal(x, n, full_expression)
mybdd = expr2bdd(full_expression)
print_solution(x_bdd, n, mybdd)

