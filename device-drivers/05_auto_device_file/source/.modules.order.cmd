cmd_/home/nn/workspace/learn-rpi3/device-drivers/05_auto_device_file/source/modules.order := {   echo /home/nn/workspace/learn-rpi3/device-drivers/05_auto_device_file/source/auto_device_file.ko; :; } | awk '!x[$$0]++' - > /home/nn/workspace/learn-rpi3/device-drivers/05_auto_device_file/source/modules.order