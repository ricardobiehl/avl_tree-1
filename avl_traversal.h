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

#ifndef _AVL_TRAVERSAL_H
#define _AVL_TRAVERSAL_H

#include "avl_tree.h"

struct avl_tree_node *
avl_tree_first_in_order(const struct avl_tree_node *root);

struct avl_tree_node *
avl_tree_last_in_order(const struct avl_tree_node *root);

struct avl_tree_node *
avl_tree_next_in_order(const struct avl_tree_node *node);

struct avl_tree_node *
avl_tree_prev_in_order(const struct avl_tree_node *node);

struct avl_tree_node *
avl_tree_first_in_postorder(const struct avl_tree_node *root);

struct avl_tree_node *
avl_tree_next_in_postorder(const struct avl_tree_node *prev,
                           const struct avl_tree_node *prev_parent);

#endif /* _AVL_TRAVERSAL_H */
