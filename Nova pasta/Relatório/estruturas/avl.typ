== Árvore AVL @avl
=== Definição

Uma Árvore AVL — cujas iniciais homenageiam Adelson, Velsky e Landis — é uma árvore binária de busca autobalanceada, que além de satisfazer a propriedade de ordenação de uma BST, mantém um fator de balanceamento restrito em cada nó:

+ Todos os valores na subárvore esquerda de um nó são menores que o valor armazenado nesse nó;

+ Todos os valores na subárvore direita de um nó são maiores que o valor armazenado nesse nó;

+ O fator de balanceamento de cada nó - isto é, a diferença entre as alturas de sua subárvore esquerda e de sua subárvore direita - deve ser -1, 0 ou +1.

Essa garantia assegura que a altura da árvore permaneça em $O(log n)$, fazendo com que operações de busca, inserção e remoção sejam realizadas em tempo $O(log n)$ no pior caso.

#figure(
  image("imagens/avl.jpeg", width: 90%),
  caption: [Exemplo de árvore AVL com raiz inicial igual a 20 e sequência de inserção:\
  20, 10, 25, 7, 16, 30, 5, 8, 15, 27, 40, 3, 19, 23, 35, 42, 18. @cadilag-arv-binaria]
)

=== Implementação

  + *Função #raw("insertAVL")*
    - A função se divide em dois casos:
    
      + *Árvore vazia*
      
        Caso a árvore esteja vazia, um nó é criado por meio da função auxiliar `createNodeAVL`. Esse nó é designado como raiz da árvore passada como argumento. Nenhuma comparação é necessária nesse caso (#raw("numComparisons = 0")).
        
      + *Árvore não vazia*
  
        Caso a árvore não esteja vazia, inicia-se uma busca iterativa para localizar a posição correta de inserção, com contagem do número de comparações realizadas.

    - *Durante a busca:*
      - Se a palavra já existir na árvore, o ID do documento é verificado na lista do nó atual por meio de #raw("lookupValue"). Caso o ID ainda não esteja registrado, ele é adicionado à lista #raw("documentIds").
      
      - Se a palavra _não existir_, um novo nó é criado e inserido como filho esquerdo ou direito do último nó visitado (#raw("parent")), dependendo do resultado da comparação de palavras.
    
    - Após a inserção de um novo nó, inicia-se o *procedimento de reequilíbrio (balanceamento)* a partir do pai do novo nó, utilizando a função auxiliar #raw("rebalance").
    
      - A altura dos nós é atualizada por meio de #raw("updateHeight").
      
      - O *fator de balanceamento* de cada nó é calculado com #raw("getBalanceFactor"), e são aplicadas rotações apropriadas:
    
        + *Caso Esquerda-Esquerda:* rotação simples à direita.
        
        + *Caso Esquerda-Direita:* rotação à esquerda no filho esquerdo, seguida de rotação à direita no nó desbalanceado.
        
        + *Caso Direita-Direita:* rotação simples à esquerda.
        
        + *Caso Direita-Esquerda:* rotação à direita no filho direito, seguida de rotação à esquerda no nó desbalanceado.
    
      - Durante as rotações, os ponteiros para os pais são atualizados para manter a integridade da estrutura da árvore. Se a raiz for alterada, o ponteiro #raw("tree.root") é atualizado.

  + * Função #raw("searchAVL")*

    A busca na árvore é feita iterativamente a partir da raiz, comparando a palavra procurada com as palavras armazenadas em cada nó.\
    A função se divide em dois casos:

    - * Palavra registrada *

      Se a palavra for encontrada, o campo #raw("found") da estrutura #raw("searchResult") é atualizado para `1`, e a lista de #raw("documentIds") correspondente é retornada.

    - *Palavra não registrada* 

      Se a palavra não for encontrada até alcançar um nó #raw("null"), o campo #raw("found") é mantido em `0`, e #raw("documentIds") é retornado como #raw("null"). Durante o processo, é contabilizado o número de comparações realizadas e o tempo de execução é medido.

  + * Funções auxiliares de balanceamento *

    - #raw("getHeight(node)"): Retorna a altura de um nó ou `0` se for `null`.
    
    - #raw("updateHeight(node)"): Atualiza a altura de um nó com base nas alturas dos filhos.
    
    - #raw("getBalanceFactor(node)"): Calcula o fator de balanceamento como a diferença entre as alturas do filho esquerdo e do direito.
    
    - #raw("rotateLeft(node)") / #raw("rotateRight(node)"): Realizam rotações simples para restaurar o balanceamento da árvore, ajustando também os ponteiros de pais e filhos.
    
    - #raw("rebalance(node)"): Decide qual tipo de rotação aplicar com base no fator de balanceamento, e retorna o novo nó raiz da subárvore após o reequilíbrio.


=== Resultados

A seguir, apresentamos os resultados da execução das operações de inserção e busca na árvore *AVL* para 10 000 arquivos:

#align(center,
  table(
    columns: (auto, auto),
    table.header(
      table.cell(
        align: center,
        colspan: 2,
        [Resultados encontrados]
      )
    ),
    [Tempo de inserção],
    [253.733],
    [Tempo de busca],
    [1.29002],
    [Número de comparações],
    [47,230,297],
    [Altura da árvore],
    [16],
    [Tamanho do menor galho],
    [10],
  )

)



*Distribuição de Comparações nas Buscas*

A imagem abaixo mostra um histograma representando a distribuição da quantidade de comparações realizadas durante operações de busca:

#figure(
  image("../gráficos/buscas_avl.png"), 
  caption: "Frequência de Comparações para buscas AVL."
)

A maior parte das buscas exigiu entre 10 e 14 comparações, com um pico de frequência em torno de 13 comparações. Isso indica que, mesmo com um grande volume de palavras e documentos, a estrutura AVL manteve um desempenho estável e balanceado.

A cauda à esquerda mostra que algumas buscas exigiram poucas comparações (em torno de 2 a 6), provavelmente em casos em que a palavra estava próxima da raiz. Já os casos com maior número de comparações (até 17) representam situações em que a palavra estava em folhas mais profundas — ainda assim, esses casos são menos frequentes, mostrando a eficiência do balanceamento automático da AVL.

==== Análise Quantitativa

  - *Comparações mais frequentes*: 12 a 14  
  
  - *Comparação mínima observada*: 1  
  
  - *Comparação máxima observada*: 17  
  
  - *Tendência central (moda)*: aproximadamente 13

Esse resultado está de acordo com o esperado para uma árvore AVL, onde a altura é mantida em `O(log n)` mesmo após muitas inserções. Isso garante que o número de comparações para busca também permaneça logarítmico na maioria dos casos.

#figure(

  image("../arvores/imagem2.png"), 

  caption: "Imagem da AVL gerada com a função saveTree para o primeiro documento."

)