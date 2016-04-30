/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs_exit.c
 * 04/30/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: none
 * post: de-allocates data structures and exits the program
 */
void fs_exit()
{
    /* close open file descriptors */
    close(gl.fd_flist);
    close(gl.fd_dlist);

    /* TODO: don't forget about this, leaking so much memory :( */
}

