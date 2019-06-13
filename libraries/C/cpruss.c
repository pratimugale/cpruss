#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "cpruss.h"

char command[150];
int  prun;
char status[8];

void start(int n){
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
    if (n == 1){
        FILE *file = fopen("/sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state", "r"); 
        if (file != NULL){
            fgets(status, sizeof status, file);
            fclose(file);
            return status;
        }
    }
    else if (n == 2){
        FILE *file = fopen("/sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state", "r"); 
        if (file != NULL){
            fgets(status, sizeof status, file);
            fclose(file);
            return status;
        }
        else{
             printf("Invalid PRUn input in function state()\n");
        }

    }

}

int check_module(char *module){
    //Function to check if the "pru_rproc" or "rpmsg_pru" module is loaded into the kernel.
    //Function returns 0 if module IS loaded and
    //                 1 if pru_rproc is NOT loaded. (Needs to be loaded)
    //                 2 if pru_rpmsg is NOT loaded. (Needs to be loaded)
    //                 3 if wrong option is chosen.

    char rproc[10] = "pru_rproc";
    char rpmsg[10] = "rpmsg_pru";
    if (!strcmp(module, rproc)){
        //strcmp returns 0 if strings are same
        
        FILE *file = popen("lsmod | grep pru_rproc", "r");

        char buf[16];
        if (fread (buf, 1, sizeof (buf), file) > 0){ // If there is some result then module definitely must be loaded 
            printf("The pru_rproc module is currently loaded into the Linux Kernel.\n");
            fclose(file);
            return 0;
        }
        else{
            printf("The pru_rproc module is NOT currently loaded.\n");
            fclose(file);
            return 1;
        }
    }
    else if(!strcmp(module, rpmsg)){
        FILE *file = popen("lsmod | grep rpmsg_pru", "r");
        
        char buf[16];
        if (fread (buf, 1, sizeof (buf), file) > 0){ // If there is some result then module definitely must be loaded 
            printf("The rpmsg_pru module is currently loaded into the Linux Kernel.\n");
            fclose(file);
            return 0;
        }
        else{
            printf("The rpmsg_pru module is NOT currently loaded.\n");
            fclose(file);
            return 2;
        }
    }
    else{
        return 3;
    }
}

void modprobe(){
    //Procedure to add all the related remoterpoc modules to the Linux Kernel

    modprobe_pru_rproc();
    modprobe_rpmsg_pru();
}

int rmmod(int n=0){
    //Procedure to remove the "pru_rproc" module from the Linux Kernel
    //Parameters:     0 - NOT Forcibly i.e. module won't be removed if any PRU is running
    //                Any other value - Remove FORCIBLY i.e. stop the PRUs and then remove the module
    //
    //Return values : 0 - Couldn't be removed as the PRUs were running
    //                1 - rmmod completed successfully
    int x = rmmod_pru_rproc(n);
    int y = rmmod_rpmsg_pru(n);
}

void make(char *path){
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

void modprobe_pru_rproc(){
    //Procedure to add the "pru_rproc" module to the Linux Kernel
    char rproc[10] = "pru_rproc";
    if (check_module(rproc) == 1){
        strcpy(command, "sudo modprobe pru_rproc");
        system(command);
        printf("loaded 'pru_rproc' module in the kernel.\n");
    }
}

void modprobe_rpmsg_pru(){
    //Procedure to add the "rpmsg_pru" module to the Linux Kernel

    char rpmsg[10] = "rpmsg_pru";
    if (check_module(rpmsg) == 2){
        strcpy(command, "sudo modprobe rpmsg_pru");
        system(command);
        printf("loaded 'rpmsg_pru' module in the kernel.\n");
        strcpy(command, "sudo modprobe virtio_rpmsg_bus");
        system(command);
        printf("loaded 'virtio_rpmsg_bus' module in the kernel.\n");
    }
}

int rmmod_pru_rproc(int n=0){
    //Procedure to remove the "pru_rproc" module from the Linux Kernel
    //Parameters:     0 - NOT Forcibly i.e. module won't be removed if any PRU is running
    //                Any other value - Remove FORCIBLY i.e. stop the PRUs and then remove the module
    //
    //Return values : 0 - Couldn't be removed as the PRUs were running
    //                1 - rmmod completed successfully
    strcpy(command, "sudo rmmod pru_rproc");
    char rproc[10] = "pru_rproc";
    if (!check_module(rproc) && (!strcmp(state(1), "offline") && !strcmp(state(2), "offline"))){
        system(command);
        printf("'pru_rproc' module removed.\n");
        return 1;
    }
    else if (!check_module(rproc) && (strcmp(state(1), "offline") || strcmp(state(2), "offline"))){
        if(n == 1){
            //forcibly
            stop(1);
            stop(2);
            system(command);
            printf("'pru_rproc' module removed.\n");
            return 1;
        }
        else{
            printf("Module couldn't be removed as the PRUs are currently running.\n");
            return 0;
        }
    }
    else if (check_module(rproc) == 1){
        printf("'pru_rproc' module is already removed.\n");
        return 1;
    }
}

int rmmod_rpmsg_pru(int n=0){
    //Procedure to remove the "rpmsg_pru" module from the Linux Kernel
    //Parameters: n = 0 - NOT Forcibly i.e. module won't be removed if any PRU is running
    //                Any other value - Remove FORCIBLY i.e. stop the PRUs and then remove the module
    //
    //Return values : 0 - Couldn't be removed as the PRUs were running
    //                1 - rmmod completed successfully
    strcpy(command, "sudo rmmod rpmsg_pru");
    char rpmsg[10] = "rpmsg_pru";
    if (!check_module(rpmsg) && (!strcmp(state(1), "offline") && !strcmp(state(2), "offline"))){
        system(command);
        printf("'rpmsg_pru' module removed.\n");
        strcpy(command, "sudo rmmod virtio_rpmsg_bus");
        system(command);
        printf("'virtio_rpmsg_bus' module removed.\n");
        return 1;
    }

    else if (!check_module(rpmsg) && (strcmp(state(1), "offline") || strcmp(state(2), "offline"))){
        if(n == 1){
            //forcibly
            printf("Debug 2");
            stop(1);
            stop(2);
            system(command);
            printf("'rpmsg_pru' module removed.\n");
            char command2[150];
            strcpy(command2, "sudo rmmod virtio_rpmsg_bus");
            system(command2);
            printf("'virtio_rpmsg_bus' module removed.\n");
            return 1;
        }
        else{
            printf("Module couldn't be removed as the PRUs are currently running.\n");
            return 0;
        }
    }
    else if (check_module(rpmsg) == 2){
        printf("'rpmsg_pru' module is already removed.\n");
        return 1;
    }
}

int send_msg(char *message, int n){
    //Function to write a message to the given PRU channel
    //      n = 0 => first PRU
    //      n = 1 => second PRU
    //      Return Values:
    //       result > 0: Successful
    //              < 0: Unsuccessful
    //int MAX_BUFFER_SIZE = 512;
    //char readBuf[MAX_BUFFER_SIZE];  
    char device[] = "/dev/rpmsg_pru";
    int result = 0;
    if (n == 0){
        char channel[] = "30";
        int length = (strlen(device)+strlen(channel)+1);
        char path[length] ;
        path[0] = '\0';   // ensures the memory is an empty string
        strcat(path,device);
        strcat(path,channel);
        //printf("The string is %s\n", path);
        int fd = open(path, O_RDWR);
        if (fd > 0){
            //printf("fd = %i\n", fd);
            printf("Opened the device, writing '%s'\n", message);
            result = write(fd, message , 13);
            //printf("Result: %i\n", result);
        }
        else{
            printf("Failed to open /dev/rpmsg30; hence can't write to the file; ensure that pru0 has been probed\n");
        }
        close(fd);
    }
    else if (n == 1){
        char channel[3] = "31";
        int length = (strlen(device)+strlen(channel)+1);
        char path[length] ;
        path[0] = '\0';   // ensures the memory is an empty string
        strcat(path,device);
        strcat(path,channel);
        //printf("The string is %s\n", path);
        int fd = open(path, O_RDWR);
        if (fd > 0){
             //printf("fd = %i\n", fd);
            printf("Opened the device, writing '%s'\n", message);
            result = write(fd, message , 13);
            //printf("Result: %i\n", result);
        }
        else {
            printf("Failed to open /dev/rpmsg31; hence can't write to the file; ensure that pru0 has been probed\n");
        }
        close(fd);
    }
    /*
     * If the RPMsg channel doesn't exist yet the character device
     * won't either.
     * Make sure the PRU firmware is loaded and that the rpmsg_pru
     * module is inserted.
     */
    /* The RPMsg channel exists and the character device is opened */
    return result;
}

char* get_msg(int n){

    int MAX_BUFFER_SIZE = 512;
    char* readBuf = new char[MAX_BUFFER_SIZE];  
    int result = 0;
    char device[] = "/dev/rpmsg_pru";
    if (n == 0){
        char channel[] = "30";
        int length = (strlen(device)+strlen(channel)+1);
        char path[length] ;
        path[0] = '\0';   // ensures the memory is an empty string
        strcat(path,device);
        strcat(path,channel);
        int fd = open(path, O_RDWR);
        if (fd > 0){
            int output = read(fd, readBuf, MAX_BUFFER_SIZE);
            //printf("Output from PRUs: %s\n\n", readBuf);
        }
        else {
            printf("Failed to open /dev/rpmsg30; hence can't read the file; ensure that pru0 has been probed\n");
            return NULL;
        }
        close(fd);
        return readBuf;
    }
    else if (n == 1){
        char channel[3] = "31";
        int length = (strlen(device)+strlen(channel)+1);
        char path[length] ;
        path[0] = '\0';   // ensures the memory is an empty string
        strcat(path,device);
        strcat(path,channel);
        int fd = open(path, O_RDWR);
        if (fd > 0){
            int output = read(fd, readBuf, MAX_BUFFER_SIZE);
            // printf("Output from PRUs: %s\n\n", readBuf);
        }
        else {
            printf("Failed to open /dev/rpmsg31; hence can't read the file; ensure that pru1 has been probed\n");
            return NULL;
        }
        close(fd);
        return readBuf;
    }
    
}
