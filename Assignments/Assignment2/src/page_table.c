/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page_table.c
 * 03/30/2016
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
    page* p;
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
            ret->numLoaded = 0;

            for (i = 0; i < numPages; i++)
            {
                p = createPage();
                if (p == NULL)
                {
                    printf("[ERROR]\tCould not malloc a new page!\n");
                    fflush(stdout);
                    break;
                }
                ret->pages[i] = p;
            }
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

/* pre: none
 * post: creates a new page with a unique number
 * return: a pointer to the newly created page or NULL on error
 */
page* createPage()
{
    page* ret;

    ret = (page*)malloc(sizeof(page));
    if (ret != NULL)
    {
        if (!gl_pages_total)
            gl_pages_total = 0;
        ret->number = ++gl_pages_total;
        ret->valid = 0;
        ret->accessed = 0;
    }
    return ret;
}

