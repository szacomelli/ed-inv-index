#include <stdio.h>
#include <stdlib.h>
#include "bst.h"          // For insert, search, destroy
#include "data.h"

// building the tree
BinaryTree* buildTree(string** docInfo, string mode) {
    clock_t start = clock();
    // for the stats
    BinaryTree* tree = createBST();
    float totalInsTime = 0;
    float meanInsTime = 0;
    int count = 0;
    int len = 0;
    int maxHeight = 0;
    while (docInfo[len]) len++; // gets docInfo length
    for (int i = 0; i < len; i++) {
        if (i % 1000 == 0 && i != 0) printf("Documents scanned: %d\n", i);
        int docLen = 0;
        while (docInfo[i][docLen]) docLen++; // gets docInfo[i] length
        for (int j = 0; j < docLen; j++) {
            struct InsertResult result = insertBST(tree, *(*(docInfo + i) + j), i);
            // more stat gathering
            totalInsTime += result.executionTime;
            maxHeight = maxHeight < result.numComparisons ? result.numComparisons : maxHeight;
            count++;

        }
    }
    meanInsTime = ((float)totalInsTime)/count;
    clock_t end = clock();
    clock_t totalTime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("All %d documents were scanned\n", len);
    if (strcmp(mode, "stats") == 0) printf(
        "Total insertion time: %lf\nMean insertion time: %lf\nNumber of words: %d\nTree build time:%lf\n",
        totalInsTime, meanInsTime, count, totalTime
    );

    //uncomment this if you have Graphviz installed, use a Linux system and want to see the tree's graph
    // saveTree(tree);
    // if you use Windows, the graph will not be automatically generated; instead, you will need to run
    // dot -Tsvg ./test.txt in the parent directory of src.


    return tree;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("WRONG USAGE: too few arguments\n(usage: ./PROGRAM MODE NUMBER_OF_FILES PATH_TO_FILE)");
        return 1;
    }
    if (strcmp(argv[1], "search") != 0 && strcmp(argv[1], "stats") != 0) {
        printf("The supported modes are \"search\" and \"stats\", not \"%s\"\n", argv[1]);
        return 1;
    }

    for (int i=0; i < strSize(argv[2]); i++)
    if (argv[2][i] < 48 || argv[2][i] > 57) {printf("WRONG USAGE: first argument must be a number\n"); return 1;}

    int docNumber = atoi(argv[2]) > -1 ? atoi(argv[2]) : 0;

    string** docInfo = readStrs(argv[3], 0, docNumber);



    BinaryTree* tree = buildTree(docInfo, argv[1]);


    char prConf = '0';
    printf("Print tree? (y/n) ");
    scanf(" %c", &prConf);
    if (prConf == 'y') printTree(tree);

    char word[100];
    while(strcmp(word, "#stop") != 0) {
        printf("Write the word to be searched (#stop to stop execution): ");
        scanf("%s", word);
        printf("%s\n", word);
        printf("\n");
        if (strcmp(word, "#stop") != 0) {
            struct SearchResult result = searchBST(tree, word);
            if (result.found) {
                printf("Word found at depth %d\n", result.numComparisons);

                if (strcmp(argv[1], "stats") == 0) {
                    printf("Execution time: %lf\nNumber of comparison: %d\n", result.executionTime, result.numComparisons);
                }


                printf("Print documentIds? (y/n):");
                char conf = '0';
                scanf(" %c", &conf);
                printf("\n");

                if (conf == 'y') printList(result.documentIds);
            }
            else printf("Word not found...\n");
        }

    }

    // freeing everything
    destroyBST(tree);

    freeDocs(docInfo);
}
