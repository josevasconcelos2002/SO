#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>

int main() {
    pid_t pid;
    int fildes[2];
    pipe(fildes);
    int n = 42;

    if ((pid = fork()) == 0) {
        close(fildes[1]);
        int n_recebido;
        read(fildes[0], &n_recebido, sizeof(int));
        printf("Filho recebeu o número: %d\n", n_recebido);
        close(fildes[0]);
    } else {
        close(fildes[0]);
        // a)
        sleep(10);
        write(fildes[1], &n, sizeof(int));
        printf("Pai enviou o número: %d\n", n);
        close(fildes[1]);
    }
    
    return 0;
}
