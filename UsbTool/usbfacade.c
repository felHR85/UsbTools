/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include "usbfacade.h"
#include "parser.h"
#include </opt/local/include/libusb-1.0/libusb.h>

static int open_usb_session(libusb_context** context)
{
    return libusb_init(context);
}

static void close_usb_session(libusb_context* context)
{
    libusb_exit(context);
}

static libusb_device* get_device(libusb_device** devices,ssize_t count,char* vid, char* pid)
{
    libusb_device* device;
    
    int i = 0;
    while(i <= count - 1)
    {
        struct libusb_device_descriptor descriptor;
        libusb_get_device_descriptor(devices[i],&descriptor);
        // TO-DO check given pid and vid
        // char vid and pid (Hex values) to uint8_t is not trivial. Need a function for that!!!!
        i++;
    }
    
    return device;
}


int setup_packet(UsbParser* parser, UsbResponse*** requests)
{
    libusb_context* context;
    libusb_device** devices;
    
    if(open_usb_session(&context) == 0) // LibUsb session opened
    {
        ssize_t count = libusb_get_device_list(context, &devices);
        
        if(count < 0) // error listing devices
        {
            return -1;
        }
        
        libusb_device* device = get_device(devices, count, parser->vid, parser->pid);
        
        
    }else // Some error occurred
    {
        return -1;
    }

    return 0;
}