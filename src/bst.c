#include "bst.h"

static tNode *createNodeWithWord(string word, int docId)
{

    tNode *newNode = createtNode();
    // printList(newNode->documentIds);
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for tNode.\n");
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
    // printList(newNode->documentIds);


    return newNode;
}

static tNode *bstInsertRec(tNode *root, tNode *newNode, int *numCmp, int *duplicateFound)
{
    if (root == NULL)
    {
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
        tNode *leftChild = bstInsertRec(root->left, newNode, numCmp, duplicateFound);
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
        tNode *rightChild = bstInsertRec(root->right, newNode, numCmp, duplicateFound);
        if (!(*duplicateFound))
        {
            root->right = rightChild;
            rightChild->parent = root;
            rightChild->height = root->height + 1;
        }
    }

    return root;
}

static tNode *bstSearchRec(tNode *root, string word, int *numCmp)
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

static void bstFreeRec(tNode *root)
{
    if (root == NULL)
        return;

    bstFreeRec(root->left);
    bstFreeRec(root->right);

    freeList(root->documentIds);

    free(root->word);

    free(root);
}

// struct InsertResult insert(bTree *tree, string word, int docId)
// {
//     struct InsertResult result;
//     result.numComparisons = 0;
//     result.executionTime = 0.0;

//     if (tree == NULL)
//     {
//         fprintf(stderr, "Error: tree pointer is NULL\n");
//         return result;
//     }

//     clock_t start = clock();

//     // First case: tree is empty
//     if (tree->root == NULL)
//     {
//         tNode *newNode = createNodeWithWord(word, docId);
//         tree->root = newNode;
//         tree->root->height = 1;
//         newNode->parent = NULL;
//         result.numComparisons = 1;
//         clock_t end = clock();
//         result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
//         return result;
//     }

//     // Second case: tree is not empty
//     tNode *newNode = createNodeWithWord(word, docId);
//     int duplicateFound = 0;
//     tNode *updatedRoot = bstInsertRec(tree->root, newNode, &result.numComparisons, &duplicateFound);

//     if (duplicateFound)
//     {

//         // If the word already exists, we do not change the root
//         free(newNode->word);

//         freeList(newNode->documentIds);
//         free(newNode);


//         // If the word already exists, we just add the document ID to the existing node
//         tNode *existing = bstSearchRec(updatedRoot, word, &(int){0});
//         if (existing)

//         {

//             if (lookupValue(existing->documentIds, &docId) == -1)
//             {
//                 insertValue(existing->documentIds, &docId);
//             }
//         }
//     }
//     else
//     {
//         // If the word does not exist, we update the root
//         tree->root = updatedRoot;
//     }

//     clock_t end = clock();
//     result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

//     return result;
// }

int searchWord(tNode* node, string word, tNode** currNode, tNode** lastNode) {
    if (node == NULL) return 0;

    if (strcmp(node->word, word) == 0) {
        *currNode = node;
        return 1;
    }
    else if (strcmp(word, node->word) < 0) {
        if (!node->left) *lastNode = node;
        return searchWord(node->left, word, currNode, lastNode);
    }
    else {
        if (!node->right) *lastNode = node;
        return searchWord(node->right, word, currNode, lastNode);

    }
}

struct InsertResult insert(bTree *tree, string word, int docId)
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
        tNode *newNode = createNodeWithWord(word, docId);
        tree->root = newNode;
        tree->root->height = 1;
        newNode->parent = NULL;
        result.numComparisons = 1;
        clock_t end = clock();
        result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        return result;
    }

    // Second case: tree is not empty
    // tNode *newNode = createNodeWithWord(word, docId);
    // int duplicateFound = 0;
    // tNode *updatedRoot = bstInsertRec(tree->root, newNode, &result.numComparisons, &duplicateFound);

    tNode* lastNode = NULL;
    tNode* currNode = NULL;
    int isDuplicate = searchWord(tree->root, word, &currNode, &lastNode);


    if (isDuplicate)
    {
        insertValue(currNode->documentIds, &docId);
    }
    else
    {

        tNode *newNode = createNodeWithWord(word, docId);
        // printf("%s\n", word);
        if (strcmp(lastNode->word, newNode->word) < 0) {
            lastNode->right = newNode;
            newNode->parent = lastNode;
            newNode->height = newNode->parent->height + 1;

        }
        else {
            lastNode->left = newNode;
            newNode->parent = lastNode;
            newNode->height = newNode->parent->height + 1;

        }
    }

    clock_t end = clock();
    result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    return result;
}

// struct SearchResult search(bTree *tree, string word)
// {
//     struct SearchResult result;
//     result.found = 0;
//     result.documentIds = NULL;
//     result.numComparisons = 0;
//     result.executionTime = 0.0;

//     if (tree == NULL || tree->root == NULL)
//     {
//         // If the tree is NULL or empty, we return an empty result
//         return result;
//     }

//     clock_t start = clock();

//     // recursive search
//     tNode *foundNode = bstSearchRec(tree->root, word, &result.numComparisons);
//     if (foundNode)
//     {
//         result.found = 1;
//         result.documentIds = foundNode->documentIds;
//     }
//     else
//     {
//         result.found = 0;
//         result.documentIds = NULL;
//     }

//     clock_t end = clock();
//     result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
//     return result;
// }

struct SearchResult search(bTree *tree, string word)
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

    // recursive search
    // tNode *foundNode = bstSearchRec(tree->root, word, &result.numComparisons);
    tNode* lastNode = NULL;
    tNode* currNode = NULL;
    int wordFound = searchWord(tree->root, word, &currNode, &lastNode);
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

void destroy(bTree *tree)
{
    if (tree == NULL)
        return;
    if (tree->root != NULL)
    {
        bstFreeRec(tree->root);
        tree->root = NULL;
    }
}
