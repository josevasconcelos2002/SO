#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){

    for(int i = 1; i<=10 ; i++){
        pid_t pid;
        int status;
    
    
        if((pid = fork()) == 0){
            // child-process code
            printf("Child nr %d,  PID: %d\nParent PID: %d\n", i, getpid(), getppid());
            _exit(i);
        } else {
            // parent-process code
            pid_t child = wait(&status);
            printf("Child %d with %d exit status!\n\n", pid, WEXITSTATUS(status));
        }
    }
    return 0;
}