/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 init.c
 * 04/27/2016
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

    line = NULL;
    while ((n = getline(&line, 0, dir_stream)) != 0)
    {
        /* error check */
        if (n < 0)
        {
            perror(gl.executable);

            exit(-1);
        }

        vect = str2vect(line);

        /* TODO: create directories and add them to the tree */

        free_vect(vect);
        free(line);
    }

    line = NULL;
    while ((n = getline(&line, 0, file_stream)) != 0)
    {
        /* error check */
        if (n < 0)
        {
            perror(gl.executable);

            exit(-1);
        }

        /* TODO: create files and add them to the tree and disk */

        free(line);
    }
}

