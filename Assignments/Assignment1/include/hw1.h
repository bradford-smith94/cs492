/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 hw1.h
 * 02/21/2016
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

#define PRODUCT_MAX_LIFE 1024

struct s_product
{
    int id;
    time_t timestamp;
    int life; /* capped at 1024 */
};

struct s_env
{
    unsigned int seed;
    int productCount;
    int maxProductCount;
} gl_env;

int                 main(int argc, char** argv);
struct s_product*   produceProduct();
void*               producer();
void*               consumer();

#endif /* _HW1_H_ */
