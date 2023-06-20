#ifndef __DHT11_H__
#define __DHT11_H__

#include "common.h"
#include "device.h"

#define DHT11_TAG 0x73

typedef struct __attribute__((packed))
{
    uint8_t tag;
    uint8_t re_tag;
    uint8_t temperature;
    uint8_t humidity;
    uint8_t heat_index;
    uint8_t checksum;
} dht11_data_t;

result_codes is_dht11(struct usb_serial_port *port);

#endif // __DHT11_H__