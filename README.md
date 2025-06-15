# ed-inv-index
Implementing inverted indexing with trees, for a college assignment.

## How to use

Just run `make all` in the main directory of the repo. This will create two executables: 
- main_bst: the main file for searching and seeking statistics on a inverse index implemented using binary search tree;

- test_bst: file with unitary tests for the binary search tree;
- main_avl: the same as main_bst, but using AVL tree to implement the inverted index;
- test_avl: file with unitary tests for the Adelson-Velsky and Landis tree.

You can, then, run any of them as you please.

## If you want to use the BST or AVL in C++ code
For that purpose, take a look at the src directory after you have compiled the files with make.
You'll see several .o's there, for each of the .c and .h files of the project. You'll need to compile them with you main C++ code in order to use the avl.c or bst.c content.
Also, in your C++ code, you'll need to #include the `bst_wrapper.h` or `avl_wrapper.h` header file. It'll give you access to the functions defined in almost all .c files, and access to the namespace AVL/BST.
That is, you'll have access to `BST::create`, `BST::insert`, `BST::search` and `BST::destroy`, functions for the BST creation and usage. Or, in the case of AVL, `AVL::create`, `AVL::insert`, `AVL::destroy` or `AVL::search`.

Then, just use the functions you want in your C++ code and remember to compile the .cpp along with all the .o's in src.

If you find any problems, just create an issue.
