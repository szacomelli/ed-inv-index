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
