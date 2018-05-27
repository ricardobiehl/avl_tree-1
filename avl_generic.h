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
 * AVL tree generic operations
 * ===========================
 */

#ifndef _AVL_GENERIC_H
#define _AVL_GENERIC_H

#include "avl_tree.h"

struct avl_tree_node *
avl_tree_lookup(const struct avl_tree_node *root,
                const void *cmp_ctx,
                int (*cmp)(const void *, const struct avl_tree_node *));

struct avl_tree_node *
avl_tree_lookup_node(const struct avl_tree_node *root,
                     const struct avl_tree_node *node,
                     int (*cmp)(const struct avl_tree_node *,
                                const struct avl_tree_node *));

struct avl_tree_node *
avl_tree_insert(struct avl_tree_node **root_ptr,
                struct avl_tree_node *item,
                int (*cmp)(const struct avl_tree_node *,
                           const struct avl_tree_node *));

#endif /* _AVL_GENERIC_H */
