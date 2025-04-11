#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){

    int fd1 = open("/etc/passwd", O_CREAT | O_RDONLY, 0644);
    int fd_saida = open("../tmp/saida.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    int fd_erros = open("../tmp/erros.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (fd1 == -1 || fd_saida == -1 || fd_erros == -1) {
        write(STDERR_FILENO, "Erro ao abrir os arquivos\n", 25);
        return 1;
    }


    int dup_1 = dup2(fd1, STDIN_FILENO);
    int dup_2 = dup2(fd_saida, STDOUT_FILENO);
    int dup_3 = dup2(fd_erros, STDERR_FILENO);

    close(fd1);
    close(fd_saida);
    close(fd_erros);

    if((dup_1 == -1) || (dup_2 == -1) || (dup_3 == -1)){
        write(STDERR_FILENO, "Erro ao redirecionar os descritores\n", 36);
        return 1;
    }

    execlp("wc", "wc", NULL);

    printf("terminei");
    return 0;
}