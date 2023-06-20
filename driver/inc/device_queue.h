#ifndef __DEVICE_QUEUE_H__
#define __DEVICE_QUEUE_H__

#include "common.h"

void device_queue_add(struct usb_serial_port *port, uint8_t tag);
void device_queue_remove(struct usb_serial_port *port);
void device_queue_destroy(void);

#endif // __DEVICE_QUEUE_H__