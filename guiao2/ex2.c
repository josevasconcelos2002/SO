#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    pid_t pid;
    int status;

    if((pid = fork()) == 0){
        // child-process code
        printf("Child PID: %d\nParent PID: %d\n\n", getpid(), getppid());
        _exit(0);
    } else {
        // parent-process code
        pid_t child = wait(&status);
        if(WIFEXITED(status) == 1){
            printf("Child %d exited normally\nParent PID: %d\nParent PPID: %d\n", child, getpid(), getppid());
        }
    }
    return 1;
}