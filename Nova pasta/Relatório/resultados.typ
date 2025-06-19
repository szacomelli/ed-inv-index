= Resultados e comparações gerais


== Complexidade de tempo

Com base na solução previamente discutida, adotou‑se uma abordagem robusta cujas implementações apresentam, em média, complexidade próxima de $O(m log n)$, com ligeiro acréscimo ocasionado pelas seguintes características:

  - *Vetores ordenados*\
    A ordenação prévia dos vetores reduz o custo de busca na posição adequada.
  
  - *Alta proporção de palavras duplicadas*\
    Como muitas chaves já existem no vetor, a inserção geralmente ocorre em tempo constante amortizado, $O(1)$, reservando operações de custo $O(m)$ apenas para casos excepcionais.

Dessa forma, o custo médio de inserção em cada vetor aproxima‑se de $O(log n)$, resultando no comportamento geral mencionado.\

O gráfico abaixo apresenta os tempos de execução medidos para todas as árvores:

#image("gráficos/complexidade.png")

Observa‑se que todas as árvores exibem complexidade de tempo muito próxima — o que era de se esperar, já que compartilham a mesma base algorítmica. Em detalhes:

- A *BST* mantém‑se como a curva inferior, refletindo sua implementação mais simples.

- A *Árvore Rubro‑Negra* e a *Árvore AVL* apresentam desempenho semelhante entre si, pois ambas incorporam rotações que acrescentam um pequeno "_overhead_"#footnote[Custo adicional, em termos de tempo, recursos ou complexidade, associado à execução de uma operação, processo, ou sistema.] em relação à BST.

Assim, embora as três estruturas operem na mesma ordem de grandeza, as diferenças de implementação (principalmente as rotações) explicam o leve acréscimo de custo nas árvores balanceadas. Essa métrica ainda é sensível a fatores aleatórios, e pode não ser replicável em todos os casos.


== Alturas e balanceamento

Devido a baixa replicabilidade dos tempos de execução, podemos comparar os modelos também pelas alturas das árvores. O _plot_ abaixo mostra a altura relativa ao número de inserções:

#image("gráficos/balanceamento.png")

Obtém-se, novamente, os resultados esperados:

- A *AVL* se autobalanceia a cada iteração, mantendo com uma altura semelhante ao valor teórico, sendo uma boa aproximação discreta do valor de $log n$

- A *RBT* também é uma árvore balanceada, então se aproxima também da curva 

- A *BST* não se balanceia, então cresce rapidamente, se mantém mais alta que todas as outras arvores, e não é bem representada pela curva teórica

== Contagem de comparações 

Ao combinar as densidades de distribuição do número de comparações de cada estrutura, obtemos o gráfico de barras abaixo:

#image("gráficos/comparacoes_hist.png")

Os resultados obtidos estão em conformidade com as características esperadas de cada árvore:

  - *Árvore AVL (barras amarelas)*: revela uma forte concentração à esquerda, com um menor número de comparações e variação reduzida, o que evidencia seu balanceamento rigoroso;
  
  - *Árvore BST (barras azuis)*: apresenta distribuição mais dispersa e picos ocasionais, demonstrando a ausência de balanceamento e maior flutuação no número de comparações;
  
  - *Árvore Rubro‑Negra (barras vermelhas)*: situa‑se entre as duas anteriores; por possuir um balanceamento menos severo, apresenta concentração inicial significativa e alguns valores de comparações superiores aos da AVL.

Modificando os dados para analisarmos apenas inserções de palavras novas, podemos observar o comportamento contínuo do número de comparações:
  
#image("gráficos/comparacoes_line.png")


 - *Todas as árvores* se aproximam da curva de altura teórica
 
 - A *AVL* mantém‑se muito próxima a essa referência, estabilizando‑se ligeiramente abaixo dela, com variação baixa, mostrando seu balanceamento;
 
 - A *BST* ultrapassa rapidamente a curva teórica e mantém um crescimento contínuo de altura a partir desse ponto, evidenciando a falta de balanceamento. Além disso, apresenta grande oscilação, com picos mais altos e vales mais baixos que qualquer outra árvore;
 
 - A *RBT* se comporta como uma média das outras árvores, apresentando alguns pontos atípicos, caindo bem abaixo da AVL por vezes, mas se estabilizando com números maiores.


