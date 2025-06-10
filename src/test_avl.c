#include <stdio.h>
#include "avl.h"
//#include "tree_utils.h"

void create_test() {
    printf("--- Create test ---\n");
    BinaryTree* tree = create();
    if (tree == NULL) {
        printf("Failed to create tree.\n\n");
        return;
    }
    printf("Tree created successfully.\n\n");

    free(tree);
}

void createNode_test() {
    printf("--- createNode test --- \n");
    Node* node = createNode("example", 42);
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

    BinaryTree* tree = create();

    InsertResult res1 = insert(tree, "apple", 1);
    if (res1.status != INSERT_SUCCESS) {
        printf("Test failed: insert 'apple' first time\n\n");
        free(tree);
        return;
    }

    InsertResult res2 = insert(tree, "banana", 2);
    if (res2.status != INSERT_SUCCESS) {
        printf("Test failed: insert 'banana' first time\n\n");
        free(tree);
        return;
    }

    InsertResult res3 = insert(tree, "apple", 3); // duplicate word, new docId
    if (res3.status != INSERT_DUPLICATE) {
        printf("Test failed: insert duplicate 'apple'\n\n");
        free(tree);
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
        free(tree);
        return;
    }

    if (lookupValue(current->documentIds, &(int){3}) == -1) {
        printf("Test failed: documentId 3 not found for 'apple'\n\n");
        free(tree);
        return;
    }

    printf("Insert test passed.\n\n");
    free(tree);
}


void test_search() {
    printf("--- Search test ---\n");

    // Create a new binary AVL tree
    BinaryTree* tree = create();

    // Insert words and their corresponding document IDs
    insert(tree, "apple", 1);
    insert(tree, "banana", 2);
    insert(tree, "carrot", 3);

    // Search for an existing word in the tree
    SearchResult res1 = search(tree, "banana");
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
    SearchResult res2 = search(tree, "durian");
    if (!res2.found) {
        printf("Search test passed: 'durian' correctly not found.\n");
    } else {
        printf("Search test failed: 'durian' should not be found.\n");
    }

    // Free the tree after testing
    destroy(tree);
}


int main() {
    create_test();

    createNode_test();

    test_insert();

    test_search();

    return 0;
}
