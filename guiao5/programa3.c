#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 2048


int main(){
    int fifo = open("fifos/fifo", O_RDONLY);
    char buffer[BUFF_SIZE];
    int n_read;
    while((n_read = read(fifo, buffer, BUFF_SIZE))>0){
        write(1, buffer, n_read);
    }
    close(fifo);
    unlink("fifos/fifo");
    return 0;
}