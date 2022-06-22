cd driver

echo "Loading the kernel module"
sudo insmod led-sysfs.ko

echo "Useful command:"
echo "lsmod"
echo "dmesg"
