cmd_/home/nn/Yocto-Cuong/learn-rpi3/rpi3-led-driver/driver/Module.symvers := sed 's/\.ko$$/\.o/' /home/nn/Yocto-Cuong/learn-rpi3/rpi3-led-driver/driver/modules.order | scripts/mod/modpost -m -a  -o /home/nn/Yocto-Cuong/learn-rpi3/rpi3-led-driver/driver/Module.symvers -e -i Module.symvers   -T -