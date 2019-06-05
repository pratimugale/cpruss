#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "cpruss.h"

//Function prototypes
//The n in the parameter stands for which PRU you currently want to use
//n = 1: PRU 1: /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state
//n = 2: PRU 2: /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state

/* -------------------CLEANUP LATER--------
void start(int n);
void stop(int n);
void restart(int n);
char* state(int n);

Global Variables
char command[150];
int prun;
char status[8];

*/

// main() function is for temporary testing 
/*int main(void){
    printf("Started executing!\n");
    //restart();
    prun = 1;
    restart(prun);

    state(2);
    printf("Completed execution!\n");

    return 0;
}*/

char command[150];
int  prun;
char status[8];

void start(int n){
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
    if(n == 1){
        // strcmp() returns 0 if both strings DO match!
        if (strcmp(state(1), "running")){
            strcpy(command, "echo start | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state");
            system(command);
        }
        else{
            printf("PRU 1 is currently running and start() function cannot be executed.\n"); 
        }
    }
    else if (n == 2){
        if (strcmp(state(2), "running")){
             strcpy(command, "echo start | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state");
             system(command);
        }
        else{
            printf("PRU 2 is currently running and start() function cannot be executed.\n"); 
        }
    }
    else{
        printf("Invalid PRUn input in function start()\n");
    }
}

void stop(int n){
    //Procedure to Stop the PRU execuion(on whichever firmware is currently being executed)

    if (n == 1){
        if (strcmp(state(1), "offline")){
            strcpy(command, "echo stop | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state");
            system(command);
        }
        else{
            printf("PRU 1 is already offline and cannot be stop()ped.\n");
        }
    }
    else if (n == 2){
        if (strcmp(state(2), "offline")){
            strcpy(command, "echo stop | sudo tee -a /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state");
            system(command);
        }
        else{
            printf("PRU 2 is already offline and cannot be stop()ped.\n");
        }
    }
    else{
        printf("Invalid PRUn input in function stop()\n");
    }
}

void restart(int n){
    //Procedure to stop the current execution and start again.(executes same firmware again)
    //For all practical purposes, restart() is better to use than start()
    if (n == 1 || n == 2){ 
        stop(n);
        start(n);
    }
    else{
        printf("Invalid PRUn input provided in function restart()\n");
    }
}

char* state(int n){
    //Returns (as a string), the current state of the PRU

    //state = "abcdefg\0";
    //return strdup(&state[0]);

    if (n == 1){
        FILE *file = fopen("/sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state", "r"); 
        if (file != NULL){
            fgets(status, sizeof status, file);
            fclose(file);
            return status;
            //printf("Status of PRU 1: %s", status);
        }
    }
    else if (n == 2){
        FILE *file = fopen("/sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state", "r"); 
        if (file != NULL){
            fgets(status, sizeof status, file);
            fclose(file);
            return status;
            //printf("Status of PRU 2: %s", status);
        }
        else{
             printf("Invalid PRUn input in function state()\n");
        }

    }

}

int check_module(){
    //Function to check if the "pru_rproc" module is loaded into the kernel.
    //Function returns 0 if module is NOT loaded and
    //                 1 if it IS loaded.
    FILE *file = popen("lsmod | grep pru_rproc", "r");

    char buf[16];
    if (fread (buf, 1, sizeof (buf), file) > 0){ // If there is some result then module definitely must be loaded 
        printf("The pru_rproc module is loaded in the Linux Kernel.\n");
        fclose(file);
        return 1;
    }
    else{
        printf("The pru_rproc module is NOT loaded.\n");
        fclose(file);
        return 0;
    }
}

void modprobe(){
    //Procedure to add the "pru_rproc" module to the Linux Kernel
    if (!check_module()){
        strcpy(command, "sudo modprobe pru_rproc");
        system(command);
        printf("Module added.\n");
    }
}

int rmmod(int n=0){
    //Procedure to remove the "pru_rproc" module from the Linux Kernel
    //Parameters:     0 - NOT Forcibly i.e. module won't be removed if any PRU is running
    //                Any other value - Remove FORCIBLY i.e. stop the PRUs and then remove the module
    //
    //Return values : 0 - Couldn't be removed as the PRUs were running
    //                1 - rmmod completed successfully
    strcpy(command, "sudo rmmod pru_rproc");
    if (check_module() && (!strcmp(state(1), "offline") && !strcmp(state(2), "offline"))){
        system(command);
        printf("Module Removed.\n");
        return 1;
    }
    else if (check_module() && (strcmp(state(1), "offline") || strcmp(state(2), "offline"))){
        if(n == 1){
            //forcibly
            stop(1);
            stop(2);
            system(command);
            printf("Module Removed.\n");
            return 1;
        }
        else{
            printf("Module couldn't be removed as the PRUs are currently running.\n");
            return 0;
        }
    }
    else if (!check_module()){
        printf("Module is already removed.\n");
        return 1;
    }
}

void make(char *path){
    //Procedure that runs the "make" command on the Makefile whose location is specified in the argument 
    //Always give the absolute path to be sure
    //*******************
    //DO NOT PASS THE ARGUMENT AS A STRING CONSTANT ELSE A WARNING WILL BE THROWN
    //INSTEAD DO THIS(in your calling program):
    //char path[7] = "~/path";
    //make(path);
    printf("Makefile Path given: %s\n", path);
    char temp[150] = "cd ";
    strcat(temp, path);
    char mak[9] = " && make";
    strcat(temp, mak);
    strcpy(command, temp);
    system(command);
}

// Complete this function
void load_firmware(char *path, int prun){
    //This function loads the PRUs with the firmware provided in its argument
    //Also mention the .out firmware in the path
    //
    //NOTE: Here 0 => PRU 1
    //           1 => PRU 2
    if (prun == 0 || prun == 1){
        printf("Firmware Path given: %s\n", path);
        char temp[150] = "sudo cp ";
        strcat(temp, path);
        char mak[50] = " /lib/firmware/am335x-pru";
        strcat(temp, mak);
        char pru[2];
        sprintf(pru, "%i", prun);
        strcat(temp, pru);
        char mak2[4] = "-fw";
        strcat(temp, mak2);
        strcpy(command, temp);
        printf("Executing: %s\n", command);
        system(command);
    }
    else {
        printf("Enter Valid PRU Number.");
    }
}
