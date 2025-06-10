#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

// Creates and initializes an empty AVL tree
BinaryTree* create() {
    BinaryTree* tree = (BinaryTree*) malloc(sizeof(BinaryTree));
    if (!tree) {
        printf("Error in create(): memory allocation failed\n");
        exit(1);
    }
    tree->root = NULL;
    return tree;
}

// Creates a new node with the given word and document ID
Node* createNode(const string word, int documentId) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) {
        printf("Error in createNode(): memory allocation failed\n");
        exit(1);
    }

    // Copy the word into a new allocated string
    string wordCopy = malloc(strSize(word) + 1);
    strCopy(word, wordCopy);
    node->word = wordCopy;

    // Create the list of document IDs and insert the first one
    node->documentIds = createList("int");
    insertValue(node->documentIds, &documentId);

    // Initialize AVL node metadata
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

// Get the height of a node (0 if node is NULL)
int getHeight(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Update the height of a node based on children heights
void updateHeight(Node* node) {
    if (node != NULL) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

// Calculate balance factor of a node (left height - right height)
int getBalanceFactor(Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update parents if needed
    if (T2 != NULL) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x; // new root after rotation
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update parents if needed
    if (T2 != NULL) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y; // new root after rotation
}

// Rebalance function - returns the new root of the subtree after balancing
Node* rebalance(Node* node) {
    if (node == NULL) return node;

    // Update height of this ancestor node
    updateHeight(node);

    // Get balance factor
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Already balanced
    return node;
}
