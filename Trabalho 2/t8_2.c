#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_func(void* arg) {
    pause(); // A thread fica "dormindo"
    return NULL;
}

int main() {
    int count = 0;
    while (1) {
        pthread_t t;
        if (pthread_create(&t, NULL, thread_func, NULL)) {
            perror("pthread_create");
            break;
        }
        count++;
        printf("Thread criada: %d\n", count);
    }
    return 0;
}
