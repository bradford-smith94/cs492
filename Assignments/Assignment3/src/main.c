/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 main.c
 * 04/20/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in int 'argc' and char** 'argv' command line arguments which
 *      include:
 *      -f <file_list>
 *      -d <dir_list>
 *      -s <disk size>
 *      -b <block size>
 * post: runs the filesystem simulation program
 * return: 0 on sucessful exit, something else on error
 */
int main(int argc, char** argv)
{
    int n;
    char* line;
    char** v;

    /* parse args and setup global environment */
    parse_args(argc, argv);

    /* main command reading loop */
    line = (char*)malloc(256 * sizeof(char));
    while (1)
    {
        /* prompt */
        printf("> ");
        fflush(stdout);

        /* fd 0 is stdin */
        if ((n = read(0, line, 256)) == -1)
        {
            perror(argv[0]);

            fs_exit();
            exit(-1);
        }
        else if (n == 0)
        {
            fs_exit();
            break;
        }
        else
        {
            /* overwrite newline with NULL-byte */
            line[n - 1] = '\0';

#ifdef DEBUG
            printf("Read line: <%s>\n", line);
            fflush(stdout);
#endif

            /* TODO: use strtok to parse out the command? or turn 'line' into a
             * vector
             */
        }

        /* TODO: remove this break after checking for commands */
        break;
    }

    fs_exit();
    return 0;
}

