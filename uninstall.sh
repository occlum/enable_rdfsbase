#!/bin/bash

sudo /sbin/modprobe -r enable_rdfsbase
sudo rm -rf "/lib/modules/"`uname -r`"/kernel/drivers/occlum"
sudo /sbin/depmod
if [ -e "/etc/modules" ]; then
    # Ubuntu
    sudo /bin/sed -i '/^enable_rdfsbase$/d' /etc/modules
elif [ -d "/etc/modules-load.d" ]; then
    # CentOS
    sudo rm -f /etc/modules-load.d/enable_rdfsbase.conf
fi
