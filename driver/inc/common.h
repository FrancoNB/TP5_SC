#ifndef __COMMON_H__
#define __COMMON_H__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/tty.h>
#include <linux/usb.h>
#include <linux/usb/serial.h>

#define STRING_CONVERT_OFFSET 4

typedef enum
{
    DEVICE_TFMINI = 4,
    DEVICE_DHT11 = 3,
    RESULT_OK = 2,
    RESULT_TRUE = 1,
    RESULT_FALSE = 0,
    DEVICE_UNKNOWN = -1,
    DEVICE_CONN_FAILED = -2,
    DEVICE_READ_FAILED = -3,
    DEVICE_SCAN_FAILED = -4
} result_codes;

#endif // __COMMON_H__