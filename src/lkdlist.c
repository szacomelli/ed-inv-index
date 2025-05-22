#include "lkdlist.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>


lkdList* createList() {
    lkdList* list = (lkdList*) malloc(sizeof(lkdList));
    // list->head = (node*) malloc(sizeof(node));
    // list->tail = (node*) malloc(sizeof(node));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->overallType = "void";
    return list;
}   

node* createNode(void* value, string type) {
    node* Node = (node*) malloc(sizeof(node));
    Node->value = value;
    Node->index = -1;
    Node->type = type;
    return Node;
}

void insertNode(lkdList* List, node* Node) {
    if (List == NULL || Node == NULL) return;
    else if (List->head == NULL) {
        List->head = Node;
        List->tail = List->head;
        List->size = 1;
        List->overallType = Node->type;
        Node->index = 0;
        return;
    }
    
    node* iterator = List->head;
    while (iterator->next != NULL) {
        iterator = iterator->next;
    }
    iterator->next = Node;
    Node->prev = iterator;
    List->size += 1;
    Node->index = iterator->index + 1;
}


