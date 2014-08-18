/*
 Created by felhr (felhr85@gmail.com)
 */

#include <stdio.h>
#include "parser.h"

int test_selected(UsbParser* parser)
{
    return parser->test_parser;
}

void print_parsed_data(UsbParser* parser)
{
    if(parser->host2device == 1)
        printf("Direction: Host to Device\n");
    else if(parser->device2host == 1)
        printf("Direction: Device to Host\n");
    
    
    if(parser->standard_req == 1)
        printf("Type: Standard Request\n");
    else if(parser->class_req == 1)
        printf("Type: Class Request\n");
    else if(parser->vendor_req == 1)
        printf("Type: Vendor Request\n");
    else if(parser->reserved_req == 1)
        printf("Type: Reserved Request\n");
    
    if(parser->device == 1)
        printf("Recipient: Device\n");
    else if(parser->endpoint == 1)
        printf("Recipient: Endpoint\n");
    else if(parser->interface == 1)
        printf("Recipient: Interface\n");
    
    if(parser->vid != NULL)
    {
        while(*(parser->vid) != '\0')
        {
            printf("Vid:  %c \n", *(parser->vid));
            parser->vid++;
        }
    }
    
    if(parser->pid != NULL)
    {
        while(*(parser->pid) != '\0')
        {
            printf("Pid:  %c \n", *(parser->pid));
            parser->pid++;
        }
    }
    
    if(parser->list == 1)
        printf("List Usb Devices");
    
    if(parser->help == 1)
        printf("Show Help");
}