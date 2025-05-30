#ifndef BST_UTILS_H
#define BST_UTILS_H

#include "tree_utils.h"
#include "str.h"
#include "lkdlist.h"

bTree* createBSTWithRoot(string rootWord);
void insertBST(bTree* tree, string word, int docId);
void removeBST(bTree* tree, string word);
void buildBSTFromList(bTree* tree, string* wordList, int* docIds);
tNode* insertNodeBST(tNode* root, tNode* newNode, tNode** insertedNode);
tNode* removeNodeBST(tNode* root, string word);
tNode* minValueNode(tNode* node);
tNode* searchNodeBST(tNode* root, string word, int* comparisons);
void inOrderPrint(tNode* root);

#endif