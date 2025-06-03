#include <stdio.h>
#include "tree_utils.h"

tNode* createtNode() {
    tNode* node = malloc(sizeof(tNode));
    node->word = NULL;

    node->documentIds = createList("int");
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = -1;    // usado na AVL
    node->isRed = 0;
    return node;
}

bTree* createTree() {
    tNode* root;
    tNode* NIL;
    bTree* tree = malloc(sizeof(bTree));
    tree->root = NULL;
    tree->NIL = NULL;
    return tree;
}

int prtIndexAux(tNode* tnode, int idx) {
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

void pTreeAux(tNode* node, int* idxs, int col, int plus, int height) {
    if (!node) return;
    int tmp = 0;
    if (plus) idxs[col] = 1;
    for (tmp = 0; tmp < col; tmp++)
        printf("%c ", *(idxs + tmp)? 179 : ' ');
    if (node->left && node->right) {
        printf("%c%c%c%c %s [%d]\n", plus? 195 : 192, 196, 194, 196, node->word, node->documentIds->size);
        pTreeAux(node->left, idxs, col+1, 1, height);
        pTreeAux(node->right, idxs, col+1, 0, height);
    } else if (node->left || node->right) {
        printf("%c%c%c%c %s [%d]\n", plus? 195 : 192, 196, 194, 196, node->word, node->documentIds->size);
        pTreeAux((node->left)? node->left : node->right, idxs, col+1, 0, height);
    } else {
        printf("%c%c%c%c %s [%d]\n", plus? 195 : 192, 196, 196, 196, node->word, node->documentIds->size);
    }
    if (idxs[height]) idxs[height] = 0;
    idxs[col] = 0;
    return;
}

void printTree(bTree* tree) {
    int *idxs = calloc(tree->root->height, 4);
    for(int tmp = 0; tmp < tree->root->height; tmp++) *(idxs + tmp) = 0;
    pTreeAux(tree->root, idxs, 0, 0, tree->root->height);
    free(idxs);
    return;
}

void printIndex(bTree* tree) {
    if (tree == NULL) return;
    tNode* iterator = tree->root;
    int currIndex = prtIndexAux(iterator, 0);
    return;
}

int getMaxID(tNode* node) {
    if (node == NULL) return 0;

    int left = getMaxID(node->left);
    int right = getMaxID(node->right);

    int currID = node->documentIds->size;
    if (right > currID) currID = right;
    if (left > currID) currID = left;

    return currID;
}

void svTreeAux(tNode* node, int maxID, FILE* file) {
    if (node == NULL) return;
    int color1 = 225*(((float) maxID - node->documentIds->size)/maxID) + 30;
    int color2 = 111*(((float) maxID - node->documentIds->size)/maxID) + 144;
    printf("%x %x\n", color1, color2);

    fprintf(file, "\t%s [fillcolor = \"#%02x%02x%02x\", fontcolor = \"%s\", color = \"%s\"]\n\t%s",
        node->word, color1,color2,255,"black",
        "black",node->word);
    if (node->right && node->left) {
        fprintf(file, "-> {%s %s}\n", node->right->word, node->left->word);
        svTreeAux(node->left, maxID, file);
        svTreeAux(node->right, maxID, file);
    }
    else if (node->left && !node->right || !node->left && node->right ) {
        fprintf(file, "-> %s\n", node->right ? node->right : node->left);
        svTreeAux(node->right ? node->right : node->left, maxID, file);
    }
    else fprintf(file, "\n");

    return;
}

void saveTree(bTree* tree) {
    FILE* file = fopen("test.txt", "w");
    if (file == NULL) return;

    fprintf(file, "digraph {\n\tbgcolor=\"navajowhite\"\n\tnode [style=\"filled\", shape=\"component\"]\n");

    int maxID = getMaxID(tree->root);
    svTreeAux(tree->root, maxID, file);

    fprintf(file, "}\n");
    fclose(file);

    system("mkdir graph ; dot -Tsvg ./test.txt > ./graph/output.svg");
    return;
}
