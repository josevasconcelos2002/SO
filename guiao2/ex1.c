#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    pid_t pid;

    if((pid = fork()) == 0){
        // child-process code
        printf("Child PID: %d\nParent PID: %d\n", getpid(), getppid());
    } else {
        // parent-process code
        printf("Parent PID: %d\nChild PID: %d\n", getpid(), pid);
    }
    return 1;
}