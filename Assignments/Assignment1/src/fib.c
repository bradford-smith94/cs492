/* Bradford Smith (bsmith8)
 * CS 492 Assignment 1 fib.c
 * 03/04/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "hw1.h"

/* pre: takes in positive integer 'n'
 * post: computes fibonacci of 'n'
 * return: the 'n'th fibonacci number
 */
int fibonacci(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return (fibonacci(n - 1) + fibonacci(n - 2));
}
