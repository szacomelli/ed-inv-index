# ed-inv-index
Implementing inverted indexing with trees, for a college assignment.

## How to use

Just run `make all` in the main directory of the repo. This will create two executables: 
- main_bst: the main file for searching and seeking statistics on a inverse index implemented using binary search tree;
- test_bst: file with unitary tests for the binary search tree;
- main_avl: the same as main_bst, but using AVL tree to implement the inverted index;
- test_avl: file with unitary tests for the Adelson-Velsky and Landis tree;
- main_rbt: same as main_bst, but using the Red-Black Tree to implement the inverse index;
- test_rbt: file with tests for the BST.

You can, then, run any of them as you please.

### How to run the programs
After compiling to `main_<tree>` or `test_<tree>`, you will probably want to use them. Below are the instructions to do so:
- `main_<tree>`: For these, run `./main_<tree> <mode> <num_docs> <path_docs>`. The \<mode\> stands for `search`, if you want to build the tree and search for words (in an interactive and self-explanatory way), and `stats`, if you want to gather statistics about the program's performance. The statistics gathered are saved in .csv files, inside \<root\>/stats directory (where \<root\> is the main repository directory). \<num_docs\> is the number of documents that the user wants the program to read, and \<path_docs\> is the directory where the .txts are in, relatively to \<root\>. The .txts need to be named in the form of `doc_number.txt`, where doc_number starts from 0 and increse by steps of 1;

- `test_<tree>`: These are pretty straightforward. Just run it with `./test_<tree>` and the program will prompt the user to type `y` if they want to run the tests or `n` otherwise.

## If you want to use the BST or AVL in C++ code
For that purpose, take a look at the src directory after you have compiled the files with make.
You'll see several .o's there, for each of the .c and .h files of the project. You'll need to compile them with you main C++ code in order to use the avl.c or bst.c content.
Also, in your C++ code, you'll need to #include the `bst_wrapper.h` or `avl_wrapper.h` header file. It'll give you access to the functions defined in almost all .c files, and access to the namespace AVL/BST.
That is, you'll have access to `BST::create`, `BST::insert`, `BST::search` and `BST::destroy`, functions for the BST creation and usage. Or, in the case of AVL or RBT, `AVL::create`, `AVL::insert`, `AVL::destroy`, `AVL::search` or `RBT::create`, `RBT::insert`, `RBT::destroy`, `RBT::search`.

Then, just use the functions you want in your C++ code and remember to compile the .cpp along with all the .o's in src.

If you find any problems, just create an issue.
