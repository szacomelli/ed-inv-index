#include <stdio.h>
#include "tree_utils.h"

tNode* createNode() {
    tNode* node = malloc(sizeof(tNode));
    node->word = NULL;

    node->documentIds = createList("int");
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = -1;    // usado na AVL
    node->isRed = 0;
    return node;
}
