#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "person.h"
#include <stdlib.h>

#define FILE_NAME "file_pessoas"

int nr_registos = 0;

void add_person(char *name, int age){
    struct person p = new_Person(name,age);
    int fd = open(FILE_NAME, O_CREAT| O_WRONLY | O_APPEND, 0600);
    ssize_t wrote_bytes = write(fd, &p, sizeof(p));
    printf("Bytes wrote: %ld\n", wrote_bytes);

    if(wrote_bytes == -1){
        char* msg = "Ocorreu um erro ao escrever no ficheiro!\n";
        write(STDERR_FILENO, msg, sizeof(msg));
    } else if(wrote_bytes > 0){
        nr_registos++;
        printf("registo %d\n", nr_registos);
    }
    close(fd);
}

void list_N_persons(int N){
    int fd = open(FILE_NAME, O_RDONLY);
    struct person p;
    int i = 0;

    while(read(fd, &p, sizeof(p)) > 0 && i < N){
        printf("Name: %s, Age: %d \n", p.name, p.age);
        i++;
    }
    close(fd);
}

void update_person_age(char *name, int age){
    int fd = open(FILE_NAME, O_RDWR); // Abrir para leitura e escrita
    if (fd == -1) {
        perror("Erro ao abrir o ficheiro");
        return;
    }

    struct person p;
    off_t offset;

    // Ler registros até encontrar a pessoa
    while (read(fd, &p, sizeof(p)) > 0) {
        offset = lseek(fd, 0, SEEK_CUR) - sizeof(p); // Obter o offset do registro atual

        if (strcmp(p.name, name) == 0) {
            p.age = age; // Atualizar a idade
            
            lseek(fd, offset, SEEK_SET); // Voltar para a posição do registro
            ssize_t wrote_bytes = write(fd, &p, sizeof(p));
            if (wrote_bytes == -1) {
                perror("Erro ao escrever o registro atualizado");
            } else {
                printf("Registro atualizado: Nome: %s, Nova Idade: %d\n", p.name, p.age);
            }
            break; // Sair do loop após a atualização
        }
    }

    close(fd);
}




int main(int argc, char* argv[]){

    if (strcmp(argv[1],"--help") == 0)
    {
        printf("Usage:\n");
        printf("Add new person: ./pessoas -i [name] [age]\n");
        printf("List N persons: ./pessoas -l [N]\n");
        printf("Change person age: ./pessoas -u [name] [age]\n");
        printf("Change person age (v2): ./pessoas -o [position] [age]\n");
        return 1;
    }

    if ( strcmp(argv[1],"-i") == 0 )
    {
        if(argc < 4){
            printf("Usage:\n");
            printf("Add new person: ./pessoas -i [name] [age]\n");
            return 1;
        }
        char *name = argv[2];
        int age = atoi(argv[3]);
        add_person(name, age);
    }

    if ( strcmp(argv[1],"-l") == 0 )
    {
        if(argc < 3){
            printf("Usage:\n");
            printf("List first N persons: ./pessoas -l [N]\n");
            return 1;
        }
        int N = atoi(argv[2]);
        list_N_persons(N);
    }

    if ( strcmp(argv[1],"-u") == 0 )
    {
        if(argc < 4){
            printf("Usage:\n");
            printf("Update some person age: ./pessoas -u [name] [age]\n");
            return 1;
        }
        char *name = argv[2];
        int age = atoi(argv[3]);
        update_person_age(name,age);
    }

    if ( strcmp(argv[1],"-o") == 0 )
    {
        // TO DO
    }

    return 0;
}
