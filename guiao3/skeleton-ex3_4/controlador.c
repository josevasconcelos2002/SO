#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysystem.h"


int controller(int N, char** commands) {
    int n_vezes[N];

    for (int j = 0; j < N; j++) {
        n_vezes[j] = 0;
    }

    for (int i = 0; i < N; i++) {
        int r = -1;

        while (r != 0) {
            r = mysystem(commands[i]);
            n_vezes[i]++;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%s %d\n", commands[i], n_vezes[i]);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    char* commands[argc - 1];

    for (int i = 1; i < argc; i++) {
        commands[i - 1] = strdup(argv[i]);
    }

    controller(argc - 1, commands);

    for (int i = 0; i < argc - 1; i++) {
        free(commands[i]);
    }

    return 0;
}
