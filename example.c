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

#ifndef container_of
#include <stddef.h> /* offsetof() */
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#include "avl_tree.h"

#include "example.h"

struct example*
avl_search(struct avl_tree_link *link, struct avl_tree_root *root,
           unsigned long key)
{
	struct avl_tree_node **current = &root->avl_tree_node;

	tree_search_for_each (link, current) {
		struct example *tmp;

		tmp = container_of(*current, struct example, node);

		if (key < tmp->key)
			current = &(*current)->left;
		else if (key > tmp->key)
			current = &(*current)->right;
		else
			return tmp;
	}

	return NULL;
}

/*
 * NOTE: the use of link in deletion might have some
 * performance penalty. It was done this way to allow
 * reusing avl_search()
 */
int
avl_delete(struct avl_tree_root *root, unsigned long key)
{
	struct avl_tree_link link;

	if (avl_search(&link, root, key) == NULL)
		return -1;

	avl_tree_remove(root, *link.node);

	return 0;
}

int
avl_insert(struct avl_tree_root *root, struct example *new)
{
	struct avl_tree_link link;

	if (avl_search(&link, root, new->key) != NULL)
		return -1;

	*link.node = &new->node;
	(*link.node)->parent = link.parent;
	(*link.node)->balance = 0;
	avl_tree_rebalance_after_insert(root, *link.node);

	return 0;
}
