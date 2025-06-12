#include <stdio.h>
#include "avl.h"
//#include "tree_utils.h"

void create_test() {
    printf("--- Create test ---\n");
    BinaryTree* tree = createAVL();
    if (tree == NULL) {
        printf("Failed to create tree.\n\n");
        return;
    }
    printf("Tree created successfully.\n\n");

    free(tree);
}

void createNode_test() {
    printf("--- createNode test --- \n");
    Node* node = createNodeAVL("example", 42);
    if (node == NULL) {
        printf("Failed to create node.\n\n");
        return;
    }
    printf("Node created successfully.\n");

    if (node->documentIds != NULL && node->documentIds->head != NULL) {
        int firstDocId = *(int*)node->documentIds->head->value;
        printf("Node first document ID: %d\n\n", firstDocId);
    } else {
        printf("Node documentIds list is empty.\n\n");
    }

    // Manual cleanup
    free(node->word);
    free(node);
}


void test_insert() {
    printf("--- Insert test ---\n");

    BinaryTree* tree = createAVL();

    struct InsertResult res1 = insertAVL(tree, "apple", 1);
    if (res1.status != 1) {
        printf("Test failed: insert 'apple' first time\n\n");
        destroyAVL(tree);
        return;
    }

    struct InsertResult res2 = insertAVL(tree, "banana", 2);
    if (res2.status != 1) {
        printf("Test failed: insert 'banana' first time\n\n");
        destroyAVL(tree);
        return;
    }

    struct InsertResult res3 = insertAVL(tree, "apple", 3); // duplicate word, new docId
    if (res3.status != 2) {
        printf("Test failed: insert duplicate 'apple'\n\n");
        destroyAVL(tree);
        return;
    }

    // Check if documentId 3 was added to 'apple'
    Node* current = tree->root;
    while (current != NULL && strcmp(current->word, "apple") != 0) {
        if (strcmp("apple", current->word) < 0) current = current->left;
        else current = current->right;
    }

    if (current == NULL) {
        printf("Test failed: 'apple' node not found\n\n");
        destroyAVL(tree);
        return;
    }

    if (lookupValue(current->documentIds, &(int){3}) == -1) {
        printf("Test failed: documentId 3 not found for 'apple'\n\n");
        destroyAVL(tree);
        return;
    }

    printf("Insert test passed.\n\n");

    printf("New insert test for duplicate 'banana'\n");
    struct InsertResult res4 = insertAVL(tree, "banana", 2); // duplicate word, same docId
    if (res4.status != 2) {
        printf("Test failed: insert duplicate 'banana' with same docId\n\n");
        destroyAVL(tree);
        return;
    }

    printf("Insert test passed.\n\n");
    destroyAVL(tree);
}


void test_search() {
    printf("--- Search test ---\n");

    // Create a new binary AVL tree
    BinaryTree* tree = createAVL();

    // Insert words and their corresponding document IDs
    insertAVL(tree, "apple", 1);
    printTree(tree);
    insertAVL(tree, "banana", 2);
    printTree(tree);
    insertAVL(tree, "carrot", 3);
    printTree(tree);
    // Search for an existing word in the tree
    struct SearchResult res1 = searchAVL(tree, "banana");
    if (res1.found) {
        printf("Search test passed: 'banana' found.\n");
        printf("Number of comparisons: %d\n", res1.numComparisons);
        printf("Execution time: %.6f seconds\n", res1.executionTime);

        // Print all document IDs where 'banana' appears
        if (res1.documentIds != NULL) {
            printf("Document IDs for 'banana': ");
            node* iter = res1.documentIds->head;
            while (iter != NULL) {
                printf("%d ", *(int*)iter->value);
                iter = iter->next;
            }
            printf("\n");
        }
    } else {
        printf("Search test failed: 'banana' should be found.\n");
    }

    // Search for a word not present in the tree
    struct SearchResult res2 = searchAVL(tree, "durian");
    if (!res2.found) {
        printf("Search test passed: 'durian' correctly not found.\n");
    } else {
        printf("Search test failed: 'durian' should not be found.\n");
    }

    // Search for "apple" (likely to be the root)
    struct SearchResult res3 = searchAVL(tree, "apple");
    if (res3.found) {
        printf("Search test passed: 'apple' found.\n");
    } else {
        printf("Search test failed: 'apple' should be found.\n");
    }

    // Free the tree after testing
    destroyAVL(tree);
}


int main() {
    create_test();

    createNode_test();

    test_insert();

    test_search();

    return 0;
}
