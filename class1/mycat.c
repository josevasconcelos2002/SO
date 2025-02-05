#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define SIZE 4096


int main(int argc, char** argv){
    printf("ARGC: %d \n", argc);
    for(int i = 0; i<argc ; i++){
        printf("argv[%d] = %s \n", i, argv[i]);
    }

    char buffer[SIZE] = {0};
    ssize_t bytesRead = 0;

    if(argc == 1){
        // funcionalidade simples
        while((bytesRead = read(0, buffer, SIZE)) > 0){
            write(1,buffer,bytesRead);
        }
    }
    else if(argc == 2){
        // funcionalidade avancada
        int fd = open(argv[1], O_RDONLY);
        while((bytesRead = read(fd, buffer, SIZE)) > 0){
            write(1,buffer,bytesRead);
        }
        printf("\n");
        close(fd);
    }
    return 0;
}