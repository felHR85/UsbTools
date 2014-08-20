/*
 Created by felhr (felhr85@gmail.com)
 */

#ifndef usbtool_usbfacade_h
#define usbtool_usbfacade_h

#include "parser.h"

typedef struct UsbDevice
{
    uint16_t id_vendor;
    uint16_t id_product;
    
}UsbDevice;

typedef struct UsbResponse
{
    int response; // 0 error , 1 ok
    uint8_t bm_request_type;
    uint8_t b_request;
    uint16_t w_value;
    uint16_t w_index;
    uint16_t w_length;
    
}UsbResponse;

int list_usb_devices(UsbDevice*** devices);
int setup_packet(UsbParser * parser, UsbResponse*** responses);
void free_usb_devices(UsbDevice*** devices);


#endif
