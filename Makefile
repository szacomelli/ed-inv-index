all: main_bst test_bst

main_bst: src/main_bst.c src/bst.o src/data.o src/lkdlist.o src/str.o src/tree_utils.o
	gcc src/bst.o src/data.o src/lkdlist.o src/str.o src/tree_utils.o src/main_bst.c -o main_bst

test_bst: src/bst.o src/data.o src/lkdlist.o src/str.o src/tree_utils.o src/test_bst.c
	gcc src/bst.o src/data.o src/lkdlist.o src/str.o src/tree_utils.o src/test_bst.c -o test_bst

src/bst.o: src/bst.c
	gcc src/bst.c -c -o src/bst.o

src/data.o: src/data.c
	gcc src/data.c -c -o src/data.o

src/lkdlist.o: src/lkdlist.c
	gcc src/lkdlist.c -c -o src/lkdlist.o

src/str.o: src/str.c
	gcc src/str.c -c -o src/str.o

src/tree_utils.o: src/tree_utils.c
	gcc src/tree_utils.c -c -o src/tree_utils.o

ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
clear:
	del *.out *.exe *.o .\src\*.o .\src\*.exe .\src\*.out
else
    detected_OS := $(shell uname)  # same as "uname -s"
clear:
	rm *.out *.exe *.o ./src/*.o ./src/*.exe ./src/*.out main_bst test_bst
endif
