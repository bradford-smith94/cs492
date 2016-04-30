/* Bradford Smith (bsmith8)
 * CS 492 Assignment 3 file.c
 * 04/30/2016
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
    int i; /* loop counter */
    fs_block* b; /* temp block */
    node* n; /* temp node */

    numBlocksNeeded = file->size / gl.bsize;
    n = gl.ldisk;

#ifdef DEBUG
    printf("[DEBUG]\tAllocating file <%s>\n", file->name);
    fflush(stdout);
#endif

    /* only allocate if the number of needed blocks has changed */
    while (numBlocksNeeded > file->allocatedBlocks)
    {
        /* iterate forward over gl.ldisk to find the next free node */
        for (; n != NULL && !(((fs_block*)(n->data))->isFree); n = n->next)
            ; /* note empty loop */

        /* if we reached the end without allocating the whole file */
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

            /* if only part of the node is needed */
            if (b->e_addr - b->s_addr > numBlocksNeeded)
            {
                file->allocatedBlocks += numBlocksNeeded;

                /* update file->lfile */
                for (i = b->s_addr; i < b->e_addr; i++)
                    appendNode(&(file->lfile), createNode((void*)createBlock(i, i + 1, 0)));

                /* update gl.ldisk */
                splitLdiskNode(b->s_addr + numBlocksNeeded);
            }
            else /* else the whole node is needed */
            {
                file->allocatedBlocks += b->e_addr - b->s_addr;

                /* update file->lfile */
                for (i = b->s_addr; i < b->s_addr + numBlocksNeeded; i++)
                    appendNode(&(file->lfile), createNode((void*)createBlock(i, i + 1, 0)));

                /* update gl.ldisk */
                b->isFree = 0;
            }
        }
    }

    /* merge nodes in gl.ldisk */
    mergeLdiskNodes();
#ifdef DEBUG
    printf("[DEBUG]\tAllocated File\n");
    fflush(stdout);
#endif
}

/* pre: takes in a char* 'name', the data stored in the nodes of gl.tree must be
 *      of the type fs_file*
 * post: finds the the tree node in gl.tree that holds a fs_file* with the name
 *      'name'
 * return: a leaf* that points to the node in gl.tree that holds an fs_file*
 *      with the name 'name', or NULL if such a node is not found
 */
leaf* findInHierarchy(char* name)
{
    leaf* ret;
    leaf* t; /* temp tree */
    node* n;
    node* neighbors; /* linked_list to hold the order for BFS */

    ret = NULL;
    t = gl.tree;

#ifdef DEBUG
    printf("[DEBUG]\tFind <%s> in gloabl tree\n", name);
    fflush(stdout);
#endif

    /* while node is not null and it's name doesn't match */
    while (t != NULL && strcmp(name, ((fs_file*)(t->data))->name))
    {
        if ((n = t->children) != NULL)
        {
            do /* add all children to the neighbors queue */
            {
                appendNode(&neighbors, n);
            } while ((n = n->next) != NULL);
        }

        if ((n = popNode(&neighbors)) != NULL)
        {
            t = (leaf*)(n->data);
        }
        else
            t = NULL;
    }

    return ret;
}

/* pre: takes in a fs_file* 'file' which must be either a valid file or
 *      directory
 * post: adds 'file' to the appropriate position in gl.tree, if the name of
 *      'file' contains 'PATH_SEP' then these are followed to add 'file' as a
 *      child of the appropriate tree node, else 'file' is added as a child of
 *      gl.cur_dir
 */
void addToHierarchy(fs_file* file)
{
    char* name;
    char* part;
    char delim[2];
    leaf* pd; /* temp tree node (parent dir) */
    int p; /* num path separations */

    delim[0] = PATH_SEP;
    delim[1] = '\0';
    name = strdup(file->name);

#ifdef DEBUG
    printf("[DEBUG]\tAdding <%s> to the global tree\n", file->name);
    fflush(stdout);
#endif

    if ((p = countPathSeparations(name)))
    {
        part = strtok(name, delim);
        if (part == NULL)
            part = delim;
        pd = findInHierarchy(part);
        while (p--)
        {
            part = strtok(NULL, delim);
            if (p > 0)
                pd = findInHierarchy(part);
        }

#ifdef DEBUG
        printf("[DEBUG]\t<%s> name shortened to <%s>\n", file->name, part);
        fflush(stdout);
#endif

        /* we're making the file name shorter so strcpy should be fine */
        file->name = strcpy(file->name, part);
        /* TODO: possible memory leak? */
    }
    else
        pd = gl.cur_dir;

    free(name);

    /* append to the tree */
    appendLeaf(&pd, createLeaf((void*)file));
}

/* pre: takes in a char* 'fname' which is a file name
 * post: counts the number of occurances of the path separator 'PATH_SEP' in
 *      'fname'
 * return: an integer which is the number of occurances of 'PATH_SEP' in 'fname'
 */
int countPathSeparations(char* fname)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < strlen(fname); i++)
        if (fname[i] == PATH_SEP)
            count++;

    return count;
}

