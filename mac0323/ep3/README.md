<div id="content">
<h1 class="title">MAC323 Algoritmos e estruturas de dados II</h1>

<div id="outline-container-sec-1" class="outline-2">
<h2 id="sec-1">Exercício-Programa 3</h2>
<div class="outline-text-2" id="text-1">
</div><div id="outline-container-sec-1-1" class="outline-3">
<h3 id="sec-1-1">Variante do Web Exercise 4.1.5 de Algs4th</h3>
<div class="outline-text-3" id="text-1-1">
<ul class="org-ul">
<li>Estude o <i>Web Exercise</i> 4.1.5 (Perfect maze) de Algs4th, disponível
em <a href="http://algs4.cs.princeton.edu/41undirected/">http://algs4.cs.princeton.edu/41undirected/</a>.
</li>

<li>Altere a classe <code>Maze.java</code> para que ela tenha o seguinte
comportamento.

<ul class="org-ul">
<li>O usuário executará seu programa dando um inteiro <code>N</code> na linha de
comando.  Alternativamente, uma semente <code>seed</code> para o gerador de
números aleatórios também será dada na linha de comando:
<pre>
$ java-algs4 Maze N [seed]
</pre>
<p>
Naturalmente, o labirinto gerado pelo seu programa deve ser o
mesmo quando executado com a mesma semente.  Uma vez gerado, seu
programa deve desenhar o labirinto em uma janela.
</p>
</li>
<li>O usuário dará na entrada padrão uma seqüência de pares
origem/destino.  Por exemplo, poderíamos ter 
<pre>
$ cat st.txt
 1  1 30 30
 1 30 30  1
 1 15 30 15
15  1 15 30
 5 20 25 15
15 15 17 17
$ java-algs4 Maze 30 20150527 < st.txt 
</pre>
<p>
A linha <code>1 1 30 30</code> indica que queremos um caminho da posição <code>(1,
    1)</code> à posição <code>(30, 30)</code>.  Na execução acima, seu programa deve
desenhar o labirinto, e deve então resolver cada um dos 6 pares
origem/destino em <code>st.txt</code>.  Para cada par, seu programa deve
desenhar a solução, da mesma forma que faz a versão original de
<code>Maze.java</code>.
</p>

<p>
Por exemplo, uma execução de seu programa poderia gerar o seguinte
labirinto: 
</p>
<img src="../img/60x60.jpg" alt="Custo amortizado de put()" /> 
<p>
Se o usuário der o par origem/destino <code>(1, 1)/(60, 60)</code>, seu
programa geraria a seguinte solução e figura:
</p>
<img src="../img/60x60a.jpg" alt="Custo amortizado de put()" /> 
<p>
Para o par origem/destino <code>(10, 55)/(45, 10)</code>, seu
programa geraria a seguinte solução e figura: 
</p>
<img src="../img/60x60b.jpg" alt="Custo amortizado de put()" /> 
</li>
</ul>
</li>

<li><b>Importante.</b> Seu programa deve ser tal que, para cada par
origem/destino, o tempo gasto pelo seu programa é <i>proporcional ao
comprimento do caminho entre a origem e o destino</i>.  Diga por que
seu programa satisfaz este requisito.  (Note que, em particular, seu
programa não pode fazer uma busca em largura ou uma busca em
profundidade para cada par origem/destino.)
</li>

<li><i>Sugestão.</i>  Ao criar o labirinto, armazene informações adicionais
(por exemplo, não seria útil ter algo como <code>edgeTo[]</code>?).
</li>
</ul>

<hr />
<p>
Página <a href="../index.html">principal</a> de MAC323, 1o. semestre de 2015
</p>
<hr />
</div>
</div>
</div>
</div>
<div id="postamble" class="status">
<p class="author">Author: <a href="https://www.ime.usp.br/~yoshi/">Yoshiharu Kohayakawa</a></p>
<p class="email">Email: <a href="mailto:yoshi@ime.usp.br">yoshi@ime.usp.br</a></p>
<p class="date">Created: 2015-06-05 Fri 11:04</p>
<p class="creator"><a href="http://www.gnu.org/software/emacs/">Emacs</a> 24.4.51.2 (<a href="http://orgmode.org">Org</a> mode 8.2.10)</p>
<p class="validation"><a href="http://validator.w3.org/check?uri=referer">Validate</a></p>
</div>