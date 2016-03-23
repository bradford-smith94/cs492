/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 main.c
 * 03/23/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "VMsimulator.h"

/* pre: takes in int argc and char** argv command line agruments
 * post: runs the virtual memory simulation program
 * return: 0 on success, else 1
 */
int main(int argc, char** argv)
{
    /* parameters */
    char* plist;
    char* ptrace;
    int pageSize;
    char* pageReplacement;
    int prePaging;

    /* other variables */
    FILE* plistfd;
    FILE* ptracefd;
    char c;
    int numProcs;
    int i;
    ptable** proc_ptables;
    char* line;
    size_t len;
    ssize_t ret;

    /* verifiy number of arguments */
    if (argc != 6)
    {
        printf("usage: %s <plist> <ptrace> <page size> <FIFO|LRU|Clock> <+|- pre-paging on/off>\n",
                argv[0]);
        return 1;
    }
    else /* parse and error check arguments */
    {
        plist = argv[1];
        ptrace = argv[2];

        pageSize = atoi(argv[3]);
        if (pageSize <= 0)
        {
            printf("[ERROR]\tInvalid page size [%s]!\n", argv[3]);
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

    /* initialize page swap counter to zero for start */
    gl_page_swaps = 0;

    /* open files for reading */
    plistfd = fopen(plist, "r");
    if (plistfd == NULL)
    {
        printf("[ERROR]\tCould not open plist file!\n");
        return 1;
    }
    ptracefd = fopen(ptrace, "r");
    if (ptracefd == NULL)
    {
        printf("[ERROR]\tCould not open ptrace file!\n");
        return 1;
    }

    /* read from plist to count the number of lines (processes) */
    numProcs = 0;
    i = 0;
    while (!feof(plistfd))
    {
        c = fgetc(plistfd);
        i++;
        if (c == '\n')
        {
            if (i > 1)
            {
                i = 0;
                numProcs++;
            }
        }
    }

#ifdef DEBUG
    printf("[DEBUG]\t%d processes detected\n", numProcs);
    fflush(stdout);
#endif

    /* create a list of page tables (one for each process) */
    proc_ptables = (ptable**)malloc(sizeof(ptable*)*numProcs);

    /* move the fd back to the start of the file so we can read it again */
    rewind(plistfd);

    /* read from plist again to setup proc_ptables */
    i = 0;
    line = NULL;
    len = 0;
    while ((ret = getline(&line, &len, plistfd)) != -1)
    {
        /* skip over all empty lines */
        if (!strcmp(line, "\n"))
            continue;

#ifdef DEBUG
        printf("[DEBUG]\tRead plist line: %s", line);
        fflush(stdout);
#endif

        /* this returns the PID, next strtok will be the mem locs */
        strtok(line, " ");
        proc_ptables[i++] = createPageTable(pageSize, atoi(strtok(NULL, " ")));
    }

    /* read from ptrace and run the simulation */
    free(line);
    line = NULL;
    len = 0;
    while ((ret = getline(&line, &len, ptracefd)) != -1)
    {
        /* skip over all empty lines */
        if (!strcmp(line, "\n"))
            continue;

#ifdef DEBUG
        printf("[DEBUG]\tRead ptrace line: %s", line);
        fflush(stdout);
#endif

        /* this returns the PID, next strtok will be the mem loc to access */
        i = atoi(strtok(line, " "));
    }


    /* close files, ignoring any errors on close */
    fclose(plistfd);
    fclose(ptracefd);

    /* free memory */
    for (i = 0; i < numProcs; i++)
        deletePageTable(proc_ptables[i]);
    free(proc_ptables);

    /* print total number of page swaps on exit */
    printf("Total page swaps: %lu\n", gl_page_swaps);
    return 0;
}

