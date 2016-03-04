/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 product.c
 * 02/22/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: none
 * post: allocates and initializes a new product
 * return: a pointer to a newly allocated and initialized product or NULL if
 *      malloc fails
 */
struct s_product* produceProduct()
{
    struct s_product* p;

    p = (struct s_product*)malloc(1*sizeof(struct s_product));

    /* if malloc works initialize the product */
    if (p != NULL)
    {
        p->id = ++gl_env.productCount;
        p->timestamp = time(NULL);
        p->life = random() % PRODUCT_MAX_LIFE; /* see product.h for PRODUCT_MAX_LIFE */
#ifdef DEBUG
        printf("[DEBUG]\tCreated Product [%d] time: %li life: %d\n",
                p->id,
                p->timestamp,
                p->life);
        fflush(stdout);
#endif
    }

    return p;
}

