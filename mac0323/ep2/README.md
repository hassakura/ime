<div id="content">
<h1 class="title">MAC323 Algoritmos e estruturas de dados II</h1>

<div id="outline-container-sec-1" class="outline-2">
<h2 id="sec-1">Exercício-Programa 2</h2>
</div>

<div id="outline-container-sec-2" class="outline-2">
<h2 id="sec-2">Variante simples do Exercício 4.4.8 de IntroCS</h2>
<div class="outline-text-2" id="text-2">
<ul class="org-ul">
<li>Você deve inicialmente recordar o Creative exercise 4.4.8 (<i>IP
lookup by country</i>) de IntroCS, que você já fez.
</li>

<li>Dessa vez, você deve usar o arquivo <a href="../../sandbox/Data/dbip-city-2015-05h.csv">dbip-city-2015-05h.csv</a> (que tem
4920676 linhas), de <a href="https://db-ip.com/db/">https://db-ip.com/db/</a> ("IP address to city (low
resolution)").
</li>

<li>Seu programa deve receber o nome de arquivo dbip-city-2015-05h.csv
na linha de comando.  Se houver apenas esse argumento, seu programa
deve receber uma lista de endereços IP na entrada padrão.  Para cada
entrada padrão, seu programa deve imprimir as informações
encontradas em dbip-city-2015-05h.csv, no formato do exemplo abaixo.

<ul class="org-ul">
<li>Exemplo:
</li>
</ul>
</li>
</ul>
<pre>
<p>
$ cat IPs 
143.107.45.22
143.108.10.6
200.130.33.22
140.180.223.42
169.229.216.200
131.111.59.156
210.152.135.178
195.220.216.32
188.93.105.22
$ java-algs4 IPLookUpDeLuxe dbip-city-2015-05h.csv &lt; IPs
Miami, Mato Grosso Do Sul, BR
Miami, Mato Grosso Do Sul, BR
Palmas, Tocantins, BR
Princeton, New Jersey, US
San Francisco, California, US
Cambridge, Cambridgeshire, GB
Minato, Tokyo, JP
Paris, Île-de-France, FR
Moscow, Moscow, RU
</p>
</pre>
<p>
(Você pode notar que o banco de dados não é completamente sem erros.)  
</p>

<ul class="org-ul">
<li>Se o usuário executar seu programa com mais de um argumento na linha
de comando, ele deve ler da entrada padrão um arquivo como <a href="../../sandbox/Data/ssh.log">este</a>.
Este arquivo foi extraído do arquivo <code>system.log</code> de um sistema que
permite acesso remoto por <code>ssh</code>.  Esse arquivo mostra tentativas de
acesso ilícito de máquinas diversas.  Seu programa deve extrair os
números IPs de onde vêm essas tentativas de acesso ilícito e deve
usar o arquivo dbip-city-2015-05h.csv para localizar a origem
geográfica desses acessos.  Cada local de origem deve ser impresso
uma única vez, junto com o número de tentativas de acesso daquele
local.  Esta lista deve ser impressa ordenada pelo número de
tentativas de acesso, em ordem decrescente.

<ul class="org-ul">
<li>Exemplo:
</li>
</ul>
</li>
</ul>
<pre>
<p>
$ cat ssh.log
May 27 00:01:32 machine.ime.usp.br <code>sshd[33205]</code>: Invalid user adam from 175.126.111.86
May 27 00:09:00 machine.ime.usp.br <code>sshd[33213]</code>: Invalid user carol from 175.126.111.86
May 27 00:12:57 machine.ime.usp.br <code>sshd[33218]</code>: Invalid user chloe from 175.126.111.86
May 27 00:17:04 machine.ime.usp.br <code>sshd[33223]</code>: Invalid user chloe from 175.126.111.86
&#x2026;
$ java-algs4 IPLookUpDeLuxe dbip-city-2015-05h.csv - &lt; ssh.log
1672 Seoul, Seoul, KR
718 Phoenix, Arizona, US
316 Kiev, Kyiv city, UA
269 Tunis, Tunis, TN
178 Nanchang, Jiangxi, CN
&#x2026;
</p>
</pre>

<ul class="org-ul">
<li>Você deve implementar sua solução com <code>ST.java</code>, <code>RedBlackBST.java</code>
e <code>BST.java</code> (são portanto três implementações distintas).  Compare
o desempenho dessas três implementações.
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
<div id="postamble" class="status">
<p class="author">Author: <a href="https://www.ime.usp.br/~yoshi/">Yoshiharu Kohayakawa</a></p>
<p class="email">Email: <a href="mailto:yoshi@ime.usp.br">yoshi@ime.usp.br</a></p>
<p class="date">Created: 2015-06-05 Fri 11:04</p>
<p class="creator"><a href="http://www.gnu.org/software/emacs/">Emacs</a> 24.4.51.2 (<a href="http://orgmode.org">Org</a> mode 8.2.10)</p>
<p class="validation"><a href="http://validator.w3.org/check?uri=referer">Validate</a></p>
</div>