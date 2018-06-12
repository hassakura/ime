MAC 0329 - Álgebra Booleana e Aplicações

Exercício programa 3 (EP3)

Grupo:

Felipe de Oliveira Campos Moreira - nUSP: 8516347
Gabriel Baptista                  - nUSP: 8941300
Hélio Hideki Assakura Moreira     - nUSP: 8941064
Pedro Ivo Siqueira Nepomuceno     - nUSP: 8941321

Para o desenvolvimento desta etapa do projeto utilizamos o logisim. Dentro do arquivo dividimos o programa nas seguintes partes:
Main, PC, CTRL, protector,First, FF clock, Selector MUX, Condicional, ALU, Selector OP, Acumulator, I/O Controller, Start, Selector MUX jmpC, selector Acum.

Main:
No main há expostos a memória RAM e o IR, dentro da RAM há expostos os números com os dados do programa, os quais serão processados pelo programa.

A memória RAM tem fios, que saem dela para o componente, ligados ao IR e em CTRL e também há fios, que entram nela, ligados 
a CTRL e PC.
IR recebe fios de CTRL e da memória RAM e tem como fio de saída para CTRL.
A ALU é a o local aonde é a realizada as operações com dois dados.
CTRL recebe fios de basicamente todos subcircuitos do programa e ele é responsável por controlar as instruções,dados,
controle dos tics dos clocks,etc

PC:
PC foi implementado usando flip-flops T e tem por entrada e saída números de 8 bits é um registrador especial, que
armazena um endereço de memória e também possui uma entrada chamada count up, que ao receber um pulso incrementa 
o seu valor em uma unidade.

First:
First serve para contar se é o primeiro ciclo do computador, o qual deve manter IR e acumulador zerados.

FF Clock:
FF clock foi implementado usando dois flip-flops T de tal maneira que ao receber 1 no in temos uma sequência de outputs
do tipo O110.

Selector MUX:
Selector MUX serve para auxilir o CTRL que recebe a instrução e devolve 1 bit para o ser o seletor do MUX e do DMX.

Protector:
Protector é implementado para auxiliar o CTRL na parte em que automatizou-se o circuito utilizando o sistema de clocks.

ALU:
Local no qual o programa recebe dois dados, e de acordo com a operação selecionada irá prover um resultado, passando adiante no programa.

Selector OP:
Selector que verifica qual operação será realizada, caso o comando a ser executada seja uma operação artimética.

Selector MUX JmpC:
Selector que descobre qual o salto que está sendo executado, e de acordo com a saída, seleciona um mux correspondente.


Selector Acum:
Quando seta 1 quando é necessário colocar uma conta da ALU para o acumulador e seta 9 quando for necessário colocar o que está na memória para o acumulador direto


