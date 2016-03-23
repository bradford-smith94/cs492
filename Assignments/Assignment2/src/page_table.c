/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page_table.c
 * 03/23/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "page.h"

/* pre: takes in ints pSize and pTotal
 * post: creates a new page table with page size 'pSize' and number of memory
 *      locations 'pTotal'
 * return: a pointer to the newly created page table or NULL on error
 */
ptable* createPageTable(int pSize, int pTotal)
{
    ptable* ret;
    int i;
    int numPages = pTotal / pSize;

#ifdef DEBUG
    printf("[DEBUG]\tCreating page table: page size [%d] num mem locs [%d]\n",
            pSize, pTotal);
    fflush(stdout);
#endif

    ret = (ptable*)malloc(sizeof(ptable));
    if (ret != NULL)
    {
        ret->pages = (page**)malloc(sizeof(page*)*numPages);
        if (ret->pages != NULL)
        {
            ret->numPages = numPages;

            for (i = 0; i < numPages; i++)
                ret->pages[i] = NULL;
        }
    }

    return ret;
}

/* pre: takes in a ptable* p
 * post: frees the memory associated with the page table p
 */
void deletePageTable(ptable* p)
{
    int i;

    if (p != NULL)
    {
        for (i = 0; i < p->numPages; i++)
        {
            if (p->pages[i] != NULL)
                free(p->pages[i]);
        }
        free(p->pages);
        free(p);
    }
}

/* pre: takes in a ptable* p
 * post: adds a page to 'p' with a unique number and timestamp
 * return: the new page's number on success, else 0
 */
int addPage(ptable* p)
{
    int i;

    /* find the next NULL page */
    for (i = 0; i < p->numPages; i++)
        if (p->pages[i] == NULL)
            break;

    /* if there was a NULL page */
    if (i < p->numPages)
    {
        p->pages[i] = (page*)malloc(sizeof(page));
        if (p->pages[i] == NULL)
        {
            printf("[ERROR]\tUnable to malloc a new page!\n");
            return 0;
        }

        if (!gl_pages_total)
            gl_pages_total = 0;
        p->pages[i]->number = ++gl_pages_total;
        p->pages[i]->valid = 0;
        p->pages[i]->accessed = 0;
    }
    else
    {
        printf("[ERROR]\tUnable to add page; page table full!\n");
        return 0;
    }

    return p->pages[i]->number;
}

