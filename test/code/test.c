#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

int main(void){
    printf("Started executing!\n");

    char command[200];
//    strcpy(command, "touch setup1.sh");
  //  system(command);
  //  strcpy(command, "echo #!/bin/bash > setup1.sh");
  //  system(command);
  //  strcpy(command, "echo export PRUN=0 > setup1.sh");
   // system(command);
   // strcpy(command, "echo export TARGET=hello > setup1.sh");
   // system(command);
   // strcpy(command, "chmod +x setup1.sh");
   // system(command);
    strcpy(command, "ls -l `which sh`");
    system(command);
   // strcpy(command, "echo PRUN=$PRUN");
   // system(command);
   // strcpy(command, "echo TARGET=$TARGET");
   // system(command);

   // strcpy(command, "echo none > /sys/class/leds/beaglebone\:green\:usr3/trigger");
   // system(command);

    printf("Completed execution!\n");

    return 0;
}
