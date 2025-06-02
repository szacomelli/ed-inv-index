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

int main() {
    bTree* tree = createTree(); 
    if (tree == NULL) {
        fprintf(stderr, "Failed to create the tree.\n");
        return EXIT_FAILURE;
    }

    while (1) {
        printf("\n=== BST CLI MENU ===\n");
        printf("1) Insert word + docId\n");
        printf("2) Search word\n");
        printf("3) Print tree\n");
        printf("4) Exit\n");
        printf("Choose an option (1-4): ");

        char option[4];
        readLine(option, sizeof(option));
        if (option[0] == '1' && option[1] == '\0') {
            /* 1) Insert word + docId */
            char word[MAX_WORD_LEN];
            char docBuf[32];
            int docId;

            printf("Enter the word to insert: ");
            readLine(word, MAX_WORD_LEN);
            if (strSize(word) == 0) {
                printf("Invalid word.\n");
                continue;
            }

            printf("Enter the document ID (integer): ");
            readLine(docBuf, sizeof(docBuf));
            docId = atoi(docBuf);

            struct InsertResult ir = insert(tree, word, docId);
            printf("> Inserted/updated '%s' with docId=%d.\n", word, docId);
            printf("  Comparisons: %d | Time (s): %.6f\n",
                   ir.numComparisons, ir.executionTime);
        }
        else if (option[0] == '2' && option[1] == '\0') {
            /* 2) Search word */
            char word[MAX_WORD_LEN];
            printf("Enter the word to search: ");
            readLine(word, MAX_WORD_LEN);
            if (strSize(word) == 0) {
                printf("Invalid word.\n");
                continue;
            }

            struct SearchResult sr = search(tree, word);
            if (sr.found) {
                printf("> The word '%s' was FOUND.\n", word);
                printf("  Document IDs: ");
                // Traverse the list of IDs (lkdList) and print all
                node* it = sr.documentIds->head;
                while (it != NULL) {
                    printf("%d ", *(int*)(it->value));
                    it = it->next;
                    if (it != NULL) printf(", ");
                }
                printf("\n");
            } else {
                printf("> The word '%s' was NOT found.\n", word);
            }
            printf("  Comparisons: %d | Time (s): %.6f\n",
                   sr.numComparisons, sr.executionTime);
        }
        else if (option[0] == '3' && option[1] == '\0') {
            /* 3) Print tree in the requested format */
            if (tree->root == NULL) {
                printf("[Empty tree]\n");
            } else {
                printf("\n--- Tree Structure (BST) ---\n");
                printTree(tree);
            }
        }
        else if (option[0] == '4' && option[1] == '\0') {
            /* 4) Exit */
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid option. Try again.\n");
        }
    }

    /* Before exiting, free BST memory */
    destroy(tree);
    free(tree);
    return EXIT_SUCCESS;
}
