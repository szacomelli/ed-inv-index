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

int searchWord(Node* node, string word, Node** currNode, Node** lasNode) {
    if (node == NULL) return 0;

    if (strcmp(node->word, word) == 0) {
        *currNode = node;
        return 1;
    }
    else if (strcmp(word, node->word) < 0) {
        if (!node->left) *lasNode = node;
        return searchWord(node->left, word, currNode, lasNode) + 1;
    }
    else {
        if (!node->right) *lasNode = node;
        return searchWord(node->right, word, currNode, lasNode) + 1;
    }
}

int updateHeight(Node *node, string word) {
   if (!node) return -1;
   if (strcmp(word, node->word) < 0) {
      int leftHeight = updateHeight(node->left, word);
      node->height = leftHeight > node->right->height ? leftHeight + 1 : node->right->height + 1;
      return node->height;
   }
   else if (strcmp(word, node->word) > 0) {
      int rightHeight = updateHeight(node->right, word);
      node->height = rightHeight > node->left->height ? rightHeight + 1 : node->left->height + 1;
      return node->height;
   }
   else return node->height;
}

struct InsertResult insertBST(BinaryTree *tree, string word, int docId)
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
        result.numComparisons = 0;
        clock_t end = clock();
        result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        return result;
    }

    // Second case: tree is not empty
    Node* lasNode = NULL;
    Node* currNode = NULL;
    result.numComparisons = searchWord(tree->root, word, &currNode, &lasNode);

    if (currNode) // If currNode isn't NULL (i.e. if word was founded and the pointer changed)
    {
        insertValue(currNode->documentIds, &docId);
    }
    else
    {

        Node *newNode = createNodeWithWord(word, docId);
        if (strcmp(lasNode->word, newNode->word) < 0) {
            lasNode->right = newNode;
            newNode->parent = lasNode;
            newNode->height = 0;

        }
        else {
            lasNode->left = newNode;
            newNode->parent = lasNode;
            newNode->height = 0;

        }
        updateHeight(tree->root, word);
    }

    clock_t end = clock();
    result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    return result;
}

struct SearchResult searchBST(BinaryTree *tree, string word)
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
    result.numComparisons = searchWord(tree->root, word, &currNode, &lasNode);
    if (currNode)
    {
        result.found = 1;
        result.documentIds = currNode->documentIds;
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

static void bstFreeRec(Node *root) {
    if (root == NULL)
        return;
    bstFreeRec(root->left);
    bstFreeRec(root->right);
    freeList(root->documentIds);
    root->documentIds = NULL;
    free(root->word);
    root->word = NULL;
    free(root);
    root = NULL;
}

void destroyBST(BinaryTree *tree)
{
    if (tree == NULL)
        return;
    if (tree->root != NULL)
    {
        bstFreeRec(tree->root);
        tree->root = NULL;
        free(tree);
        tree = NULL;
    }
}
