#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>

int main() {
    pid_t pid;
    int fildes[2];
    pipe(fildes);

    if ((pid = fork()) == 0) {
        close(fildes[0]);
        int n_enviado = 7;
        write(fildes[1], &n_enviado, sizeof(int));
        printf("Filho enviou o número: %d\n", n_enviado);
        close(fildes[1]);
    } else {
        close(fildes[1]);
        int n_recebido;
        // EOF -> read retorna 0
        while (read(fildes[0], &n_recebido, sizeof(int)) > 0) {
            printf("Pai recebeu o número: %d\n", n_recebido);
        }
        close(fildes[0]);
    }
    
    return 0;
}
