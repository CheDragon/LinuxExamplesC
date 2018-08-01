#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");

static int value_a = 0;
static int value_b = 0;

module_param(value_a, int, S_IRUGO);
module_param(value_b, int, S_IRUGO);

static int module_a_init(void){
  printk(KERN_DEBUG "MODULE init, values: a=%d, b=%d\n", value_a, value_b);
  return 0;
}

static void module_a_exit(void){
  printk(KERN_DEBUG "Module a removed\n");
}

int get_a(void){
  return value_a;
}

int get_b(void){
  return value_b;
}

EXPORT_SYMBOL_GPL(get_a);
EXPORT_SYMBOL_GPL(get_b);

module_init(module_a_init);
module_exit(module_a_exit);
