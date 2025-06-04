#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree_utils.h"  // typedefs tNode, BinaryTree, InsertResult, SearchResult, createtNode(), createTree()

/* @brief Creates an empty binary tree.
 *
 * @return A pointer to the the binary tree
 *         - If the tree is empty, returns NULL
 *         - If the tree is not empty, returns a pointer to the tree
 */
#define create() createTree();

/* @brief Inserts a word and its associated ID into the binary tree.
 *
 * @param tree Pointer to the binary tree
 * @param word The word to be inserted
 * @param docId The document ID where the word is found
 *
 * @return An InsertResult struct containing the number of comparisons and the execution time
 *         - numComparisons: Number of comparisons made during insertion
 *         - executionTime: Time taken to perform the insertion in seconds
 */
struct InsertResult insert(BinaryTree* tree, string word, int docId);

/* @brief Searches for a word in the binary tree.
 *
 * @param tree Pointer to the binary tree
 * @param word The word to be searched
 *
 * @return A SearchResult struct containing the search result
 *         - found: 1 if the word was found, 0 otherwise
 *         - documentIds: A linked list of document IDs where the word was found
 */
struct SearchResult search(BinaryTree* tree, string word);

/* @brief Frees the binary tree, its nodes, words and ID lists.
 *
 * @detail This function frees all the memory allocated for the binary tree and its nodes.
 *
 * @param tree Pointer to the binary tree
 */
void destroy(BinaryTree* tree);
