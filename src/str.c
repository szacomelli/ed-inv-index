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
        }
        else if (wordOne[currI] > wordTwo[currI]) {
            result += 1;
        }
        else currI += 1;
    }
    return result;
}

int countChar(string txt, char wanted) {
    if (!txt) return 0;
    int count = 0;
    int idx = 0;
    while (txt[idx]) if(txt[idx++] == wanted) count++;
    return count;
}

int strSize(string word) {
    if (!word) {
        printf("Error in strsize(): 'word' param is NULL");
        exit(1);
    }
    uint len = 0;
    while(word[len]) len++;
    return len;
}

void strImplant(string src, string dst, uint start, uint end) {
    if (!src) {
        printf("Error in strImplant(): 'src' pointer is NUL;\n");
        exit(1);
    }
    uint len = strSize(dst);
    uint idx = start;
    while (idx < end) {
        dst[idx] = src[idx - start];
        idx++;
    }
    if ((idx + start) > len)
        dst[idx + start] = '\0';
}

void strCopy(string src, string dst) {
    if (!src) {
        printf("Error in strcopy(): 'src' pointer is NULL;\n");
        exit(1);
    }
    uint len = strSize(src);
    uint idx = 0;
    while (idx < len) dst[idx++] = src[idx];
    dst[idx] = '\0';
}

void strConcat(string str1, string str2, string result, char sep) {
    if (!str1 | !str2) {
        printf("Error in strConcat(): 'str' pointer is NULL;\n");
        exit(1);
    }
    uint idxR = 0;
    uint idx = 0;
    while(str1[idx]) result[idxR++] = str1[idx++];
    if (sep) result[idxR++] = sep;
    idx = 0;
    while(str2[idx]) result[idxR++] = str2[idx++];
    result[idxR] = '\0';
}

string* strSplit(string str, char sep) {
    if (!str) {
        return NULL;
    }
    uint idx = 0;
    uint qtd = 1 + countChar(str, sep);
    idx = 0;
    string* result = malloc(sizeof(string)*(qtd+1));
    qtd = 1;
    result[0] = str;
    while (str[idx]) { 
        if ((str[idx] == sep) && str[idx+1]) {
            str[idx] = '\0';
            result[qtd] = (str + idx + 1);
            qtd++;
        }
        idx++;
    }
    result[qtd] = NULL;
    return result;
}