/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page_table.c
 * 03/22/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "page.h"

/* pre: takes in ints pSize and pTotal
 * post: creates a new page table with page size 'pSize' and number of memory
 *      locations 'pTotal'
 * return: a pointer to the newly created page table
 */
ptable* createPageTable(int pSize, int pTotal)
{
    ptable* ret;
    int numPages = pTotal / pSize;

    ret = (ptable*)malloc(sizeof(ptable));
    ret->pages = (page*)malloc(sizeof(page)*numPages);

    return ret;
}

/* pre: takes in a ptable* p
 * post: frees the memory associated with the page table p
 */
void deletePageTable(ptable* p)
{
    free(p->pages);
    free(p);
}

