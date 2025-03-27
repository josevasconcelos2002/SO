#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "defs.h"
#include "vector.h"

int main (int argc, char * argv[]) {
    init_vector();
    print_vector();

    mkfifo(RESPONSE_FIFO, 0666);
    mkfifo(REQUEST_FIFO, 0666);

    int request_fifo = open(REQUEST_FIFO, O_RDONLY | O_NONBLOCK);

    int n;
    Msg mensagem;


    while (1) {

            n = read(request_fifo, &mensagem, sizeof(Msg));


            if(n>0){

                int logs = open("logs.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);

                printf("\nMensagem recebida:\n");
                printf("Needle: %d\n", mensagem.needle);
                printf("PID: %d\n", mensagem.pid);
                printf("Occurrences: %d\n", mensagem.occurrences);
                
                mensagem.occurrences = count_needle(mensagem.needle);

                char buffer[128];
                int len = snprintf(buffer, sizeof(buffer),
                   "Needle: %d\nPID: %d\nOccurrences: %d\n\n",
                   mensagem.needle, mensagem.pid, mensagem.occurrences);

                write(logs, buffer, len);

                char *response_fifo_name = malloc(128);
                sprintf(response_fifo_name, "../fifos/response_fifo_%d", mensagem.pid);
                
                int response_fifo = open(response_fifo_name, O_WRONLY);
                
                write(response_fifo, &mensagem, sizeof(Msg));
                printf("\nResposta enviada:\n");
                printf("Needle: %d\n", mensagem.needle);
                printf("Occurrences: %d\n", mensagem.occurrences);
                
                free(response_fifo_name);
                close(logs);
                close(response_fifo);
            }
            
    } 

    close(request_fifo);
    unlink(RESPONSE_FIFO);
    unlink(REQUEST_FIFO);

    return 0;
}
