#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("kprobe that prints a message when execve is called");

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

static struct kprobe kp;

static int handler_pre(struct kprobe* p, struct pt_regs* regs) {
  printk(KERN_INFO "kprobe: execve called!\n");
  return 0;
}

static int __init kprobe_init(void) {
  int ret;

  kp.symbol_name = "__x64_sys_execve";
  kp.pre_handler = handler_pre;

  ret = register_kprobe(&kp);
  if (ret < 0) {
    printk(KERN_INFO "register_kprobe failed, returned %d\n", ret);
    return ret;
  }

  printk(KERN_INFO "kprobe registered at %p\n", kp.addr);
  return 0;
}

static void __exit kprobe_exit(void) {
  unregister_kprobe(&kp);
  printk(KERN_INFO "kprobe unregistered\n");
}

module_init(kprobe_init);
module_exit(kprobe_exit);

MODULE_LICENSE("GPL");