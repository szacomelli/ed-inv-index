#include "data.h"

#define MAX_BUFFER 100

int docSize(FILE* buffer) {
    fseek(buffer, 0, SEEK_END);
    int size = ftell(buffer);
    rewind(buffer);
    return ++size; // To count the EOF character
}

string readSingle(string path, int numDoc) {
    string name = malloc(strSize(path) + 20);
    snprintf(name, 29, "%s%d.txt\0", path, numDoc);
    FILE* doc = fopen(name, "r");

    if (!doc) {
        printf("Error in \"readSingle()\": error opening \"%s\";\nVerify path;\n", name);
        exit(1);
    }
    free(name);
    int doclen = docSize(doc);
    string txt = malloc(doclen);
    fgets(txt, doclen, doc);
    fclose(doc);
    return txt;
}

string* readTxts(string path, const int start, const int end) {
    string* allTxt = malloc(sizeof(string)*(end-start+1));
    for (int idx = start; idx <= end; idx++) {
        *(allTxt + idx) = readSingle(path, idx);
    }
    return allTxt;
}

string** readStrs(string path, const int start, const int end) {
    string** allStrs = malloc(sizeof(string*)*(end-start+2));
    string txt = NULL;
    int size = strSize(path);
    if (path[size] != '/') {
        string oldP = (string) malloc(size + 1);
        strCopy(path, oldP);
        path = (string) malloc(size + 2);
        strConcat(oldP, "/", path, '\0');
    }
    for (int idx = start; idx <= end; idx++) {
        txt = readSingle(path, idx);
        *(allStrs + idx) = strSplit(txt, ' ');
    }
    *(allStrs + end) = NULL;
    return allStrs;
}

void freeDocs(string** allTxt) {
    int len = 0;
    while (allTxt[len]) len++;
    for (int i = 0; i < len; i++) {
        if (i % 1000 == 0 && i != 0) printf("Documents freed: %d\n", i);
        // printf("%d", i);
        int docLen = 0;

        // while (allTxt[i][docLen]) docLen++;
        // for (int j = 0; j < docLen; j++) {
        //     free(allTxt[i][j]);


        // }
        free(allTxt[i]);
    }
    free(allTxt);
    printf("All documents were freed\n");
    return;
}
