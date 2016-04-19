/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 linkedList.h
 * 04/19/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct s_node {
    void* data;
    struct s_node* next;
};

typedef struct s_node node;

node*   createNode(void*);
void    appendNode(node**, node*);
node*   removeNode(node**, node*);

#endif /* _LINKEDLIST_H_ */
