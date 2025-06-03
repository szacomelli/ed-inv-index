#include "data.h"

#define MAX_BUFFER 100

int docSize(FILE* buffer) {
    fseek(buffer, 0, SEEK_END);
    int size = ftell(buffer);
    rewind(buffer);
    return ++size; // To count the EOF character
}

string readSingle(string path, int numDoc) {
    string name = malloc(strSize(path) + 10);
    snprintf(name, 19, "%s%d.txt\0", path, numDoc);
    FILE* doc = fopen(name, "r");
    free(name);
    if (!doc) {
        printf("Error in \"readSingle()\": error opening the document %d;\n", numDoc);
        exit(1);
    }
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
    for (int idx = start; idx <= end; idx++) {
        txt = readSingle(path, idx);
        *(allStrs + idx) = strSplit(txt, ' ');
    }
    *(allStrs + end) = NULL;
    return allStrs;
}