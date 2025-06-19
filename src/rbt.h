#include "tree_utils.h"
#include <time.h>

/* @brief Creates and initializes an empty RBT tree.
 *
 * @return A pointer to the newly created RBT tree.
 *         - If memory allocation fails, the function returns NULL.
 */
BinaryTree* createRBT();

/* @brief Inserts a word and its associated document ID into the RBT tree.
 *
 * If the word already exists in the tree, the document ID is added to its list
 * if it is not already present. The tree is then rebalanced if necessary.
 *
 * @param tree Pointer to the RBT tree.
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
struct InsertResult insertRBT(BinaryTree* tree, string word, int documentId);

/* @brief Searches for a word in the RBT tree.
 *
 * @param tree Pointer to the RBT tree.
 * @param word The word to search for.
 *
 * @return A SearchResult struct containing:
 *         - found: 1 if the word was found, 0 otherwise.
 *         - documentIds: Pointer to the list of document IDs associated with the word (if found).
 *         - numComparisons: Number of string comparisons performed.
 *         - executionTime: Time taken for the search in seconds.
 */
struct SearchResult searchRBT(BinaryTree* tree, string word);

/* @brief Frees all memory allocated for the RBT tree and its nodes.
 *
 * This function frees the entire tree, including all nodes and
 * their associated resources.
 *
 * @param tree Pointer to the RBT tree to be destroyed.
 */
void destroyRBT(BinaryTree* tree);
