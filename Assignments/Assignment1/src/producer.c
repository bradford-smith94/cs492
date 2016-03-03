/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 producer.c
 * 03/03/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: takes in a void* 'n' which must be a pointer to an integer
 * post: create a producer thread
 */
void* producer(void *n)
{
    int number;

    number = *((int*)n);

#ifdef DEBUG
    printf("[DEBUG]\tStarting producer [%d]\n", number);
    fflush(stdout);
#endif

    /* return NULL removes compiler warning */
    return NULL;
}

