/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 file.c
 * 04/27/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in a char* 'name', int 'size' and char 'isDirectory' which should
 *      only have the values zero or one (respectively false or true)
 * post: creates an new fs_file with the name 'name' of size 'size' and
 *      'isDirectory' to signify if this file is a regular file or a directory
 * return: a fs_file* pointing to the newly allocated file, or NULL on error
 */
fs_file* createFile(char* name, int size, char isDirectory)
{
    fs_file* ret;

    if ((ret = (fs_file*)malloc(sizeof(fs_file))) != NULL)
    {
        ret->name = name;
        ret->size = size;
        ret->timestamp = time(NULL);
        ret->isDirectory = isDirectory;
        ret->lfile = NULL; /* empty linked_list */
    }

    return ret;
}

