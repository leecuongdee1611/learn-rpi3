cmd_/home/nn/workspace/learn-rpi3/device-drivers/06_cdev_file_operation/source/Module.symvers := sed 's/\.ko$$/\.o/' /home/nn/workspace/learn-rpi3/device-drivers/06_cdev_file_operation/source/modules.order | scripts/mod/modpost -m -a  -o /home/nn/workspace/learn-rpi3/device-drivers/06_cdev_file_operation/source/Module.symvers -e -i Module.symvers   -T -