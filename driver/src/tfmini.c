#include "tfmini.h"

static uint16_t next_id = 1;

static int is_valid_data(tfmini_data_t *data)
{
    uint16_t checksum = 0;
    
    for(int i = 0; i < sizeof(tfmini_data_t) - 1; i++)
        checksum += ((u8 *)data)[i];

    return (u8)checksum == data->checksum;
}

result_codes device_is_tfmini(struct usb_serial_port *port, uint8_t *tag)
{
    tfmini_data_t data;
    result_codes result;

    device_config_t config = {
        .baudrate = 115200,
        .bits_data = 8,
        .bits_parity = 0,
        .bits_stop = 1
    };
    
    result = device_config_uart(port, config);

    if (result != RESULT_OK)
        return RESULT_FALSE;

    for(int i = 0; i < 10; i++)
    {
        result = device_read(port, &data, sizeof(tfmini_data_t));

        if (result != RESULT_OK)
            continue;
        
        if(!is_valid_data(&data))
            continue;

        if(data.tag != TFMINI_TAG || data.re_tag != TFMINI_TAG)
            continue;

        *tag = data.tag;

        return RESULT_TRUE;
    }
        
    return RESULT_FALSE;
}

struct device** device_add_tfmini(struct class *device_class, uint16_t id, uint8_t *devices_objects_count)
{
    struct device **devices_objects = kmalloc(sizeof(struct devices*) * 3, GFP_KERNEL);
    
    devices_objects[0] = device_create(device_class, NULL, MKDEV(0, 0), NULL, "%s_%d_distance", TFMINI_NAME, id);
    devices_objects[1] = device_create(device_class, NULL, MKDEV(0, 0), NULL, "%s_%d_strength", TFMINI_NAME, id);
    devices_objects[2] = device_create(device_class, NULL, MKDEV(0, 0), NULL, "%s_%d_signal_quality", TFMINI_NAME, id);

    *devices_objects_count = 3;

    return devices_objects;
}

uint16_t device_tfmini_get_new_id(void)
{
    return next_id++;
}