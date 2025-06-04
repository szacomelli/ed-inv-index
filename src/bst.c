#include "bst.h"

static Node *createNodeWithWord(string word, int docId)
{
    Node *newNode = createNode();
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for Node.\n");
        exit(EXIT_FAILURE);
    }

    int len = strSize(word);
    newNode->word = (string)malloc((len + 1) * sizeof(char));
    if (newNode->word == NULL)
    {
        fprintf(stderr, "Error: failed to allocate memory for word.\n");
        exit(EXIT_FAILURE);
    }
    strCopy(word, newNode->word);

    insertValue(newNode->documentIds, &docId);
    return newNode;
}

static Node *bstInsertRec(Node *root, Node *newNode, int *numCmp, int *duplicateFound)
{
    if (root == NULL)
    {
        // if tree is empty, newNode becomes root
        return newNode;
    }

    (*numCmp)++;
    int cmp = strcmp(newNode->word, root->word);
    if (cmp == 0)
    {
        // duplicate word
        *duplicateFound = 1;
        return root;
    }
    else if (cmp < 0)
    {
        // if newNode->word < root->word -> follow left subtree
        Node *leftChild = bstInsertRec(root->left, newNode, numCmp, duplicateFound);
        if (!(*duplicateFound))
        {
            root->left = leftChild;
            leftChild->parent = root;
            leftChild->height = root->height + 1;
        }
    }
    else
    {
        // if newNode->word > root->word -> follow right subtree
        Node *rightChild = bstInsertRec(root->right, newNode, numCmp, duplicateFound);
        if (!(*duplicateFound))
        {
            root->right = rightChild;
            rightChild->parent = root;
            rightChild->height = root->height + 1;
        }
    }

    return root;
}

static Node *bstSearchRec(Node *root, string word, int *numCmp)
{
    if (root == NULL)
    {
        return NULL;
    }

    (*numCmp)++;
    int cmp = strcmp(word, root->word);
    if (cmp == 0)
    {
        return root;
    }
    else if (cmp < 0)
    {
        return bstSearchRec(root->left, word, numCmp);
    }
    else
    {
        return bstSearchRec(root->right, word, numCmp);
    }
}

static void bstFreeRec(Node *root)
{
    if (root == NULL)
        return;

    bstFreeRec(root->left);
    bstFreeRec(root->right);

    freeList(root->documentIds);

    free(root->word);

    free(root);
}

int searchWord(Node* node, string word, Node** currNode, Node** lasNode) {
    if (node == NULL) return 0;

    if (strcmp(node->word, word) == 0) {
        *currNode = node;
        return 1;
    }
    else if (strcmp(word, node->word) < 0) {
        if (!node->left) *lasNode = node;
        return searchWord(node->left, word, currNode, lasNode);
    }
    else {
        if (!node->right) *lasNode = node;
        return searchWord(node->right, word, currNode, lasNode);
    }
}

struct InsertResult insert(BinaryTree *tree, string word, int docId)
{
    struct InsertResult result;
    result.numComparisons = 0;
    result.executionTime = 0.0;

    if (tree == NULL)
    {
        fprintf(stderr, "Error: tree pointer is NULL\n");
        return result;
    }

    clock_t start = clock();

    // First case: tree is empty
    if (tree->root == NULL)
    {
        Node *newNode = createNodeWithWord(word, docId);
        tree->root = newNode;
        tree->root->height = 1;
        newNode->parent = NULL;
        result.numComparisons = 1;
        clock_t end = clock();
        result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        return result;
    }

    // Second case: tree is not empty
    // Node *newNode = createNodeWithWord(word, docId);
    // int duplicateFound = 0;
    // Node *updatedRoot = bstInsertRec(tree->root, newNode, &result.numComparisons, &duplicateFound);

    Node* lasNode = NULL;
    Node* currNode = NULL;
    int isDuplicate = searchWord(tree->root, word, &currNode, &lasNode);


    if (isDuplicate)
    {
        insertValue(currNode->documentIds, &docId);
    }
    else
    {

        Node *newNode = createNodeWithWord(word, docId);
        // printf("%s\n", word);
        if (strcmp(lasNode->word, newNode->word) < 0) {
            lasNode->right = newNode;
            newNode->parent = lasNode;
            newNode->height = newNode->parent->height + 1;

        }
        else {
            lasNode->left = newNode;
            newNode->parent = lasNode;
            newNode->height = newNode->parent->height + 1;

        }
    }

    clock_t end = clock();
    result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    return result;
}

struct SearchResult search(BinaryTree *tree, string word)
{
    struct SearchResult result;
    result.found = 0;
    result.documentIds = NULL;
    result.numComparisons = 0;
    result.executionTime = 0.0;

    if (tree == NULL || tree->root == NULL)
    {
        // If the tree is NULL or empty, we return an empty result
        return result;
    }

    clock_t start = clock();
    Node* lasNode = NULL;
    Node* currNode = NULL;
    int wordFound = searchWord(tree->root, word, &currNode, &lasNode);
    if (wordFound)
    {
        result.found = 1;
        result.documentIds = currNode->documentIds;
        result.numComparisons = currNode->height;
    }
    else
    {
        result.found = 0;
        result.documentIds = NULL;
    }

    clock_t end = clock();
    result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    return result;
}

void destroy(BinaryTree *tree)
{
    if (tree == NULL)
        return;
    if (tree->root != NULL)
    {
        bstFreeRec(tree->root);
        tree->root = NULL;
        free(tree);
    }
}
