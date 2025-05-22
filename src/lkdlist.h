#include <stdio.h>

typedef struct Node {
    void* value;
    char* type;
    int index;
    struct Node* next;
    struct Node* prev;
} node;

typedef struct linkedList {
    node* head;
    node* tail;
    int size;
    char* overallType;
} lkdList;

lkdList* createList();
