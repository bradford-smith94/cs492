/* Bradford Smith (bsmith8)
 * CS 492 Assignment 2 VMsimulator.h
 * 03/31/2016
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

/* maximum page size */
#define MAX_PAGE_SIZE 32

/* options for defining page replacement method */
#define OPT_FIFO "FIFO"
#define OPT_LRU "LRU"
#define OPT_CLOCK "Clock"

/* global counter of page swaps */
unsigned long gl_page_swaps;

int main(int, char**);
int isPowTwo(int);

#endif /* _VMSIMULATOR_H_ */
