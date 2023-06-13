/**
 * @file drv.c
 * 
 * @author
 * 
 * Bottini, Franco Nicolas - Robledo, Valentín - Lencina, Aquiles Benjamín
 * 
 * Group: CLOVERS
*/

<<<<<<< HEAD
#include <linux/kernel.h>
#include <linux/module.h>

static int __init drv_init(void)
=======
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

int drv_init(void)
>>>>>>> 13f0747b3e7b4afb1a0f12bdda31be9553028509
{
    printk(KERN_INFO "DHT11: Initializing...\n");
    
    return 0;
}

<<<<<<< HEAD
static void __exit drv_exit(void)
=======
void drv_exit(void)
>>>>>>> 13f0747b3e7b4afb1a0f12bdda31be9553028509
{
    printk(KERN_INFO "DHT11: Exiting...\n");
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");
<<<<<<< HEAD
MODULE_AUTHOR("Bottini, Franco Nicolas");
MODULE_AUTHOR("Robledo, Valentín");
MODULE_AUTHOR("Lencina, Aquiles Benjamin");
=======
MODULE_AUTHOR("Franco Bottini, Valentín Robledo, Aquiles Lencina");
>>>>>>> 13f0747b3e7b4afb1a0f12bdda31be9553028509
MODULE_DESCRIPTION("DHT11 Driver");