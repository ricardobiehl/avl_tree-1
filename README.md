# Overview

This is a zero-dependency, high performance C implementation of AVL trees.  It
is intended to be incorporated into C programming projects that need to use
self-balancing binary search trees.

This implementation is "intrusive", meaning that the tree node structure must be
embedded inside the data structure to be indexed in the tree.  This is the style
commonly used in kernel data structures.  This is actually the more general
style of implementation; a void pointer and comparison callback-based
implementation can (but does not have to be) be built on top of it.

This implementation is non-recursive, so it does not suffer from stack
overflows.

# Features

Briefly, the supported operations are:

- Insertion
- Deletion
- Search
- In-order traversal (forwards and backwards)
- Post-order traversal

See avl_tree.h for details.

# Files

- avl_generic:    Generic tree insert and look up operations.
- avl_iteration:  Helpers to iterate over the tree.
- avl_traversal:  Helpers to traverse the tree.

- avl_tree.h:  Implementation file.
- avl_tree.c:  Implementation header.
- test.c:      A test program.

# License

This code and its accompanying files have been released into the public domain.
There is NO WARRANTY, to the extent permitted by law.  See the CC0 Public Domain
Dedication in the COPYING file for details.
