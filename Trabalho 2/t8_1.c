#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  // para pid_t

int main() {
    int count = 0;
    while (1) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            break;
        } else if (pid == 0) {
            pause(); // Processo filho "congela" aqui
        } else {
            count++;
            printf("Processo criado: %d\n", count);
        }
    }
    return 0;
}
