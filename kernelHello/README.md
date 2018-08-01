# KernelModule

To install this module, get it ready with run the command:
make -C [headers location] M=$(pwd) modules

Install module with:
sudo insmod hello.ko

Check outcome with dmesg

Uninstall with sudo rmmod hello

Check outcome with dmesg
