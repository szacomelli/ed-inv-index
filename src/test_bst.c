#include <stdio.h>
#include <assert.h>

#include "bst.h"

int main()
{
    printf("Running tests...\n");
    printf("Test 1\n");
    bTree* tree = create();
    assert(tree != NULL);


    // Test inserting a word
    printf("Test 2\n");
    
    struct InsertResult ir1 = insert(tree, "test", 1);
    struct InsertResult ir2 = insert(tree, "nescatibiribas", 2);

    assert(ir1.numComparisons > 0);
    assert(ir1.executionTime >= 0.0);

    assert(ir2.numComparisons > 0);
    assert(ir2.executionTime >= 0.0);

    printf("Test 3\n");

    // Test searching for the inserted word
    struct SearchResult sr = search(tree, "test");
    assert(sr.found == 1);
    assert(sr.documentIds->size == 1);
    assert(sr.numComparisons > 0);
    assert(sr.executionTime >= 0.0);

    printf("Test 4\n");


    // Test searching for a non-existent word
    sr = search(tree, "nonexistent");
    assert(sr.found == 0);
    assert(sr.documentIds == NULL);
    
    printf("Test 5\n");


    // Print the tree structure
    printTree(tree);

    // Clean up
    destroy(tree);
    free(tree);

    printf("All tests passed successfully!\n");
    return EXIT_SUCCESS;}