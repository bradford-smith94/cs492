/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 tree.c
 * 04/26/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "tree.h"

/* pre: takes in a void* 'data'
 * post: allocates a new tree leaf that holds 'data'
 * return: a leaf* pointing to the newly allocated tree leaf, or NULL on error
 */
leaf* createLeaf(void* data)
{
    leaf* ret;

    ret = NULL;
    if (data != NULL)
    {
        if ((ret = (leaf*)malloc(sizeof(leaf))) != NULL)
        {
            ret->data = data;
            ret->children = NULL;
        }
    }

    return ret;
}

/* pre: takes in a leaf** 'tree' and a leaf* 'l'
 * post: appends 'l' to the tree as a child of 'tree'
 */
void appendLeaf(leaf** tree, leaf* l)
{
    if (l != NULL)
    {
        if ((*tree) == NULL)
            (*tree) = l;
        else
        {
            appendNode(&((*tree)->children), (void*)l);
        }
    }
}

/* pre: takes in a leaf** 'tree' and a leaf* 'l'
 * post: removes 'l' from the tree pointed to by 'tree'
 * return: a leaf* pointing to the leaf that was removed from 'tree'
 */
leaf* removeLeaf(leaf** tree, leaf* l)
{
    leaf* ret;

    ret = NULL;
    if (l != NULL)
    {
        if ((*tree) != NULL)
        {
            /* TODO: */
        }
    }

    return ret;
}

