#ifndef PERSON_H
#define PERSON_H

// Struct definition
struct person {
    char name[50];
    int age;
};

// Function declarations
struct person new_Person(char *name, int age);

#endif