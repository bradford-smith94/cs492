/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 consumer.c
 * 03/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: takes in a void* 'n' which must be a pointer to an integer
 * post: creates a consumer thread
 */
void* consumer(void *n)
{
    int number;
    int i;
    struct s_product* prod;

    number = *((int*)n);

#ifdef DEBUG
    printf("[DEBUG]\tStarting consumer [%d]\n", number);
    fflush(stdout);
#endif

    /* consume products while we have not reached maxProductCount */
    while (gl_env.consumptionCount < gl_env.maxProductCount)
    {
        /* lock and check consumptionCount again in case of weird scheduling */
        pthread_mutex_lock(&gl_env.consume_prod_lock);
        if (gl_env.consumptionCount == gl_env.maxProductCount)
        {
            pthread_mutex_unlock(&gl_env.consume_prod_lock);
            break;
        }

        if (gl_env.scheduling == FCFS)
        {
            /* do a real pop and keep it til' it's gone */
            prod = pop_q();

            for (i = 0; i < prod->life; i++)
                fibonacci(10);

            /* free memory */
            free(prod);

            /* lock and increment consumptionCount */
            pthread_mutex_lock(&gl_env.consume_prod_lock);
            gl_env.consumptionCount++;
            pthread_mutex_unlock(&gl_env.consume_prod_lock);
        }
        else if (gl_env.scheduling == RR)
        {
            /* do a "reserved" pop in case we need to put it back */
            prod = reserved_pop_q();

            if (prod->life >= gl_env.quantum)
            {
                for (i = 0; i < gl_env.quantum; i++)
                    fibonacci(10);

                /* put the product back */
                replace_push_q(prod);
            }
            else
            {
                for (i = 0; i < prod->life; i++)
                    fibonacci(10);

                /* "fully" remove product */
                decrement_q();

                /* free memory */
                free(prod);

                /* lock and increment consumptionCount */
                pthread_mutex_lock(&gl_env.consume_prod_lock);
                gl_env.consumptionCount++;
                pthread_mutex_unlock(&gl_env.consume_prod_lock);
            }
        }

        /* usleep for 100 milliseconds */
        usleep(100000);
    }

    /* return NULL removes compiler warning */
    return NULL;
}

