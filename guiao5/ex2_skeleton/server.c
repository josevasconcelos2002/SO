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

    int response_fifo = open(RESPONSE_FIFO, O_WRONLY);
    int request_fifo = open(REQUEST_FIFO, O_RDONLY | O_NONBLOCK);

    int n;
    Msg mensagem;

    while ((n = read(request_fifo, &mensagem, sizeof(Msg))>0)) {

            printf("\nMensagem recebida:\n");
            printf("Needle: %d\n", mensagem.needle);
            printf("PID: %d\n", mensagem.pid);
            printf("Occurrences: %d\n", mensagem.occurrences);

            
            mensagem.occurrences = count_needle(mensagem.needle);

            
            write(response_fifo, &mensagem, sizeof(Msg));
            printf("\nResposta enviada:\n");
            printf("Needle: %d\n", mensagem.needle);
            printf("Occurrences: %d\n", mensagem.occurrences);
    } 

    close(response_fifo);
    close(request_fifo);
    unlink(RESPONSE_FIFO);
    unlink(REQUEST_FIFO);

    return 0;
}
