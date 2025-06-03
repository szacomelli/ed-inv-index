#include <stdio.h>
#include <stdlib.h>
#include "str.h"          // For strcmp, strCopy, strSize
#include "tree_utils.h"   // For printTree, createtNode, createTree, etc.
#include "bst.h"          // For insert, search, destroy
#include "lkdlist.h"      // For traversing the list of IDs in case of search

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

int main(int argc, char *argv[]) {

    if (argc < 3) {printf("WRONG USAGE\n"); return 1;}


    for (int i=0; i < strSize(argv[1]); i++)
    if (argv[1][i] < 48 || argv[1][i] > 57) {printf("WRONG USAGE AGAIN\n"); return 1;}

    int docNumber = atoi(argv[1]) > -1 ? (atoi(argv[1]) <= 10000 ? atoi(argv[1]) : 10000) : 0



}
