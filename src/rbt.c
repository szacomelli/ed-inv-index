#include "rbt.h"

BinaryTree* createRBT() {
  BinaryTree* tree = createTree();
  tree->NIL = createNode();
  if (!tree->NIL || !tree) {
    printf("Error creating BRT\n");
    return NULL;
  }
  tree->NIL->height = -1;
  tree->NIL->word = (string)malloc(4);
  strCopy("NIL", tree->NIL->word);
  return tree;  
}

int updateHeight(Node *node, string word, Node *NIL) {
   if (!node || node == NIL) return -1;
   if (strcmp(word, node->word) < 0) {
      int leftHeight = updateHeight(node->left, word, NIL);
      int rightHeight = 0;
      if (!node->right) rightHeight = -1;
      else rightHeight = node->right->height;
      node->height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
      return node->height;
   }
   else if (strcmp(word, node->word) > 0) {
      int rightHeight = updateHeight(node->right, word, NIL);
      int leftHeight = 0;
      if (!node->left) leftHeight = -1;
      else leftHeight = node->left->height;
      node->height = rightHeight > leftHeight ? rightHeight + 1 : leftHeight + 1;
      return node->height;
   }
   else {
     int leftHeight = -1;
     int rightHeight = -1;
     if (node->right) rightHeight = node->right->height;
     if (node->left) leftHeight = node->left->height;
     node->height = rightHeight > leftHeight ? rightHeight + 1 : leftHeight + 1;
     return node->height;
   }
}

// for the cases where inserting node breaks the balance, we need to "rotate" branches
void rotate(Node* node, int isRight) {
  if (isRight) {
    // saves the branches that will be implanted somewhere else
    Node* leftChild = node->left;
    Node* newLeft = leftChild->right;

    // in case of a parent, re-point the parent/next pointers
    leftChild->parent = node->parent;
    if (node->parent && leftChild->parent->left == node) leftChild->parent->left = leftChild;
    else if (node->parent && leftChild->parent->right == node) leftChild->parent->right = leftChild;

    // repointing the nodes, the rotation itself
    leftChild->right = node;
    node->parent = leftChild;
    node->left = newLeft;

    // in case of leftChild having a branch
    if (newLeft) newLeft->parent = node;
    
  }
  else { // everything is the same as above
    Node* rightChild = node->right;
    Node* newRight = rightChild->left;

    rightChild->parent = node->parent;
    if (rightChild->parent->left == node) rightChild->parent->left = rightChild;
    else if (rightChild->parent->right == node) rightChild->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
    node->right = newRight;
    if (newRight) newRight->parent = node;
    //updateHeight(newRight);
  }
  return;
}

// get the case the insert is currently stuck in
// 1: red uncle. 2: black uncle, asymmetric case. 3: black uncle, symmetric case
int getCase(Node* node) {
  int parLeft = 0;
  Node* grand = node->parent->parent;
  if (grand->left == node->parent) parLeft = 1;
  if (parLeft && grand->right->isRed || !parLeft && grand->left->isRed) return 1;
  else if (parLeft && node->parent->right == node || !parLeft && node->parent->left == node) return 2;
  else return 3;
}

// helper function to resolve the first insertion case
void firstHelper(Node* node, Node* NIL) {
  if (node->parent == NIL || node->parent->parent == NIL) return; // ensures we're not dealing with root or invalid nodes
  Node* grand = node->parent->parent;
  // sets colors
  node->parent->isRed = 0;
  grand->isRed = 1;
  if (grand->right == node->parent) grand->left->isRed = 0;
  else if (grand->left == node->parent) grand->right->isRed = 0;
  // call recursive function to recolor above nodes
  firstHelper(grand, NIL);
}

// helper for the third case (it's used by second)
void thirdHelper(Node* node) {
  // does the recoloring and rotations to rebalance the tree
  node->parent->isRed = 0;
  node->parent->parent->isRed = 1;
  if (node->parent->parent->left == node->parent) rotate(node->parent->parent, 1);
  else rotate(node->parent->parent, 0);

}

// helper for second case (reducts to symmetric third case and calls the third helper)
void secondHelper(Node* node) {
  if (node->parent->parent->left == node->parent) {
    rotate(node->parent, 0); 
    thirdHelper(node->left);
  }
  else {
    rotate(node->parent, 1);
    thirdHelper(node->right);
  }  
}

struct InsertResult insertRBT(BinaryTree* tree, string word, int docID) {
  if (!tree || !word || docID < 0) {
    struct InsertResult result = {.executionTime = 0, .numComparisons = 0, .status = 0};
    return result;
  }

  struct InsertResult result;
  clock_t startTime = clock();


  if (!(tree->root)) { // when the tree is still empty
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
    result.status = 1;
  }
  else {
    Node* iterator = tree->root;
    Node* last = NULL;
    int numComp = 0;
    int found = 0;
    // searching for duplicates
    while (iterator != tree->NIL) {
      numComp++;
      last = iterator;
      if (strcmp(word, iterator->word) < 0) iterator = iterator->left; 
      else if (strcmp(word, iterator->word) > 0) iterator = iterator->right;
      else if (strcmp(word, iterator->word) == 0) {
        found++;
        break;
      }
    }
    if (found) {
      int idFound = 0;
      node* listIt = iterator->documentIds->tail;
      while (listIt != NULL) {
        if (*((int*) listIt->value) == docID) {
          idFound = 1;
          break;
        }
        listIt = listIt->prev;
      }
      if (!idFound) {
        insertValue(iterator->documentIds, &docID);
      }

      double totalTime = (double) (clock() - startTime)/CLOCKS_PER_SEC;
      result.executionTime = totalTime;
      result.numComparisons = numComp;
      result.status = 2;
      return result; // will return if the duplicate word is found
    }
    // if not, will insert a new node
    Node* newNode = createNode();
    newNode->word = (string)malloc( strSize(word) + 1);
    strCopy(word, newNode->word);
    newNode->documentIds = createList("int");
    newNode->right = tree->NIL;
    newNode->left = tree->NIL;
    newNode->isRed = 1;
    newNode-> height = 0;
    insertValue(newNode->documentIds, &docID);
    if (strcmp(word, last->word) < 0) last->left = newNode;
    else last->right = newNode;
    newNode->parent = last;
    newNode->height = 0;

    // here, it rebalances the tree, accordingly with the current case
    if (last->isRed) {
      int nCase = getCase(newNode);
      if (nCase == 1) firstHelper(newNode, tree->NIL);
      else if (nCase == 2) {
        if (newNode->parent->parent == tree->root) tree->root = newNode;
        secondHelper(newNode);
        if (newNode->left) updateHeight(tree->root, newNode->left->word, tree->NIL);
        if (newNode->right) updateHeight(tree->root, newNode->right->word, tree->NIL);
      }
      else if (nCase == 3) { 
        if (newNode->parent->parent == tree->root) tree->root = newNode->parent;
        thirdHelper(newNode);
        if (newNode->parent->right) updateHeight(tree->root, newNode->parent->right->word, tree->NIL);
        if (newNode->parent->left) updateHeight(tree->root, newNode->parent->left->word, tree->NIL);
      }
      tree->root->isRed = 0;
    }
    
    result.numComparisons = numComp;
    updateHeight(tree->root, word, tree->NIL);

  }
  
  double totalTime = (double) (clock() - startTime)/CLOCKS_PER_SEC;
  result.executionTime = totalTime;
  result.status = 1;
  return result;
}

struct SearchResult searchRBT(BinaryTree* tree, string word) {
  struct SearchResult result;
  result.found = 0;
  result.documentIds = NULL;
  result.executionTime = 0;
  result.numComparisons = 0;
  if (!tree || !word) return result;
  result.documentIds = NULL;
  int numComp = 0;
  Node* iterator = tree->root;
  // works the same as in the insert function
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
