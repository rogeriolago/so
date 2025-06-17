#include <unistd.h>     // fork(), getpid(), access()
#include <stdio.h>      // printf(), scanf(), fopen()
#include <stdlib.h>     // exit()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait()
#include <time.h>       // clock()
#include <string.h>     // strlen(), strtok()

#define MAXN 1100
int n = 10;

// Função Bubble Sort
void bubble_sort(int vetor[]) {
    int ordenado = 0;
    while (!ordenado) {
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

    printf("Digite 10 números inteiros:\n");
    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);

    pid_t filho1 = fork();

    if (filho1 == 0) {
        // Filho 1: Bubble Sort
        int vet1[10];
        for (int i = 0; i < n; i++) vet1[i] = arr[i];

        clock_t start = clock();
        bubble_sort(vet1);
        clock_t end = clock();
        double tempo = (double)(end - start) / CLOCKS_PER_SEC;

        FILE *f = fopen("resultado_bubble.txt", "w");
        if (f == NULL) {
            perror("Erro ao abrir arquivo");
            exit(1);
        }

        fprintf(f, "Bubble Sort\nTempo: %.6f\n", tempo);
        for (int i = 0; i < n; i++) fprintf(f, "%d ", vet1[i]);
        fprintf(f, "\n");
        fclose(f);

        exit(0);
    }

    pid_t filho2 = fork();

    if (filho2 == 0) {
        // Filho 2: Quick Sort
        int vet2[10];
        for (int i = 0; i < n; i++) vet2[i] = arr[i];

        clock_t start = clock();
        quick_sort(vet2, 0, n - 1);
        clock_t end = clock();
        double tempo = (double)(end - start) / CLOCKS_PER_SEC;

        FILE *f = fopen("resultado_quick.txt", "w");
        if (f == NULL) {
            perror("Erro ao abrir arquivo");
            exit(1);
        }

        fprintf(f, "Quick Sort\nTempo: %.6f\n", tempo);
        for (int i = 0; i < n; i++) fprintf(f, "%d ", vet2[i]);
        fprintf(f, "\n");
        fclose(f);

        exit(0);
    }

    // Pai espera os dois filhos
    wait(NULL);
    wait(NULL);

    printf("\n[Pai] Ambos os filhos terminaram.\n");

    // Lê resultado do Bubble Sort
    FILE *f1 = fopen("resultado_bubble.txt", "r");
    if (f1) {
        char linha[256];
        printf("\n--- Resultado Bubble Sort ---\n");
        while (fgets(linha, sizeof(linha), f1)) printf("%s", linha);
        fclose(f1);
    } else {
        perror("Erro ao abrir resultado_bubble.txt");
    }

    // Lê resultado do Quick Sort
    FILE *f2 = fopen("resultado_quick.txt", "r");
    if (f2) {
        char linha[256];
        printf("\n--- Resultado Quick Sort ---\n");
        while (fgets(linha, sizeof(linha), f2)) printf("%s", linha);
        fclose(f2);
    } else {
        perror("Erro ao abrir resultado_quick.txt");
    }

    return 0;
}
