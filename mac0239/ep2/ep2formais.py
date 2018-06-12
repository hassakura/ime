# Gabriel Baptista									8941300
#	Helio Hideki Assakura Moreira			8941064

from pyeda.inter import *
from parser import *


# A funcao recebe uma lista de caminhos paths e retorna um dict
# com os caminhos organizados por indices, na forma:
#		No origem -> [Nos destinos]

def c_graph(paths):
	graph = {}
	for path in paths:
		if (path[0] in graph):
			graph[path[0]].append(path[1])
		else:
			graph[path[0]] = [path[1]]
	return graph

# A funcao recebe uma lista com os estados do modelo, e retorna
# um dict com as bddvars correspondentes, com o mesmo nome,
# na forma:
# 		estado -> bddvar

def c_variables(states):
	l_variables = []
	dict_bddvars = {}
	for item in states:
		if (type(item) == tuple):
			for step in item:
				if (step not in l_variables): 
					l_variables.append(step)
		else:
			if (item not in l_variables): 
					l_variables.append(item)
	for variable in l_variables:
		dict_bddvars[variable] = (bddvar(variable))
	return dict_bddvars

# A funcao recebe um dict dict_bddvars com as variaveis do modelo
# e uma lista states com os estados, e retorna um dict com as
# formulas correspondentes de cada estado, na forma:
#			estado -> formula

def c_formulas(dict_bddvars, states):
	dict_formulas = {}
	for state in states:
		formula = 1
		if (type(state) == tuple):
			for variable in dict_bddvars:
				if variable in state:
					formula = formula & dict_bddvars[variable]
				else:
					formula = formula & ~dict_bddvars[variable]
		else:
			for variable in dict_bddvars:
				if variable == state: 
					formula = formula & dict_bddvars[variable]
				else:
					formula = formula & ~dict_bddvars[variable]
		dict_formulas[state] = formula
	return dict_formulas

# A funcao recebe um grafo graph, um dict dict_formulas_primed com as
# formulas dos estados futuros (X') e duas listas, states e states_primed,
# que correspondem as listas de estados e de estados futuros, e devolve
# a formula de transicao do modelo, B->

def c_formula_transitions(graph, dict_formulas_primed, states, states_primed):
	formula = 0
	for node in graph:
		for next_node in graph[node]:
			formula = formula | (dict_formulas[states[node]] & dict_formulas_primed[states_primed[next_node]])
	return formula

# Funcao responsavel pelo calculo da Pre-imagem Fraca, recebendo um bdd 
# X, e retornando todos os estados que apontam para o estado alvo

def pre_imagem_fraca(X):
	X = expr(str(bdd2expr(X)).replace("x", "xp"))
	soluction = expr2bdd(X) & formula_transitions
	for x in dict_bddvars_primed.values():
		soluction = soluction.restrict({x:0}) | soluction.restrict({x:1})
	return soluction

# Funcao que calcula a Pre-imagem forte, por meio da Pre-imagem fraca

def pre_imagem_forte(X):
		return (S & ~pre_imagem_fraca(S & ~X))

#	Funcao principal do EP. A construção foi feita de acordo com o algoritmo
# apresentado no enunciado, assim como as funcoes SAT_EX, SAT_AF e SAT_EU
	
def SAT(phi):
	if (phi.kind == "1"): return S
	elif (phi.kind == "0"): return 0
	elif (phi.kind[0] == 'x'): 
		return dict_formulas[phi.kind]
	elif (phi.kind == '-'): return (S & ~(SAT(phi.childs[0])))
	elif (phi.kind == '*'): return SAT(phi.childs[0]) & SAT(phi.childs[1])
	elif (phi.kind == '+'): return SAT(phi.childs[0]) | SAT(phi.childs[1])
	elif (phi.kind == 'AX'): return SAT(CTLtree('- EX -'+str(phi.childs[0])))
	elif (phi.kind == 'EX'): return SAT_EX(phi)
	elif (phi.kind == 'AU'): return SAT(CTLtree('- +(EU(- '+str(phi.childs[1])+')(*(- '+str(phi.childs[0])+')(- '+str(phi.childs[1])+')))(EG(- '+str(phi.childs[1])+'))'))
	elif (phi.kind == 'EU'):
		return SAT_EU(phi.childs[0],phi.childs[1])	
	elif (phi.kind == 'EF'): return SAT(CTLtree('EU(1)('+str(phi.childs[0])+')'))
	elif (phi.kind == 'EG'): return SAT(CTLtree('-AF-'+str(phi.childs[0])))
	elif (phi.kind == 'AF'): return SAT_AF(phi)
	elif (phi.kind == 'AG'): return SAT(CTLtree('-EF-'+str(phi.childs[0])))
	else : print()

def SAT_EX(phi):
	X = SAT(phi)
	Y = pre_imagem_fraca(X)
	return Y

def SAT_AF(phi):
	X = S
	Y = SAT(phi)
	while (X != Y):
		X = Y 
		Y = Y & pre_imagem_forte(phi)
	return Y

def SAT_EU(phi1, phi2):
	W = SAT(phi1)
	X = S
	Y = SAT(phi2)
	while (X != Y):
		X = Y
		Y = Y | (W & pre_imagem_fraca(Y))
	return Y

#	A funcao recebe um BDD Bdd_solution com a solucao do problema, e o indice
# do estado a ser considerado, e imprime todos os estados que satisfazem a
#	formula, alem de verificar se o estado solicitado tambem satisfaz a formula

def solutions (Bdd_solution, k_state):
	sol_states = []
	for formula in dict_formulas:
		solucoes = list(dict_formulas[formula].satisfy_all())
		for sol in solucoes:
			if (Bdd_solution.restrict(sol)):
				sol_states.append(formula)
	print ('Estados solucoes: ', sol_states)
	if k_state in sol_states:
		print ('O estado ', k_state,' SATISFAZ a formula')
	else:
		print ('O estado ', k_state,' NAO SATISFAZ a formula')


global dict_bddvars, dict_formulas, dict_bddvars_primed, dict_formulas_primed
global formula_transitions
global S

len_states = int(input())
paths = eval(input())
str_states = input()
states_primed = eval(str_states.replace('x','xp'))
states = eval(str_states)
phi = CTLtree(input())
k_state = eval(input())
graph = c_graph(paths)

#	Criacao dos dicts, para serem usados na resolucao do problema
dict_bddvars = c_variables(states)
dict_formulas = c_formulas(dict_bddvars, states)
dict_bddvars_primed = c_variables(states_primed)
dict_formulas_primed = c_formulas(dict_bddvars_primed, states_primed)

#	Criacao da formula das transicoes
formula_transitions = c_formula_transitions(graph, dict_formulas_primed, states, states_primed)

#	Criacao da formula geral do modelo
S = 0
for formula in dict_formulas.values():
	S = S | formula

#	Solucao do problema
solutions (SAT(phi), k_state)