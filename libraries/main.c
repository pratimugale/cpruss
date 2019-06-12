#include "cpruss.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define DEVICE_NAME "/dev/rpmsg_pru31"

int main(){

    //start(1);
    //char temp[48] = "/tmp/pru0-gen/hello.out";
    //load_firmware(temp, 0);

    char device[] = "/dev/rpmsg_pru";
    char channel[] = "31";
    
    int length = (strlen(device)+strlen(channel)+1);
    char path[length] ;
    path[0] = '\0';   // ensures the memory is an empty string
    strcat(path,device);
    strcat(path,channel);
    printf("The string is %s\n", path);

    int fd = open(path, O_RDWR);
    printf("fd = %i\n", fd);
    printf("Opened the device, writing 'pratim'");

    int result = write(fd, "pratim", 14);
    printf("Result: %i\n", result);

    char readBuf[10];
    int output = read(fd, readBuf, 10);
    printf("Output from PRUs: %s\n\n", readBuf);
    return 0;
}
