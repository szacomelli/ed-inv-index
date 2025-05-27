#include <stdio.h>
#include <stdlib.h>
#include "str.h"

typedef struct Node {
    void* value;
    int index;
    string type;
    Node* prev;
    Node* next;
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

void lookupValue(lkdList* list, void* value);
