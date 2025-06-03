// #include <stdio.h>
// #include <stdlib.h>
#include <time.h>
#include "tree_utils.h"
// #include "lkdlist.h"  
// #include "str.h"     

bTree* create();

struct InsertResult insert(bTree* tree, string word, int docId);

struct SearchResult search(bTree* tree, string word);

void printTreeT(bTree* tree);

void destroy(bTree* tree);
