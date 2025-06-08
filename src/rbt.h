#include "tree_utils.h"
#include <time.h>

BinaryTree* createRBT();

struct InsertResult insertRBT(BinaryTree* tree, const string word, int documentId);

struct SearchResult searchRBT(BinaryTree* tree, const string word);

void destroyRBT(BinaryTree* tree);