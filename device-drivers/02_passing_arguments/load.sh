cd source

echo "Loading the kernel module"
# sudo insmod main.ko
sudo insmod main.ko valueETX=14 nameETX="Cuong" arr_valueETX=100,102,104,106

echo "Seeing the modules were inserted"
lsmod

echo "Shown the prints in the init function"
dmesg
