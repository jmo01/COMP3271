// it is like import statement in Java
#include <stdio.h> // standard i/o; this include statement is like import statement in Java.
#include <stdlib.h> // standard library
#include <string.h> // necessary to use string functions like strlen()

#define SIZE 128 // constant definition; it is like final variable declaration in Java.
int test = 5; // global variable; it is like a public instance variable in Java.

int main(int argc, char* argv[]) {
    int i;
    char name[32];
    
    printf("Welcome to C programming world!\n");
    printf("%d arguments:\n", argc); 
    /* %d means an integer */
    
    for (i = 0; i < argc; i++) {
        printf("\t%s\n", argv[i]); // %s means a string from the next argument
    }
    
    name[0] = 'C'; 
    name[1] = 'o'; 
    name[2] = 'm'; 
    name[3] = 'p';
    name[4] = 'u';
    name[5] = 't'; 
    name[6] = 'e'; 
    name[7] = 'e'; 
    name[8] = '\0'; 
    name[9] = 'r';
    
    // what will be printed?
    printf("The length of %s is %d.\n", name, strlen(name)); 
    
    return 0;
}