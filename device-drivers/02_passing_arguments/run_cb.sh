sudo chmod 775 /sys/module/main/parameters/cb_valueETX
sudo sh -c "echo 5 > /sys/module/main/parameters/cb_valueETX"
dmesg
