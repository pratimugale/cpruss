#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Function prototypes
void start();

char command[200];

int main(void){
    printf("Started executing!\n");

    start();
    printf("Completed execution!\n");

    return 0;
}

void start(){
    //Procedure to Start the PRU execution(on whichever firmware is currently loaded)
    //PRU needs to be stopped before using this function again.

    strcpy(command, "echo start | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state");
    system(command);

    
}
