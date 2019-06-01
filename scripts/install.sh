#!/bin/bash

# This script will install everything included in the repository

# For the shortened terminal commands:
chmod +x short-commands.sh
./short-commands.sh
source ~/.bashrc

# Move the cpruss.h header file to /usr/local/include to that it is accessible from any C program
sudo cp ../libraries/C/cpruss.h /usr/local/include
