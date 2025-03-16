#include "mysystem.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

int mysystem(const char* command) {
    char* args[N];
    char cmd_copy[256];

    // Faz uma cópia da string original para não modificá-la
    strncpy(cmd_copy, command, sizeof(cmd_copy) - 1);
    cmd_copy[sizeof(cmd_copy) - 1] = '\0';

    char* token = strtok(cmd_copy, " ");
    int i = 0;

    while (token != NULL && i < N - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Finaliza a lista de argumentos

    // DEBUG: Mostrar os argumentos extraídos
    printf("Executando: ");
    for (int j = 0; args[j] != NULL; j++) {
        printf("%s ", args[j]);
    }
    printf("\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork falhou");
        return -1;
    }

    if (pid == 0) {  // Processo filho
        execvp(args[0], args);
        perror("execvp falhou");  // Só executa se execvp falhar
        _exit(127);
    }

    // Processo pai
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return -1;
}
