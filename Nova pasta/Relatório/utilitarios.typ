= Utilitários


O módulo `tree_utils` oferece funções auxiliares para criação, visualização e exportação de árvores binárias (AVL, BST e RBT) utilizadas no projeto.

*Funcionalidades principais*

+ Criação:
  - `createNode()`: inicializa um nó com campos padrão e lista de documentos vazia.
  
  - `createTree()`: cria uma estrutura de árvore com raiz e NIL nulos.

+ Impressão:

  - `printTree(tree)`: mostra a árvore no terminal com formatação gráfica por caracteres Unicode (adaptada a Windows ou Unix).
  
  - `printIndex(tree)`: exibe as palavras e os IDs de documentos armazenados em cada nó, por ordem "in-order".

+ Análise:

  - `calculateHeight(node)`: calcula a altura de uma subárvore.
  
  - `getMaxID(node)`: retorna o maior número de IDs de documentos encontrados em um único nó.
  
  - `calculateMinPath(node, NIL)`: retorna o comprimento do menor caminho da subárvore até uma folha.


+ Exportação:

  - `saveTree(tree)`: gera visualização gráfica da árvore em SVG com cores representando a densidade de documentos em cada nó, usando o Graphviz#footnote[Nesse caso, a função `saveTree` usa o programa Graphviz, que deve estar instalado previamente no computador para que a função consiga utilizá-lo. Além disso, o Graphviz parece ter uma tendência a exportar a árvore com os nós de maior valor à esquerda da raiz, que difere da convenção que estamos utilizando nas nossas estruturas. ].

*Observações*

  - A visualização textual da árvore facilita depuração e compreensão da estrutura.
  
  - O uso de cores na exportação gráfica permite identificar nós mais "relevantes" visualmente.
  
  - O código trata corretamente ponteiros nulos e usa estruturas portáveis.

