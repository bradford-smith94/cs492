/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs.h
 * 04/24/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _FS_H_
#define _FS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> /* for open */
#include <sys/stat.h> /* for open */
#include <fcntl.h> /* for open */

#include "linkedList.h"

/* global environment wrapper */
struct s_env {
    int fd_flist; /* file descriptor for file_list.txt */
    int fd_dlist; /* file descriptor for dir_list.txt */
    int dsize; /* disk size */
    int bsize; /* block size */
} gl;

/* functions ================================================================ */
int     main(int, char**);
void    usage(char*);
void    parse_args(int, char**);
char**  str2vect(char*);
void    free_vect(char**);

void    fs_cd(char*);
void    fs_ls();
void    fs_mkdir(char*);
void    fs_create(char*);
void    fs_append(char*, int);
void    fs_remove(char*, int);
void    fs_delete(char*);
void    fs_exit();
void    fs_dir();
void    fs_prfiles();
void    fs_prdisk();

#endif /* _FS_H_ */
