#include <linux/init.h>    // included for __init and __exit macros
#include <linux/kernel.h>  // included for KERN_INFO
#include <linux/module.h>  // included for all kernel modules

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple hello world kernel module");

/*
Load the module and run it straightaway:

sudo insmod kernel_example.ko

Check that it is loaded:

lsmod | grep kernel_example

View the message:

sudo dmesg

See module information:

modinfo ./kernel_example.ko

Remove the module

sudo rmmod kernel_example
*/

static int __init hello_init(void) {
  printk(KERN_INFO "Hello World!\n");
  return 0;
}

static void __exit hello_exit(void) {
  printk(KERN_INFO "Closing down the kernel module.\n");
}

module_init(hello_init);
module_exit(hello_exit);
