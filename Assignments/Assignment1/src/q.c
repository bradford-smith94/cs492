/* Bradford Smith (bsmith9)
 * CS 492 Assignment 1 q.c
 * 03/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "q.h"

/* this struct is how the queue works */
struct q_entry_t {
    struct s_product *p;
    struct q_entry_t *next;
};

static pthread_mutex_t q_lock; /* lock for accessing the queue */
static pthread_cond_t q_full; /* condition for when the queue is full */
static pthread_cond_t q_empty; /* condition for when the queue is empty */
static int maxSize; /* the max size of the queue */
static int count; /* number of items in the queue (accounting for reserved spaces) */
static int realCount; /* number of items in the queue (not accounting for reserved spaces) */
static struct q_entry_t *q; /* a queue 'node' */

/* pre: takes in a positive integer 'size'
 * post: intializes a queue of size 'size'
 */
void init_q(int size)
{
    pthread_mutex_init(&q_lock, NULL);
    pthread_cond_init(&q_full, NULL);
    pthread_cond_init(&q_empty, NULL);
    maxSize = size;
    count = 0;
    realCount = 0;
    q = NULL;
}

/* pre: the q has been initialized, takes in a struct s_product* 'prod'
 * post: pushes 'prod' onto the queue
 */
void push_q(struct s_product* prod)
{
    struct q_entry_t *newEntry;
    struct q_entry_t *tmp;

    newEntry = malloc(sizeof(struct q_entry_t));
    if (prod == NULL || newEntry == NULL)
        return;

    newEntry->p = prod;
    newEntry->next = NULL;

    pthread_mutex_lock(&q_lock);
    while (count == maxSize)
        pthread_cond_wait(&q_full, &q_lock);

    if (q == NULL)
        q = newEntry;
    else
    {
        tmp = q;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = newEntry;
    }
    if (count++ == 0)
        pthread_cond_broadcast(&q_empty);
    ++realCount;
    pthread_mutex_unlock(&q_lock);
}

/* pre: the queue has been initialized
 * post: pops the queue
 * return: a struct s_product* which is the product that was just removed from
 *      the queue or NULL if the queue was empty
 */
struct s_product* pop_q()
{
    struct s_product *ret = NULL;
    struct q_entry_t *tmp;

    pthread_mutex_lock(&q_lock);
    while (realCount == 0)
        pthread_cond_wait(&q_empty, &q_lock);

    if (q != NULL)
    {
        tmp = q;
        ret = tmp->p;
        q = tmp->next;

        free(tmp);

        if (count-- == maxSize)
            pthread_cond_broadcast(&q_full);
        --realCount;
    }
    pthread_mutex_unlock(&q_lock);

    return ret;
}

/* pre: the queue has been initialized
 * post: pops the queue without decrementing it's size
 * return: a struct s_product* which is the product that was just removed from
 *      the queue, or NULL if the queue was empty
 */
struct s_product* reserved_pop_q()
{
    struct s_product *ret = NULL;
    struct q_entry_t *tmp;

    pthread_mutex_lock(&q_lock);
    while (realCount == 0)
        pthread_cond_wait(&q_empty, &q_lock);

    if (q != NULL)
    {
        tmp = q;
        ret = tmp->p;
        q = tmp->next;

        free(tmp);

        --realCount;
    }
    pthread_mutex_unlock(&q_lock);

    return ret;
}

/* pre: the q has been initialized, takes in a struct s_product* 'prod'
 * post: pushes 'prod' onto the queue wihtout incrementing it's size, meant for
 *      use after a 'reserved_pop_q'
 */
void replace_push_q(struct s_product* prod)
{
    struct q_entry_t *newEntry;
    struct q_entry_t *tmp;

    newEntry = malloc(sizeof(struct q_entry_t));
    if (prod == NULL || newEntry == NULL)
        return;

    newEntry->p = prod;
    newEntry->next = NULL;

    pthread_mutex_lock(&q_lock);
    if (q == NULL)
        q = newEntry;
    else
    {
        tmp = q;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = newEntry;
    }
    if (realCount++ == 0)
        pthread_cond_broadcast(&q_empty);
    pthread_mutex_unlock(&q_lock);
}

/* pre: the queue has been initialized and a 'reserved_pop_q' has been done
 *      without being followed by a 'replace_push_q'
 * post: decrements the queue's size and broadcasts to threads that may be
 *      waiting on a full queue
 */
void decrement_q()
{
    pthread_mutex_lock(&q_lock);
    if (count-- == maxSize)
        pthread_cond_broadcast(&q_full);
    pthread_mutex_unlock(&q_lock);
}

