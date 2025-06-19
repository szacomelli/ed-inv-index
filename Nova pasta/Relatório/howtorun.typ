= Como compilar e executar o código
#import "@preview/codly:1.2.0": *
#import "@preview/codly-languages:0.1.1": *
#codly(languages: codly-languages)
#show: codly-init.with()

  ```bash
    make all
    ./main_<árvore> <search/stats> <número_de_docs> <diretório_dos_docs>
    ./test_<árvore>
  ```

  Além disso, há um _wrapper_ que converte as funções implementadas em `C` para um _namespace_ que pode ser utilizado em `C++`. Para utilizá-las, basta importar o arquivo `<árvore>_wrapper.h` no código C++ e usar as funções `insert`, `create`, `destroy` e `search` definidas no _namespace_ específico da árvore, esse último sendo:
  
    - BST para a árvore binária simples;
    
    - AVL para a árvore binária balanceada:
    
    - RBT para a árvore rubro-negra.
    Exemplo: para chamar a função que cria uma RBT, bastaria importar `rbt_wrapper.h` e chamar a função `RBT::create()`.