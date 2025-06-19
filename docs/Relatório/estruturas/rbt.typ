== Árvore Rubro-Negra @rbt
=== Definição

Uma Árvore Rubro-Negra (RBT - _Red-Black Tree_) é uma árvore binária de busca balanceada que associa a cada nó um atributo de cor (vermelho ou preto) e impõe propriedades que garantem profundidade balanceada após operações de inserção e remoção. Essas regras asseguram que o caminho mais longo da raiz até qualquer folha não exceda o dobro do caminho mais curto, mantendo complexidade assintótica $O(log n)$ para operações fundamentais.

Uma RBT é uma árvore que satisfaz as seguintes propriedades:
  + Todo nó é ou preto ou vermelho;
  
  + Todos os nós nulos (que nesse caso consideramos como os nós folha) são pretos;
  
  + Um nó vermelho não pode ter filhos que sejam também vermelhos;
  
  + Todo caminho de um dado nó e qualquer uma de suas folhas (os nós nulos de seus descendentes) tem o mesmo número de nós pretos;
  
  + Por fim, se um nó tem exatamente um filho, esse filho deve ser vermelho.

A última propriedade é, na verdade, uma conclusão lógica que segue das propriedades 2 e 4. Isso porque, se um nó preto tivesse apenas um filho e este, por sua vez, fosse preto, então esse filho (ou seus descendentes) também teriam filhos pretos (pois as folhas de qualquer nó são sempre pretas). Isso, por sua vez, faria com que houvesse um número diferente de nós pretos no caminho entre o nó inicial e cada uma de suas folhas, violando a propriedade 4.

Perceba que a propriedade 3 implica que o caminho de cada nó até sua folha mais distante será sempre menor ou igual ao dobro da distância do caminho entre esse nó e sua folha mais próxima. Isso indica que essas árvores são "aproximadamente balanceadas", uma vez que, apesar das alturas dos nós diferirem em mais do que $|1|$, ela ainda garante tempo logarítmico para suas operações.

#figure(
  image("imagens/rbt.jpeg", width: 90%),
  caption: [Exemplo de árvore RBT com raiz inicial igual a 20 e sequência de inserção:\ 
  (20, 10, 30, 5, 3, 7, 8, 15, 18, 19, 16, 25, 23, 27, 35, 40, 42). @cadilag-arv-binaria]
)

=== Implementação


A implementação da árvore Rubro-Negra compartilha elementos com árvores binárias convencionais. Contudo, as operações de inserção e remoção demandam abordagens específicas, pois as operações de busca não alteram a árvore e a de criação retorna uma árvore vazia.

Considerando o escopo deste trabalho, algoritmos de remoção de nós não foram implementados. Consequentemente, as diferenças entre as funções de inserção da RBT e de uma BST convencional são o centro da análise.

Observa-se que, caso tenhamos uma árvore rubro-negra e insiramos um nó vermelho genérico, ele substituirá uma das folhas (os nós nulos) e passará a ter dois filhos pretos (novamente, os nós nulos). Olhando para seu pai, ele pode ser vermelho ou preto. Se for preto, não há nada que ser feito. Porém, se for vermelho, a terceira propriedade estará sendo quebrada e, portanto, é necessário rebalancear a árvore. Nesse caso, uma das seguintes situações é possível:

  + O tio do nó é vermelho;
  
  + O tio do nó é preto e a posição do nó relativa ao pai é diferente da posição do pai relativa ao avô. 
  
  + O tio do nó é preto e a posição do nó relativa ao pai é a mesma do pai relativa ao avô (ou seja, se o pai fica à esquerda do avô, o filho fica à esquerda do pai nesse caso);

De fato, é trivial ver que, ao inserir-se um nó vermelho qualquer na árvore, ele sempre recairá em um dos casos acima. Agora, basta ver como rebalancear a árvore a partir desses casos:

  + No primeiro caso, como o pai é vermelho e o tio também, o avô é necessariamente preto (para não violar a propriedade 3), logo é possível repintar os três nós para suas cores contrárias, fazendo com que a "altura preta" da árvore não mude e, além disso, o novo nó inserido também não esteja mais ferindo qualquer propriedade. Porém, como o avô mudou de cor e agora é vermelho, ele pode ser filho de outro nó também vermelho, o que quebra a propriedade 3. Perceba, porém, que esse é apenas o caso que acabamos de resolver, o que indica que podemos apenas fazer o processo descrito recursivamente, até atingir a raiz que, por ser sempre preta, pode ter filhos vermelhos sem problema algum. Assim, a árvore volta a cumprir com as propriedades.
  
  + Nesse caso, basta fazer a rotação necessária para reduzir o caso atual para o próximo e, então, resolver àquela maneira. Isso é feita com uma rotação à esquerda no pai, caso o filho esteja à sua direita, ou à direita no pai, caso o filho fique à esquerda. Após isso, basta tomar o caso 3.  
  
  + Já no terceiro caso, o pai é vermelho e o tio é preto. Porém, o avô ainda precisa ser preto (pois o pai é vermelho). Logo, se fizermos uma rotação, colocando o avô como filho do pai, a altura preta da sub-árvore à esquerda do pai diminuirá em 1, mas se manterá igual para a sub-árvore da direita (quebrando a propriedade 4). Porém, se pintarmos o antigo avô de vermelho e o antigo pai de preto, não quebraremos a propriedade 3 (pois o tio, novo filho do antigo avô, é preto) e rebalancearemos a altura preta da árvore, além de fazer com que a propriedade 3 deixe de ser violada pelo nó que inserimos. Perceba que após a rotação, o filho do antigo pai que era diferente do nó inserido passa a ser o filho do antigo avô, logo ele também não altera a altura preta da árvore. Esse processo de troca e recolorimento de nós é feito com uma rotação no avô (à direita se o nó inserido ficar à esquerda do pai ou à esquerda caso contrário) e mudando a cor dos nós pai e avô. Com isso, as propriedades são recuperadas.
  
  Com isso, temos a seguinte função de inserção:
  
  + *função insertRBT*
  
      + *Árvore vazia* \
        Caso a árvore esteja vazia, basta criar uma da mesma forma que é feito na BST. Porém, pintando o nó adicionado de preto e inserindo um nó adicional: *NIL*, que representará os nós nulos (folhas) da árvore.
        
      + *Árvore não vazia*\
        Nesse caso, insere-se um nó como na BST. Se o nó pai for vermelho, chama-se a função *#raw("getCase")* para identificar qual dos três cenários de inserção da RBT aplica-se à estrutura. Em seguida, usa-se uma das seguintes funções, a depender do caso retornado pela *#raw("getCase")*:
        
        + *#raw("firstHelper")*: muda a cor dos nós pai, avô e tio e chama-se recursivamente, até que chegue na raiz, onde ela para e retorna. Ou seja, trata o caso 1;
        
        + *#raw("secondHelper")*: executa a rotação apropriada, a depender da orientação relativa do nó ao seu pai, para que a árvore caia no caso 3. Ou seja, resolve o caso 2;
        
        + *#raw("thirdHelper")*: por fim, a *#raw("thirdHelper")* muda a cor do pai e do avô e executa a rotação apropriada no avô, para rebalancear a árvore. Resolve o caso 3.
        
Além disso, a função de rotação utilizada segue exatamente a mesma lógica da implementada na AVL.

A seguir, temos a função de busca #raw("searchRBT"), que, como não difere da equivalente na BST, foi implementada da mesma forma. Da mesma forma, as funções #raw("createRBT") e #raw("destroyRBT") funcionam exatamente como suas análogas na BST.

=== Resultados

A seguir, apresentamos os resultados da execução das operações de inserção e busca na árvore *RBT* para 10 000 arquivos:

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
    [1.68],
    [Número de comparações],
    [48444111],
    [Altura da árvore],
    [17],
    [Tamanho do menor galho],
    [10],
  )

)

*Distribuição de Comparações nas Buscas*

A imagem abaixo mostra um histograma representando a frequência de comparações realizadas durante as operações de busca:

#figure(

  image("../gráficos/buscas_rbt.png"), 

  caption: "Frequência de Comparações para buscas RBT."

)

A maior parte das buscas exigiu entre 10 e 15 comparações, com um pico concentrado em torno de 12. A distribuição é relativamente simétrica, com a maior frequência centralizada, mas com casos que se estendem até cerca de 25 comparações.

Esse comportamento é característico de árvores rubro-negras, que mantêm um balanceamento eficiente, mesmo com variações na profundidade entre diferentes caminhos da árvore.

==== Análise Quantitativa

  - Comparações mais frequentes: entre 11 e 13

  - Comparação mínima observada: 2

  - Comparação máxima observada: 25

  - Tendência central (moda): aproximadamente 12

O número de comparações se manteve dentro do esperado para essa estrutura, evidenciando que o balanceamento automático proporcionado pelas regras de cores é eficaz para garantir boas condições de busca mesmo com grande volume de dados.

#figure(

  image("../arvores/imagem3.png"), 

  caption: "Imagem da BRT gerada com a função saveTree para o primeiro documento."

)