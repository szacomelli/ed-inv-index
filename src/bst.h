#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree_utils.h"  // typedefs tNode, bTree, InsertResult, SearchResult, createtNode(), createTree()

/*
Creates a Binary Search Tree. In fact, is just a define for the
createTree in tree_utils.
*/
#define create() createTree();

/*
Inserts a string and one integer in a tree, where each node has a different
word and, for every word, a list of integers associated with it.
Also returns a struct with stats about inserting performance.
*/
struct InsertResult insert(bTree* tree, string word, int docId);

/*
Searches for a word in the tree. Returns the struct SearchResult
with stats about the searching and also if the word as found.
*/
struct SearchResult search(bTree* tree, string word);

/*
Frees a tree, its nodes and also the list of IDs and the words.
*/
void destroy(bTree* tree);
