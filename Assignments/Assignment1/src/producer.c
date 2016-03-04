/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 producer.c
 * 03/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: takes in a void* 'n' which must be a pointer to an integer
 * post: create a producer thread
 */
void* producer(void *n)
{
    int number;
    struct s_product* prod;

    number = *((int*)n);

#ifdef DEBUG
    printf("[DEBUG]\tStarting producer [%d]\n", number);
    fflush(stdout);
#endif

    /* create products while we have not reached maxProductCount */
    while (gl_env.productCount < gl_env.maxProductCount)
    {
        /* lock on creating a product in order to be sure we have the correct
         * productCount
         */
        pthread_mutex_lock(&gl_env.create_prod_lock);

        /* check count again in case of weird scheduling */
        if (gl_env.productCount == gl_env.maxProductCount)
        {
            pthread_mutex_unlock(&gl_env.create_prod_lock);
            break;
        }
#ifdef DEBUG
        printf("[DEBUG]\tProducer [%d] producing product\n", number);
        fflush(stdout);
#endif
        prod = produceProduct();

        pthread_mutex_unlock(&gl_env.create_prod_lock);

        /* the queue handles critical sections itself */
        push_q(prod);

        printf("Producer %d has produced product %d\n", number, prod->id);
        fflush(stdout);

        /* usleep for 100 milliseconds */
        usleep(100000);
    }

    /* return NULL removes compiler warning */
    return NULL;
}

