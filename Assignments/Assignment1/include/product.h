/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 product.h
 * 03/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#define PRODUCT_MAX_LIFE 1024

/* a struct representing a product */
struct s_product
{
    int id;
    time_t timestamp;
    time_t time_inserted;
    int life; /* capped at PRODUCT_MAX_LIFE */
};

#endif /* _PRODUCT_H_ */
