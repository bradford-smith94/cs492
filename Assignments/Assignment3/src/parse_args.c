/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 parse_args.c
 * 04/17/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in int 'argc' and char** 'argv' command line arguments which
 *      include:
 *      -f <file_list>
 *      -d <dir_list>
 *      -s <disk size>
 *      -b <block size>
 * post: parses args and sets up the global environment
 */
void parse_args(int argc, char** argv)
{
    int i;

    if (argc != 9)
    {
        usage(argv[0]);
        exit(-1);
    }

    /* search for '-f' */
    for (i = 0; i < 9; i++)
        if (!strcmp(argv[i], "-f"))
            break;
    if (i < 8)
    {
        if ((gl.fd_flist = open(argv[i + 1], O_RDONLY)) < 0)
        {
            perror(argv[0]);

            exit(-1);
        }
    }
    else
    {
        usage(argv[0]);
        exit(-1);
    }

    /* search for '-d' */
    for (i = 0; i < 9; i++)
        if (!strcmp(argv[i], "-d"))
            break;
    if (i < 8)
    {
        if ((gl.fd_dlist = open(argv[i + 1], O_RDONLY)) < 0)
        {
            perror(argv[0]);

            exit(-1);
        }
    }
    else
    {
        usage(argv[0]);
        exit(-1);
    }

    /* search for '-s' */
    for (i = 0; i < 9; i++)
        if (!strcmp(argv[i], "-s"))
            break;
    if (i < 8)
        gl.dsize = atoi(argv[i + 1]);
    else
    {
        usage(argv[0]);
        exit(-1);
    }

    /* search for '-b' */
    for (i = 0; i < 9; i++)
        if (!strcmp(argv[i], "-b"))
            break;
    if (i < 8)
        gl.bsize = atoi(argv[i + 1]);
    else
    {
        usage(argv[0]);
        exit(-1);
    }
}

