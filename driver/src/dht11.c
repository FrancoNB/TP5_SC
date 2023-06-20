#include "dht11.h"

static int is_valid_data(dht11_data_t *data)
{
    uint16_t checksum = 0;
    
    for(int i = 0; i < sizeof(dht11_data_t) - 1; i++)
        checksum += ((u8 *)data)[i];

    return (u8)checksum == data->checksum;
}

result_codes is_dht11(struct usb_serial_port *port)
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

        return DEVICE_DHT11;
    }

    return RESULT_FALSE;
}

