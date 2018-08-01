# KernelModule

To run this run the command:
make -C [headers location] M=$(pwd) modules

Install module with:
sudo insmod mod_a.ko value_a=[number] value_b=[number]

Check outcome with dmesg

Uninstall with sudo rmmod mod_a

Check outcome with dmesg

Install then mod_b using the same procedure (Edit Makefile before)

Check the result with dmesg
