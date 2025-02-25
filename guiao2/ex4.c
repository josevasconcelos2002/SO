#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#define N 10

int main(){
    
    pid_t pids[N];
    for(int i = 0; i<N ; i++){
        pids[i] = fork();
        int status;
    
    
        if(pids[i] == 0){
            // child-process code
            _exit(i+1);
        }
    }

    for(int i = 0; i<N ; i++){
        int status;
        pid_t child = waitpid(pids[i],&status, 0);
        printf("Child nr %d, exited with code %d\n", i, WEXITSTATUS(status));
    }
    return 0;
}