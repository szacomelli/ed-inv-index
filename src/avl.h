#ifndef AVL_H
#define AVL_H
#include "tree_utils.h"  // typedefs Node, BinaryTree, InsertResult, SearchResult, plus list helpers

/* @brief Creates and initializes an empty AVL tree.
 *
 * @return A pointer to the newly created AVL tree.
 *         - If memory allocation fails, the program will exit.
 */
BinaryTree* createAVL();

/* @brief Creates a new AVL tree node with the given word and document ID.
 *
 * This function duplicates the word string and creates
 * an empty list for document IDs, then inserts the given document ID.
 *
 * @param word The word to be stored in the node.
 * @param documentId The document ID associated with the word.
 *
 * @return A pointer to the newly created node.
 *         - If memory allocation fails, the program will exit.
 */
Node* createNodeAVL(const string word, int documentId);

/* @brief Inserts a word and its associated document ID into the AVL tree.
 *
 * If the word already exists in the tree, the document ID is added to its list
 * if it is not already present. The tree is then rebalanced if necessary.
 *
 * @param tree Pointer to the AVL tree.
 * @param word The word to be inserted.
 * @param documentId The document ID associated with the word.
 *
 * @return An InsertResult struct containing:
 *         - status: 1 if insertion or document ID addition succeeded,
 *                   2 if word already existed and document ID was added,
 *                   0 on failure.
 *         - numComparisons: Number of string comparisons performed.
 *         - executionTime: Time taken for the insertion in seconds.
 */
struct InsertResult insertAVL(BinaryTree* tree, const string word, int documentId);

/* @brief Searches for a word in the AVL tree.
 *
 * @param tree Pointer to the AVL tree.
 * @param word The word to search for.
 *
 * @return A SearchResult struct containing:
 *         - found: 1 if the word was found, 0 otherwise.
 *         - documentIds: Pointer to the list of document IDs associated with the word (if found).
 *         - numComparisons: Number of string comparisons performed.
 *         - executionTime: Time taken for the search in seconds.
 */
struct SearchResult searchAVL(BinaryTree* tree, const string word);

/* @brief Frees all memory allocated for a single AVL tree node and its contents.
 *
 * This includes the word string, the list of document IDs,
 * and recursively frees its left and right children.
 *
 * @param node Pointer to the node to be destroyed.
 */
void destroyNodeAVL(Node* node);

/* @brief Frees all memory allocated for the AVL tree and its nodes.
 *
 * This function frees the entire tree, including all nodes and
 * their associated resources.
 *
 * @param tree Pointer to the AVL tree to be destroyed.
 */
void destroyAVL(BinaryTree* tree);

#endif
