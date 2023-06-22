#include "dht11.h"

static uint16_t next_id = 1;

static int is_valid_data(dht11_data_t *data)
{
    uint16_t checksum = 0;
    
    for(int i = 0; i < sizeof(dht11_data_t) - 1; i++)
        checksum += ((u8 *)data)[i];

    return (u8)checksum == data->checksum;
}

result_codes device_is_dht11(struct usb_serial_port *port, uint8_t *tag)
{
    dht11_data_t data;
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
        result = device_read(port, &data, sizeof(dht11_data_t));

        if (result != RESULT_OK)
            continue;
        
        if(!is_valid_data(&data))
            continue;

        if(data.tag != DHT11_TAG || data.re_tag != DHT11_TAG)
            continue;

        *tag = data.tag;

        return RESULT_TRUE;
    }

    return RESULT_FALSE;
}

struct device** device_add_dht11(struct class *device_class, uint16_t id, uint8_t *devices_objects_count)
{
    struct device **devices_objects = kmalloc(sizeof(struct devices*) * 3, GFP_KERNEL);
       
    devices_objects[0] = device_create(device_class, NULL, MKDEV(0, 0), NULL, "%s_%d_temperature", DHT11_NAME, id);
    devices_objects[1] = device_create(device_class, NULL, MKDEV(0, 0), NULL, "%s_%d_humidity", DHT11_NAME, id);
    devices_objects[2] = device_create(device_class, NULL, MKDEV(0, 0), NULL, "%s_%d_heat_index", DHT11_NAME, id);

    *devices_objects_count = 3;
    
    return devices_objects;
}

uint16_t device_dht11_get_new_id(void)
{
    return next_id++;
}
