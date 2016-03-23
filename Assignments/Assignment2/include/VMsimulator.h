/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 VMsimulator.h
 * 03/23/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _VMSIMULATOR_H_
#define _VMSIMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "page.h"

/* maximum number of memory locations */
#define MAX_MEM 512

/* global counter of page swaps */
unsigned long gl_page_swaps;

int main(int, char**);

#endif /* _VMSIMULATOR_H_ */
