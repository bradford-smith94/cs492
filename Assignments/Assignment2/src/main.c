/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 main.c
 * 03/22/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "VMsimulator.h"

/* pre: takes in int argc and char** argv command line agruments
 * post: runs the virtual memory simulation program
 * return: 0 on success, else 1
 */
int main(int argc, char** argv)
{
    char* plist;
    char* ptrace;
    int pageSize;
    char* pageReplacement;
    int prePaging;

    if (argc != 6)
    {
        printf("usage: %s <plist> <ptrace> <page size> <FIFO|LRU|Clock> <+|- pre-paging on/off>\n",
                argv[0]);
        return 1;
    }
    else
    {
        plist = argv[1];
        ptrace = argv[2];

        pageSize = atoi(argv[3]);
        if (pageSize <= 0)
        {
            printf("[ERROR]\tInvalid page size!\n");
            return 1;
        }

        pageReplacement = argv[4];
        if (!strcmp(pageReplacement, "FIFO") &&
            !strcmp(pageReplacement, "LRU") &&
            !strcmp(pageReplacement, "Clock"))
        {
            printf("[ERROR]\tInvalid page replacement method!\n");
            return 1;
        }

        if (!strcmp(argv[5], "+"))
            prePaging = 1;
        else if (!strcmp(argv[5], "-"))
            prePaging = 0;
        else
        {
            printf("[ERROR]\tInvalid value for pre-paging!\n");
            return 1;
        }

#ifdef DEBUG
        printf("[DEBUG]\tplist: %s\n[DEBUG]\tptrace: %s\n[DEBUG]\tpageSize: %d\n\
[DEBUG]\tpageReplacement: %s\n[DEBUG]\tprePaging: %d\n",
            plist, ptrace, pageSize, pageReplacement, prePaging);
        fflush(stdout);
#endif
    }

    return 0;
}

