cmd_/home/nn/workspace/learn-rpi3/device-drivers/04_device_number/source/modules.order := {   echo /home/nn/workspace/learn-rpi3/device-drivers/04_device_number/source/static_alloc.ko; :; } | awk '!x[$$0]++' - > /home/nn/workspace/learn-rpi3/device-drivers/04_device_number/source/modules.order