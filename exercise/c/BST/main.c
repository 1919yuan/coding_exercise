/* Given a binary search tree and the value of a node, find the in-order successor of the specified node. */

/*                 9 */
/*               /   \ */
/*             5      14 */
/*           /      /    \ */
/*         2       12    17 */
/*                   \ */
/*                   13 */

/* INPUT: */
/* 1) a binary search tree */
/* 2) value of a given node (integer) */

/* OUTPUT: */
/* reference of the in-order successor node */

#include "bst.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    Node *root=NULL;
    Node *res=NULL;
    int key = atoi(argv[1]);
    tree_insert(&root, 9);
    tree_insert(&root, 5);
    tree_insert(&root, 2);
    tree_insert(&root, 14);
    tree_insert(&root, 12);
    tree_insert(&root, 13);
    tree_insert(&root, 17);
    res = find_successor(root, key);
    if (res)
        printf("%d\n", res->key);
    res = tree_delete(&root, res);
    if (res) free(res);
    res = find_successor(root, key);
    if (res)
        printf("%d\n", res->key);
    return 0;
}
