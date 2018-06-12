<div id="content">
<h1 class="title">MAC323 Algoritmos e estruturas de dados II</h1>

<div id="outline-container-sec-1" class="outline-2">
<h2 id="sec-1">Exercício-Programa 4 (Enunciado completo)</h2>
</div>

<div id="outline-container-sec-2" class="outline-2">
<h2 id="sec-2">Um sistema de navegação primitivo</h2>
<div class="outline-text-2" id="text-2">
<ul class="org-ul">
<li>Neste EP, você produzirá um sistema de navegação simples (um
"GPS").
</li>

<li>Os dados geográficos que você usará vêm do projeto <a href="https://www.openstreetmap.org">OpenStreetMap</a>
(OSM).  Leia um pouco sobre esse projeto na <a href="https://en.wikipedia.org/wiki/OpenStreetMap">entrada</a> correspondente
da Wikipedia.  Naturalmente, veja também a <a href="https://www.openstreetmap.org/about">página</a> da própria OSM.
</li>

<li>O produto final que você deve produzir é um sistema que, dados dois
pontos <i>s</i> e <i>t</i>, encontra um caminho mais curto de <i>s</i> para <i>t</i>.
</li>
</ul>
</div>

<div id="outline-container-sec-2-1" class="outline-3">
<h3 id="sec-2-1">Como proceder</h3>
<div class="outline-text-3" id="text-2-1">
</div><div id="outline-container-sec-2-1-1" class="outline-4">
<h4 id="sec-2-1-1">Arquivos XML de mapas OSM</h4>
<div class="outline-text-4" id="text-2-1-1">
<ul class="org-ul">
<li>Se você acessar a URL 

<p>
<a href="http://www.openstreetmap.org/export?bbox=-46.7425,-23.5651,-46.7207,-23.5523">http://www.openstreetmap.org/export?bbox=-46.7425,-23.5651,-46.7207,-23.5523</a>,
</p>

<p>
e usar a função "export", você pode obter um arquivo XML com as
informações contidas nesse mapa, como <a href="../../sandbox/Data/EP4/USP/map.osm-USP.xml">esse arquivo</a> (seu arquivo pode
ser levemente diferente).
</p>
</li>

<li>O arquivo XML do exemplo acima pode ser processado para se extrair
os pontos de referência (<code>nodes</code>), com informações geográficas (isto
é, latitude e longitude desses pontos de referência).  Você terá de
ler um pouco sobre o formato desses arquivos XML gerados pelo OSM;
veja, por exemplo, 

<p>
<a href="http://wiki.openstreetmap.org/wiki/OSM_XML">http://wiki.openstreetmap.org/wiki/OSM_XML</a>.
</p>

<p>
Extraindo os nós com suas localizações geométricas, obtemos, a
partir de nosso arquivo XML acima, <a href="../../sandbox/Data/EP4/USP/USP.vll">esse arquivo</a> (nesse arquivo, cada
linha tem o formato <code>&lt;node id&gt;</code> <code>&lt;latitude&gt;</code> <code>&lt;longitude&gt;</code>).  Usando
uma variante de <code>PlotFilter.java</code> de S&amp;W, você pode produzir imagens como
essa: 
</p>

<p>
<img src="../../sandbox/Data/EP4/USP/USPNodes.png" alt="nodes USP map" /> 
</p>
</li>

<li>Boas formas de se explorar o conteúdo de mapas OSM são descritas em

<p>
<a href="http://wiki.openstreetmap.org/wiki/Browsing">http://wiki.openstreetmap.org/wiki/Browsing</a>
</p>
</li>

<li>Você terá de calcular as distâncias entre <code>nodes</code> em um mapa.  Para
tanto, você precisará saber como determinar a distância entre dois
pontos dados pelas suas latitudes e longitudes.  Aqui, vamos supor
que a terra é uma esfera perfeita, com raio de 6371 km.  Para esta
parte do EP, veja

<p>
<a href="http://www.movable-type.co.uk/scripts/latlong.html">http://www.movable-type.co.uk/scripts/latlong.html</a>
</p>

<p>
Experimente usar a interface da página acima para calcular a
distância entre os seguintes dois pontos:
</p>

<p>
<a href="http://www.openstreetmap.org/?&amp;mlat=-23.55727&amp;mlon=-46.73398#map=17/-23.56/-46.73">http://www.openstreetmap.org/?&amp;mlat=-23.55727&amp;mlon=-46.73398#map=17/-23.56/-46.73</a>
</p>

<p>
<a href="http://www.openstreetmap.org/?&amp;mlat=-23.5633&amp;mlon=-46.7216#map=17/-23.56/-46.73">http://www.openstreetmap.org/?&amp;mlat=-23.5633&amp;mlon=-46.7216#map=17/-23.56/-46.73</a>
</p>

<p>
Os pontos acima tem latitudes e longitudes dadas em <code>mlat</code> e
<code>mlon</code>.  
</p>

<ul class="org-ul">
<li><b>Observação.</b> Na verdade, supor que a terra é plana já seria
suficiente neste EP.  <i>Você pode fazer isso.</i>
</li>
</ul>
</li>
</ul>
</div>
</div>

<div id="outline-container-sec-2-1-2" class="outline-4">
<h4 id="sec-2-1-2">Grafos dirigidos a partir de arquivos XML de OSM</h4>
<div class="outline-text-4" id="text-2-1-2">
<ul class="org-ul">
<li>A organização das ruas estão codificadas em mapas OSM.  Tal
informação é exportada nos arquivos XML correspondentes.  
</li>

<li><i>Para simplificar este EP, vamos usar um programa já pronto para
extrair essa informação dos arquivos XML.</i>  Tal programa está
escrito em <code>Python</code> e usa <code>NetworkX</code> (que é, aliás, um sistema que
pode ser de seu interesse).  
</li>

<li>Instale em seu sistema <code>NetworkX</code>:

<p>
<a href="http://networkx.github.io">http://networkx.github.io</a>
</p>

<p>
Você precisará também de um programa chamado <code>gistfile1.py</code>.  Use
<a href="../../sandbox/Data/EP4/gistfile1.py">essa versão</a>, que é uma versão levemente alterada da versão original:
</p>

<p>
<a href="https://gist.github.com/aflaxman/287370/">https://gist.github.com/aflaxman/287370/</a>
</p>
</li>

<li>Para facilitar o uso de <code>gistfile1.py</code>, use também <a href="../../sandbox/Data/EP4/xmltoadj.py"><code>xmltoadj.py</code></a>.  Eis
um exemplo de uso:
<pre>
$ python xmltoadj.py map.osm-USP.xml USP.adjlist
</pre>
<p>
O script <code>xmltoadj.py</code> lê o arquivo <a href="../../sandbox/Data/EP4/USP/map.osm-USP.xml"><code>map.osm-USP.xml</code></a> e produz o
arquivo <a href="../../sandbox/Data/EP4/USP/USP.adjlist"><code>USP.adjlist</code></a>. 
</p>
</li>

<li>O arquivo <code>USP.adjlist</code> tem um formato natural: por exemplo, uma
linha da forma <code>a b c</code> significa que o vértice <code>a</code> manda arcos para
<code>b</code> e <code>c</code>.  Veja

<p>
<a href="http://networkx.github.io/documentation/latest/reference/readwrite.adjlist.html#format">http://networkx.github.io/documentation/latest/reference/readwrite.adjlist.html#format</a>
</p>

<p>
Note que os nomes dos vértices que aparecem em <code>USP.adjlist</code> são os
<code>id</code> dos <code>nodes</code> no arquivo XML (entretanto, nem todo <code>node</code> no
arquivo XML ocorre no grafo).
</p>
</li>

<li>O arquivo <code>USP.adjlist</code> pode ser lido usando-se <code>SymbolDigraph.java</code>
(na verdade, o cabeçalho no arquivo <code>USP.adjlist</code> precisa ser
removido).
</li>

<li>Eis uma figura do grafo em <code>USP.adjlist</code>: 

<p>
<img src="../../sandbox/Data/EP4/USP/USPGraph.png" alt="USP Graph" /> 
</p>

<p>
Esse grafo tem 1271 vértices e 1926 arcos.
</p>
</li>

<li>Fazendo um <i>zoom</i> em uma região menor, podemos ver o grafo melhor: 

<p>
<img src="../../sandbox/Data/EP4/USP/BlocoC.png" alt="Zoomed USP Graph" /> 
</p>

<p>
Os vértices do grafo (que são <code>nodes</code> no mapa OSM) são representados
por pontos pretos.  Os arcos do grafo são representados por
segmentos de reta.  Os pontos vermelhos indicam a mão das
ruas/orientação dos arcos: em um arco de <code>v</code> para <code>w</code>, há um ponto
vermelho perto de <code>w</code> e este arco representa uma via com mão única,
de <code>v</code> para <code>w</code>.  Dois pontos vermelhos no segmento entre <code>v</code> e <code>w</code>
indicam que a via é de mão dupla.
</p>
</li>
</ul>
</div>
</div>
</div>

<div id="outline-container-sec-2-2" class="outline-3">
<h3 id="sec-2-2">Caminhos mais curtos</h3>
<div class="outline-text-3" id="text-2-2">
<ul class="org-ul">
<li>Suponha agora que queremos ir do <code>node</code> <code>1931475238</code> ao <code>node</code>
<code>1831379092</code>, de carro, por um caminho curto.  Você pode ver quais
são esses nodes usando as URLs

<p>
<a href="http://www.openstreetmap.org/node/1931475238">http://www.openstreetmap.org/node/1931475238</a>
</p>

<p>
<a href="http://www.openstreetmap.org/node/1831379092">http://www.openstreetmap.org/node/1831379092</a>
</p>

<p>
Seu sistema deve então executar o algoritmo de Dijkstra no grafo
apropriado para encontrar um caminho mais curto.  O resultado seria
assim: 
</p>

<p>
<img src="../../sandbox/Data/EP4/USP/MAC-IB.png" alt="MAC-IB path" /> 
</p>

<p>
O caminho encontrado tem aproximadamente 2.7 km. 
</p>
</li>

<li>Seu sistema deverá ser tal que o usuário deverá poder dar <i>pares
latitude/longitude para especificar a origem e o destino</i>.  Para
tanto, seu programa deverá encontrar os vértices do grafo mais
próximos dos pontos dados pelo usuário, e usar tais vértices como o
par origem/destino.
</li>

<li>O usuário deverá poder dar vários pares origem/destino (como pares
latitude/longitude).
</li>

<li>Seu programa deverá ter uma saída gráfica, exibindo o caminho
encontrado para cada par origem/destino dado pelo usuário.  Seu
programa deverá também dizer o comprimento de cada caminho
encontrado.
</li>
</ul>
</div>
</div>

<div id="outline-container-sec-2-3" class="outline-3">
<h3 id="sec-2-3">Outro exemplo</h3>
<div class="outline-text-3" id="text-2-3">
<ul class="org-ul">
<li>Você pode obter um mapa para uma parte da cidade de São Paulo usando
a URL

<p>
<a href="http://www.openstreetmap.org/export?&bbox=-46.7357,-23.606,-46.5613,-23.5036">http://www.openstreetmap.org/export?&bbox=-46.7357,-23.606,-46.5613,-23.5036</a>
</p>

<p>
O arquivo XML correspondente é <a href="../../sandbox/Data/EP4/SP/map.osm-SP.xml">este</a>.  O grafo correspondente tem
62327 vértices e 98222 arcos. 
</p>
</li>

<li>Ao se procurar um caminho do IME à Praça da Sé, seu sistema poderia
devolver um caminho como esse:

<p>
<img src="../../sandbox/Data/EP4/SP/MAC-Se.png" alt="MAC-Se path" /> 
</p>

<p>
Esse caminho tem aproximadamente 12km de comprimento.  O grafo em
que a busca foi feita tem 62327 vértices e 98222 arcos.
</p>

<p>
No caso de mapas grandes, você pode optar por mostrar apenas os
vértices do grafo, para a imagem não ficar muito poluída (essa opção
poderia ser dada ao usuário).
</p>
</li>
</ul>
</div>
</div>

<div id="outline-container-sec-2-4" class="outline-3">
<h3 id="sec-2-4">Requisitos</h3>
<div class="outline-text-3" id="text-2-4">
<p>
Delineamos aqui como deve ser seu EP do ponto de vista do usuário e de
implementação.
</p>

<ul class="org-ul">
<li><i>Forma de uso</i>

<ul class="org-ul">
<li>O usuário determinará o mapa a ser usado e produzirá o arquivo
XML correspondente (digamos, <code>map-osm.xml</code>), usando o OSM.
</li>

<li>O usuário executará o <i>script</i> <code>xmltoadj.py</code> para produzir o
arquivo com as listas de adjacência do grafo dirigido
correspondente (digamos, <code>G.adjlist</code>).
</li>

<li>O usuário então executará seu programa, digamos <code>EP4</code>, fornecendo
como entrada o arquivo XML do mapa e o arquivo com as listas de
adjacência (arquivos <code>map-osm,xml</code> e <code>G.adjlist</code>).  Seu programa
deve então entrar em um modo interativo.  Nesse modo, o usuário
deverá ser capaz de fazer várias coisas:

<ul class="org-ul">
<li>O usuário deverá ser capaz de definir a região do mapa a ser
desenhado nas figuras, dando dois pontos: o ponto inferior
esquerdo e o ponto superior direito.  Esses pontos devem ser
pares latitude/longitude.  

<ul class="org-ul">
<li>"Desenhar o mapa" significa desenhar o grafo dirigido da
região (o mais fácil é simplesmente ignorar os pontos que caem
fora do "canvas").
</li>
</ul>
</li>

<li>Em qualquer momento, o usuário deve ser capaz de pedir que a
figura seja atualizada.  O usuário deverá ser capaz de dizer se
ele quer que sejam desenhadas as arestas do grafo ou não (os
vértices devem ser sempre desenhados).  Note que, como o usuário
pode especificar a região do mapa a ser desenhada, ele poderá
fazer <i>zoom ins</i> e <i>zoom outs</i> na figura do grafo.
</li>

<li>O usuário deverá ser capaz de pedir um caminho de comprimento
mínimo entre um par de pontos (origem e destino), também dados
por pares latitude/longitude.  Seu programa deve encontrar os
vértices do grafo mais próximos dos pontos dados, e deve
encontrar um caminho mínimo entre eles (ou dizer que o destino
não é acessível dessa origem).  Uma vez encontrado um caminho
mínimo, ele deve ser indicado com alguma cor diferente na figura
atual (os vértices e as arestas devem ser dessa cor).  Seu
programa deve também dizer o comprimento do caminho encontrado.
</li>

<li><i>O usuário deverá ser capaz de dar os pontos de origem e destino
com o mouse.</i>  Para tanto, o usuário deverá ter um modo de
alternar entre interação via mouse e via teclado.
</li>

<li>O usuário deverá ser capaz de "limpar" a figura, removendo-se o
caminho mínimo atual (o mais fácil é redesenhar a figura).
</li>
</ul>
</li>
</ul>
</li>

<li><i>Implementação</i>.  É natural decompor seu sistema em várias classes.
As seguintes classes são naturais.  Se você encontrar outra
decomposição melhor, você pode usá-la.  Se você não usar uma boa
decomposição, sua nota pode sofrer reduções.

<ul class="org-ul">
<li><code>EdgeWeightedDigraph.java</code>.  A classe de S&amp;W para grafos dirigidos
com pesos nos arcos. 
</li>

<li><code>SymbolEWDigraph.java</code>.  Deve ter a mesma relação com a classe
<code>EdgeWeightedDigraph.java</code> como as classes <code>SymbolDigraph.java</code> e
<code>Digraph.java</code> tem entre si.
</li>

<li><code>Location.java</code>.  Objetos dessa classe especificam um ponto na
superfície da terra.  Você poderia implementar como pares
latitude/longitude. 
</li>

<li><code>GeoInto.java</code>.  Um objeto dessa classe deve ter, como componente
principal, uma tabela de símbolos com elementos da forma <code>&lt;node
    id, location&gt;</code>, onde <code>node id</code> é o identificador de um nó de um
mapa OSM e <code>location</code> é a localização desse nó.
</li>

<li><code>SymbolGeoEWDigraph.java</code>.  Um objeto dessa classe deve ter, como
elementos principais, um <code>SymbolEWDigraph</code> e um <code>GeoInfo</code>, este
último contendo a localização geográfica dos vértices no
<code>SymbolEWDigraph</code>.
</li>
</ul>
</li>
</ul>
</div>
</div>

<div id="outline-container-sec-2-5" class="outline-3">
<h3 id="sec-2-5">Vocês podem fazer este EP em duplas</h3>
<div class="outline-text-3" id="text-2-5">
<ul class="org-ul">
<li>Cada dupla deve entregar um único trabalho.  Um membro de cada par
deve entregar o trabalho no Paca (<i>não esqueçam de colocar os nomes
de ambos os integrantes do par no trabalho</i>).  O outro membro da
equipe deve entregar um texto, dizendo quem é seu parceiro.
</li>
</ul>
</div>
</div>

<div id="outline-container-sec-2-6" class="outline-3">
<h3 id="sec-2-6">Alterações, correções e atualizações</h3>
<div class="outline-text-3" id="text-2-6">
<p>
Como estou divulgando versões parciais do enunciado, vou manter um
<i>log</i> das alterações, correções e atualizações mais importantes.
</p>

<ul class="org-ul">
<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-23 Tue 06:50]</span></span> Requisito sobre interação via mouse
adicionado.  
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-21 Sun 19:06]</span></span> Requisitos do EP definidas.  Enunciado
próximo de completo.
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-21 Sun 18:00]</span></span> Exemplo com mapa de parte da cidade de São
Paulo adicionada. 
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-20 Sat 16:07]</span></span> Exemplo de caminho mínimo adicionado.
Especificação da saída do EP adicionada.
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-20 Sat 14:50]</span></span> <code>gistfile1.py</code> refinado, para levar em conta
oneway tags que são -1.  Grafos do enunciado gerados novamente de
acordo. 
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-20 Sat 13:31]</span></span> Os grafos nos enunciado foram gerados
novamente, com a nova versão de <code>gistfile1.py</code>.
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-20 Sat 13:30]</span></span> O script <code>gistfile1.py</code> foi refinado, para
levar em conta a mão das rotatórias.
</li>

<li><span class="timestamp-wrapper"><span class="timestamp">[2015-06-20 Sat 13:30]</span></span> O script <code>gistfile1.py</code> foi refinado, para
não incluir passagens de pedestres, ciclovias, etc.
</li>
</ul>
</div>
</div>
</div>
</div>
<div id="postamble" class="status">
<p class="author">Author: <a href="https://www.ime.usp.br/~yoshi/">Yoshiharu Kohayakawa</a></p>
<p class="email">Email: <a href="mailto:yoshi@ime.usp.br">yoshi@ime.usp.br</a></p>
<p class="date">Created: 2015-07-01 Wed 09:41</p>
<p class="creator"><a href="http://www.gnu.org/software/emacs/">Emacs</a> 24.4.51.2 (<a href="http://orgmode.org">Org</a> mode 8.2.10)</p>
<p class="validation"><a href="http://validator.w3.org/check?uri=referer">Validate</a></p>
</div>