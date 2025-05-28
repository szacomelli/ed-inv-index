#include <stdio.h>
#include <stdlib.h>
#include "str.h"

#define capacity(object) (sizeof(object)/sizeof(object[0]))

typedef struct Node {
    void* value;
    int index;
    string type;
    struct Node* prev;
    struct Node* next;
    int valueSize;
} node;

typedef struct linkedList {
    node* head;
    node* tail;
    int size;
    string overallType;
} lkdList;

lkdList* createList();

void memCopy(void* dst, void* src, int numBytes);

node* createNode(void* value, string type);

void insertNode(lkdList* List, node* Node);

void nodeValue(void* value, node* Node);

void insertValue(lkdList* list, void* value);

int lookupValue(lkdList* list, void* value);

node* lookIndex(lkdList* list, int index);

void getIndexValue(lkdList* list, int index, void* value);
