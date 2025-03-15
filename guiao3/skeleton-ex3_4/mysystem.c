#include "mysystem.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

// recebe um comando por argumento
// retorna -1 se o fork falhar
// caso contrario retorna o valor do comando executado
int mysystem (const char* command) {
	pid_t pid;
	char *commands = strtok(command, " ");


	int res = -1;
	if((pid = fork()) == 0){
		res = execl()
	}

	return res;
}