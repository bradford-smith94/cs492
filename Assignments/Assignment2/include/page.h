/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page.h
 * 03/22/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _PAGE_H_
#define _PAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* create data structures */
struct s_page
{
    int number;
    int valid;
    int accessed;
};

typedef struct s_page page;

struct s_ptable
{
    page* pages;
};

typedef struct s_ptable ptable;

unsigned int gl_total;

/* declare functions */
ptable* createPageTable(int, int);
void deletePageTable(ptable*);

void addPage(ptable*);

#endif /* _PAGE_H_ */
