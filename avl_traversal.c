/*
 * intrusive, nonrecursive AVL tree data structure (self-balancing
 * binary search tree)
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
 * Nonrecursive AVL tree traversal functions
 * =========================================
 */

#include "avl_tree.h"

/* Returns the left child (sign < 0) or the right child (sign > 0) of the
 * specified AVL tree node.
 * Note: for all calls of this, 'sign' is constant at compilation time,
 * so the compiler can remove the conditional.  */
static AVL_INLINE struct avl_tree_node *
avl_get_child(const struct avl_tree_node *parent, int sign)
{
	if (sign < 0)
		return parent->left;
	else
		return parent->right;
}

static AVL_INLINE struct avl_tree_node *
avl_tree_first_or_last_in_order(const struct avl_tree_root *root, int sign)
{
	const struct avl_tree_node *first = root->avl_tree_node;

	if (first) {
		while (avl_get_child(first, +sign))
			first = avl_get_child(first, +sign);
	}

	return (struct avl_tree_node *)first;
}

/* Starts an in-order traversal of the tree: returns the least-valued node, or
 * NULL if the tree is empty.  */
struct avl_tree_node *
avl_tree_first_in_order(const struct avl_tree_root *root)
{
	return avl_tree_first_or_last_in_order(root, -1);
}

/* Starts a *reverse* in-order traversal of the tree: returns the
 * greatest-valued node, or NULL if the tree is empty.  */
struct avl_tree_node *
avl_tree_last_in_order(const struct avl_tree_root *root)
{
	return avl_tree_first_or_last_in_order(root, 1);
}

static AVL_INLINE struct avl_tree_node *
avl_tree_next_or_prev_in_order(const struct avl_tree_node *node, int sign)
{
	const struct avl_tree_node *next;

	if (avl_get_child(node, +sign))
		for (next = avl_get_child(node, +sign);
		     avl_get_child(next, -sign);
		     next = avl_get_child(next, -sign));
	else
		for (next = avl_get_parent(node);
		     next && node == avl_get_child(next, +sign);
		     node = next, next = avl_get_parent(next));

	return (struct avl_tree_node *)next;
}

/* Continues an in-order traversal of the tree: returns the next-greatest-valued
 * node, or NULL if there is none.  */
struct avl_tree_node *
avl_tree_next_in_order(const struct avl_tree_node *node)
{
	return avl_tree_next_or_prev_in_order(node, 1);
}

/* Continues a *reverse* in-order traversal of the tree: returns the
 * previous-greatest-valued node, or NULL if there is none.  */
struct avl_tree_node *
avl_tree_prev_in_order(const struct avl_tree_node *node)
{
	return avl_tree_next_or_prev_in_order(node, -1);
}

/* Starts a postorder traversal of the tree.  */
struct avl_tree_node *
avl_tree_first_in_postorder(const struct avl_tree_root *root)
{
	const struct avl_tree_node *first = root->avl_tree_node;

	if (first)
		while (first->left || first->right)
			first = first->left ? first->left : first->right;

	return (struct avl_tree_node *)first;
}

/* Continues a postorder traversal of the tree.  @prev will not be deferenced as
 * it's allowed that its memory has been freed; @prev_parent must be its saved
 * parent node.  Returns NULL if there are no more nodes (i.e. @prev was the
 * root of the tree).  */
struct avl_tree_node *
avl_tree_next_in_postorder(const struct avl_tree_node *prev,
			   const struct avl_tree_node *prev_parent)
{
	const struct avl_tree_node *next = prev_parent;

	if (next && prev == next->left && next->right)
		for (next = next->right;
		     next->left || next->right;
		     next = next->left ? next->left : next->right);

	return (struct avl_tree_node *)next;
}
