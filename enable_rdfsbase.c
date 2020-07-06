/* SPDX-License-Identifier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * A kernel module to enable RDFSBASE family instructions on x86.
 *
 * Copyright (c) 2018-2019 Intel Corp. All rights reserved.
 * Author: Hongliang Tian <tatetian@gmail.com>
 */

#include <linux/compiler.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <asm/tlbflush.h>
#include <asm/smp.h>

#define LOG(...)            printk(KERN_INFO "enable_rdfsbase: " __VA_ARGS__)

#define CR4_FSGSBASE_BIT    (16)
#define CR4_FSGSBASE_MASK   (1UL << CR4_FSGSBASE_BIT)


static void set_cr4_fsgsbase(void *_unused)
{
#if KERNEL_VERSION(4, 0, 0) <= LINUX_VERSION_CODE
	cr4_set_bits(CR4_FSGSBASE_MASK);
#else
	unsigned long cr4_val;

	cr4_val = read_cr4();
	if ((cr4_val | CR4_FSGSBASE_MASK) != cr4_val) {
		cr4_val |= CR4_FSGSBASE_MASK;
		write_cr4(cr4_val);
	}
#endif
}

static void clear_cr4_fsgsbase(void *_unused)
{
#if KERNEL_VERSION(4, 0, 0) <= LINUX_VERSION_CODE
	cr4_clear_bits(CR4_FSGSBASE_MASK);
#else
	unsigned long cr4_val;

	cr4_val = read_cr4();
	if ((cr4_val & ~CR4_FSGSBASE_MASK) != cr4_val) {
		cr4_val &= ~CR4_FSGSBASE_MASK;
		write_cr4(cr4_val);
	}
#endif
}

int __init enable_rdfsbase_init(void)
{
	int cpu;
	int err;

	LOG("Loaded\n");

	if (!boot_cpu_has(X86_FEATURE_FSGSBASE)) {
		LOG("FSGSBASE feature is not supported by this CPU!\n");
		return -ENODEV;
	}

	for_each_online_cpu(cpu) {
		err = smp_call_function_single(cpu, set_cr4_fsgsbase, NULL, 1);

		if (err)
			LOG("Fail to set CR4.FSGSBASE on CPU %d\n", cpu);
		else
			LOG("RDFSBASE and its friends are now enabled on CPU %d\n", cpu);
	}

	return 0;
}

void __exit enable_rdfsbase_exit(void)
{
	int cpu;
	int err;

	for_each_online_cpu(cpu) {
		err = smp_call_function_single(cpu, clear_cr4_fsgsbase, NULL, 1);

		if (err)
			LOG("Fail to clear CR4.FSGSBASE on CPU %d\n", cpu);
		else
			LOG("RDFSBASE and its friends are now disabled on CPU %d\n", cpu);
	}

	LOG("Unloaded\n");
}

module_init(enable_rdfsbase_init);
module_exit(enable_rdfsbase_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Hongliang Tian, Intel Corp.");
MODULE_DESCRIPTION("Enable RDFSBASE family instructions on x86");
