// #include <stdio.h>
// #include <stdlib.h>
#include <time.h>
#include "tree_utils.h"
// #include "lkdlist.h"
// #include "str.h"

/* @brief Creates an empty binary tree.
 *
 * @return A pointer to the root of the binary tree
 *         - If the tree is empty, returns NULL
 *         - If the tree is not empty, returns a pointer to the root of the tree
 */
bTree *create();

/* @brief Inserts a word into the binary tree.
 *
 * @param tree Pointer to the binary tree
 * @param word The word to be inserted
 * @param docId The document ID where the word is found
 *
 * @return An InsertResult struct containing the number of comparisons and the execution time
 *         - numComparisons: Number of comparisons made during insertion
 *         - executionTime: Time taken to perform the insertion in seconds
 */
struct InsertResult insert(bTree *tree, string word, int docId);

/* @brief Searches for a word in the binary tree.
 *
 * @param tree Pointer to the binary tree
 * @param word The word to be searched
 *
 * @return A SearchResult struct containing the search result
 *         - found: 1 if the word was found, 0 otherwise
 *         - documentIds: A linked list of document IDs where the word was found
 */
struct SearchResult search(bTree *tree, string word);

/* @brief Destroys the binary tree
 *
 * @detail This function frees all the memory allocated for the binary tree and its nodes.
 *
 * @param tree Pointer to the binary tree
 */
void destroy(bTree *tree);
