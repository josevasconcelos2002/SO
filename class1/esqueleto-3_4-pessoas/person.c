#include "person.h"

// TO DO



struct person new_Person(char* name, int age){
    struct person p;
    strcpy(p.name, name);
    p.age = age;
    return p;
}
