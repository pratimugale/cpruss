#!/bin/bash

# These are a set of commands that will be able to control the PRUs directly without having to go to the directory

echo "alias pru1start='echo start | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state'" >> ~/.bashrc
echo "alias pru2start='echo start | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state'" >> ~/.bashrc
echo "alias pru1stop='echo stop | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state'" >> ~/.bashrc
echo "alias pru2stop='echo stop | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state'" >> ~/.bashrc
echo "alias pru1restart='echo stop | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state && echo start | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a334000.pru/remoteproc/remoteproc1/state'" >> ~/.bashrc
echo "alias pru2restart='echo stop | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state && echo start | sudo tee /sys/devices/platform/ocp/4a326004.pruss-soc-bus/4a300000.pruss/4a338000.pru/remoteproc/remoteproc2/state'" >> ~/.bashrc
