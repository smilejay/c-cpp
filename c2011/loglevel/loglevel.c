#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for log level */
#include <linux/init.h>         /* Needed for the macros */
 
MODULE_AUTHOR("Jay, <Jay's email> ");
MODULE_DESCRIPTION("To test: console log level.");
MODULE_LICENSE("GPL");
MODULE_VERSION("Version-0.0.1");
 
static int __init hello_start(void)
{
printk(KERN_INFO "Loading loglevel module...\n");
printk(KERN_INFO "Hello, Jay.\n");
printk(KERN_EMERG "------------------------------------\n");

printk(KERN_EMERG "Hello, EMERG.\n");
printk(KERN_ALERT "Hello, ALERT.\n");
printk(KERN_CRIT "Hello, CRIT.\n");
printk(KERN_ERR "Hello, ERR.\n");
printk(KERN_WARNING"Hello, WARNING.\n");
printk(KERN_NOTICE "Hello, NOTICE.\n");
printk(KERN_INFO "Hello, INFO.\n");
printk(KERN_DEBUG "Hello, DEBUG.\n");

printk(KERN_EMERG "------------------------------------\n");

return 0;
}
 
static void __exit hello_end(void)
{
printk(KERN_INFO "Goodbye, Jay.\n");
}
 
module_init(hello_start);
module_exit(hello_end);
