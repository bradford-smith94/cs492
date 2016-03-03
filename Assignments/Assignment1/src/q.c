/* Bradford Smith (bsmith9)
 * CS 492 Assignment 1 q.c
 * 03/03/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "q.h"

/* this struct is how the queue works */
struct q_entry_t {
    struct product *p;
    struct q_entry_t *next;
};

static pthread_mutex_t q_lock = PTHREAD_MUTEX_INITIALIZER;

static int maxSize = 0;
static int count = 0;
static struct q_entry_t *q;

/* pre: takes in a positive integer 'size'
 * post: intializes a queue of size 'size'
 */
void init_q(int size)
{
    maxSize = size;
    count = 0;
    q = NULL;
}
