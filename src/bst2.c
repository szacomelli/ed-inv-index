#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree_utils.h"  // typedefs tNode, bTree, InsertResult, SearchResult, createtNode(), createTree()
#include "lkdlist.h"     // lkdList, createList(), insertValue(), lookupValue(), freeList(), printList()
#include "str.h"         // strcmp (implementação própria), strCopy(), strSize()


struct InsertResult insert(bTree* tree, string word, int docId);

struct SearchResult search(bTree* tree, string word);

void printTree(bTree* tree);

void destroy(bTree* tree);

void insertValue(bTree* tree, tNode* node) {

}


struct InsertResult insert(bTree* tree, string word, int docId) {
    //comecar contar tempo


}
