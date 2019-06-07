# PRU-RPMSG EXAMPLE

This example is based on the `lab-5` of the `pru-software-support-package`.<br>
Code Repository: http://git.ti.com/pru-software-support-package/pru-software-support-package/trees/master<br>
Also explained on: http://processors.wiki.ti.com/index.php/PRU_Training:_Hands-on_Labs (But using CCS - Code Composer Studio)<br>

To run the starter RPMsg example, follow the following steps:<br>

Few points: 
* My Kernel: 4.14.71-ti-r80 (use `$ uname -r` to find out kernel version)
* Debian Version: BeagleBoard.org Debian Image 2018-10-07 (use `$ cat /etc/issue` to find)

1. Clone the repo from TI's website: http://git.ti.com/pru-software-support-package/pru-software-support-package/trees/master
2. `$ cd pru-software-support-package/labs/lab_5/solution/am335x/PRU_RPMsg_Echo_Interrupt1`.
3. Set the PRU_CGT variable `$ export PRU_CGT = /usr/share/ti/cgt-pru`
4. Run `make` and `sudo copy` the generated .out file to `/lib/firmware/am335x-pru1-fw`. We will be using the 2nd PRU in this example.(Would have used `am335x-pru0-fw` for 1st PRU).
5. Make sure that the RPMsg Modules are loaded into the kernel i.e.: <br>
   * `$ sudo modprobe pru_rproc`
   * `$ sudo modprobe rpmsg_pru`
   * `$ sudo modprobe virtio_rpmsg_bus`<br>
   `lsmod` should have the following entris now: <br>
   * `virtio_rpmsg_bus`
   * `rpmsg_pru`
   * `rpmsg_core`
   * `pruss_soc_bus`
   * `pru_rproc`
   * `pruss`
   * `pruss_intc`
   These can easily be found using `$ lsmod | grep pru` & `$ lsmod | grep rpmsg`.<br>
6. cd into `/sys/class/remoteproc`<br>
   `ls`: remoteproc1: for PRU1, remoteproc2: for PRU2<br> _The entry `remoteproc0` relates to the Wakeup M3 (CM3) remoteproc driver that helps with low power tasks on the Cortex M3 co-processor in the AM33xx family of devices-**it has no role in controlling the PRU-ICSS**._
7. cd into `remoteproc2`.
8. `$ echo amm335x-pru1-fw | sudo tee firmware` - to load the firmware. In earlier versions, this process was different.
9. `$ echo start | sudo tee state` - to start the second PRU on which we are working on.
10. `$ dmesg` or `$ dmesg | grep pru` - The last few lines of dmesg should be something like this: <br> 
[   76.778231] pruss 4a300000.pruss: creating PRU cores and other child platform devices<br>
[   76.811666] remoteproc remoteproc1: 4a334000.pru is available<br>
[   76.811792] pru-rproc 4a334000.pru: PRU rproc node /ocp/pruss_soc_bus@4a326004/pruss@0/pru@34000 probed successfully<br>
[   76.813392] remoteproc remoteproc2: 4a338000.pru is available<br>
[   76.813498] pru-rproc 4a338000.pru: PRU rproc node /ocp/pruss_soc_bus@4a326004/pruss@0/pru@38000 probed successfully<br>
[ 2035.360460] remoteproc remoteproc2: powering up 4a338000.pru<br>
[ 2035.371491] remoteproc remoteproc2: Booting fw image am335x-pru1-fw, size 74032<br>
[ 2035.374631] pruss 4a300000.pruss: configured system_events[63-0] = 0x00000000.000c0000<br>
[ 2035.374652] pruss 4a300000.pruss: configured intr_channels = 0x0000000a host_intr = 0x0000000a<br>
[ 2035.383501] virtio_rpmsg_bus virtio0: creating channel rpmsg-pru addr 0x1f<br>
[ 2035.384526] rpmsg_pru virtio0.rpmsg-pru.-1.31: new rpmsg_pru device: /dev/rpmsg_pru31<br>
[ 2035.385431] virtio_rpmsg_bus virtio0: rpmsg host is online<br>
[ 2035.385594] remoteproc remoteproc2: registered virtio0 (type 7)<br>
[ 2035.385605] remoteproc remoteproc2: remote processor 4a338000.pru is now up<br>


##Sources:
* Derek Molly's Exploring BeagleBone<br>
* https://groups.google.com/d/msg/beagleboard/4P9NdglojBo/qqizuGCZAQAJ
