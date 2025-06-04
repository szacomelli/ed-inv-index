#include <stdio.h>
#include <stdlib.h>
#include "str.h"          // For strcmp, strCopy, strSize
#include "tree_utils.h"   // For printTree, createtNode, createTree, etc.
#include "bst.h"          // For insert, search, destroy
#include "lkdlist.h"      // For traversing the list of IDs in case of search
#include "data.h"

// #define MAX_WORD_LEN 128

/* Helper function to read a line from stdin and remove '\n'. */
static void readLine(char* buffer, int size) {
    if (fgets(buffer, size, stdin) == NULL) {
        // In case of EOF or error, just set empty string
        buffer[0] = '\0';
        return;
    }
    // Remove trailing '\n' if it exists
    size_t len = strSize(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

bTree* buildTree(string** docInfo, string mode) {
    clock_t start = clock();
    bTree* tree = createTree();
    float totalInsTime = 0;
    float meanInsTime = 0;
    int count = 0;
    int len = 0;
    int maxHeight = 0;
    while (docInfo[len]) len++;
    for (int i = 0; i < len; i++) {
        if (i % 1000 == 0 && i != 0) printf("Documents scanned: %d\n", i);
        // printf("%d", i);
        int docLen = 0;
        while (docInfo[i][docLen]) docLen++;
        for (int j = 0; j < docLen; j++) {
            // printf("Index [%d][%d], word %s\n", i, j, *(*(docInfo + i) + j));
            struct InsertResult result = insert(tree, *(*(docInfo + i) + j), i);
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
    // saveTree(tree);


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

    int docNumber = atoi(argv[2]) > -1 ? (atoi(argv[2]) <= 10102 ? atoi(argv[2]) : 10102) : 0;

    string** docInfo = readStrs(argv[3], 0, docNumber);



    bTree* tree = buildTree(docInfo, argv[1]);


    char word[100];
    printf("Write the word to be searched: ");
    scanf("%s", word);
    printf("%s\n", word);
    printf("\n");
    struct SearchResult result = search(tree, word);
    if (result.found) {
        printf("Word found at height %d\n", result.numComparisons);

        if (strcmp(argv[1], "stats") == 0) {
            printf("Execution time: %lf\n Number of comparison: %d\n", result.executionTime, result.numComparisons);
        }


        printf("Print documentIds? (y/n):");
        char conf = '0';
        scanf(" %c", &conf);
        printf("\n");

        if (conf == 'y') printList(result.documentIds);
    }
    else printf("Word not found...\n");


    // printTree(tree);
    destroy(tree);

    freeDocs(docInfo);
}
