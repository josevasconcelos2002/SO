#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 2048


int main(){
    int fifo = mkfifo("fifos/fifo", 0666);
    return fifo;
}