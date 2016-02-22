/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 q.h
 * 02/22/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _Q_H_
#define _Q_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "product.h"

void init_q();
void push_q(void*);
void* pop_q();

#endif /* _Q_H_ */
