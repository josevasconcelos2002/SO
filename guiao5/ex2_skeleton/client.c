#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"

int main (int argc, char * argv[]) {

    if (argc < 2) {

        printf("USAGE: ./client <number_to_search>\n");
        _exit(1);
		
    } else if (argc == 2) {
        int n = atoi(argv[1]);

        char *response_fifo_name = malloc(128);
        sprintf(response_fifo_name, "../fifos/response_fifo_%d", getpid());
        mkfifo(response_fifo_name, 0666);

        Msg mensagem;
        mensagem.needle = n;
        mensagem.pid = getpid();
        mensagem.occurrences = 0;

        int request_fifo = open(REQUEST_FIFO, O_WRONLY);

        int n_w = write(request_fifo, &mensagem, sizeof(Msg));
        if (n_w != sizeof(Msg)) {
            printf("Erro ao escrever no pipe! Esperado %ld bytes, mas escrevemos %d\n", sizeof(Msg), n_w);
        } else {
            printf("\nMensagem enviada:\n");
            printf("Needle: %d\n", mensagem.needle);
            printf("PID: %d\n", mensagem.pid);
            printf("Occurrences: %d\n", mensagem.occurrences);
        }

        close(request_fifo);

        int response_fifo = open(response_fifo_name, O_RDONLY);

        Msg msg_recieved;
        int n_r = read(response_fifo, &msg_recieved, sizeof(Msg));
        if (n_r > 0) {
            printf("\nMensagem recebida:\n");
            printf("Needle: %d\n", msg_recieved.needle);
            printf("PID: %d\n", msg_recieved.pid);
            printf("Occurrences: %d\n", msg_recieved.occurrences);
        } else {
            printf("Erro ao ler resposta do servidor ou resposta vazia.\n");
        }

        free(response_fifo_name);
        close(response_fifo);
    }

    return 0;
}
