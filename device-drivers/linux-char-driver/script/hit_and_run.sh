#!/bin/bash
DRIVER=../driver
USER=../user_program

echo "*** Build the vchar_driver"
cd $DRIVER
sudo make clean
sudo make all

echo "*** Load the vchar_driver"
sudo insmod vchar_driver.ko

echo "*** Check the vchar_driver installed" 
dmesg | grep tail

echo "*** Run user program"
cd $USER
make clean
make all
./user_test

echo "*** Unload the vchar_driver"
sudo rmmod vchar_driver