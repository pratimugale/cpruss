#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Function prototypes
void start();
void stop();
void restart();

char command[150];

int main(void){
    printf("Started executing!\n");

    restart();
    printf("Completed execution!\n");

    return 0;
}

void start(){
    //Procedure to Start the PRU execution(on whichever firmware is currently loaded)
    //PRU needs to be stopped before using this function again.
    //For all practical purposes, use restart() instead of start

    //TODO: check if PRU state is already running

    /*
    FILE *file = fopen("/sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state", "r"); 
    if (file != NULL){
        char status[8];
        fgets(status, sizeof status, file);
        if (status[0] != "r"){
            strcpy(command, "echo start | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state");
            system(command);
            printf("----------------------->%s",status); 
            printf("--------------------------");
            printf("hi");

        }
        else {
            //Delete following line
            printf("PRU was running.");
        }
    }*/
    strcpy(command, "echo start | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state");
    system(command);
}
void stop(){
    strcpy(command, "echo stop | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state");
    system(command);
}
void restart(){
    //For all practical purposes, use restart() instead of start
    stop();
    start();
}
