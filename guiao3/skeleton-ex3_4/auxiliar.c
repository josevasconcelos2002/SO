#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // Para sleep()

int main(int argc, char *argv[]) {
    int res;
    usleep(100000);
    srandom(time(NULL) ^ getpid());
    res = random() % 3;
    return res;
}
