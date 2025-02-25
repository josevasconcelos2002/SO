#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    printf("PID: %d\nPPID: %d\n", getpid(), getppid());
    return 1;
}