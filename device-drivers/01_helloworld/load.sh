cd source

echo "Loading the kernel module"
sudo insmod hello_world_module.ko

echo "Seeing the modules were inserted"
lsmod

echo "Shown the prints in the init function"
dmesg
