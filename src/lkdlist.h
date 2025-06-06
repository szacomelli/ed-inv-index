#include <stdio.h>
#include <stdlib.h>
#include "str.h"

#define capacity(object) (sizeof(object)/sizeof(object[0]))

typedef struct lNode {
    void* value;
    int index;
    string type;
    struct lNode* prev;
    struct lNode* next;
    int valueSize;
} node;

typedef struct linkedList {
    node* head;
    node* tail;
    int size;
    string overallType;
} lkdList;

lkdList* createList(string type);

void memCopy(void* dst, void* src, int numBytes);

node* createlNode(void* value, string type);

void insertNode(lkdList* List, node* Node);

void nodeValue(void* value, node* Node);

void insertValue(lkdList* list, void* value);

int lookupValue(lkdList* list, void* value);

node* lookIndex(lkdList* list, int index);

void getIndexValue(lkdList* list, int index, void* value);

void freeNode(node* Node, node** pvNode, node** nxNode);

void freeList(lkdList* list);

void deleteIndex(lkdList* list, int index, void* value);

void printList(lkdList* list);
