#include <stdio.h>
#include <stdlib.h>
#include "str.h"          // For strcmp, strCopy, strSize
#include "tree_utils.h"   // For printTree, createtNode, createTree, etc.
#include "bst.h"          // For insert, search, destroy
#include "lkdlist.h"      // For traversing the list of IDs in case of search
#include "data.h"

#define MAX_WORD_LEN 128

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

bTree* buildTree(string** docInfo) {
    bTree* tree = createTree();
    int len = 0;
    while (docInfo[len]) len++;
    for (int i = 0; i < len; i++) {
        if (i % 1000 == 0) printf("Documents scanned: %d\n", i);
        // printf("%d", i);
        int docLen = 0;
        while (docInfo[i][docLen]) docLen++;
        for (int j = 0; j < docLen; j++) {
            // printf("Index [%d][%d], word %s\n", i, j, *(*(docInfo + i) + j));
            insert(tree, *(*(docInfo + i) + j), i);

        }
    }
    printf("All documents were scanned\n");
    // saveTree(tree);

    return tree;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {printf("WRONG USAGE: too few arguments\n"); return 1;}
    if (strcmp(argv[1], "search") != 0 && strcmp(argv[1], "stats") != 0) {
        printf("The supported modes are \"search\" and \"stats\", not \"%s\"\n", argv[1]);
        return 1;
    }

    for (int i=0; i < strSize(argv[2]); i++)
    if (argv[2][i] < 48 || argv[2][i] > 57) {printf("WRONG USAGE: first argument must be a number\n"); return 1;}

    int docNumber = atoi(argv[2]) > -1 ? (atoi(argv[2]) <= 10000 ? atoi(argv[2]) : 10000) : 0;

    string** docInfo = readStrs(argv[3], 0, docNumber);

    if (strcmp(argv[1], "search") == 0) {

        bTree* tree = buildTree(docInfo);


        char word[100];
        printf("Write the word to be searched: ");
        scanf("%s", word);
        printf("%s\n", word);
        printf("\n");
        struct SearchResult result = search(tree, word);
        if (result.found) printf("Word found at height %d\n", result.numComparisons);
        else printf("Word not found...\n");
    }



}
