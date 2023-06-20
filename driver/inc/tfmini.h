#ifndef __TFMINI_H__
#define __TFMINI_H__

#include "common.h"
#include "device.h"

#define TFMINI_TAG 0x59

typedef struct __attribute__((packed))
{
    uint8_t  tag;
    uint8_t  re_tag;
    uint16_t distance;
    uint16_t strength;
    uint8_t  reserved;
    uint8_t  signal_quality;
    uint8_t  checksum;
} tfmini_data_t;

result_codes is_tfmini(struct usb_serial_port *port);

#endif // __TFMINI_H__