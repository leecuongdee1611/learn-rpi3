cd source

echo "Loading the kernel module"
sudo insmod static_alloc.ko

echo "Useful command such as:"
echo "lsmod"
echo "dmesg"
echo "cat /proc/devices"
