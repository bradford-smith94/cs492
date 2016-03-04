/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 consumer.c
 * 03/03/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: takes in a void* 'n' which must be a pointer to an integer
 * post: creates a consumer thread
 */
void* consumer(void *n)
{
    int number;

    number = *((int*)n);

#ifdef DEBUG
    printf("[DEBUG]\tStarting consumer [%d]\n", number);
    fflush(stdout);
#endif

    /* consume products while we have not reached maxProductCount */
    while (gl_env.consumptionCount < gl_env.maxProductCount)
    {
        pthread_mutex_lock(&gl_env.consume_prod_lock);
        if (gl_env.consumptionCount == gl_env.maxProductCount)
        {
            pthread_mutex_unlock(&gl_env.consume_prod_lock);
            break;
        }
    }

    /* return NULL removes compiler warning */
    return NULL;
}

