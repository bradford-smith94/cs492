/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 init.c
 * 04/28/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: the flist file has been opened and it's file descriptor is in
 *      gl.fd_flist and the dir_list file has been opened and it's file
 *      descriptor is in gl.fd_dlist
 * post: parses the flist and dlist files to initialize the global file
 *      hierarchy
 */
void init()
{
    ssize_t n;
    size_t s;
    char* line;
    char** vect;
    FILE* dir_stream;
    FILE* file_stream;

    /* make sure the tree starts as NULL */
    gl.tree = NULL;

    /* open streams on the file descriptors */
    if ((dir_stream = fdopen(gl.fd_dlist, "r")) == NULL)
    {
        perror(gl.executable);

        exit(-1);
    }

    /* open streams on the file descriptors */
    if ((file_stream = fdopen(gl.fd_flist, "r")) == NULL)
    {
        perror(gl.executable);

        exit(-1);
    }

#ifdef DEBUG
    printf("[DEBUG]\tInitialize directories...\n");
    fflush(stdout);
#endif

    line = NULL;
    s = 0;
    while ((n = getline(&line, &s, dir_stream)) != 0)
    {
        /* error check */
        if (n < 0 && !feof(dir_stream))
        {
            perror(gl.executable);

            exit(-1);
        }
        else if (feof(dir_stream))
            break;

        /* overwrite the newline character */
        line[n - 1] = '\0';

#ifdef DEBUG
        printf("[DEBUG]\tfound directory: <%s>\n", line);
        fflush(stdout);
#endif

        /* TODO: create directories and add them to the tree */

        free(line);
        s = 0;
    }

#ifdef DEBUG
    printf("[DEBUG]\tInitialize files...\n");
    fflush(stdout);
#endif

    line = NULL;
    s = 0;
    while ((n = getline(&line, &s, file_stream)) != 0)
    {
        /* error check */
        if (n < 0 && !feof(file_stream))
        {
            perror(gl.executable);

            exit(-1);
        }
        else if (feof(file_stream))
            break;

        /* overwrite the newline character */
        line[n - 1] = '\0';

        /* break line up into a vector for easier parsing */
        vect = str2vect(line);

#ifdef DEBUG
        printf("[DEBUG]\tfound file entry:\n\t");
        for (int i = 0; vect[i] != NULL; i++)
            printf("<%s>,", vect[i]);
        printf("\n");
        fflush(stdout);
#endif

        /* TODO: create files and add them to the tree and disk */

        free_vect(vect);
        free(line);
        s = 0;
    }
}

