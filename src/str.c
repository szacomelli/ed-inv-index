#include "str.h"

int strcmp(string wordOne, string wordTwo) {
    int result = 0;
    // int sizeOne = sizeof(wordOne) - 1;
    // int sizeTwo = sizeof(wordTwo) - 1;
    int currI = 0;
    while (result == 0) {
        if (wordOne[currI] == '\0' || wordTwo[currI] == '\0') break;
        else if (wordOne[currI] < wordTwo[currI]) {
            result -= 1;
            break;
        }
        else if (wordOne[currI] > wordTwo[currI]) {
            result += 1;
            break;
        }
        else currI += 1;
    }
    return result;
}