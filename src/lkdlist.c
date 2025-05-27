<<<<<<< HEAD
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

void nodeValue(void* value, node* Node) {
    if (Node == NULL) return NULL;
    if (strcmp(Node->type, "string") == 0) {
        str = malloc(sizeof(Node->value));
        string* strPtr = malloc(sizeof(string));
        strcopy(str, (string) Node->value, 0, capacity(str));
        strPtr = &str;
        value = strPtr;
        return;
    }
    else if (strcmp(Node->type, "int") == 0) {
        
    }
    else if (strcmp(Node->type, "double") == 0) {

    }
    else if (strcmp(Node->type, "char") == 0) {

    }
    else if (strcmp(Node->type, "bool") == 0) {

    }
    else if (strcmp(Node->type, "unsigned int") == 0) {

    }
}
=======
>>>>>>> 4e59fac5ce7f5e2ef655013e9f64d28224fa0645
