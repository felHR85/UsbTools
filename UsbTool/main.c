/*
Created by felhr (felhr85@gmail.com)
*/

#include <stdio.h>
#include "parser.h"
#include "error.h"
#include "testparser.h"
#include "help.h"
#include "logprinter.h"
#include "usbfacade.h"

int main(int argc, const char * argv[])
{
    UsbParser* parser;
    int status = parse_commands(&parser, argc, argv);
    
    if(status == OK_PARAMS) // parsed valid data
    {
        if(test_selected(parser)) // test parser
        {
            print_parsed_data(parser);

        }else if(help_selected(parser)) // show help
        {
            print_help();
        }else if(list_selected(parser)) // list usb devices
        {
            UsbDevice** devices;
            list_usb_devices(&devices);
            print_list_log(devices, 0);
        }else // control requests
        {
            UsbResponse** responses;
            int response = setup_packet(parser, &responses);
            if(response == 0)
                print_responses_log(responses, OK_RESPONSES);
            else if(response == LIBUSB_INIT_FAILED)
                print_usb_error(LIBUSB_INIT_FAILED);
            else if(response == NO_DEVICE_PRESENT)
                print_usb_error(NO_DEVICE_PRESENT);
            else if(response == INTERFACE_NOT_CLAIMED)
                print_usb_error(INTERFACE_NOT_CLAIMED);
        }
    }else
    {
        print_parsing_error(status);
    }
    
    return 0;
}

