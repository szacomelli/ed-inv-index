#include "rbt.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <time.h>

// building the tree
BinaryTree* buildTree(string** docInfo, string mode) {
    system("mkdir stats");
    FILE *insertWordsCSV = fopen("./stats/rbt_word_inserts.csv", "w");
    FILE *insertDocCSV = fopen("./stats/rbt_doc_inserts.csv", "w");
    FILE *insertCSV = fopen("./stats/rbt_total_inserts.csv", "w");
    clock_t start = clock();

    BinaryTree* tree = createRBT();

    // variables to get the time of inserts
    float totalInsTime = 0;
    float meanInsTime = 0;
    int count = 0;

    int compCount = 0;
    double compCountMean = 0;

    // for the docInfo array lengths
    int len = 0;
    int maxHeight = 0;
    while (docInfo[len]) len++; // gets docInfo length

    // for storaging stats for the entire documents
    double docTimes[len];


    for (int i = 0; i < len; i++) {
        if (i % 1000 == 0 && i != 0) printf("Documents scanned: %d\n", i);
        int docLen = 0;
        while (docInfo[i][docLen]) docLen++; // gets docInfo[i] length
        for (int j = 0; j < docLen; j++) {
            struct InsertResult result = insertRBT(tree, *(*(docInfo + i) + j), i);
            // more stat gathering
            if (strcmp(mode, "stats") == 0 )
              fprintf(insertWordsCSV, "%s,%d,%lf,%d,%d;\n",
                      *(*(docInfo + i) + j), result.status, result.executionTime,
                      result.numComparisons, tree->root->height);
            totalInsTime += result.executionTime;
            maxHeight = maxHeight < result.numComparisons ? result.numComparisons : maxHeight;
            count++;
            compCount = compCount + result.numComparisons;

        }
        docTimes[i] = totalInsTime - (i != 0 ? docTimes[i-1] : 0);
        fprintf(insertDocCSV, "%d,%lf,%lf,%d,%d;",
                i, docTimes[i], docTimes[i]/docLen, tree->root->height, docLen);

    }
    // computing more stats
    meanInsTime = ((float)totalInsTime)/count;
    compCountMean = compCount/count;
    clock_t end = clock();
    double totalTime = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("All %d documents were scanned\n", len);
    // writing in the docs
    if (strcmp(mode, "stats") == 0) fprintf( insertCSV,
        /* "Total insertion time: %lf\nMean insertion time: %lf\nNumber of words: %d\nTree build time:%lf\n", */
        "%lf,%lf,%d,%lf,%d,%f;",
        totalInsTime, meanInsTime, count, totalTime, compCount, compCountMean
    );
    fclose(insertCSV);
    fclose(insertDocCSV);
    fclose(insertWordsCSV);
    //uncomment this if you have Graphviz installed, use a Linux system and want to see the tree's graph
    //saveTree(tree);
    // if you use Windows, the graph will not be automatically generated; instead, you will need to run
    // dot -Tsvg ./test.txt in the parent directory of src (in Windows, the command name may differ).


    return tree;
}

void getSearchInfo(string** docInfo, BinaryTree* tree) {
  FILE *searchCSV = fopen("./stats/rbt_total_search.csv", "w");
  FILE *searchWordCSV = fopen("./stats/rbt_word_search.csv", "w");
  FILE *searchDocCSV = fopen("./stats/rbt_doc_search.csv", "w");
  clock_t start = clock();

  // for the stats
  double totalSTime = 0;
  double meanSTime = 0;
  int count = 0;
  int compCount = 0;
  double compCountMean = 0;

  // size os docInfo
  int len = 0;

  int maxHeight = 0;
  while (docInfo[len]) len++; // gets docInfo length
  double docTimes[len];
  double docComp[len];
  for (int i = 0; i < len; i++) {
      if (i % 1000 == 0 && i != 0) printf("Documents searched: %d\n", i);

      // length of actual doc
      int docLen = 0;
      while (docInfo[i][docLen]) docLen++; // gets docInfo[i] length

      for (int j = 0; j < docLen; j++) {
          struct SearchResult result = searchRBT(tree, *(*(docInfo + i) + j));

          // more stat gathering
          fprintf(searchWordCSV, "%s,%d,%lf,%d,%d;\n",
                  *(*(docInfo + i) + j), result.found, result.executionTime,
                  result.numComparisons, result.documentIds->size);
          totalSTime += result.executionTime;
          maxHeight = maxHeight < result.numComparisons ? result.numComparisons : maxHeight;
          count++;
          compCount = compCount + result.numComparisons;

      }
      docTimes[i] = totalSTime - (i != 0 ? docTimes[i-1] : 0);
      docComp[i] = compCount - (i != 0 ? docComp[i-1] : 0);
      fprintf(searchDocCSV, "%d,%lf,%lf,%d,%f,%d;",
                i, docTimes[i], docTimes[i]/docLen, docComp[i],(float)docComp[i]/docLen, docLen);

  }
  meanSTime = ((double)totalSTime/count);
  compCountMean = (double)compCount/count;
  clock_t end = clock();
  double totalTime = ((double)(end - start))/CLOCKS_PER_SEC;
  fprintf( searchCSV,
        /* "Total insertion time: %lf\nMean insertion time: %lf\nNumber of words: %d\nTree build time:%lf\n", */
        "%lf,%lf,%d,%lf,%d,%f;",
        totalSTime, meanSTime, count, totalTime, compCount, compCountMean
    );
  fclose(searchCSV);
  fclose(searchWordCSV);
  fclose(searchDocCSV);
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
          struct SearchResult result = searchRBT(tree, word);
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
    destroyRBT(tree);

    freeDocs(docInfo);
}
