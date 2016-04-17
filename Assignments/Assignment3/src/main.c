/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 main.c
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
 * post: runs the filesystem simulation program
 * return: 0 on sucessful exit, something else on error
 */
int main(int argc, char** argv)
{
    /* parse args and setup global environment */
    parse_args(argc, argv);

    fs_exit();
    return 0;
}

