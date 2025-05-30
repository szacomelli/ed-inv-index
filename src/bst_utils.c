#include <stdio.h>
#include <stdlib.h>
#include "bst_utils.h"
#include "tree_utils.h"

// rootWord: the idea is that it is "mmmmmmm"
bTree* createBSTWithRoot(string rootWord) {
    bTree* tree = createTree();
    tree->root = createNode();
    tree->root->word = rootWord;
    return tree;
}

void insertBST(bTree* tree, string word, int docId) {
    if (!tree) return;
    tNode* newNode = createNode();
    newNode->word = word;
    insertNodeBST(tree->root, newNode, NULL);
    insertValue(newNode->documentIds, &docId);
}

tNode* insertNodeBST(tNode* root, tNode* newNode, tNode** insertedNode) {
    if (!root) return newNode;
    int cmp = strcmp(newNode->word, root->word);
    if      (cmp < 0) {
        root->left = insertNodeBST(root->left, newNode, insertedNode);
        root->left->parent = root;
    }
    else if (cmp > 0) {
        root->right = insertNodeBST(root->right, newNode, insertedNode);
        root->right->parent = root;
    }
    else if (insertedNode) {
        *insertedNode = root;
        return root;
    }
    return root;
}

tNode* removeNodeBST(tNode* root, string word) {
    if (!root) return NULL;
    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        root->left = removeNodeBST(root->left, word);
    } else if (cmp > 0) {
        root->right = removeNodeBST(root->right, word);
    } else {
        if (!root->left) {
            tNode* temp = root->right;
            freeList(root->documentIds);
            free(root);
            return temp;
        } else if (!root->right) {
            tNode* temp = root->left;
            freeList(root->documentIds);
            free(root);
            return temp;
        }
        tNode* temp = minValueNode(root->right);
        root->word = temp->word;
        root->right = removeNodeBST(root->right, temp->word);
    }
    return root;
}

tNode* minValueNode(tNode* node) {
    tNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

tNode* searchNodeBST(tNode* root, string word, int* comparisons) {
    if (!root) return NULL;
    (*comparisons)++;
    int cmp = strcmp(word, root->word);
    if (cmp == 0) return root;
    else if (cmp < 0) return searchNodeBST(root->left, word, comparisons);
    else return searchNodeBST(root->right, word, comparisons);
}

void buildBSTFromList(bTree* tree, string* wordList, int* docIds) {
    for (int i = 0; wordList[i] != NULL; i++) {
        insertBST(tree, wordList[i], docIds[i]);
    }
}

void inOrderPrint(tNode* root) {
    if (!root) return;
    inOrderPrint(root->left);
    printf("%s: ", root->word);
    printList(root->documentIds);
    inOrderPrint(root->right);
}

int main() {
    printf("===== TEST BST =====\n");

    // Criar árvore com raiz fixa "mmmmmmmmm"
    bTree* tree = createBSTWithRoot("mmmmmmmmm");
    if (!tree || !tree->root) {
        printf("Erro ao criar a árvore.\n");
        return 1;
    }

    // Palavras para teste
    string palavras[] = {
        "laranja", "abacaxi", "maca", "goiaba", "manga",
        "melancia", "limão", "uva", "acerola", "caju"
    };
    int num = sizeof(palavras) / sizeof(string);

    printf("\nInserindo palavras na BST...\n");
    for (int i = 0; i < num; i++) {
        printf("Inserindo \"%s\" com ID %d...\n", palavras[i], i + 1);
        insertBST(tree, palavras[i], i + 1);
    }

    printf("\nImprimindo árvore em ordem:\n");
    inOrderPrint(tree->root);

    // Testar busca
    printf("\nTestando busca:\n");
    string termosBusca[] = { "manga", "pêssego", "abacaxi", "melancia" };
    int numBusca = sizeof(termosBusca) / sizeof(string);
    for (int i = 0; i < numBusca; i++) {
        int comps = 0;
        tNode* found = searchNodeBST(tree->root, termosBusca[i], &comps);
        if (found) {
            printf("Encontrado \"%s\" após %d comparações. IDs:\n",
                   termosBusca[i], comps);
            printList(found->documentIds);
        } else {
            printf("Não encontrado \"%s\" após %d comparações.\n",
                   termosBusca[i], comps);
        }
    }

    printf("\nDestruindo árvore...\n");
    destroyTree(tree);
    printf("Finalizado.\n");

    return 0;
}
