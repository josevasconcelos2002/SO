#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 4096

int main(int argc, char** argv){
    printf("ARGC: %d \n", argc);
    for(int i = 0; i<argc ; i++){
        printf("argv[%d] = %s \n", i, argv[i]);
    }

    char destPath[512];
    snprintf(destPath, sizeof(destPath), "%s/%s", argv[2], argv[1]); 

    char buffer[SIZE] = {0};
 

    if(argc == 3){
        // ./mycp [SOURCE] [DESTINATION]
        int fdSrc = open(argv[1], O_RDONLY);
        int fdDest= open(destPath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        clock_t start = clock();
        ssize_t bytesRead = 0;

        while( (bytesRead = read(fdSrc, buffer, SIZE)) > 0){
            write(fdDest, buffer, bytesRead);
        }
        clock_t end = clock();
        double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    
        printf("Tempo total de cópia: %.6f segundos\n", elapsed);
        close(fdSrc);
        close(fdDest);
        
    }
}