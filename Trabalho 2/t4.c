#include <unistd.h>     // fork(), getpid()
#include <stdio.h>      // printf(), scanf()
#include <stdlib.h>     // exit(), atoi()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait()
#include <time.h>       // clock()

#define MAXN 1100

int n = 10, vetor[MAXN];

// Bubble sort (usado pelo pai)
void bubble_sort() {
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

// Quick sort (usado pelo filho)
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

    pid_t filho = fork();

    if (filho > 0) {
        // Processo pai
        for (int i = 0; i < n; i++) vetor[i] = arr[i]; // copiar para vetor usado no pai

        clock_t start = clock();
        bubble_sort();
        clock_t end = clock();

        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n[Pai] Tempo com Bubble Sort: %.6f segundos\n", tempo);
        printf("[Pai] Vetor ordenado: ");
        for (int i = 0; i < n; i++) printf("%d ", vetor[i]);
        printf("\n");

        wait(NULL); // espera o filho terminar
    } else if (filho == 0) {
        // Processo filho
        int vetor_filho[10];
        for (int i = 0; i < n; i++) vetor_filho[i] = arr[i];

        clock_t start = clock();
        quick_sort(vetor_filho, 0, n - 1);
        clock_t end = clock();

        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n[Filho] Tempo com Quick Sort: %.6f segundos\n", tempo);
        printf("[Filho] Vetor ordenado: ");
        for (int i = 0; i < n; i++) printf("%d ", vetor_filho[i]);
        printf("\n");

        exit(0); // finaliza o processo filho
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
