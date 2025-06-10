#include <stdio.h>
#include "avl.h"

void create_test() {
    printf("--- Create test ---\n");
    BinaryTree* tree = create();
    if (tree == NULL) {
        printf("Failed to create tree.\n\n");
        return;
    }
    printf("Tree created successfully.\n\n");
}

void createNode_test() {
    printf("--- createNode test --- \n");
    Node* node = createNode("example", 42);
    if (node == NULL) {
        printf("Failed to create node.\n\n");
        return 1;
    }
    printf("Node created successfully.\n");

    if (node->documentIds != NULL && node->documentIds->head != NULL) {
        int firstDocId = *(int*)node->documentIds->head->value;
        printf("Node first document ID: %d\n\n", firstDocId);
    } else {
        printf("Node documentIds list is empty.\n\n");
    }
}


void test_insert() {
    printf("--- Insert test ---\n");

    BinaryTree* tree = create();

    InsertResult res1 = insert(tree, "apple", 1);
    if (res1.status != INSERT_SUCCESS) {
        printf("Test failed: insert 'apple' first time\n\n");
        return;
    }

    InsertResult res2 = insert(tree, "banana", 2);
    if (res2.status != INSERT_SUCCESS) {
        printf("Test failed: insert 'banana' first time\n\n");
        return;
    }

    InsertResult res3 = insert(tree, "apple", 3); // duplicate word, new docId
    if (res3.status != INSERT_DUPLICATE) {
        printf("Test failed: insert duplicate 'apple'\n\n");
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
        return;
    }

    if (lookupValue(current->documentIds, &(int){3}) == -1) {
        printf("Test failed: documentId 3 not found for 'apple'\n\n");
        return;
    }

    printf("Insert test passed.\n\n");
}


int main() {
    create_test();

    createNode_test();

    test_insert();

    return 0;
}
