/* Bradford Smith (bsmith8)
 * CS 492 Lab 1 dp_one.c
 * 02/17/2016
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h> /* for sleep */

/* number of philosophers */
#define NUMP 5

/* list of mutexes (forks) */
pthread_mutex_t fork_mutex[NUMP];

/* mutex for "turn to grab/drop forks" */
pthread_mutex_t grab_mutex;
pthread_mutex_t drop_mutex;

int main()
{
    int i;
    pthread_t diner_thread[NUMP];
    int dn[NUMP];
    void *diner();
    for (i = 0; i < NUMP; i++)
        pthread_mutex_init(&fork_mutex[i], NULL);
    pthread_mutex_init(&grab_mutex, NULL);
    pthread_mutex_init(&drop_mutex, NULL);

    for (i = 0; i < NUMP; i++)
    {
        dn[i] = i;
        pthread_create(&diner_thread[i], NULL, diner, &dn[i]);
    }
    for (i = 0; i < NUMP; i++)
        pthread_join(diner_thread[i], NULL);
    pthread_exit(0);
}

/* create thread */
void *diner(int *i)
{
    int v;
    int eating = 0;
    printf("I'm diner %d\n", *i);
    v = *i;
    while (eating < 5)
    {
        printf("%d is thinking\n", v);
        sleep(v / 2);
        printf("%d is hungry\n", v);
        pthread_mutex_lock(&grab_mutex); /* take the grab fork lock */
        pthread_mutex_lock(&fork_mutex[v]); /* take left fork */
        pthread_mutex_lock(&fork_mutex[(v + 1) % NUMP]); /* take right fork */
        pthread_mutex_unlock(&grab_mutex); /* drop the grab fork lock */
        printf("%d is eating\n", v);
        eating++;
        sleep(1);
        printf("%d is done eating\n", v);
        pthread_mutex_lock(&drop_mutex); /* take the drop fork lock */
        pthread_mutex_unlock(&fork_mutex[v]); /* put left fork */
        pthread_mutex_unlock(&fork_mutex[(v + 1) % NUMP]); /* put right fork */
        pthread_mutex_unlock(&drop_mutex); /* drop the drop fork lock */
    }
    pthread_exit(NULL);
}

