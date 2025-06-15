#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <time.h>

// building the tree
BinaryTree* buildTree(string** docInfo, string mode) {
    system("mkdir stats");
    FILE *insertCSV = fopen("./stats/inserts.csv", "w");
    clock_t start = clock();
    // for the stats
    BinaryTree* tree = createAVL();
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
            struct InsertResult result = insertAVL(tree, *(*(docInfo + i) + j), i);
            // more stat gathering
            if (strcmp(mode, "stats") == 0 )
              fprintf(insertCSV, "%s,%d,%lf,%d,%d;\n",
                      *(*(docInfo + i) + j), result.status, result.executionTime,
                      result.numComparisons, tree->root->height);
            totalInsTime += result.executionTime;
            maxHeight = maxHeight < result.numComparisons ? result.numComparisons : maxHeight;
            count++;

        }
    }
    meanInsTime = ((float)totalInsTime)/count;
    clock_t end = clock();
    clock_t totalTime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("All %d documents were scanned\n", len);
    if (strcmp(mode, "stats") == 0) fprintf( insertCSV,
        /* "Total insertion time: %lf\nMean insertion time: %lf\nNumber of words: %d\nTree build time:%lf\n", */
        "%lf,%lf,%d,%lf,0;",
        totalInsTime, meanInsTime, count, totalTime
    );
    fclose(insertCSV);
    //uncomment this if you have Graphviz installed, use a Linux system and want to see the tree's graph
    //saveTree(tree);
    // if you use Windows, the graph will not be automatically generated; instead, you will need to run
    // dot -Tsvg ./test.txt in the parent directory of src.


    return tree;
}

void getSearchInfo(string** docInfo, BinaryTree* tree) {
  FILE *searchCSV = fopen("./stats/search.csv", "w");
  clock_t start = clock();
  // for the stats

  float totalSTime = 0;
  float meanSTime = 0;
  int count = 0;
  int len = 0;
  int maxHeight = 0;
  while (docInfo[len]) len++; // gets docInfo length
  for (int i = 0; i < len; i++) {
      if (i % 1000 == 0 && i != 0) printf("Documents searched: %d\n", i);
      int docLen = 0;
      while (docInfo[i][docLen]) docLen++; // gets docInfo[i] length
      for (int j = 0; j < docLen; j++) {
          struct SearchResult result = searchAVL(tree, *(*(docInfo + i) + j));
          // more stat gathering
          fprintf(searchCSV, "%s,%d,%lf,%d,%d;\n",
                  *(*(docInfo + i) + j), result.found, result.executionTime,
                  result.numComparisons, result.documentIds->size);
          totalSTime += result.executionTime;
          maxHeight = maxHeight < result.numComparisons ? result.numComparisons : maxHeight;
          count++;
      }
  }
  meanSTime = ((float)totalSTime/count);
  clock_t end = clock();
  clock_t totalTime = ((double)(end - start))/CLOCKS_PER_SEC;
  fprintf( searchCSV,
        /* "Total insertion time: %lf\nMean insertion time: %lf\nNumber of words: %d\nTree build time:%lf\n", */
        "%lf,%lf,%d,%lf,0;",
        totalSTime, meanSTime, count, totalTime
    );
  fclose(searchCSV);
  return;
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



    BinaryTree* tree = buildTree(docInfo, argv[1]);

    if (strcmp(argv[1], "stats") == 0) getSearchInfo(docInfo, tree);
    else {
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
          struct SearchResult result = searchAVL(tree, word);
          if (result.found) {
            printf("Word found at height %d\n", result.numComparisons);

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
    }

    // freeing everything
    destroyAVL(tree);

    freeDocs(docInfo);
}
