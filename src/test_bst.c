#include <stdio.h>
#include <assert.h>

#include "bst.h"

/**
 * Função auxiliar para imprimir o resultado de uma busca:
 *   — chama search(…) na árvore;
 *   — imprime se a palavra foi ou não encontrada, quantas comparações
 *     levou e o tempo de execução;
 *   — caso encontrada, percorre a lista de documentIds e imprime todos.
 */
static void printSearchResult(BinaryTree *tree, const char *word) {
    struct SearchResult sr = searchBST(tree, (string)word);

    if (sr.found) {
        printf(
            "Palavra '%s' encontrada  (comparacoes = %d, tempo = %f s)\n",
            word,
            sr.numComparisons,
            sr.executionTime
        );
        printf("  Document IDs:");
        // percorre manualmente a lista de documentIds
        node *iter = sr.documentIds->head;
        while (iter) {
            printf(" %d", *(int*)(iter->value));
            iter = iter->next;
        }
        printf("\n\n");
    } else {
        printf(
            "Palavra '%s' NAO encontrada  (comparacoes = %d, tempo = %f s)\n\n",
            word,
            sr.numComparisons,
            sr.executionTime
        );
    }
}

int main() {
    BinaryTree *tree = createBST();
    struct InsertResult ir;

    // 1) Inserções de palavras distintas em diferentes documentos
    ir = insertBST(tree, "maca", 1);
    printf("Inseriu 'maca' no doc 1      (comparacoes = %d, tempo = %f s)\n",
           ir.numComparisons, ir.executionTime);

    ir = insertBST(tree, "banana", 2);
    printf("Inseriu 'banana' no doc 2    (comparacoes = %d, tempo = %f s)\n",
           ir.numComparisons, ir.executionTime);

    ir = insertBST(tree, "laranja", 3);
    printf("Inseriu 'laranja' no doc 3   (comparacoes = %d, tempo = %f s)\n",
           ir.numComparisons, ir.executionTime);

    ir = insertBST(tree, "abacaxi", 4);
    printf("Inseriu 'abacaxi' no doc 4   (comparacoes = %d, tempo = %f s)\n",
           ir.numComparisons, ir.executionTime);

    // 2) Inserir palavra duplicada ("banana") no documento 5
    ir = insertBST(tree, "banana", 5);
    printf("Inseriu 'banana' no doc 5 (duplicado)  (comparacoes = %d, tempo = %f s)\n\n",
           ir.numComparisons, ir.executionTime);

    // 3) Testar buscas em vários casos
    printf("=== RESULTADO DAS BUSCAS ===\n\n");

    printSearchResult(tree, "maca");
    printSearchResult(tree, "banana");
    printSearchResult(tree, "laranja");
    printSearchResult(tree, "abacaxi");
    printSearchResult(tree, "uva");  // palavra que não existe
    printSearchResult(NULL, "qualquer coisa");

    // 4) Destruição da árvore e liberação de memória
    destroyBST(tree);
    free(tree);
    return 0;
}
