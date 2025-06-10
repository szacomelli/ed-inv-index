#ifndef AVL_H
#define AVL_H

#include "lkdlist.h"
#include "str.h"

// Forward declaration of Node struct
typedef struct Node {
    string word;        // Word stored in this node
    lkdList* documentIds; // List of document IDs where the word appears
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int height;         // Height of the node for balancing
} Node;

typedef struct {
    Node* root;         // Root of the AVL tree
} BinaryTree;

// Result of insert operation
typedef struct {
    int numComparisons;    // Number of comparisons performed during insert
    double executionTime;  // Execution time of insert in seconds
    // Add other metrics if needed
} InsertResult;

// Result of search operation
typedef struct {
    int found;             // 1 if word found, 0 otherwise
    lkdList* documentIds;  // List of document IDs where word appears (NULL if not found)
    double executionTime;  // Execution time of search in seconds
    int numComparisons;    // Number of comparisons performed during search
    // Add other metrics if needed
} SearchResult;

// Creates and initializes a new empty AVL tree
BinaryTree* create();

// Inserts a word with the associated document ID into the AVL tree
InsertResult insert(BinaryTree* tree, const string word, int documentId);

// Searches for a word in the AVL tree and returns info about it
SearchResult search(BinaryTree* tree, const string word);

// Frees all memory allocated for the AVL tree
void destroy(BinaryTree* tree);

#endif // AVL_H
