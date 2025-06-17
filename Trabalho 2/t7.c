#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 100

int vetor[N];

void bubble_sort(int v[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (v[j] > v[j+1]) {
                int tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

void imprime_vetor(const char *msg, int v[], int n) {
    printf("%s\n", msg);
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n\n");
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        vetor[i] = rand() % 1000;
    }

    imprime_vetor("Vetor antes do fork():", vetor, N);

    pid_t pid = fork();

    if (pid == 0) {
        // Filho
        bubble_sort(vetor, N);
        imprime_vetor("[Filho] Vetor ordenado:", vetor, N);
        exit(0);
    } else if (pid > 0) {
        // Pai
        waitpid(pid, NULL, 0);
        imprime_vetor("[Pai] Vetor depois do filho terminar:", vetor, N);
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
