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


    pid_t pid = fork();

    if (pid == 0) {
        
        write(STDOUT_FILENO, "Processo filho a escrever no ficheiro de saida\n", 48);
        write(STDERR_FILENO, "Teste de erro pelo filho.\n", 27);

        
        char buffer[128];
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            write(STDOUT_FILENO, "Conteúdo lido do /etc/passwd:\n", 29);
            write(STDOUT_FILENO, buffer, bytes_read);
        } else {
            write(STDERR_FILENO, "Erro ao ler o arquivo /etc/passwd\n", 34);
        }

    } else if (pid > 0) {
        
        write(STDOUT_FILENO, "terminei\n", 9);
    } else {
        
        write(STDERR_FILENO, "Erro ao criar o processo filho\n", 30);
        return 1;
    }

    printf("terminei");
    return 0;
}