/*
 * avl_tree.h - intrusive, nonrecursive AVL tree data structure (self-balancing
 *		binary search tree), header file
 *
 * Written in 2014-2016 by Eric Biggers <ebiggers3@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide via the Creative Commons Zero 1.0 Universal Public Domain
 * Dedication (the "CC0").
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the CC0 for more details.
 *
 * You should have received a copy of the CC0 along with this software; if not
 * see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <stdbool.h>
#include <stddef.h>

#ifdef __GNUC__
#  define AVL_INLINE inline __attribute__((always_inline))
#else
#  define AVL_INLINE inline
#  warning "AVL tree functions may not be inlined as intended"
#endif

/* Node in an AVL tree.  Embed this in some other data structure.  */
struct avl_tree_node {

	struct avl_tree_node *parent;

	/* Pointer to left child or NULL  */
	struct avl_tree_node *left;

	/* Pointer to right child or NULL  */
	struct avl_tree_node *right;

	int balance;
};

struct avl_tree_root {
	struct avl_tree_node *avl_tree_node;
};

#define AVL_ROOT  (struct avl_tree_root) {NULL, }

struct avl_tree_link {
	struct avl_tree_node *parent;
	struct avl_tree_node **node;
};

#define tree_search_for_each(l, current) \
	for ((l)->parent = NULL, (l)->node = current; \
	     *current; \
	     (l)->parent = *(l)->node, (l)->node = current)

/* Cast an AVL tree node to the containing data structure.  */
#define avl_tree_entry(entry, type, member) \
	((type*) ((char *)(entry) - offsetof(type, member)))

/* Returns a pointer to the parent of the specified AVL tree node, or NULL if it
 * is already the root of the tree.  */
static AVL_INLINE struct avl_tree_node *
avl_get_parent(const struct avl_tree_node *node)
{
	return node->parent;
}

/* Marks the specified AVL tree node as unlinked from any tree.  */
static AVL_INLINE void
avl_tree_node_set_unlinked(struct avl_tree_node *node)
{
	node->parent = node;
}

/* Returns true iff the specified AVL tree node has been marked with
 * avl_tree_node_set_unlinked() and has not subsequently been inserted into a
 * tree.  */
static AVL_INLINE bool
avl_tree_node_is_unlinked(const struct avl_tree_node *node)
{
	return node->parent == node;
}

/* (Internal use only)  */
extern void
avl_tree_rebalance_after_insert(struct avl_tree_root *root,
				struct avl_tree_node *inserted);

/* Removes an item from the specified AVL tree.
 * See implementation for details.  */
extern void
avl_tree_remove(struct avl_tree_root *root, struct avl_tree_node *node);

#endif /* _AVL_TREE_H_ */
