/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 hw1.h
 * 03/03/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _HW1_H_
#define _HW1_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>
#include <time.h>

#include "product.h" /* provides definition of product */
#include "q.h" /* provides a "queue" */

/* a struct wrapping global variables together */
struct s_env
{
    int productCount;
    int consumptionCount;
    int maxProductCount;
    pthread_mutex_t create_prod_lock;
    pthread_mutex_t consume_prod_lock;
} gl_env; /* accessed through gl_env */


/* defined methods */
int                 main(int argc, char** argv);
struct s_product*   produceProduct();
void*               producer(void*);
void*               consumer(void*);

#endif /* _HW1_H_ */
