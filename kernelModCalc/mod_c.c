#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int add_values(void);
int substract_values(void);

static char *username = "Default user name";

module_param(username, charp, S_IRUGO);

static int module_c_init(void){
  printk(KERN_DEBUG "Module c init\n");
  printk(KERN_DEBUG "Hello %s\n", username);
  printk(KERN_DEBUG "Add values: %d\n", add_values());
  printk(KERN_DEBUG "Substract values: %d\n", substract_values());
  return 0;
}

static void module_c_exit(void){
  printk(KERN_DEBUG "Removing module b\n");
}

module_init(module_c_init);
module_exit(module_c_exit);
