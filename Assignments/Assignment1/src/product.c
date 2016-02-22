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
        srandom(gl_env.seed);
        p->life = random() % PRODUCT_MAX_LIFE; /* see hw1.h for PRODUCT_MAX_LIFE */
    }

    return p;
}

