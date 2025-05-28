#include <stdio.h>
#include <stdlib.h>
#include "str.h"

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

node* createNode(void* value, string type);

void insertNode(lkdList* List, node* Node);

void nodeValue(void* value, node* Node);

int lookupValue(lkdList* list, void* value);

node* lookIndex(lkdList* list, int index);

void getIndexValue(lkdList* list, int index, void* value);

void freeNode(node* Node, node** pvNode, node** nxNode);

void freeList(lkdList* list);

void deleteIndex(lkdList* list, int index, void* value);
