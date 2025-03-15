#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    pid_t pid;
    int status;

    if((pid = fork()) == 0){
        execl("/bin/ls", "ls", "-l", NULL);
        _exit(0);
    } else{
        wait(&status);
    }
}