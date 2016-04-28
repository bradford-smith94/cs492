/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 file.c
 * 04/28/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "fs.h"

/* pre: takes in an int 's', int 'e' and char 'isFree' which should only have
 *      the values zero or one (respectively false or true)
 * post: creates a new fs_block with the start address of 's', end address of
 *      'e' and 'isFree' to signify if this block is free or used
 * return: a fs_block* pointing to the newly allocated block, or NULL on error
 */
fs_block* createBlock(int s, int e, char isFree)
{
    fs_block* ret;

    if ((ret = (fs_block*)malloc(sizeof(fs_block))) != NULL)
    {
        ret->s_addr = s;
        ret->e_addr = e;
        ret->isFree = isFree;
    }

    return ret;
}

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
        ret->allocatedBlocks = 0; /* file hasn't been allocated yet */
        ret->timestamp = time(NULL);
        ret->isDirectory = isDirectory;
        ret->lfile = NULL; /* empty linked_list */
    }

    return ret;
}

/* pre: takes in a fs_file* 'file' that has been initialized, and gl.ldisk has
 *      been created
 * post: allocates blocks for 'file'
 */
void allocateFile(fs_file* file)
{
    int numBlocksNeeded;
    node* n;

    numBlocksNeeded = file->size / gl.bsize;
    n = gl.ldisk;

    /* only allocate if the number of needed blocks has changed */
    for (; numBlocksNeeded > file->allocatedBlocks; file->allocatedBlocks++)
    {
        /* iterate forward over gl.ldisk to find the next free node */
        for (; n != NULL && !(((fs_block*)(n->data))->isFree); n = n->next)
            ;
        if (n == NULL)
        {
            fprintf(stderr, "%s: Out of space\n", gl.executable);
            fflush(stderr);

            /* TODO: not sure if this error is fatal, break if not fatal */
            exit(-1);
        }
        else
        {
            /* TODO: update gl.ldisk */
        }
    }
}

