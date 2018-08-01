#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int get_a(void);
int get_b(void);

static int module_b_init(void){
  printk(KERN_DEBUG "Module b init\n");


  return 0;
}

static void module_b_exit(void){
  printk(KERN_DEBUG "Removing module b\n");
}

int substract_values(void){
  return get_a()-get_b();
}

int add_values(void){
  return get_a()+get_b();
}

EXPORT_SYMBOL_GPL(substract);
EXPORT_SYMBOL_GPL(add);

module_init(module_b_init);
module_exit(module_b_exit);
