# Introduction

This is a Linux kernel module that enables RDFSBASE, WRFSBASE, RDGSBASE, WRGSBASE instructions on x86. These instructions are disabled by default on Linux. They can be enabled by setting the 16th bit of CR4, i.e., CR4.FSGSBASE.

# How to Build

To compile the kernel module, run the following command

    make

# How to Use

To enable RDFSBASE instruction and its friends, run the following command

    make install

To disable RDFSBASE instruction and its friends, run the following command

    make uninstall
