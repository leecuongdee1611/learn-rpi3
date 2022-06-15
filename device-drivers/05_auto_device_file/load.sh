cd source

echo "Loading the kernel module"
sudo insmod auto_device_file.ko

echo "Useful command such as:"
echo "lsmod"
echo "dmesg"
echo "cat /proc/devices"
