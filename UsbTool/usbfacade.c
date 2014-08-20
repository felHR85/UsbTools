/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include "usbfacade.h"
#include "parser.h"
#include <libusb.h>

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
        int vid_integer = (int) strtol(parser->vid, NULL, 16);
        int pid_integer = (int) strtol(parser->pid, NULL, 16);
        
        libusb_device_handle* device_handle = libusb_open_device_with_vid_pid(context, vid_integer, pid_integer);
        if(device_handle != NULL)
        {
            uint8_t bm_request = create_setup_bmrequest(parser);
            if(libusb_claim_interface(device_handle, 0))
            {
                *requests = malloc(sizeof(256 * sizeof(UsbResponse*)));
                
                for(uint8_t i=0;i<=255;i++)
                {
                    int response = libusb_control_transfer(device_handle, bm_request, i, 0x0000, 0x0000, NULL, 0x0000, 500);
                    
                    (*requests[i])->response = response;
                    (*requests[i])->bm_request_type = bm_request;
                    (*requests[i])->b_request = i;
                    (*requests[i])->w_value = 0x0000;
                    (*requests[i])->w_index = 0x0000;
                }
            }else
            {
                libusb_close(device_handle);
                close_usb_session(&context);
                return -1;
            }
            
            libusb_close(device_handle);
            close_usb_session(&context);
            return 0;
        }else
        {
            close_usb_session(&context);
            return -1;
        }
        
    }else // Some error occurred
    {
        close_usb_session(&context);
        return -1;
    }
   
}