#include <unistd.h>     // fork(), getpid()
#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // exit()
#include <sys/types.h>  // pid_t
#include <time.h>       // clock()

#define MAXN 1100

int n = 10;

// Função Bubble Sort
void bubble_sort(int vetor[]) {
    int ordenado = 0;
    while (ordenado == 0) {
        ordenado = 1;
        for (int i = 0; i < n - 1; i++) {
            if (vetor[i] > vetor[i + 1]) {
                int tmp = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = tmp;
                ordenado = 0;
            }
        }
    }
}

// Função Quick Sort
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivo = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivo) {
                i++;
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
        int tmp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = tmp;

        int pi = i + 1;
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main() {
    int arr[10];

    // Leitura dos 10 números
    printf("Digite 10 números inteiros:\n");
    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);

    pid_t filho1 = fork();

    if (filho1 == 0) {
        // Primeiro filho: Bubble Sort
        int vetor_bubble[10];
        for (int i = 0; i < n; i++) vetor_bubble[i] = arr[i];

        clock_t start = clock();
        bubble_sort(vetor_bubble);
        clock_t end = clock();

        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n[Filho 1 - Bubble Sort] PID = %d\n", getpid());
        printf("Tempo: %.6f segundos\n", tempo);
        printf("Vetor ordenado: ");
        for (int i = 0; i < n; i++) printf("%d ", vetor_bubble[i]);
        printf("\n");

        exit(0);
    }

    pid_t filho2 = fork();

    if (filho2 == 0) {
        // Segundo filho: Quick Sort
        int vetor_quick[10];
        for (int i = 0; i < n; i++) vetor_quick[i] = arr[i];

        clock_t start = clock();
        quick_sort(vetor_quick, 0, n - 1);
        clock_t end = clock();

        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n[Filho 2 - Quick Sort] PID = %d\n", getpid());
        printf("Tempo: %.6f segundos\n", tempo);
        printf("Vetor ordenado: ");
        for (int i = 0; i < n; i++) printf("%d ", vetor_quick[i]);
        printf("\n");

        exit(0);
    }

    // Processo pai
    printf("\n[Pai] PID = %d - Filhos criados, pai continua executando.\n", getpid());
    printf("[Pai] Não está esperando os filhos.\n");

    return 0;
}
