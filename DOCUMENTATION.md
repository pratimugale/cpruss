# Documentation
Rpmsg is a virtio-based messaging bus that allows kernel drivers to communicate
with remote processors available on the system. In turn, drivers could then
expose appropriate user space interfaces, if needed.
## Installation
- To install everything, run the `install.sh` file in `scripts` directory. 
- Then log out and log in again to your device so that the changes are made. (as .bashrc is executed at the time of logging in).

## Uninstall
- Run the `uninstall.sh` script in `scripts` directory. (`$ source uninstall.sh`)

## Parts Installation 

1. The `short-commands.sh` bash script present in `scripts` directory: <br> Run this `$ source short-commands.sh` command in the terminal.<br> On executing this command, some lines will be appended to the `.bashrc` file which is present in your user directory. The new .bashrc file will be installed the next time you log out and log back in, but if you want it installed now, you can just source the file. `$ source ~/.bashrc`
