#include "str.h"

int strcmp(string strOne, string strTwo) {
    if (!strOne || !strTwo) {
        printf("Error in strcmp(): received a NULL param");
        exit(1);
    }
    int currI = 0;
    while (strOne[currI] || strTwo[currI]) {
        if (strOne[currI] == '\0') return -1;
        else if (strTwo[currI] == '\0') return 1;
        else if (strOne[currI] < strTwo[currI]) return -1;
        else if (strOne[currI] > strTwo[currI]) return 1;
        currI++;
    }
    return 0;
}

int countChar(string txt, char wanted) {
    if (!txt) return 0;
    int count = 0;
    int idx = 0;
    while (txt[idx]) {
        if(txt[idx] == wanted) count++;
        idx++;
    }
    return count;
}

int strSize(string str) {
    if (!str) {
        printf("Error in strSize(): 'str' param is NULL");
        exit(1);
    }
    int len = 0;
    while(str[len]) len++;
    return len;
}

void strImplant(string src, string dst, int start, int end) {
    if (!src) {
        printf("Error in strImplant(): 'src' pointer is NULL;\n");
        exit(1);
    } else if (start > end) {
        printf("Error in strImplant(): end must be greater than start;\n");
        exit(1);
    }
    int len = strSize(dst);
    int idx = start;
    while (idx < end) {
        dst[idx] = src[idx - start];
        idx++;
    }
    if ((idx + start) > len)
        dst[idx + start] = '\0';
}

void strCopy(string src, string dst) {
    if (!src) {
        printf("Error in strCopy(): 'src' pointer is NULL;\n");
        exit(1);
    }
    // int len = strSize(src);
    int idx = 0;
    // while (idx < len) {
    //     dst[idx] = src[idx];
    //     idx++;
    // }
    while (src[idx]) {
        dst[idx] = src[idx];
        idx++;
    }
    dst[idx] = '\0';
}

void strConcat(string strOne, string strTwo, string result, char sep) {
    if (!strOne) {
        printf("Error in strConcat(): 'strOne' pointer is NULL;\n");
        exit(1);
    } else if (!strTwo) {
        printf("Error in strConcat(): 'strTwo' pointer is NULL;\n");
        exit(1);
    }
    int idxR = 0;
    int idx = 0;
    while(strOne[idx]) {
        result[idxR] = strOne[idx];
        idxR++; idx++;
    }
    if (sep) {
        result[idxR++] = sep;
        idxR++;
    }
    idx = 0;
    while(strTwo[idx]) {
        result[idxR] = strTwo[idx];
        idxR++; idx++;
    }
    result[idxR] = '\0';
}

string* strSplit(string str, char sep) {
    if (!str) {
        return NULL;
    }
    int idx = 0;
    int qtd = 1 + countChar(str, sep);
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

int isSubstr(string strOne, string strTwo) {
    if (!strOne | !strTwo) {
        return 0;
    }
    int actO = 0;
    int actT = 0;
    while (strTwo[actT]) {
        if (strTwo[actT] == strOne[0]) {
            while(strOne[actO] == strTwo[actT + actO]) actO++;
            if (strOne[actO] == '\0') return 1;
            actO = 0;
        }
        else if (strTwo[actT] == '\0') return 0;
        actT++;
    }
    return 0;
}