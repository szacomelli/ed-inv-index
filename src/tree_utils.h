#include "str.h"
#include "lkdlist.h"

typedef struct Node {
    string word;
    lkdList* documentIds;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
} Node;

typedef struct BinaryTree {
    Node* root;
    Node* NIL;  // usado na RBT (Opcional)
} BinaryTree;

Node* createNode();

BinaryTree* createTree();

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
