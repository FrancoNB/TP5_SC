/**
 * @file drv.c
 * 
 * @author
 * 
 * Bottini, Franco Nicolas - Robledo, Valentín - Lencina, Aquiles Benjamín
 * 
 * Group: CLOVERS
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

int drv_init(void)
{
    printk(KERN_INFO "DHT11: Initializing...\n");
    
    return 0;
}

void drv_exit(void)
{
    printk(KERN_INFO "DHT11: Exiting...\n");
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franco Bottini, Valentín Robledo, Aquiles Lencina");
MODULE_DESCRIPTION("DHT11 Driver");