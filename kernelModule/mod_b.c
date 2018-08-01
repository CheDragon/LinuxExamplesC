#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int add_values(void);

static int module_b_init(void){
  printk(KERN_DEBUG "Module b init\n");
  printk(KERN_DEBUG "Add values: %d\n", add_values());
  return 0;
}

static void module_b_exit(void){
  printk(KERN_DEBUG "Removing module b\n");
}

module_init(module_b_init);
module_exit(module_b_exit);
