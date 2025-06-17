#include <unistd.h>      // fork(), execlp(), getpid(), getppid()
#include <stdio.h>       // printf(), scanf()
#include <stdlib.h>      // exit(), EXIT_FAILURE
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait()

int main() {
    int retval, n;

    // Entrada do número de filhos
    printf("Digite o número de filhos a serem criados: ");
    scanf("%d", &n);

    // Exibe PID do processo pai
    printf("\nOlá, sou o processo %5d\n", getpid());

    // Loop de criação dos filhos
    for (int i = 0; i < n; i++) {
        printf("\n--- Criando filho %d ---\n", i);

        retval = fork();

        if (retval < 0) {
            // Erro ao criar processo
            perror("Erro ao criar processo");
            exit(EXIT_FAILURE);
        }

        if (retval == 0) {
            // Código do processo filho
            printf("[%d] -> sou %5d, filho de %5d\n", i, getpid(), getppid());
            printf("Filho %d executando 'ps -f':\n", i);
            execlp("ps", "ps", "-f", NULL); // Executa o comando
            perror("execlp"); // Caso execlp falhe
            exit(EXIT_FAILURE);
        } else {
            // Código do processo pai
            wait(NULL); // Espera o filho encerrar
        }
    }

    printf("\nPai (PID = %d) terminou de criar os %d filhos.\n", getpid(), n);
    return 0;
}
