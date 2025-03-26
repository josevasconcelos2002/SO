#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 2048


int main(){
    int fifo = open("fifos/fifo", O_WRONLY);
    char buffer[BUFF_SIZE];
    int n_read;
    while((n_read = read(0, buffer, BUFF_SIZE))>0){
        write(fifo, buffer, n_read);
    }
    close(fifo);
    unlink("fifos/fifo");
    return 0;
}