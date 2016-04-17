/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 fs.h
 * 04/17/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _FS_H_
#define _FS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* functions ================================================================ */
int     main(int, char**);
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
