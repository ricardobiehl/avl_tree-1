
CFLAGS = -std=c99 -Wall -O2

test: avl_tree.o avl_generic.o avl_traversal.o test.o

test.o: avl_tree.h avl_generic.h avl_traversal.h test.c

avl_traversal.o: avl_tree.h avl_traversal.h avl_traversal.c
avl_generic.o: avl_tree.h avl_generic.h avl_generic.c

avl_tree.o: avl_tree.h avl_tree.c
