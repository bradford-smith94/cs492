/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 q.h
 * 03/03/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _Q_H_
#define _Q_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "product.h"

/* queue functions */
void                init_q(int);
void                push_q(struct s_product*);
struct s_product*   pop_q();
struct s_product*   reserved_pop_q();
void                replace_push_q(struct s_product*);
void                decrement_q();

#endif /* _Q_H_ */
