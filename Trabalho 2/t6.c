#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 20

int next = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void *threadBody(void *id)
{
    long tid = (long) id;

    pthread_mutex_lock(&lock);

    while (tid != next) {
        pthread_cond_wait(&cond, &lock);
    }

    printf("%ld\n", tid + 1);  // Imprime o número correspondente à thread

    next++;
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    long i;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, threadBody, (void *) i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
