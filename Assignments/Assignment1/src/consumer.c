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
    struct timeval end_time;

    number = *((int*)n);

#ifdef DEBUG
    printf("[DEBUG]\tStarting consumer [%d]\n", number);
    fflush(stdout);
#endif

    /* consume products while we have not reached maxProductCount */
    while (gl_env.consumptionCount < gl_env.maxProductCount)
    {
#ifdef DEBUG
        printf("[DEBUG]\tconsumption count %d\n", gl_env.consumptionCount);
        fflush(stdout);
#endif
        /* lock and check consumptionCount again in case of weird scheduling */
        pthread_mutex_lock(&gl_env.consume_prod_lock);
        if (gl_env.consumptionCount == gl_env.maxProductCount)
        {
            pthread_mutex_unlock(&gl_env.consume_prod_lock);
            break;
        }
        pthread_mutex_unlock(&gl_env.consume_prod_lock);

        if (gl_env.scheduling == FCFS)
        {
            /* do a real pop and keep it til' it's gone */
            prod = pop_q();
            if (prod == NULL)
                break;
            gettimeofday(&end_time, NULL);
            fprintf(stderr, "Product %d waited %lu\n", prod->id, end_time.tv_usec - prod->time_inserted.tv_usec);
            fflush(stderr);

#ifdef DEBUG
            printf("[DEBUG]\tConsumer [%d] working on product [%d]\n", number, prod->id);
            fflush(stdout);
#endif

            for (i = 0; i < prod->life; i++)
                fibonacci(10);

            /* lock and increment consumptionCount */
            pthread_mutex_lock(&gl_env.consume_prod_lock);
            gl_env.consumptionCount++;
            pthread_mutex_unlock(&gl_env.consume_prod_lock);

            printf("Consumer %d has consumed product %d\n", number, prod->id);
            fflush(stdout);
            gettimeofday(&end_time, NULL);
            fprintf(stderr, "Product %d turn-around %lu\n", prod->id, end_time.tv_usec - prod->time_created.tv_usec);
            fflush(stderr);

            /* free memory */
            free(prod);
        }
        else if (gl_env.scheduling == RR)
        {
            /* do a "reserved" pop in case we need to put it back */
            prod = reserved_pop_q();
            if (prod == NULL)
                break;
            gettimeofday(&end_time, NULL);
            fprintf(stderr, "Product %d waited %lu\n", prod->id, end_time.tv_usec - prod->time_inserted.tv_usec);
            fflush(stderr);

#ifdef DEBUG
            printf("[DEBUG]\tConsumer [%d] working on product [%d]\n", number, prod->id);
            fflush(stdout);
#endif

            if (prod->life > gl_env.quantum)
            {
                for (i = 0; i < gl_env.quantum; i++)
                    fibonacci(10);

                /* update the product's life */
                prod->life = prod->life - gl_env.quantum;

                /* put the product back */
                replace_push_q(prod);
            }
            else
            {
                for (i = 0; i < prod->life; i++)
                    fibonacci(10);

                /* "fully" remove product */
                decrement_q();

                /* lock and increment consumptionCount */
                pthread_mutex_lock(&gl_env.consume_prod_lock);
                ++gl_env.consumptionCount;
                pthread_mutex_unlock(&gl_env.consume_prod_lock);

                printf("Consumer %d has consumed product %d\n", number, prod->id);
                fflush(stdout);
                gettimeofday(&end_time, NULL);
                fprintf(stderr, "Product %d turn-around %lu\n", prod->id, end_time.tv_usec - prod->time_created.tv_usec);
                fflush(stderr);

                /* free memory */
                free(prod);
            }
        }

        /* usleep for 100 milliseconds */
        usleep(100000);
    }

#ifdef DEBUG
    printf("[DEBUG]\tConsumer [%d] exiting\n", number);
    fflush(stdout);
#endif

    /* return NULL removes compiler warning */
    return NULL;
}

