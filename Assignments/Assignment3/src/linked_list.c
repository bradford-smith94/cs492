/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 linked_list.c
 * 04/19/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "linked_list.h"

/* pre: takes in a void* 'data'
 * post: allocates a new linked list node holding 'data'
 * return: a node* pointing to the newly allocated linked list node, or NULL on
 *      error
 */
node* createNode(void* data)
{
    node* ret;

    ret = NULL;
    if (data != NULL)
    {
        if ((ret = (node*)malloc(sizeof(node))) != NULL)
        {
            ret->data = data;
            ret->next = NULL;
        }
    }

    return ret;
}

/* pre: takes in a node** 'list' and a node* 'n'
 * post: appends 'n' to the end of the linked list pointed to by 'list'
 */
void appendNode(node** list, node* n)
{
    if (n != NULL)
    {
        if ((*list) == NULL)
            (*list) = n;
        else
        {
            for (; (*list)->next != NULL; list = &((*list)->next))
                ; /* note the empy loop */
            (*list)->next = n;
        }
    }
}

/* pre: takes in a node** 'list'
 * post: removes the first node from 'list'
 * return: a node* pointing to the node removed from 'list'
 */
node* popNode(node** list)
{
    node* ret;

    ret = NULL;
    if ((*list) != NULL)
    {
        ret = (*list);
        (*list) = (*list)->next;
    }

    return ret;
}

/* pre: takes in a node** 'list' and a node* 'n'
 * post: removes 'n' from the linked list pointed to by 'list'
 * return: a node* pointing to the node that was removed from 'list'
 */
node* removeNode(node** list, node* n)
{
    node* ret;

    ret = NULL;
    if (n != NULL)
    {
        if ((*list) != NULL)
        {
            if ((*list) == n)
            {
                ret = (*list);
                list = &((*list)->next);
            }
            else
            {
                for (; (*list)->next != n; list = &((*list)->next))
                    ; /* note the empy loop */
                ret = (*list)->next;
                if ((*list)->next->next == NULL)
                    (*list)->next = NULL;
                else
                    (*list)->next = (*list)->next->next;
            }
        }
    }

    return ret;
}

