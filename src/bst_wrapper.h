#ifdef __cplusplus

extern "C" {
    #include "bst.h"
}

namespace BST {
    using BinaryTree = BinaryTree;
    using InsertResult = InsertResult;
    using SearchResult = SearchResult;


    inline BinaryTree* create() {
        return createTree();
    }

    inline InsertResult insert(BinaryTree* tree, string word, int docId) {
        return insertBST(tree, word, docId);
    }

    inline SearchResult search(BinaryTree* tree, string word) {
        return searchBST(tree, word);
    }

    inline void destroy(BinaryTree* tree) {
        destroyBST(tree);
    }

}

#endif
