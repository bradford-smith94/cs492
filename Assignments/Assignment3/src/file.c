/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 file.c
 * 04/29/2016
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

/* pre: takes in an int 'index' and gl.ldisk has been created
 * post: splits gl.ldisk at 'index' such that 'index' starts a new node in
 *      gl.ldisk, and sets the block on the left of the split as used
 */
void splitLdiskNode(int index)
{
    node* n; /* temp node */
    fs_block* b; /* temp block */

    n = gl.ldisk;
    b = (fs_block*)(n->data);

    /* if first node needs to be split */
    if (index < b->e_addr && index >= b->s_addr)
    {
        b->s_addr = index;
        prependNode(&gl.ldisk, createNode((void*)createBlock(0, index, 0)));
    }
    else
    {
        /* while node is not NULL and index is not in this block */
        while (n != NULL && !(index < b->e_addr && index >= b->s_addr))
            n = n->next;

        if (n != NULL)
        {
            insertNode(n, createNode((void*)createBlock(index, b->e_addr, 1)));
            b->e_addr = index;
            b->isFree = 0;
        }
        /* else fail silently, future me might hate me for this */
    }
}

/* pre: gl.ldisk has been created
 * post: merges all contiguous nodes in gl.ldisk that are in the same state
 *      (free/used)
 */
void mergeLdiskNodes()
{
    node* n; /* temp node */
    fs_block* b; /* temp block */
    fs_block* nb; /* temp next block */

    n = gl.ldisk;
    b = (fs_block*)(n->data);

    while (n != NULL && n->next != NULL)
    {
        nb = (fs_block*)(n->next->data);

        /* if this block and the next block have the same state, merge them */
        if (b->isFree == nb->isFree)
        {
            b->e_addr = nb->e_addr;
            free(removeNode(n, n->next));
        }

        n = n->next;
    }
}

/* pre: takes in a fs_file* 'file' that has been initialized, and gl.ldisk has
 *      been created
 * post: allocates blocks for 'file'
 */
void allocateFile(fs_file* file)
{
    int numBlocksNeeded; /* the number of blocks needed by the file */
    fs_block* b;
    node* n;

    numBlocksNeeded = file->size / gl.bsize;
    n = gl.ldisk;

    /* only allocate if the number of needed blocks has changed */
    while (numBlocksNeeded > file->allocatedBlocks)
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
            b = (fs_block*)(n->data);
            if (b->e_addr - b->s_addr > numBlocksNeeded)
            {
                file->allocatedBlocks += numBlocksNeeded;
                /* TODO: update gl.ldisk */
            }
            else
            {
                file->allocatedBlocks += b->e_addr - b->s_addr;
                /* TODO: update gl.ldisk */
            }
        }
    }

    /* merge nodes in gl.ldisk */
    mergeLdiskNodes();
}

