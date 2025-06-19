= Desafios

== Verificação de duplicatas e complexidade temporal

A implementação da detecção de duplicatas apresentou um dilema envolvendo desempenho e complexidade algorítmica. Diante disso, quatro abordagens diferentes foram consideradas (sendo $n$ o número de palavras únicas e $m$ o maior índice inverso da árvore):

+ *Ignorar a verificação de duplicatas*

  - Descrição: Tratamento de todas as chaves como novas inserções, sem a checagem de repetições.
  
  - Complexidade: $O(log n)$.
  
  - Vantagens: Fácil implementação.
  
  - Desvantagens: Não impede múltiplas entradas iguais, o que compromete a integridade dos dados.

+ *Comparar com o último elemento inserido*

  - Descrição: Verificação apenas em relação à última chave adicionada.
  
  - Complexidade: $O(log n)$.
  
  - Vantagens: Eficiente para dados já ordenados.
  
  - Desvantagens: Ineficiente quando os dados não estão ordenados, falhando na detecção de duplicatas.

+ *Varredura sequencial do início ao fim*

  - Descrição: Percorre toda a lista de chaves, do primeiro ao último, buscando duplicatas.
  
  - Complexidade: $O(m^2log n)$.
  
  - Vantagens: Encontra todas as duplicatas.
  
  - Desvantagens: Desempenho extremamente baixo para listas muito grandes.

+ *Varredura sequencial do fim ao início*

  - Descrição: Percorre a lista de chaves em ordem inversa, do último ao primeiro.
  
  - Complexidade $O(m^2 log n)$.
  
  - Vantagens: Maior eficiência em cenários parcialmente ordenados; mesmo nível de robustez que a varredura direta.
  
  - Desvantagens: Custo elevado em casos de dados completamente desordenados.
  
*Solução escolhida*\

A varredura inversa (do último para o primeiro) foi escolhida por oferecer maior desempenho em conjuntos de dados parcialmente ordenados — como é o caso deste trabalho, já que os documentos são lidos em ordem crescente — sem comprometer a robustez na identificação de duplicatas.

*Observação:* As complexidades indicadas são estimativas aproximadas.

== Atualizações na raiz após rotações na AVL

A implementação das rotações na AVL exigiu um ajuste extra para manter o ponteiro da raiz sempre correto:

  - Problema: Quando a rotação envolvia o nó raiz, o ponteiro #raw("tree→root") continuava apontando para o nó antigo, apesar de a subárvore interna já estar corretamente reestruturada.
  
  - Causa: A função rebalance atua apenas na subárvore desbalanceada e retorna o novo nó de raiz dessa subárvore, mas não atualiza automaticamente o ponteiro principal #raw("tree→root").
  
  - Solução encontrada: Após chamar #raw("rebalance"), verificamos se o nó retornado difere da raiz atual. Se for o caso, atribuímos manualmente #raw("tree→root") = `<nó retornado>`, garantindo que o ponteiro principal reflita a nova estrutura.

Com essa correção, garantimos que a raiz da árvore AVL esteja sempre correta, mantendo a consistência da estrutura e o bom funcionamento das operações.

Em virtude das limitações de prazo, não foi possível realizar os testes com a segunda base de dados, o que constitui um dos principais desafios enfrentados.
