/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page.h
 * 03/31/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _PAGE_H_
#define _PAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/* create data structures */
struct s_page
{
    int number;
    int valid;
    unsigned long accessed;
};

typedef struct s_page page;

struct s_ptable
{
    page** pages;
    int numPages;
    int numLoaded;
};

typedef struct s_ptable ptable;

/* global count of pages, so each page can be given a unique number */
unsigned int gl_pages_total;

/* declare functions */
ptable* createPageTable(int, int);
void deletePageTable(ptable*);
page* createPage();

#endif /* _PAGE_H_ */
