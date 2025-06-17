#ifdef __cplusplus

extern "C" {
  #include "rbt.h"
}

namespace RBT {
    using BinaryTree = BinaryTree;
    using InsertResult = InsertResult;
    using SearchResult = SearchResult;


    inline BinaryTree* create() {
        return createTree();
    }

    inline InsertResult insert(BinaryTree* tree, string word, int docId) {
        return insertRBT(tree, word, docId);
    }

    inline SearchResult search(BinaryTree* tree, string word) {
        return searchRBT(tree, word);
    }

    inline void destroy(BinaryTree* tree) {
        destroyRBT(tree);
    }

}

#endif
