#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

int main(void){
    printf("Started executing!\n");

    char command[200];
    strcpy(command, "ls");
    system(command);

    printf("Completed execution!\n");

    return 0;
}
