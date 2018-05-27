/*
 * avl_tree.c - intrusive, nonrecursive AVL tree data structure (self-balancing
 *		binary search tree), implementation file
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

/*
 * macros to iterate over AVL tree
 * ===============================
 */

#ifndef _AVL_ITERATION_H
#define _AVL_ITERATION_H

#include "avl_tree.h"

/*
 * Iterate through the nodes in an AVL tree in sorted order.
 * You may not modify the tree during the iteration.
 *
 * @child_struct
 *	Variable that will receive a pointer to each struct inserted into the
 *	tree.
 * @root
 *	Root of the AVL tree.
 * @struct_name
 *	Type of *child_struct.
 * @struct_member
 *	Member of @struct_name type that is the AVL tree node.
 *
 * Example:
 *
 * struct int_wrapper {
 *	int data;
 *	struct avl_tree_node index_node;
 * };
 *
 * void print_ints(struct avl_tree_node *root)
 * {
 *	struct int_wrapper *i;
 *
 *	avl_tree_for_each_in_order(i, root, struct int_wrapper, index_node)
 *		printf("%d\n", i->data);
 * }
 */
#define avl_tree_for_each_in_order(child_struct, root,			\
				   struct_name, struct_member)		\
	for (struct avl_tree_node *_cur =				\
		avl_tree_first_in_order(root);				\
	     _cur && ((child_struct) =					\
		      avl_tree_entry(_cur, struct_name,			\
				     struct_member), 1);		\
	     _cur = avl_tree_next_in_order(_cur))

/*
 * Like avl_tree_for_each_in_order(), but uses the reverse order.
 */
#define avl_tree_for_each_in_reverse_order(child_struct, root,		\
					   struct_name, struct_member)	\
	for (struct avl_tree_node *_cur =				\
		avl_tree_last_in_order(root);				\
	     _cur && ((child_struct) =					\
		      avl_tree_entry(_cur, struct_name,			\
				     struct_member), 1);		\
	     _cur = avl_tree_prev_in_order(_cur))

/*
 * Like avl_tree_for_each_in_order(), but iterates through the nodes in
 * postorder, so the current node may be deleted or freed.
 */
#define avl_tree_for_each_in_postorder(child_struct, root,		\
				       struct_name, struct_member)	\
	for (struct avl_tree_node *_cur =				\
		avl_tree_first_in_postorder(root), *_parent;		\
	     _cur && ((child_struct) =					\
		      avl_tree_entry(_cur, struct_name,			\
				     struct_member), 1)			\
	          && (_parent = avl_get_parent(_cur), 1);		\
	     _cur = avl_tree_next_in_postorder(_cur, _parent))

#endif /* _AVL_ITERATION_H */
