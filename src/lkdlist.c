#include "lkdlist.h"


lkdList* createList() {
    lkdList* list = (lkdList*) malloc(sizeof(lkdList));
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
    Node->prev = NULL;
    Node->next = NULL;
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
    if (Node == NULL) return;
    if (strcmp(Node->type, "string") == 0) {
        string str = malloc(strSize(*(string*)Node->value) + 1);
        strCopy(*(string*)Node->value, str);//, 0, capacity(*(string*) Node->value));
        *(string*)value = str;
        return;
    }
    else if (strcmp(Node->type, "int") == 0) {
        *(int*)value = *(int*) Node->value;
        return;
    }
    else if (strcmp(Node->type, "double") == 0) {
        *(double*)value = *(double*)Node->value;
        return;
    }
    else if (strcmp(Node->type, "char") == 0) {
        *(char*) value = *(char*) Node->value;
        return;
    }
    else if (strcmp(Node->type, "unsigned int") == 0) {
        *(unsigned int*)value = *(unsigned int*) Node->value;
        return;
    }
    else {
        memCopy(value, Node->value, Node->valueSize);
        return;
    }
}

void insertValue(lkdList* list, void* value) {
    if (list == NULL || value == NULL) return;
    node* newNode = malloc(sizeof(node));
    newNode->type = list->overallType;
    newNode->prev = list->tail;
    if (list->tail) {             //If there's a tail
        list->tail->next = newNode;
        newNode->index = list->tail->index + 1;
    } else list->head = newNode;  //If it doesn't have a tail, it also doesn't have a head
    list->tail = newNode;
    list->size += 1;
    
    if (strcmp(list->overallType, "string") == 0) {
        string str = malloc(strSize(*(string*)value) + 1);
        strCopy(*(string*)value, str);
        *(string*)newNode->value = str;
        newNode->type = "string";
        return;
    }
    else if (strcmp(list->overallType, "int") == 0) {
        newNode->value = malloc(4);
        *(int*) newNode->value = *(int*)value;
        newNode->type = "int";
        return;
    }
    else if (strcmp(list->overallType, "double") == 0) {
        newNode->value = malloc(8);
        *(double*) newNode->value = *(double*)value;
        newNode->type = "double";
        return;
    }
    else if (strcmp(list->overallType, "char") == 0) {
        newNode->value = malloc(1);
        *(char*) newNode->value = *(char*)value;
        newNode->type = "char";
        return;
    }
    else if (strcmp(list->overallType, "unsigned int") == 0) {
        newNode->value = malloc(4);
        *(unsigned int*) newNode->value = *(unsigned int*)value;
        newNode->type = "unsigned int";
        return;
    }
    else {
        memCopy(newNode->value, value, 8);
        return;
    }
}

void memCopy(void* dst, void* src, int numBytes){
    printf("You were not suposed to be here\n");
    return;
}

int lookupValue(lkdList* list, void* value) {
    node* iterator = list->head;
    while (iterator != NULL) {
        if (strcmp(iterator->type,"string") == 0 && strcmp(*(string*)value, *(string*)iterator->value) == 0) {
           return iterator->index;
        }
        else if (strcmp(iterator->type,"int") == 0 && *(int*) value == *(int*)iterator->value) {
            return iterator->index;
        }
        else if (strcmp(iterator->type,"double") == 0 && *(double*) value == *(double*)iterator->value) {
            return iterator->index;
        }
        else if (strcmp(iterator->type,"char") == 0 && *(char*) value == *(char*)iterator->value) {
            return iterator->index;
        }
        else if (strcmp(iterator->type,"unsigned int") == 0 && *(int*) value == *(int*)iterator->value) {
            return iterator->index;
        }
        iterator = iterator->next;
    }
    return -1;
}

node* lookIndex(lkdList* list, int index) {
    if (index < 0 || list == NULL) return NULL;
    else if (index > list->tail->index) return NULL;
    node* iterator = list->head;
    while (iterator != NULL) {
        if (iterator->index == index) return iterator;
        iterator = iterator->next;
    }
    return NULL;
}

void getIndexValue(lkdList* list, int index, void* value) {
    if (list == NULL || value == NULL) return;
    else if (index < 0 || index > list->tail->index) return;
    node* ndRefer = lookIndex(list, index);
    nodeValue(value, ndRefer);
    return;
}
