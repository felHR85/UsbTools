/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include "usbfacade.h"
#include "parser.h"
#include <libusb.h>

const int LIBUSB_INIT_FAILED = -1;
const int NO_DEVICE_PRESENT = -2;
const int INTERFACE_NOT_CLAIMED = -3;

static int open_usb_session(libusb_context** context)
{
    return libusb_init(context);
}

static void close_usb_session(libusb_context** context)
{
    libusb_exit(*context);
}

static uint8_t create_setup_bmrequest(UsbParser* parser)
{
    uint8_t value;
    
    if(parser->host2device == 1)
        value = 0x00;
    else if(parser->device2host == 1)
        value = 0x80;
    
    if(parser->standard_req == 1)
        value += 0x00;
    else if(parser->class_req == 1)
        value += 0x20;
    else if(parser->vendor_req == 1)
        value += 0x40;
    else if(parser->reserved_req == 1)
        value += 0x60;
    
    if(parser->device == 1)
        value += 0x00;
    else if(parser->interface == 1)
        value += 0x01;
    else if(parser->endpoint == 1)
        value += 0x02;
    
    return value;
}



int setup_packet(UsbParser* parser, UsbResponse*** requests)
{
    libusb_context* context;
    
    if(open_usb_session(&context) == 0) // LibUsb session opened
    {
        libusb_set_debug(context, 3);
        
        int vid_integer = (int) strtol(parser->vid, NULL, 16);
        int pid_integer = (int) strtol(parser->pid, NULL, 16);
        
        libusb_device_handle* device_handle = libusb_open_device_with_vid_pid(context, vid_integer, pid_integer);
        if(device_handle != NULL)
        {
            uint8_t bm_request = create_setup_bmrequest(parser);
            if(libusb_claim_interface(device_handle, 0) == 0)
            {
                *requests = malloc(sizeof(256 * sizeof(UsbResponse*)));
                
                for(int i=0;i<=255;i++)
                {
                    int response = libusb_control_transfer(device_handle, bm_request, i, 0x0000, 0x0000, NULL, 0x0000, 500);
                    
                    (*requests)[i] = malloc(sizeof(UsbResponse));
                    (*requests)[i]->response = response;
                    (*requests)[i]->bm_request_type = bm_request;
                    (*requests)[i]->b_request = i;
                    (*requests)[i]->w_value = 0x0000;
                    (*requests)[i]->w_index = 0x0000;
                }
            }else
            {
                libusb_close(device_handle);
                close_usb_session(&context);
                return INTERFACE_NOT_CLAIMED;
            }
            libusb_release_interface(device_handle, 0);
            libusb_close(device_handle);
            close_usb_session(&context);
            return 0;
        }else
        {
            close_usb_session(&context);
            return NO_DEVICE_PRESENT;
        }
        
    }else // Some error occurred
    {
        close_usb_session(&context);
        return LIBUSB_INIT_FAILED;
    }
   
}

int list_usb_devices(UsbDevice*** devices)
{
    libusb_context* context;
    libusb_device** devs;
    
    if(open_usb_session(&context) == 0)
    {
        ssize_t count = libusb_get_device_list(context, &devs);
        *devices = malloc((count + 1) * sizeof(UsbDevice*));
        
        struct libusb_device_descriptor* descriptor;
        
        for(int i=0;i<=count-1;i++)
        {
            if((*devices[i]) != NULL)
            {
                libusb_get_device_descriptor(devs[i], descriptor);
                (*devices[i])->id_product = descriptor->idProduct;
                (*devices[i])->id_vendor = descriptor->idVendor;
            }
        }
        
        devices[count] = NULL;
        libusb_free_device_list(devs, 1);
        close_usb_session(&context);
        return (int) count;
        
    }else
    {
        close_usb_session(&context);
        return -1;
    }
    return 0;
}

void free_usb_devices(UsbDevice*** devices)
{
    if(*devices != NULL)
        free(*devices);
}