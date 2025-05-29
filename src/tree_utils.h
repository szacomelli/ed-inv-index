#include "str.h"
#include "lkdlist.h"

typedef struct tNode {
    string word;
    lkdList* documentIds;
    struct tNode* parent;
    struct tNode* left;
    struct tNode* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
} tNode;

typedef struct BinaryTree {
    tNode* root;
    tNode* NIL;  // usado na RBT (Opcional)
} bTree;

tNode* createNode();

// auxiliares

struct InsertResult {
    int numComparisons;
    double executionTime;
    // <Possíveis outras variáveis>
};

struct SearchResult {
    int found;
    lkdList* documentIds;
    double executionTime;
    int numComparisons;
    // <Possíveis outras variáveis>
};

void printIndex(BinaryTree* tree);

void saveTree(BinaryTree* tree);

void printTree(BinaryTree* tree);
