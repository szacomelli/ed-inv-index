#include "bst_wrapper.h"

int main(void) {
    BST::BinaryTree* oi = BST::create();
    BST::insert(oi, "abacaxi", 3);
    printTree(oi);
    printTree(oi);
}
