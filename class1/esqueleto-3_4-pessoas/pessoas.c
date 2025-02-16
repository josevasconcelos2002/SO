#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "person.h"

#define FILE_NAME "file_pessoas"

void add_person(char *name, int age){
    struct person p = new_Person(name,age);
    int fd = open(FILE_NAME, O_CREAT| O_WRONLY | O_APPEND, 0600);
    write(fd, &p, sizeof(p));
    close(fd);
}



int main(int argc, char* argv[]){

    if ( argc < 3 )
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
        int age = argv[3];
        add_person(name, age);
    }

    if ( strcmp(argv[1],"-l") == 0 )
    {
        // TO DO
    }

    if ( strcmp(argv[1],"-u") == 0 )
    {
        // TO DO
    }

    if ( strcmp(argv[1],"-o") == 0 )
    {
        // TO DO
    }

    return 0;
}
