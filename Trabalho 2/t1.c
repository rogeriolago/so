#include <unistd.h>      // Para fork(), getpid(), getppid(), etc.
#include <stdio.h>       // Para printf(), scanf()
#include <stdlib.h>      // Para exit()
#include <sys/types.h>   // Para tipos como pid_t
#include <sys/wait.h>    // Para wait()

int main() {
    int retval, n;

    // Solicita ao usuário o número de filhos
    printf("Digite o número de filhos a serem criados: ");
    scanf("%d", &n);

    // Imprime o PID do processo pai
    printf("Olá, sou o processo %5d\n", getpid());

    // Loop para criar N filhos
    for (int i = 0; i < n; i++) {
        retval = fork();  // Cria um novo processo filho

        if (retval < 0) {
            // Se houve erro ao criar o processo
            perror("Erro ao criar processo");
            exit(1);
        }

        if (retval == 0) {
            // Código executado pelo processo filho
            printf("[%d] -> sou %5d, filho de %5d\n", i, getpid(), getppid());

            // Filho termina imediatamente após imprimir
            exit(0);
        } else {
            // Código executado pelo processo pai
            

            // Pai espera o filho terminar antes de continuar
            wait(NULL);
        }
    }

    printf("tchau do papai\n");

    // Após criar e esperar todos os filhos, o pai encerra
    exit(0);
    //processo meu filho
}
