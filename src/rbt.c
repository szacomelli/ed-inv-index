#include "rbt.h"

BinaryTree* createRBT() {
  BinaryTree* tree = createTree();
  tree->NIL = createNode();
  tree->NIL->height = 0;
  return tree;  
}

void rotate(Node* node, int isRight) {
  if (isRight) {
    Node* leftChild = node->left;
    Node* newLeft = leftChild->right;

    leftChild->parent = node->parent;
    if (node->parent && leftChild->parent->left == node) leftChild->parent->left = leftChild;
    else if (node->parent && leftChild->parent->right == node) leftChild->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
    node->left = newLeft;
    if (newLeft) newLeft->parent = node;
  }
  else {
    Node* rightChild = node->right;
    Node* newRight = rightChild->left;

    rightChild->parent = node->parent;
    if (rightChild->parent->left == node) rightChild->parent->left = rightChild;
    else if (rightChild->parent->right == node) rightChild->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
    node->right = newRight;
    if (newRight) newRight->parent = node;
  }
  return;
}

int getCase(Node* node) {
  int parLeft = 0;
  Node* grand = node->parent->parent;
  if (grand->left == node->parent) parLeft = 1;
  if (parLeft && grand->right->isRed || !parLeft && grand->left->isRed) return 1;
  else if (node->parent->right == node) return 2;
  else return 3;
}

void firstHelper(Node* node, Node* NIL) {
  if (node->parent == NIL || node->parent->parent == NIL) return;
  Node* grand = node->parent->parent;
  node->parent->isRed = 0;
  grand->isRed = 1;
  if (grand->right = node->parent) grand->left->isRed = 0;
  if (grand->left = node->parent) grand->right->isRed = 0;

  firstHelper(grand, NIL);
}

void secondHelper(Node* node) {
  if (node->parent->parent->left == node->parent) rotate(node->parent, 0);
  else rotate(node->parent, 1);
  secondHelper(node);
}

void secondHelper(Node* node) {
  node->parent->isRed = 0;
  node->parent->parent->isRed = 1;
  if (node->parent->parent->left == node->parent) rotate(node->parent->parent, 1);
  else rotate(node->parent->parent, 0);
}


struct InsertResult insertRBT(BinaryTree* tree, const string word, int docID) {
  if (!tree || !word || docID < 0) return;

  struct InsertResult result;
  clock_t startTime = clock();


  if (!(tree->root)) {
    Node* newRoot = createNode();
    newRoot->word = word;
    newRoot->documentIds = createList("int");
    insertValue(newRoot->documentIds, &docID);
    newRoot->left = tree->NIL;
    newRoot->right = tree->NIL;
    newRoot->parent = tree->NIL;
    newRoot->height = 0;
    tree->root = newRoot;
    result.numComparisons = 0;
  }
  else {
    struct SearchResult findDup = searchRBT(tree, word);
    if (findDup.found) {
      insertValue(findDup.documentIds, docID);
      clock_t totalTime = (double) (clock() - startTime)/CLOCKS_PER_SEC;
      result.executionTime = totalTime;
      result.numComparisons = findDup.numComparisons;
      return result;
    }

    Node* iterator = tree->root;
    Node* last = NULL;
    int numComp = 0;
    while (iterator != tree->NIL) {
      numComp++;
      last = iterator;
      if (strcmp(word, iterator->word) < 0) iterator = iterator->left;
      if (strcmp(word, iterator->word) > 0) iterator = iterator->right;
    }

    Node* newNode = createNode();
    newNode->word = word;
    newNode->documentIds = createList("int");
    newNode->right = tree->NIL;
    newNode->left = tree->NIL;
    newNode->isRed = 1;
    insertValue(newNode->documentIds, &docID);
    if (strcmp(word, last->word) < 0) last->left = newNode;
    else last->right = newNode;
    newNode->parent = last;
      

    if (last->isRed) {
      int nCase = getCase(newNode);
      if (nCase == 1) firstHelper(newNode, tree->NIL);
      else if (nCase == 2) secondHelper(newNode);
      else if (nCase == 3) thirdHelper(newNode);
      // unfinished

    }
    



  }

  clock_t totalTime = (double) (clock() - startTime)/CLOCKS_PER_SEC;
  result.executionTime = totalTime;
  return result;
}