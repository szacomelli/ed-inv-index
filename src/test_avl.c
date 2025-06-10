#include <stdio.h>
#include "avl.h"

int main() {
    BinaryTree* tree = create();
    if (tree == NULL) {
        printf("Failed to create tree.\n");
        return 1;
    }
    printf("Tree created successfully.\n");

    Node* node = createNode("example", 42);
    if (node == NULL) {
        printf("Failed to create node.\n");
        return 1;
    }
    printf("Node created successfully.\n");

    if (node->documentIds != NULL && node->documentIds->head != NULL) {
        int firstDocId = *(int*)node->documentIds->head->value;
        printf("Node first document ID: %d\n", firstDocId);
    } else {
        printf("Node documentIds list is empty.\n");
    }

    return 0;
}
