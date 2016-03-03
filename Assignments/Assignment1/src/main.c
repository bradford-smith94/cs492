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
    int numProducers;
    int numConsumers;
    int qSize;
    int scheduling;
    int quantum;
    int i;

    /* validate arguments */
    if (argc != 8)
    {
        printf("usage: %s <p1> <p2> <p3> <p4> <p5> <p6> <p7>\n", argv[0]);
        printf("\twhere:\n\tp1: the number of producer threads\n\
\tp2: the number of consumer threads\n\
\tp3: the total number of products to produce\n\
\tp4: the size of the queue used to store products (0 for unlimited)\n\
\tp5: 0 or 1 for scheduling algorithm (0=FCFS, 1=Round-Robin)\n\
\tp6: the value of the quantum for Round-Robin scheduling\n\
\tp7: the seed for the random number generator\n");
        return -1;
    }

    /* save parameters in variables and do error checking */
    numProducers = atoi(argv[1]);
    if (numProducers <= 0)
        printf("[ERROR]\tInvalid number of procuder threads");

    numConsumers = atoi(argv[2]);
    if (numConsumers <= 0)
        printf("[ERROR]\tInvalid numer of consumer threads");

    gl_env.maxProductCount = atoi(argv[3]);
    if (gl_env.maxProductCount <= 0)
        printf("[ERROR]\tInvalid number of products");
    gl_env.productCount = 0;

    qSize = atoi(argv[4]);
    if (qSize < 0)
        printf("[ERROR]\tInvalid queue size");

    scheduling = atoi(argv[5]);
    if (scheduling != 0 && scheduling != 1)
        printf("[ERROR]\tInvalid value for scheduling algorithm");

    quantum = atoi(argv[6]);
    if (quantum <= 0 && scheduling == 1) /* quantum is only important for RR */
        printf("[ERROR]\tInvalid value for Round-Robin quantum");

    gl_env.seed = atoi(argv[7]);

    /* initialize queue */
    init_q(qSize);
    pthread_t producers[numProducers];
    int pNums[numProducers];
    pthread_t consumers[numConsumers];
    int cNums[numConsumers];

    /* create producers */
    for (i = 0; i < numProducers; i++)
    {
        pNums[i] = i + 1;
        pthread_create(&producers[i], NULL, &producer, (void*) &pNums[i]);
    }

    /* create consumers */
    for (i = 0; i < numConsumers; i++)
    {
        cNums[i] = i + 1;
        pthread_create(&consumers[i], NULL, &consumer, (void*) &cNums[i]);
    }

    /* join producers */
    for (i = 0; i < numProducers; i++)
        pthread_join(producers[i], NULL);

    /* join consumers */
    for (i = 0; i < numConsumers; i++)
        pthread_join(consumers[i], NULL);

    return 0;
}

