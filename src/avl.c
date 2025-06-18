#include <time.h>
#include <time.h>
#include "avl.h"

BinaryTree* createAVL() {
    BinaryTree* tree = (BinaryTree*) malloc(sizeof(BinaryTree));
    if (!tree) {
        printf("Error in create(): memory allocation failed\n");
        exit(1);
    }
    tree->root = NULL;
    tree->NIL = NULL;
    return tree;
}

Node* createNodeAVL(const string word, int documentId) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (!node) {
        printf("Error in createNodeAVL(): memory allocation failed\n");
        exit(1);
    }

    string wordCopy = malloc(strSize(word) + 1);
    strCopy(word, wordCopy);
    node->word = wordCopy;

    node->documentIds = createList("int");
    insertValue(node->documentIds, &documentId);

    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;

    return node;
}

// Get the height of a node (0 if node is NULL)
int getHeight(Node* node) {
    return (node == NULL) ? -1 : node->height;
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

    // rotation
    x->right = y;
    y->left = T2;

    // Update parents if needed
    if (T2 != NULL) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;
    if (!x->parent);
    else if (x->parent->left == y) x->parent->left = x;
    else x->parent->right = x;


    updateHeight(y);
    updateHeight(x);

    return x; // new  "root" after rotation
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // rotation
    y->left = x;
    x->right = T2;

    // Update parents if needed
    if (T2 != NULL) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    if (!y->parent);
    else if (y->parent->left == x) y->parent->left = y;
    else y->parent->right = y;

    updateHeight(x);
    updateHeight(y);

    return y; // new "root" after rotation
}

// Rebalance function - returns the new "root" of the subtree after balancing
Node* rebalance(Node* node) {
    if (node == NULL) return node;

    updateHeight(node);
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

    return node;
}

struct InsertResult insertAVL(BinaryTree* tree, const string word, int documentId) {
    struct InsertResult result = {0};
    result.status = 0; // Defaults to failed
    result.numComparisons = 0;
    clock_t start = clock();

    if (!tree || !word) {
        return result;
    }

    if (tree->root == NULL) {
        // Tree is empty, create root node
        tree->root = createNodeAVL(word, documentId);
        if (tree->root == NULL) {
            return result;
        }
        result.status = 1;
        result.numComparisons = 1;
        result.executionTime = (double)(clock() - start) / CLOCKS_PER_SEC;
        return result;
    }

    Node* current = tree->root;
    Node* parent = NULL;
    int cmp = 0;

    // Search the tree to find the insert position or duplicate
    while (current != NULL) {
        parent = current;
        cmp = strcmp(word, current->word);
        result.numComparisons++;

        if (cmp == 0) {
            // Word already exists, add documentId if new
            int idFound = 0;
            node* listIt = current->documentIds->tail;
            while (listIt != NULL) {
                if (*((int*) listIt->value) == documentId) {
                    idFound = 1;
                    break;
                }
                listIt = listIt->prev;
            }
            if (!idFound) {
                insertValue(current->documentIds, &documentId);
            }
            result.status = 2;
            result.executionTime = (double)(clock() - start) / CLOCKS_PER_SEC;
            return result;
        } 
        else if (cmp < 0) {
            current = current->left;
        } 
        else {
            current = current->right;
        }
    }

    Node* newNode = createNodeAVL(word, documentId);
    if (newNode == NULL) {
        return result;
    }
    newNode->parent = parent;

    if (cmp < 0) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Rebalance tree starting from the new node's parent
    Node* rebNode = newNode;

    while (rebNode != NULL) {
        if (rebNode->left == tree->root || rebNode->right == tree->root) tree->root = rebNode;
        rebNode = rebalance(rebNode);
        if (rebNode->left == tree->root || rebNode->right == tree->root) tree->root = rebNode;
        rebNode = rebNode->parent;
    }

    result.status = 1;
    result.executionTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    return result;
}

struct SearchResult searchAVL(BinaryTree* tree, const string word) {
    struct SearchResult result;
    result.found = 0;
    result.documentIds = NULL;
    result.executionTime = 0.0;
    result.numComparisons = 0;

    if (tree == NULL || tree->root == NULL || word == NULL) {
        return result;
    }

    clock_t start = clock();

    Node* current = tree->root;
    while (current != NULL) {
        result.numComparisons++;
        int cmp = strcmp(word, current->word);
        if (cmp == 0) {
            // Word found
            result.found = 1;
            result.documentIds = current->documentIds;
            break;
        }
        else if (cmp < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    clock_t end = clock();
    result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    return result;
}

void destroyNodeAVL(Node* node) {
    if (node != NULL) {
        destroyNodeAVL(node->left);
        destroyNodeAVL(node->right);
        freeList(node->documentIds);
        free(node->word);
        free(node);
    }
}

void destroyAVL(BinaryTree* tree) {
    if (tree != NULL) {
        destroyNodeAVL(tree->root);
        free(tree);
    }
}
