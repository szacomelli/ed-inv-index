#include "rbt.h"

int test_create(int* total) {
    printf("\n============test_create_tree=============\n");
    BinaryTree* tree = createRBT();
    int errors = 0;
    int tests = 0;
    printf("-Teste %2d: ", tests++);
    if (!tree) {
        printf("Critical error in \"createTree()\": tree not allocated;\n");
        errors++;
    }
    else {
        printf("Ok;\n-Teste %2d: ", tests++);
        if (tree->root) {
            printf("Error in \"createTree()\": root value isn't NULL;\n");
            errors++;
        } else printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (strcmp(tree->NIL->word, "NIL")) {
            printf("Error in \"createTree()\": leaf word isn't NIL;\n");
            errors++;
        } else printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (tree->NIL->height != -1) {
            printf("Error in \"createTree()\": leaf height different from 0;\n");
            errors++;
        } else printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (tree->NIL->isRed != 0) {
            printf("Error in \"createTree()\": leaf is not a black node;\n");
            errors++;
        } else printf("Ok;\n");
    }
    printf("\nRealized a total of %d tests.\n", tests);
    printf("===========end_test_create_tree==========\n");
    *total += tests;
    return errors;
}

int test_insertion(int* total) {
    printf("\n==============test_insertion=============\n");
    int errors = 0;
    int tests = 0;
    BinaryTree* tree = createRBT();
    struct InsertResult results;
    results = insertRBT(NULL, "null", 0);
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons) {
        errors++;
        printf("Error in \"insert()\": realizing comparison in NULL;\n");
    } else printf("Ok;\n");
    results = insertRBT(tree, "root", 0);
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 1) {
        errors++;
        printf("Error in \"insert()\": realizing more comparisons than needed;\n");
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (tree->root->isRed != 0) {
        printf("Error in \"insert()\": root inserted isn't a black node;\n");
        errors++;
    } else printf("Ok;\n");
    results = insertRBT(tree, "left", 0);
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 2){
        errors++;
        printf("Error in \"insert()\": realizing more comparisons than needed;\n");    
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (tree->root->left->isRed != 1) {
        printf("Error in \"insert()\": node inserted must be red;\n");
        errors++;
    } else printf("Ok;\n");
    results = insertRBT(tree, "right", 0);
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 3){
        errors++;
        printf("Error in \"insert()\": realizing more comparisons than needed;\n");    
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (tree->root->isRed != 0) {
        printf("Error in \"insert()\": root isn't a black node;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (tree->root->right->isRed != 1) {
        printf("Error in \"insert()\": right node after rotation must be red;\n");
        errors++;
    } else printf("Ok;\n");
    results = insertRBT(tree, "tree", 0);
    printf("-Teste %2d: ", tests++);
    if (tree->root->right->isRed != 0) {
        printf("Error in \"insert()\": second layer must be black after new insertion;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (tree->root->left->isRed != 0) {
        printf("Error in \"insert()\": second layer must be black after new insertion;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (tree->root->right->right->isRed != 1) {
        printf("Error in \"insert()\": second layer must be black after new insertion;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 2){
        errors++;
        printf("Error in \"insert()\": realizing more comparisons than needed;\n");    
    } else printf("Ok;\n");
    results = insertRBT(tree, "right", 1);
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 4){
        errors++;
        printf("Error in \"insert()\": realizing more comparisons than needed;\n");    
    } else printf("Ok;\n");
    Node* root = tree->root;
    printf("-Teste %2d: ", tests++);
    if (!root) {
        printf("Error in \"insert()\": Root was not inserted;\n");
        errors++;
    } else {
        printf("Ok;\n-Teste %2d: ", tests++);
        if (root->documentIds->size != 2) {
            printf("Error in \"insert()\": IDs on root is wrong;\n");
            errors++;
        } else printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (strcmp(root->word, "right")) {
            printf("Error in \"insert()\": wrong word inserted on root;\n");
            errors++;    
        } else printf("Ok;\n");
    }
    printf("-Teste %2d: ", tests++);
    if (!root->left) {
        printf("Error in \"insert()\": Node on left not inserted;\n");
        errors++;
    } else {
        printf("Ok;\n-Teste %d: ", tests++);
        if (strcmp(root->left->word, "left")) {
            printf("Error in \"insert()\": wrong word inserted on root->left;\n");
            errors++;
        } else printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (root->left->documentIds->size != 1) {
            printf("Error in \"insert()\": IDs on root->left is wrong;\n");
            errors++;
        } else printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (root->right->right == NULL) {
            printf("Error in \"insert()\": Node on right->right not inserted;\n");
            errors++;
        } else {
            printf("Ok;\n-Teste %d: ", tests++);
            if (strcmp(root->right->right->word, "tree")) {
                printf("Error in \"insert()\": wrong word inserted on root->right->right;\n");
                errors++;
            } else printf("Ok;\n");
            printf("-Teste %2d: ", tests++);
            if (root->right->right->documentIds->size != 1) {
                printf("Error in \"insert()\": IDs on root->right->right is wrong;\n");
                errors++;
            } else printf("Ok;\n");
            results = insertRBT(tree, "right", 0);
            printf("-Teste %2d: ", tests++);
            if (root->right->right->documentIds->size != 1) {
                printf("Error in \"insert()\": size of documentIds different than expected;\n");
                errors++;
            } else printf("Ok;\n");
        }
    }
    printf("-Teste %2d: ", tests++);
    if (!root->right) {
        printf("Error in \"insert()\": Node on right not inserted;\n");
        errors++;
    } else {
        printf("Ok;\n-Teste %d: ", tests++);
        if (root->right->documentIds->size != 1) {
            printf("Error in \"insert()\": IDs on root->left->right is wrong;\n");
            errors++;
        }  printf("Ok;\n");
        printf("-Teste %2d: ", tests++);
        if (strcmp(root->left->word, "left")) {
            printf("Error in \"insert()\": wrong word inserted on root->left;\n");
            errors++;
        } else printf("Ok;\n");
    }
    insertRBT(tree, "salgado", 19);
    printf("-Teste %2d: ", tests++);
    if (strcmp(root->right->word, "salgado")) {
        printf("Error in \"insert()\": wrong word inserted on root->left;\n");
        errors++;
    } else printf("Ok;\n");
    insertRBT(tree, "soldado", 19);
    printf("-Teste %2d: ", tests++);
    if (strcmp(tree->root->word, "right")) {
        printf("Error in \"insert()\": wrong word on root after insert/rebalance;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (strcmp(tree->root->left->word, "left")) {
        printf("Error in \"insert()\": wrong word on root->left after insert/rebalance;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (strcmp(tree->root->right->word, "salgado")) {
        printf("Error in \"insert()\": wrong word on root->right after insert/rebalance;\n");
        errors++;
    } else printf("Ok;\n");
    printf("\nRealized a total of %d tests.\n", tests);
    printf("=============end-test_insertion==========\n");
    *total += tests;
    return errors;
}

int test_search(int* total) {
    printf("\n===============test_search===============\n");
    int errors = 0;
    int tests = 0;
    struct SearchResult results;
    results = searchRBT(NULL, NULL);
    printf("-Teste %2d: ", tests++);
    if (results.found) {
        printf("Error in \"search()\": found result in NULL;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons) {
        printf("Error in \"search()\": realizing comparisons in NULL tree;\n");
        errors++;
    } else printf("Ok;\n");
    BinaryTree* tree = createRBT();
    results = searchRBT(tree, NULL);
    printf("-Teste %2d: ", tests++);
    if (results.found) {
        printf("Error in \"search()\": found result in tree with NULL root;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons) {
        printf("Error in \"search()\": realizing comparisons in tree with NULL root;\n");
        errors++;
    } else printf("Ok;\n");

    insertRBT(tree, "root", 0);
    insertRBT(tree, "left", 0);
    insertRBT(tree, "right", 0);
    insertRBT(tree, "tree", 0);
    insertRBT(tree, "tree", 57);
    insertRBT(tree, "tree", 0);
    Node* root = tree->root;
    results = searchRBT(tree, "root");
    printf("-Teste %2d: ", tests++);
    if (!results.found) {
        printf("Error in \"search()\": didn't found a word in the tree;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 2) {
        printf("Error in \"search()\": realizing unnecessary comparisons;\n");
        errors++;
    } else printf("Ok;\n");
    int tmp = 0;
    nodeValue(&tmp, results.documentIds->head);
    printf("-Teste %2d: ", tests++);
    if (tmp != 0) {
        printf("Error in \"search()\": inserted wrong document number;\n");
        errors++;
    } else printf("Ok;\n");
    results = searchRBT(tree, "tree");
    printf("-Teste %2d: ", tests++);
    if (!results.found) {
        printf("Error in \"search()\": didn't found a word in the tree;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 3) {
        printf("Error in \"search()\": realized more comparisons than needed;\n");
        errors++;
    } else printf("Ok;\n");
    results = searchRBT(tree, "round");
    printf("-Teste %2d: ", tests++);
    if (results.found) {
        printf("Error in \"search()\": founded a word that isn't in the tree;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (results.numComparisons > 3) {
        printf("Error in \"search()\": realized more comparisons than needed;\n");
        errors++;
    } else printf("Ok;\n");
    printf("\nRealized a total of %d tests.\n", tests);
    printf("\n============end_test_search==============\n");
    *total += tests;
    return errors;
}

int test_destroy(int* total) {
    printf("\n===============test_destroy==============\n");
    int errors = 0;
    int tests = 0;
    BinaryTree* tree = createRBT();
    insertRBT(tree, "root", 0);
    insertRBT(tree, "left", 0);
    insertRBT(tree, "right", 0);
    insertRBT(tree, "tree", 0);
    Node* treeN = tree->root->right;
    Node* leftN = tree->root->left;
    Node* rightN = tree->root->right->right;
    destroyRBT(tree);
    printf("-Teste %2d: ", tests++);
    if (!tree) {
        printf("Error in \"destroy()\": tree was not released;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (!treeN) {
        printf("Error in \"destroy()\": a node in a released tree stayed on memory;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (!leftN) {
        printf("Error in \"destroy()\": a node in a released tree stayed on memory;\n");
        errors++;
    } else printf("Ok;\n");
    printf("-Teste %2d: ", tests++);
    if (!rightN) {
        printf("Error in \"destroy()\": a node in a released tree stayed on memory;\n");
        errors++;
    } else printf("Ok;\n");
    printf("\nRealized a total of %d tests.\n", tests);
    printf("\n=============end_test_destroy===========\n");
    *total += tests;
    return errors;
}

int main(void) {
    printf("\n -> Run the tests? (y/n)\n -->");
    int errors = getc(stdin);
    fflush(stdin);
    int tests = 0;
    if (errors == 121) {
        errors = 0;
        errors += test_create(&tests);
        errors += test_insertion(&tests);
        errors += test_search(&tests);
        errors += test_destroy(&tests);
    } else errors = 0;
    printf("\nFinalized tests execution. A total of %d errors were found in %d tests.\n", errors, tests);
    return 0;
}
