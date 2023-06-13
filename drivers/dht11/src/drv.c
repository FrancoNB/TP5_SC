/**
 * @file drv.c
 * 
 * @author
 * 
 * Bottini, Franco Nicolas - Robledo, Valentín - Lencina, Aquiles Benjamín
 * 
 * Group: CLOVERS
*/

#include <linux/kernel.h>
#include <linux/module.h>

static int __init drv_init(void)
{
    printk(KERN_INFO "DHT11: Initializing...\n");
    
    return 0;
}

static void __exit drv_exit(void)
{
    printk(KERN_INFO "DHT11: Exiting...\n");
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bottini, Franco Nicolas");
MODULE_AUTHOR("Robledo, Valentín");
MODULE_AUTHOR("Lencina, Aquiles Benjamin");
MODULE_DESCRIPTION("DHT11 Driver");