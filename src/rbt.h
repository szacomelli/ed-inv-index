#include "tree_utils.h"
#include <time.h>

BinaryTree* createRBT();

struct InsertResult insertRBT(BinaryTree* tree, string word, int documentId);

struct SearchResult searchRBT(BinaryTree* tree, string word);

void destroyRBT(BinaryTree* tree);
