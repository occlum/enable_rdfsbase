#!/bin/bash

sudo mkdir -p "/lib/modules/"`uname -r`"/kernel/drivers/occlum"
sudo cp enable_rdfsbase.ko "/lib/modules/"`uname -r`"/kernel/drivers/occlum"

if [ -e "/etc/modules" ]; then
    # Ubuntu
    sudo sh -c "cat /etc/modules | grep -Fxq isgx || echo enable_rdfsbase >> /etc/modules"
elif [ -d "/etc/modules-load.d" ]; then
    # CentOS
    sudo sh -c "echo \"enable_rdfsbase\" > /etc/modules-load.d/enable_rdfsbase.conf"
fi
sudo /sbin/depmod
sudo /sbin/modprobe enable_rdfsbase
