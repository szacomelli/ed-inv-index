#include <stdio.h>
#include "tree_utils.h"
#include <wchar.h>
#include <locale.h>

// To format printTree() according to operational system
#ifdef _WIN32
    #define C1 179
    #define C2 195
    #define C3 192
    #define C4 196
    #define C5 194
#else
    #define C1 9474
    #define C2 9500
    #define C3 9492
    #define C4 9472
    #define C5 9516
#endif

#define max(a ,b) (((a)>(b)) ? (a) : (b))

Node* createNode() {
    Node* node = malloc(sizeof(Node));
    node->word = NULL;

    node->documentIds = createList("int");
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = -1;    // usado na AVL
    node->isRed = 0;
    return node;
}

BinaryTree* createTree() {
    BinaryTree* tree = malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->NIL = NULL;
    return tree;
}

int prtIndexAux(Node* tnode, int idx) {
    if (tnode == NULL) return idx - 1;
    printf("%d. %s: ", idx, tnode->word);
    node* iterator = tnode->documentIds->head;

    while (iterator != NULL) {
        if (iterator->index > 0) printf(", ");
        printf("%d", *(int*)iterator->value);

        iterator = iterator->next;
    }
    printf(".\n");
    int currIndex = prtIndexAux(tnode->left, idx + 1);
    currIndex = prtIndexAux(tnode->right, currIndex + 1);
    return currIndex;

}

void pTreeAux(Node* node, int* idxs, int col, int plus) {
    if (!node) return;
    int tmp = 0;
    if (plus) idxs[col] = 1;
    for (tmp = 0; tmp < col; tmp++)
        printf("%lc ", *(idxs + tmp)? C1 : ' ');
    if (node->left && node->right) {
        printf("%lc%lc%lc%lc %s [%d]", plus? C2 : C3, C4, C5, C4, node->word, node->documentIds->size);
        if (node->isRed) printf(", RED node");
        printf("\n");
        pTreeAux(node->left, idxs, col+1, 1);
        pTreeAux(node->right, idxs, col+1, 0);
    } else if (node->left || node->right) {
        printf("%lc%lc%lc%lc %s [%d]", plus? C2 : C3, C4, C5, C4, node->word, node->documentIds->size);
        if (node->isRed) printf(", RED node");
        printf("\n");
        pTreeAux((node->left)? node->left : node->right, idxs, col+1, 0);
    } else {
        printf("%lc%lc%lc%lc %s [%d]", plus? C2 : C3, C4, C4, C4, node->word, node->documentIds->size);
        if (node->isRed) printf(", RED node");
        printf("\n");
    }
    if (idxs[col]) idxs[col] = 0;
    idxs[col] = 0;
    return;
}

<<<<<<< HEAD
int calculateHeight(Node* node, Node* NIL) {
    if (node == NIL) return 0;
    int left = (calculateHeight(node->left, NIL) + 1);
    int right = (calculateHeight(node->right, NIL) + 1);
    return max(left, right);
}

void printTree(BinaryTree* tree) {
    if (tree == NULL || tree->root == NULL) return;
    #ifndef _WIN32
        setlocale(LC_CTYPE, "");
    #endif

    int height = calculateHeight(tree->root, tree->NIL);
    // setlocale(LC_CTYPE, "");
    int *idxs = malloc(height*4);
    for(int tmp = 0; tmp < height; tmp++) *(idxs + tmp) = 0;

    pTreeAux(tree->root, idxs, 0, 0);
    free(idxs);
    return;
}

void printIndex(BinaryTree* tree) {
    if (tree == NULL) return;
    Node* iterator = tree->root;
    int currIndex = prtIndexAux(iterator, 0);
    return;
}

int getMaxID(Node* node) {
    if (node == NULL) return 0;

    int left = getMaxID(node->left);
    int right = getMaxID(node->right);

    int currID = node->documentIds->size;
    if (right > currID) currID = right;
    if (left > currID) currID = left;

    return currID;
}

void svTreeAux(Node* node, int maxID, FILE* file, int isRBT) {
    if (node == NULL) return;
    int color1 = 0;
    int color2 = 0;
    int color3 = 0;
    string fontcolor = "black";
    if (isRBT && node->isRed || !isRBT) {
        color1 = 46*(((float) maxID - node->documentIds->size)/maxID) + 209;
        color2 = 190*(((float) maxID - node->documentIds->size)/maxID) + 65;
        color3 = 219*(((float) maxID - node->documentIds->size)/maxID) + 36;
    }
    /* else { */
    /*     color1 = 35*(((float) maxID - node->documentIds->size)/maxID) + 220; */
    /*     color2 = 140*(((float) maxID - node->documentIds->size)/maxID) + 115; */
    /*     color3 = 227*(((float) maxID - node->documentIds->size)/maxID) + 28; */
    /*     fontcolor = "black"; */
    /* } */
    else {
        color1 = -209*(((float) maxID - node->documentIds->size)/maxID) + 209;
        color2 = -125*(((float) maxID - node->documentIds->size)/maxID) + 125;
        color3 = -36*(((float) maxID - node->documentIds->size)/maxID) + 36;
        fontcolor = "white";
    }
    fprintf(file, "\t\"%s\" [fillcolor = \"#%02x%02x%02x\", fontcolor = \"%s\", color = \"%s\"]\n\t\"%s\"",
        node->word, color1,color2,color3,fontcolor,
        "black",node->word);
    if (node->right && node->left) {
        fprintf(file, "-> {\"%s\" \"%s\"}\n", node->right->word, node->left->word);
        svTreeAux(node->left, maxID, file, isRBT);
        svTreeAux(node->right, maxID, file, isRBT);
    }
    else if (node->left && !node->right || !node->left && node->right ) {
        fprintf(file, "-> \"%s\"\n", node->right ? node->right->word : node->left->word);
        svTreeAux(node->right ? node->right : node->left, maxID, file, isRBT);
    }
    else fprintf(file, "\n");

    return;
}

void saveTree(BinaryTree* tree) {
    FILE* file = fopen("test.txt", "w");
    if (file == NULL) return;

    fprintf(file, "digraph {\n\tbgcolor=\"moccasin\"\n\tnode [style=\"filled\", shape=\"component\"]\n");

    int maxID = getMaxID(tree->root);
    svTreeAux(tree->root, maxID, file, tree->NIL ? 1 : 0);

    fprintf(file, "}\n");
    fclose(file);

    system("mkdir graph >/dev/null 2>&1");
    system("dot -Tsvg ./test.txt > ./graph/output.svg ");
    return;
}
