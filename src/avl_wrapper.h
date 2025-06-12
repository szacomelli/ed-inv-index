#ifdef __cplusplus

extern "C" {
    #include "avl.h"
}

namespace AVL {
    using BinaryTree = BinaryTree;
    using InsertResult = InsertResult;
    using SearchResult = SearchResult;


    inline BinaryTree* create() {
        return createAVL();
    }

    inline InsertResult insert(BinaryTree* tree, string word, int docId) {
        return insertAVL(tree, word, docId);
    }

    inline SearchResult search(BinaryTree* tree, string word) {
        return searchAVL(tree, word);
    }

    inline void destroy(BinaryTree* tree) {
        destroyAVL(tree);
    }

}

#endif
