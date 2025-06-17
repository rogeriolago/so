#include <unistd.h>     // Para fork(), execlp(), getpid(), getppid()
#include <stdio.h>      // Para printf(), perror()
#include <stdlib.h>     // Para exit()
#include <sys/types.h>  // Tipos como pid_t
#include <sys/wait.h>   // Para wait()

int main() {
    int pid;  // Armazena o valor retornado por fork()

    // Mostra o PID do processo principal (pai)
    printf("MAIN: Olá, sou o processo %5d\n", getpid());

    // Cria um novo processo filho
    pid = fork();

    // Verifica se houve erro na criação do processo
    if (pid < 0) {
        perror("Erro ao criar processo filho");  // Mostra erro
        exit(1);  // Encerra com erro
    }

    // Código executado pelo processo pai
    if (pid > 0) {
        printf("Pai: processo filho PID=%5d criado com sucesso\n", pid);

        // Pai espera o filho terminar
        wait(NULL);
        printf("Pai: processo filho terminou.\n");
    }

    // Código executado pelo processo filho
    else {
        printf("Filho: sou o processo %5d, filho de %5d\n", getpid(), getppid());

        // Executa o comando 'ls' (lista arquivos e diretórios)
        execlp("ls", "ls", NULL);

        // Se execlp falhar, imprime erro
        perror("Erro ao executar ls");
        exit(1);  // Encerra com erro
    }

    return 0;  // Fim do programa
}
