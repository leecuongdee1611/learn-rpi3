cd source

echo "Loading the kernel module"
sudo insmod gpio_basic.ko

echo "Useful command:"
echo "lsmod"
echo "dmesg"
echo "cat /proc/devices"
