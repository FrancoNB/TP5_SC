#include "common.h"
#include "dht11.h"
#include "tfmini.h"
#include "device_queue.h"

#define SUPPORTED_DEVICES_COUNT 2

#define VENDOR_ID 0x10C4
#define PRODUCT_ID_1 0xEA60
#define PRODUCT_ID_2 0xEA70

const char* result_codes_string[] = {
    "Scan device failed",
    "Device read failed",
    "Device connection failed",
    "Device unknown",
    "Result false",
    "Result true",
    "Result ok",
    "DHT11",
    "TFMINI"
};

result_codes (*support_testers[SUPPORTED_DEVICES_COUNT])(struct usb_serial_port*) = {
    is_dht11,
    is_tfmini
};

static result_codes is_supported_device(struct usb_serial_port *port)
{
    for(int i = 0; i < SUPPORTED_DEVICES_COUNT; i++)
    {
        result_codes result = support_testers[i](port);

        if(result != RESULT_FALSE)
            return result;
    }

    return RESULT_FALSE;
}

static int detection_routine(struct usb_device *dev, void *data)
{
    struct usb_interface *interface;
    struct usb_serial *serial;
    struct usb_serial_port *port;
    result_codes result;

    if(dev->descriptor.idVendor != VENDOR_ID || (dev->descriptor.idProduct != PRODUCT_ID_1 && dev->descriptor.idProduct != PRODUCT_ID_2))
        return 0;

    for (int i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) 
    {
        interface = dev->actconfig->interface[i];

        if(interface == NULL)
        {
            pr_err("Failed to get interface: %s\n", dev->product);
            continue;
        }

        serial = usb_get_intfdata(interface);

        if (!serial) 
        {
            pr_err("Failed to get serial: %s\n", dev->product);
            continue;
        }

        for (int j = 0; j < serial->num_ports; j++) 
        {
            port = serial->port[j];
            
            if(port == NULL)
            {
                pr_err("Failed to get port: %s\n", dev->product);
                continue;
            }

            result = is_supported_device(port);

            if(result != RESULT_FALSE)
            {
                pr_info("Device detected: %s\n", result_codes_string[result + STRING_CONVERT_OFFSET]);

                //device_queue_add(port, result);
            }
        }
    }

    return 0;
}

static int usb_device_event(struct notifier_block *nb, unsigned long action, void *data)
{
    struct usb_device *dev = (struct usb_device *)data;

    if (action == USB_DEVICE_ADD)
        detection_routine(dev, NULL);

    return NOTIFY_OK;
}

static struct notifier_block usb_device_nb = {
    .notifier_call = usb_device_event,
};

static int __init drv_init(void)
{
    usb_register_notify(&usb_device_nb);

    usb_for_each_dev(NULL, detection_routine);

    pr_info("Sensors serial module initialized\n");
    
    return 0;
}

static void __exit drv_exit(void)
{
    usb_unregister_notify(&usb_device_nb);
    
    device_queue_destroy();
    
    pr_info("Serial reader module exited\n");
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bottini, Franco Nicolas");
MODULE_AUTHOR("Robledo, Valentín");
MODULE_AUTHOR("Lencina, Aquiles Benjamin");
MODULE_DESCRIPTION("CP210x sensors interfacing driver");