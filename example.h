/*
 * Example of use
 *
 * This file was written in 2018 by Ricardo Biehl Pasquali
 * <pasqualirb@gmail.com>
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
 * 10/02/2018, 27/05/2018
 *
 * AVL named after Georgy Maximovich Adelson-Velsky and
 * Evgenii Mikhailovich Landis.
 */

#ifndef _AVL_EXAMPLE_H
#define _AVL_EXAMPLE_H

#include "avl_tree.h"

struct example {
	struct avl_tree_node node;
	unsigned long key;
};

struct example*
avl_search(struct avl_tree_link *link, struct avl_tree_root *root,
           unsigned long key);

int
avl_delete(struct avl_tree_root *root, unsigned long key);

int
avl_insert(struct avl_tree_root *root, struct example *new);

#endif /* _AVL_EXAMPLE_H */
