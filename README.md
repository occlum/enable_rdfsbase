**SECURITY NOTICE: This kernel module is intended for evaluation only, NOT in production!** Enabling `rdfsbase`-family instructions in the way shown in this kernel module creates a full unpriviledged root hole in the Linux kernel. The Linux kernel community is actively working on a patchset that does `rdfsbase` enabling in a secure way. And hopefully, we shall see the patchset merged in the near future. For more information, see [a LWN post on FSGSBASE patch series](https://lwn.net/Articles/821723/) and [discussions about the patchset on Linux mailing list](https://lwn.net/ml/linux-kernel/20200511045311.4785-1-sashal@kernel.org/).

# Introduction

This is a Linux kernel module that enables RDFSBASE, WRFSBASE, RDGSBASE, WRGSBASE instructions on x86. These instructions are disabled by default on Linux. They can be enabled by setting the 16th bit of CR4, i.e., CR4.FSGSBASE.

# How to Build

To compile the kernel module, run the following command

    make

To enable RDFSBASE instruction and its friends until the next OS reboot, run the following command

    make install

To disable RDFSBASE instruction and its friends until the next OS reboot, run the following command

    make uninstall

# How to Install

To enable RDFSBASE permanently (i.e., enabled even after the next OS reboot), run

    ./install.sh

To uninstall, run

    ./uninstall.sh

# Kernel Compatibility

This code has been tested with Linux kernel 4.15. It may or may not work with newer or older versions of Linux kernel.
