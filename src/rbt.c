#include "rbt.h"

BinaryTree* createRBT() {
  BinaryTree* tree = createTree();
  tree->NIL = createNode();
  tree->NIL->height = 0;
  tree->NIL->word = (string)malloc(4);
  strCopy("NIL", tree->NIL->word);
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
  else if (parLeft && node->parent->right == node || !parLeft && node->parent->left == node) return 2;
  else return 3;
}

void firstHelper(Node* node, Node* NIL) {
  if (node->parent == NIL || node->parent->parent == NIL) return;
  Node* grand = node->parent->parent;
  node->parent->isRed = 0;
  grand->isRed = 1;
  if (grand->right == node->parent) grand->left->isRed = 0;
  else if (grand->left == node->parent) grand->right->isRed = 0;
  firstHelper(grand, NIL);
}

void thirdHelper(Node* node) {
  node->parent->isRed = 0;
  node->parent->parent->isRed = 1;
  if (node->parent->parent->left == node->parent) rotate(node->parent->parent, 1);
  else rotate(node->parent->parent, 0);

}

void secondHelper(Node* node) {
  if (node->parent->parent->left == node->parent) {
    rotate(node->parent, 0); 
    thirdHelper(node->right);
  }
  else {
    rotate(node->parent, 1);
    thirdHelper(node->right);
  }  
}


struct InsertResult insertRBT(BinaryTree* tree, const string word, int docID) {
  if (!tree || !word || docID < 0) {
    struct InsertResult result = {.executionTime = 0, .numComparisons = 0}; 
    return result;
  }

  struct InsertResult result;
  clock_t startTime = clock();


  if (!(tree->root)) {
    Node* newRoot = createNode();
    newRoot->word = (string)malloc( strSize(word) + 1);
    strCopy(word, newRoot->word);
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
      insertValue(findDup.documentIds, &docID);
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
      else if (strcmp(word, iterator->word) > 0) iterator = iterator->right;
    }
    Node* newNode = createNode();
    newNode->word = (string)malloc( strSize(word) + 1);
    strCopy(word, newNode->word);
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
      else if (nCase == 2) {
        if (newNode->parent->parent == tree->root) tree->root = newNode;
        secondHelper(newNode);
      
      }
      else if (nCase == 3) { 
        if (newNode->parent->parent == tree->root) tree->root = newNode->parent;
        thirdHelper(newNode);
      }
      tree->root->isRed = 0;
    }
    
    result.numComparisons = numComp;
  }
  
  clock_t totalTime = (double) (clock() - startTime)/CLOCKS_PER_SEC;
  result.executionTime = totalTime;
  return result;
}

struct SearchResult searchRBT(BinaryTree* tree, const string word) {
  struct SearchResult result;
  result.found = 0;
  result.documentIds = NULL;
  int numComp = 0;
  Node* iterator = tree->root;
  while (iterator != tree->NIL) {
    numComp++;
    if (strcmp(word, iterator->word) < 0) iterator = iterator->left;
    else if (strcmp(word, iterator->word) > 0) iterator = iterator->right;
    else {
      result.found = 1;
      result.documentIds = iterator->documentIds;
      break;
    }
  }
  result.numComparisons = numComp;
  return result;
}

static void bstFreeRec(Node *root, Node* NIL)
{
  if (root == NIL) return;

  bstFreeRec(root->left, NIL);
  bstFreeRec(root->right, NIL);

   freeList(root->documentIds);
   root->documentIds = NULL;

   free(root->word);
   root->word = NULL;
   
   free(root);
   root = NULL;
}

void destroyRBT(BinaryTree *tree)
{
  if (tree == NULL) return;
  if (tree->root != NULL)
  {
    bstFreeRec(tree->root, tree->NIL);
    tree->root = NULL;
    free(tree->NIL);
    tree->NIL = NULL;
    free(tree);
    tree = NULL;
  }
}