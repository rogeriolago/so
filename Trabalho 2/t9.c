#include <unistd.h>     // fork(), getpid(), getppid()
#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // exit()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait()
#include <pthread.h>    // pthread_create, pthread_join
#include <time.h>       // clock()

#define RODADAS 20
#define NUM_FILHOS 10  // quantidade de filhos ou threads

void tarefa_filho(int i) {
    printf("[%d] -> sou %5d, filho de %5d\n", i, getpid(), getppid());
}

void* thread_func(void* arg) {
    int i = *((int*)arg);
    tarefa_filho(i);
    return NULL;
}

int main() {
    double tempo_fork_total = 0, tempo_thread_total = 0;

    for (int rodada = 0; rodada < RODADAS; rodada++) {
        // --- FORK ---
        clock_t start_fork = clock();
        for (int i = 0; i < NUM_FILHOS; i++) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Erro ao criar processo");
                exit(1);
            }
            if (pid == 0) {
                tarefa_filho(i);
                exit(0);
            } else {
                wait(NULL);
            }
        }
        clock_t end_fork = clock();
        tempo_fork_total += (double)(end_fork - start_fork) / CLOCKS_PER_SEC;

        // --- THREADS ---
        pthread_t threads[NUM_FILHOS];
        int indices[NUM_FILHOS];

        clock_t start_thread = clock();
        for (int i = 0; i < NUM_FILHOS; i++) {
            indices[i] = i;
            if (pthread_create(&threads[i], NULL, thread_func, &indices[i]) != 0) {
                perror("Erro ao criar thread");
                exit(1);
            }
        }

        for (int i = 0; i < NUM_FILHOS; i++) {
            pthread_join(threads[i], NULL);
        }
        clock_t end_thread = clock();
        tempo_thread_total += (double)(end_thread - start_thread) / CLOCKS_PER_SEC;
    }

    // RESULTADOS
    printf("\n===== RESULTADOS MÉDIOS APÓS %d RODADAS =====\n", RODADAS);
    printf("Média tempo com fork():   %.8f segundos\n", tempo_fork_total / RODADAS);
    printf("Média tempo com threads(): %.8f segundos\n", tempo_thread_total / RODADAS);

    return 0;
}
