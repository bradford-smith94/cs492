/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 page_table.c
 * 04/01/2016
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
    int numPages = (int)ceil((double)pTotal / pSize);

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

            ret->fifoHead = NULL;
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

/* pre: takes in a ptable* 'tab' and an int 'num', 'tab' must be a valid ptable*
 *      and 'num' must be >= 0 and < 'tab'->numPages
 * post: allocates and adds an entry to 'tab's fifoHead representing the page at
 *      index 'num'
 */
void pushFifo(ptable* tab, int num)
{
    fifo* tmp;
    fifo* n;

    n = (fifo*)malloc(sizeof(fifo));
    n->pageNum = num;

    tmp = tab->fifoHead;

    if (tmp == NULL)
        tmp = n;
    else
    {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = n;
    }
    n->next = NULL;
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*
 * post: pops an entry off of 'tab's
 * return: an integer that is the pageNumber of the entry popped off 'tab' or -1
 *      if no entry existed
 */
int popFifo(ptable* tab)
{
    int ret;
    fifo* tmp;

    ret = -1;
    tmp = tab->fifoHead;
    if (tab->fifoHead != NULL)
        tab->fifoHead = tab->fifoHead->next;

    if (tmp != NULL)
    {
        ret = tmp->pageNum;
        free(tmp);
    }

    return ret;
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*, and an integer
 *      's' which is >= 0 and < 'tab'->numPages
 * post: returns the index of the next invalid (unloaded) page starting at 's'
 * return: an integer index of the next invalid (unloaded) page in 'tab' or -1
 *      if one does not exist
 */
int indexOfNextInvalidPage(ptable* tab, int s)
{
    int startPos;

    startPos = s;
    while (tab->pages[s]->valid)
    {
        s = (s + 1) % tab->numPages;

        /* if we get back to the startPos without finding an invalid page */
        if (s == startPos)
        {
            s = -1;
            break;
        }
    }

    return s;
}

/* pre: takes in a ptable* 'tab' which must be a valid ptable*
 * post: returns the index of the least recently used valid (loaded) page
 * return: an integer that is the index of the least recently used valid
 *      (loaded) page in 'tab' or -1 if one does not exist
 */
int indexOfLRUValidPage(ptable* tab)
{
    int i;
    int ret;
    unsigned long min;

    ret = -1;
    for (i = 0; i < tab->numPages; i++)
    {
        if (!tab->pages[i]->valid)
            continue;

        if (!min || tab->pages[i]->accessed < min)
            min = tab->pages[i]->accessed;
    }

    return ret;
}

