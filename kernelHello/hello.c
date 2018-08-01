#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

static int hello_init(void){
  printf(KERN_DEBUG "Hello World!\n");
  return 0;
}

static void hello_exit(void){
  printf(KERN_DEBUG "Goodbye World!\n");
  return 0;
}

module_init(hello_init);
module_exit(hello_exit);
