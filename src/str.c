#include "str.h"
#include <stdlib.h>

int strcmp(string wordOne, string wordTwo) {
    int result = 0;
    // int sizeOne = sizeof(wordOne) - 1;
    // int sizeTwo = sizeof(wordTwo) - 1;
    int currI = 0;
    while (result == 0) {
        if (wordOne[currI] == '\0' || wordTwo[currI] == '\0') break;
        else if (wordOne[currI] < wordTwo[currI]) {
            result -= 1;
        }
        else if (wordOne[currI] > wordTwo[currI]) {
            result += 1;
        }
        else currI += 1;
    }
    return result;
}

int strsize(string word) {
    return (sizeof(word)/sizeof(char));
}

void strcopy(string src, string dst, uint start, uint end) {
    if (capacity(dst) < capacity(src)) {
        printf("Error in strcopy(): src bigger than dst;\n");
        exit(1);
    }
    uint idx = 0;
    while (idx + start < end) {
        dst[idx + start] = src[idx];
        idx++;
    }
    dst[idx + start] = '\0';
}