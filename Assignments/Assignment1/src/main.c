/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 main.c
 * 02/21/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: takes in int argc and char** argv command line arguments
 *  arguments should be as follows:
 *      p1: the number of producer threads
 *      p2: the number of consumer threads
 *      p3: total number of products to produce
 *      p4: size of the queue used to store products (0 for unlimited)
 *      p5: 0 or 1 for scheduling algorithm to use (0 - FCFS, 1 - Round-Robin)
 *      p6: value of quantum used for Round-Robin
 *      p7: seed for RNG
 * post: runs the producer consumer thread scheduling simulation
 * return: 0 on success, something else on error
 */
int main(int argc, char** argv)
{
    /* validate arguments */
    if (argc != 7)
    {
        printf("usage: %s <p1> <p2> <p3> <p3> <p4> <p5> <p6> <p7>\n", argv[0]);
        printf("\twhere:\n\tp1: the number of producer threads\n\
\tp2: the number of consumer threads\n\
\tp3: the total number of products to produce\n\
\tp4: the size of the queue used to store products (0 for unlimited)\n\
\tp5: 0 or 1 for scheduling algorithm (0=FCFS, 1=Round-Robin)\n\
\tp6: the value of the quantum for Round-Robin scheduling\n\
\tp7: the seed for the random number generator\n");
        return -1;
    }
    return 0;
}

