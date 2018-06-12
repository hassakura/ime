;*******************************************************;
;	Nome: Helio Hideki Assakura Moreira		;
;	NUSP: 8941064					;
;	Exercicio Programa 1				;
;*******************************************************;

section .data
	pula 	db	0xa
	len3 	equ	$ - pula
	
section .bss
	p 	resd 1 ;variavel com o numero atual a verificar
	nume  	resb 5
	cont   	resd  1 

section .text
	global _start
	global _isPrime
	global _int2str
	
;*******************************************************************************************************;
	
_isPrime:

	;Atribuicao dos valores iniciais. Seja:
		;p = numero atual a verificar se eh primo
		;i = contador que percorre todos os numeros 1<i<p

	push	rbp	
	mov	rbp, rsp	
	mov 	dword [rbp-20], edi 
	mov 	dword [rbp-8],01
	mov 	dword [rbp-4], 00
	mov 	ecx, dword [rbp-8]
	mov 	ebx, dword [rbp-4]
	jmp 	L1
	
L1:	
	;Primeira verificacao, que consiste em ver se todos os numeros <= p
	;foram visitados.
	
	cmp 	ecx, dword [rbp-20]
	jle 	L2		
	jg 	CONTIN
	
L2:	
	; Segunda verificacao, para ver se ja nao foi achado um multiplo de p
	; != 1 e != p
	
	cmp 	dword[rbp-4], 02
	jle	COND1	
	jg 	CONTIN	
	
COND1:  
	;Condicional que verifica se p eh multiplo de algum numero
	;i++
	
	mov 	eax, dword [rbp-20]	;ecx = p
	mov 	edx, 00
	div 	dword [rbp-8]    ;Divide p por i
	add 	dword [rbp-8], 01	;Passa i para o proximo numero
	mov 	ecx, dword [rbp-8]	
	test 	edx, edx	;verifica se p % i == 0
	jz 	CONDE	;Verdade, adiciona 1 ao contador de multiplos de p
	jnz 	L1	;Falso, vai para o proximo numero
	
	
CONTIN: 	
	;Alguma das verificacoes em L1 ou L2 foi falsa. Agora verificamos
	;se ele tem mais de 2 multiplos ou se ele ja conferiu todos os numeros	

	cmp 	dword [rbp-4], 02
	jg 	RET0		
	jle 	RET1

CONDE:	
	inc 	dword [rbp-4]
	mov 	ebx, dword [rbp-4]
	jmp 	L1
	
RET0: 	
	;O numero nao eh primo
	
	mov 	rsi, 0 
	jmp 	fim
	
RET1: 
	;O numero eh primo
	
	mov 	rsi, 1
        jmp 	fim
        
fim:
	pop	rbp
	ret

;*******************************************************************************************************;

	;Esse metodo consiste em dividir o numero sucessivamente por 10, e assim, conseguir converter
	;char por char para ASCII. Apos a conversao, ha a saida do numero para o usuario

_int2str:
	mov 	esi, nume     
	add 	esi, 4           ; A quantidade de digitos nao passa de 5. Olhamos para o ultimo digito
	xor 	edx, edx         
	mov 	dword [cont], 0   ; Inicia o contador de digitos em 0
	
.div10:  
	mov 	ebx, 10          ;Inicia ebx com 10, para as sucessivas divisoes 
	div 	ebx             
	add	edx,'0'         ; Converte para ASCII
	mov	byte[esi], dl   
	dec	esi             ; Pula para a proxima posicao
	xor	edx, edx        
	inc	dword [cont]    
	cmp	eax, 0          ;Comparacao feita para saber se todos os digitos foram olhados
	jne	.div10
	   	
	inc	esi             ; Chegou em 0, aponta novamente para o inicio
	mov	ecx, esi        ; Saida do numero para o usuario
	mov	edx, [cont]     
	mov	eax, 4  	
	mov	ebx, 1
	int	0x80
	
	ret
     
	
;*******************************************************************************************************;	

	;Verificacao dos numeros < 1000. O numero 1 nao eh considerado primo.
	;Entre 2 e 4, todos os numeros sao verificados. A partir do 5, podemos
	;considerar apenas os impares.
	
_start:	
	;Declaracao das variaveis e inicializacao da pilha
	
	push	rbp
	mov	rbp, rsp
	mov 	dword [p], 2
	jmp 	.M1
	
.M1:	
	;Conferindo se p nao passou de 1000
	
	cmp 	dword [p], 1000
	jle	 .M2
	jg 	.fimM
	
.M2:
	;Chamada de _isPrime. Caso seja primo, ele imprime esse numero
	;na tela. Caso nao, ele eh apenas desconsiderado
	
	mov 	eax, dword [p]
	mov 	edi, eax
	call    _isPrime
	cmp	rsi, 1
	je	.isP1
	jl	.isP0

.isP1:
	;O numero eh primo, entao ha a conversao dele para ASCII para a saida,
	;e para deixar a saida mais limpa, eh pulado uma linha
	
	mov 	eax, dword [p]
	call 	_int2str
	mov 	ecx, pula	;Pula linha       
        mov 	edx, len3     	
        mov 	eax, 4  	
        mov 	ebx, 1
        int 	0x80
        cmp 	dword [p], 5	;Verificacao para o caso de p < 5
        jl	.1to4
	add	dword [p], 2	;p >= 5, podemos acrescer 2 em p 
        jmp 	.M1
        
.1to4:
	;Caso em que p < 5, ou seja, todos os numeros devem ser verificados
	
	add	dword [p], 1
	jmp 	.M1
        
.isP0:
	;O numero nao eh primo, entao somente passamos para o proximo numero
	;a ser verificado
	
	cmp 	dword [p], 5
        jl 	.1to4
	add	dword [p], 2
        jmp 	.M1
        
.fimM:
	;Fim do programa
	
	mov     ebx,0   
        mov     eax,1
        int     0x80 
