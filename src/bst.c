#include "bst.h"

static tNode *createNodeWithWord(string word, int docId)
{
    tNode *newNode = createtNode();
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for tNode.\n");
        exit(EXIT_FAILURE);
    }

    int len = strSize(word);
    newNode->word = (char *)malloc((len + 1) * sizeof(char));
    if (newNode->word == NULL)
    {
        fprintf(stderr, "Error: failed to allocate memory for word.\n");
        exit(EXIT_FAILURE);
    }
    printf("word: %s\n", word);
    strCopy(word, newNode->word);

    insertValue(newNode->documentIds, &docId);

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

static void printTreeRec(tNode *node, char *prefix, int isLast)
{
    if (node == NULL)
        return;

    printf("%s", prefix);

    if (isLast)
    {
        // printf("\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80 ");  // └──
        // printf("└── ");
        printf("|___ ");
    }
    else
    {
        // printf("\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80 ");  // ├──
        // printf("├── ");
        printf("|--- ");
    }

    printf("%s\n", node->word);

    size_t lenPrefix = strSize(prefix);
    char *newPrefix = (char *)malloc(lenPrefix + 5);
    if (newPrefix == NULL)
    {
        fprintf(stderr, "Error allocating memory for new prefix.\n");
        exit(EXIT_FAILURE);
    }

    if (isLast)
    {
        sprintf(newPrefix, "%s    ", prefix);
    }
    else
    {
        // sprintf(newPrefix, "%s\xE2\x94\x82   ", prefix);  // │
        // sprintf(newPrefix, "%s│   ", prefix);
        sprintf(newPrefix, "%s|   ", prefix);
    }

    int numChildren = 0;
    if (node->left)
        numChildren++;
    if (node->right)
        numChildren++;

    int processed = 0;
    if (node->left)
    {
        processed++;
        printTreeRec(node->left, newPrefix, (processed == numChildren));
    }
    if (node->right)
    {
        processed++;
        printTreeRec(node->right, newPrefix, (processed == numChildren));
    }

    free(newPrefix);
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
        newNode->parent = NULL;
        result.numComparisons = 1;
        clock_t end = clock();
        result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        return result;
    }

    // Second case: tree is not empty
    tNode *newNode = createNodeWithWord(word, docId);
    int duplicateFound = 0;
    tNode *updatedRoot = bstInsertRec(tree->root, newNode, &result.numComparisons, &duplicateFound);

    if (duplicateFound)
    {
        // If the word already exists, we do not change the root
        free(newNode->word);
        freeList(newNode->documentIds);
        free(newNode);

        // If the word already exists, we just add the document ID to the existing node
        int numCmp = 0;
        tNode *existing = bstSearchRec(updatedRoot, word, &numCmp);
        if (existing)
        {
            if (!lookupValue(existing->documentIds, &docId))
            {
                insertValue(existing->documentIds, &docId);
            }
        }
    }
    else
    {
        // If the word does not exist, we update the root
        tree->root = updatedRoot;
    }

    clock_t end = clock();
    result.executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    return result;
}

bTree *create()
{
    bTree *tree = malloc(sizeof(bTree));
    if (tree == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory for bTree.\n");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    tree->NIL = NULL;
    return tree;
}


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
    tNode *foundNode = bstSearchRec(tree->root, word, &result.numComparisons);
    if (foundNode)
    {
        result.found = 1;
        result.documentIds = foundNode->documentIds;
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

void printTreeT(bTree *tree)
{
    if (tree == NULL || tree->root == NULL)
        // If the tree is NULL or empty, we do not print anything
        return;

    // First, we print the root node
    printf("%s\n", tree->root->word);

    // Second, we prepare the prefix for the children
    int numChildren = 0;
    if (tree->root->left)
        numChildren++;
    if (tree->root->right)
        numChildren++;

    // Third, we print the children recursively
    int processed = 0;
    if (tree->root->left)
    {
        processed++;
        printTreeRec(tree->root->left, "", (processed == numChildren));
    }
    if (tree->root->right)
    {
        processed++;
        printTreeRec(tree->root->right, "", (processed == numChildren));
    }
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
