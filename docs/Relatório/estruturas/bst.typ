== Árvore Binária de Busca @bst
=== Definição

Uma Árvore Binária de Busca (BST - _Binary Search Tree_) é uma estrutura de dados do tipo árvore binária em que cada nó obedece à seguinte propriedade de ordenação:

+ Todos os valores na subárvore esquerda de um nó são menores que o valor do nó;

+ Todos os valores na subárvore direita de um nó são maiores que o valor do nó.

Essa propriedade garante que operações como busca, inserção e remoção possam ser realizadas de forma eficiente, geralmente com complexidade proporcional à altura da árvore.

#figure(
  image("imagens/bst.jpeg", width: 90%),
  caption: [Exemplo de árvore BST com raiz igual a 20 e ordem de inserção:\
  20, 10, 5, 3, 7, 8, 15, 18, 16, 19, 30, 25, 23, 27, 35, 40, 42. @cadilag-arv-binaria]
) 


=== Implementação

  + *Função #raw("insertBST")*
  
    - A função se divide em 2 casos: 
    
      + *Árvore vazia*\
      
        Caso a árvore esteja vazia, um nó é criado por meio da função auxiliar #raw("createNodeWithWord") e, em seguida, esse nó é designado como a raiz da árvore passada como argumento. Nenhuma comparação é necessária nesse caso (#raw("numComparisons = 0")).
        
      + *Árvore não vazia*\
      
        Caso a árvore não esteja vazia, é realizada uma busca recursiva usando #raw("searchWord") para encontrar a posição correta de inserção.
        
        - A função encontra:
        
          - *#raw("currNode")*: nó onde a palavra foi encontrada, caso ela já exista;
          
          - *#raw("lasNode")*: último nó visitado antes de chegar a uma posição NULL, que será utilizado no caso em que a palavra inserida seja nova.
        
        - Em seguida, há a divisão em dois subcasos:
        
          - Palavra já registrada *(#raw("currNode") $!=$ NULL)*
            \ O ID do documento é adicionado à lista #raw("documentIds") do nó existente.
            
          - Palavra não registrada *(#raw("currNode") $=$ NULL)*
            \ Um novo nó é criado e inserido como filho de #raw("lasNode") (esquerda ou direita, baseado na comparação de palavras).
  
  + *Função #raw("searchBST")*\
  
    - Novamente há a utilização da função auxiliar #raw("searchWord") para percorrer a árvore e encontrar a posição relativa a palavra desejada. Em seguida, há a divisão em dois casos:
    
        + Palavra já registrada *(#raw("currNode") $!=$ NULL)*
          \ O atributo "#raw("found")" da variável "#raw("result")" é atualizado com o valor de 1 e o atributo "#raw("documentIds")" é atualizado com a lista #raw("currNode→documentIds").
            
        + Palavra não registrada *(#raw("currNode") $=$ NULL)*
          \ O atributo "#raw("found")" da variável "#raw("result")" é atualizado com o valor de 0 e o atributo "#raw("documentIds")" é atualizado com NULL.

  + *Função #raw("destroyBST")*
    - Libera todos os nós da árvore de forma recursiva:

      + Se o nó atual for NULL, retorna imediatamente.
      
      + Caso contrário, chama a função #raw("bstFreeRec(tree→root)") para liberar todos os nós.
      
      + Define #raw("tree→root") = NULL, libera a _tree_ e ajusta ponteiro para NULL.
  

=== Resultados

A seguir, apresentamos os resultados da execução das operações de inserção e busca na árvore *BST* para 10 000 arquivos:

#linebreak()
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
    [260.640],
    [Tempo de busca],
    [1.639000],
    [Número de comparações],
    [49,990,204],
    [Altura da árvore],
    [36],
    [Tamanho do menor galho],
    [5],
  )

)


*Distribuição de Comparações nas Buscas*

A imagem abaixo mostra um histograma com a frequência de comparações realizadas durante as operações de busca:

#figure(
image("../gráficos/buscas_bst.png"),
caption: "Frequência de comparações para buscas BST."
)

O gráfico mostra uma distribuição assimétrica, com uma cauda longa à direita. A maior parte das buscas exigiu entre 5 e 15 comparações, com picos em torno de 6, 8 e 11. No entanto, há casos com até 35 comparações, o que indica que algumas partes da árvore cresceram de forma desequilibrada.

Esse comportamento é típico de BSTs que não utilizam mecanismos automáticos de balanceamento. À medida que os dados são inseridos em ordem não aleatória, a árvore pode se tornar desbalanceada, aumentando o número de comparações em algumas buscas.


==== Análise Quantitativa

- Comparações mais frequentes: entre 6 e 12

- Comparação mínima observada: 1

- Comparação máxima observada: 35

- Tendência central (modas locais): 6, 8 e 11

Embora muitas buscas sejam resolvidas com poucas comparações, a ausência de balanceamento pode causar degradação do desempenho em partes específicas da árvore, tornando o custo de algumas buscas significativamente mais alto.
